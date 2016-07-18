#!/usr/bin/env python
#
#
# AUTO-GENERATED
#
# Source: NDRFEI.spd.xml
from ossie.device import start_device
import logging
import CyberRadioDriver as crd
import CyberRadioDriver.configKeys as cfgKeys
from ossie.utils import sb
import socket
import array


from NDRFEI_base import *
from frontend.fe_types import frontend_tuner_allocation

class NDRFEI_i(NDRFEI_base):
    """<DESCRIPTION GOES HERE>"""
    
    def constructor(self):
        """
        This is called by the framework immediately after your device registers with the system.
        
        In general, you should add customization here and not in the __init__ constructor.  If you have 
        a custom port implementation you can override the specific implementation here with a statement
        similar to the following:
          self.some_port = MyPortImplementation()

        For a tuner device, the structure frontend_tuner_status needs to match the number
        of tuners that this device controls and what kind of device it is.
        The options for devices are: TX, RX, RX_DIGITIZER, CHANNELIZER, DDC, RC_DIGITIZER_CHANNELIZER
     
        For example, if this device has 5 physical
        tuners, each an RX_DIGITIZER, then the code in the construct function should look like this:

        self.setNumChannels(5, "RX_DIGITIZER");
     
        The incoming request for tuning contains a string describing the requested tuner
        type. The string for the request must match the string in the tuner status.
        """
        # TODO add customization here.
        # Redefine the control port
        self.port_DigitalTuner_in = frontend.InDigitalTunerPort("DigitalTuner_in",self)
        
        # get the model number for this device and make sure CRD supports it
        radioClass = crd.getRadioClass(self.model)
        if radioClass is None: 
            raise Exception("Unknown radio model %t. Available radio types: %s"%(self.model,crd.getSupportedRadios()))
        
        # connect to the radio
        self.radio = crd.getRadioObject(self.model)
        self.radio.connect("tcp", self.host_or_dev, self.port_or_baud)
        
        if self.radio.isConnected():
            print self.radio.getVersionInfo()
        else:
            raise Exception("Unable to connect to host : %s:%s"%(self.host_or_dev, self.port_or_baud))
            
        # query the number of DDC, DUC, RX, and TX, along with rates and bandwidths
        self.numRx = self.radio.getNumTuner()
        self.numWbddc = self.radio.getNumWbddc()
        self.ratesWbddc = self.radio.getWbddcRateList()
        self.numNbddc = self.radio.getNumNbddc()
        self.ratesNbddc = self.radio.getNbddcRateList()
        
        self.numTx = self.radio.getNumTransmitters()
        self.numDuc = self.radio.getNumWbduc()    
        self.ratesDuc = self.radio.getWbducRateList()
        
        self.numDdc = self.numWbddc + self.numNbddc
        self.numChannels = self.numWbddc + self.numNbddc + self.numDuc
        
        self.bwfactor = 0.8
        
        # get the frequency range and step
        self.freqRange = self.radio.getTunerFrequencyRange()
        self.freqRes = self.radio.getTunerFrequencyRes()

        self.txfreqRange = self.radio.getTransmitterFrequencyRange()
        self.txfreqRes = self.radio.getTransmitterFrequencyRes()
        
        # set the number of channels         
        self.setNumChannels(self.numChannels,"RX_DIGITIZER")
                
        # set the TX channels
        for i in range(self.numChannels-self.numDuc, self.numChannels):
            self.frontend_tuner_status[i].tuner_type="TX"
        
        # init the frequency
        for i in range(0, self.numChannels):
            self.frontend_tuner_status[i].center_frequency=1000e6        
        
        # set the reference mode
        self.radio.setReferenceMode(self.reference)
        
        # set the cal signal
        self.addPropertyChangeListener('calf', self.setCALF)
        self.radio.setCalibrationFrequency(self.calf)
        
        # command handler
        self.addPropertyChangeListener('cmd', self.setCMD)
        
        # attenuation
        ## TODO: add attenuation control      
        
        # create lists to hold the vita49 and dataconverter objects
        self.SV49=[]
        self.DC=[]
        self.RPorts=[]
        self.Tx_SV49=[]
        self.Tx_DC=[]
        self.TPorts=[]
        self.RSink=[]
        self.sock=[]
        self.sris=[]
        
        # get a copy of the full unit configuration
        self.confdict=self.radio.getConfiguration()
        
        # set tuner allocation
        print self.frontend_tuner_allocation
        self.frontend_tuner_allocation.center_frequency=1000e6
        
        # set of SIP/DIP tables
        self.num10gbe = self.radio.getNumGigE()
        self.numDIPEntries = self.radio.getNumGigEDipEntries()
        
        for i in range(0,self.num10gbe):
            # set the source IP as .1 address corresponding to eth address
            if i == 0:                
                ethconf=crd.getInterfaceAddresses(self.tenGbe1)
            else:
                ethconf=crd.getInterfaceAddresses(self.tenGbe2)
            
            # set source IP address to x.x.x.1
            ipparts = ethconf[1].split('.')
            self.confdict[cfgKeys.CONFIG_IP][i+1][cfgKeys.IP_SOURCE]=ipparts[0]+'.'+ipparts[1]+'.'+ipparts[2]+'.1'
            
            # set the destination IP table
            for j in range(0,self.numDIPEntries):
                # set the destinations in sequence
                self.confdict[cfgKeys.CONFIG_IP][i+1][cfgKeys.IP_DEST][j][cfgKeys.GIGE_DEST_PORT]=41000+i*500+j
                self.confdict[cfgKeys.CONFIG_IP][i+1][cfgKeys.IP_DEST][j][cfgKeys.GIGE_SOURCE_PORT]=31000+i*500+j
                self.confdict[cfgKeys.CONFIG_IP][i+1][cfgKeys.IP_DEST][j][cfgKeys.GIGE_MAC_ADDR]=ethconf[0]
                self.confdict[cfgKeys.CONFIG_IP][i+1][cfgKeys.IP_DEST][j][cfgKeys.GIGE_IP_ADDR]=ethconf[1]
        
        # write back the ip configuration
        self.radio.setConfiguration(self.confdict)
        
    def process(self):
        """
        Basic functionality:
        
            The process method should process a single "chunk" of data and then return. This method
            will be called from the processing thread again, and again, and again until it returns
            FINISH or stop() is called on the device.  If no work is performed, then return NOOP.
            
        StreamSRI:
            To create a StreamSRI object, use the following code (this generates a normalized SRI that does not flush the queue when full):
                self.sri = bulkio.sri.create(self.stream_id)

        PrecisionUTCTime:
            To create a PrecisionUTCTime object, use the following code:
                tstamp = bulkio.timestamp.now() 
  
        Ports:

            Each port instance is accessed through members of the following form: self.port_<PORT NAME>
            
            Data is obtained in the process function through the getPacket call (BULKIO only) on a
            provides port member instance. The optional argument is a timeout value, in seconds.
            A zero value is non-blocking, while a negative value is blocking. Constants have been
            defined for these values, bulkio.const.BLOCKING and bulkio.const.NON_BLOCKING. If no
            timeout is given, it defaults to non-blocking.
            
            The return value is a named tuple with the following fields:
                - dataBuffer
                - T
                - EOS
                - streamID
                - SRI
                - sriChanged
                - inputQueueFlushed
            If no data is available due to a timeout, all fields are None.

            To send data, call the appropriate function in the port directly. In the case of BULKIO,
            convenience functions have been added in the port classes that aid in output.
            
            Interactions with non-BULKIO ports are left up to the device developer's discretion.
            
        Messages:
    
            To receive a message, you need (1) an input port of type MessageEvent, (2) a message prototype described
            as a structure property of kind message, (3) a callback to service the message, and (4) to register the callback
            with the input port.
        
            Assuming a property of type message is declared called "my_msg", an input port called "msg_input" is declared of
            type MessageEvent, create the following code:
        
            def msg_callback(self, msg_id, msg_value):
                print msg_id, msg_value
        
            Register the message callback onto the input port with the following form:
            self.port_input.registerMessage("my_msg", NDRFEI_i.MyMsg, self.msg_callback)
        
            To send a message, you need to (1) create a message structure, and (2) send the message over the port.
        
            Assuming a property of type message is declared called "my_msg", an output port called "msg_output" is declared of
            type MessageEvent, create the following code:
        
            msg_out = NDRFEI_i.MyMsg()
            this.port_msg_output.sendMessage(msg_out)

    Accessing the Application and Domain Manager:
    
        Both the Application hosting this Component and the Domain Manager hosting
        the Application are available to the Component.
        
        To access the Domain Manager:
            dommgr = self.getDomainManager().getRef();
        To access the Application:
            app = self.getApplication().getRef();
        Properties:
        
            Properties are accessed directly as member variables. If the property name is baudRate,
            then accessing it (for reading or writing) is achieved in the following way: self.baudRate.

            To implement a change callback notification for a property, create a callback function with the following form:

            def mycallback(self, id, old_value, new_value):
                pass

            where id is the property id, old_value is the previous value, and new_value is the updated value.
            
            The callback is then registered on the component as:
            self.addPropertyChangeListener('baudRate', self.mycallback)
            
        Allocation:
            
            Allocation callbacks are available to customize a Device's response to an allocation request. 
            Callback allocation/deallocation functions are registered using the setAllocationImpl function,
            usually in the initialize() function
            For example, allocation property "my_alloc" can be registered with allocation function 
            my_alloc_fn and deallocation function my_dealloc_fn as follows:
            
            self.setAllocationImpl("my_alloc", self.my_alloc_fn, self.my_dealloc_fn)
            
            def my_alloc_fn(self, value):
                # perform logic
                return True # successful allocation
            
            def my_dealloc_fn(self, value):
                # perform logic
                pass
            
        Example:
        
            # This example assumes that the device has two ports:
            #   - A provides (input) port of type bulkio.InShortPort called dataShort_in
            #   - A uses (output) port of type bulkio.OutFloatPort called dataFloat_out
            # The mapping between the port and the class if found in the device
            # base class.
            # This example also makes use of the following Properties:
            #   - A float value called amplitude
            #   - A boolean called increaseAmplitude
            
            packet = self.port_dataShort_in.getPacket()
            
            if packet.dataBuffer is None:
                return NOOP
                
            outData = range(len(packet.dataBuffer))
            for i in range(len(packet.dataBuffer)):
                if self.increaseAmplitude:
                    outData[i] = float(packet.dataBuffer[i]) * self.amplitude
                else:
                    outData[i] = float(packet.dataBuffer[i])
                
            # NOTE: You must make at least one valid pushSRI call
            if packet.sriChanged:
                self.port_dataFloat_out.pushSRI(packet.SRI);

            self.port_dataFloat_out.pushPacket(outData, packet.T, packet.EOS, packet.streamID)
            return NORMAL
            
        """
        
        # got through each RX connection and check for data        
        for tuner_id in range(0,len(self.SV49)):
            # make sure enabled before continuing
            if self.frontend_tuner_status[tuner_id].enabled == False:
                continue
                        
            #TODO: Connect receive data to out port
#             # receive some data
#             data = array.array('f',range(8192))
#             bytes_rxed = 0
#             while (len(data) > 0) and (bytes_rxed<65536):
#                 try:
#                     data = self.sock[tuner_id].recv(8192)
#                 except socket.error:
#                     data=[]
#                     continue            
#                 bytes_rxed = bytes_rxed + len(data)
#                                   
#             print "Data rxed = %d %d %s"%(tuner_id,bytes_rxed,self.frontend_tuner_status[tuner_id].allocation_id_csv)
#                         
#             # send out to each connection with stream_id
#             datab = range(1024)
#             tstamp = bulkio.timestamp.now()
#             self.sri = bulkio.sri.create(self.frontend_tuner_status[tuner_id].allocation_id_csv)
#             self.sri.mode=1
#             
#             try:
#                 self.port_dataFloat_out.pushSRI(self.sri)
#                 self.port_dataFloat_out.pushPacket(data,tstamp,False,self.frontend_tuner_status[tuner_id].allocation_id_csv)
#             except:
#                 print "Push exception!"
#                 print self.frontend_tuner_status[tuner_id].allocation_id_csv
#                 continue

        for tuner_id in range(0,len(self.Tx_SV49)):
            # make sure enabled before continuing
            tx_id = tuner_id + self.numDdc 
            if self.frontend_tuner_status[tx_id].enabled == False:
                continue

            #TODO: Connect transmit data to data converter
                    
        return NORMAL

    '''
    *************************************************************
    Functions supporting tuning allocation
    *************************************************************'''
    def deviceEnable(self, fts, tuner_id):
        '''
        ************************************************************
        modify fts, which corresponds to self.frontend_tuner_status[tuner_id]
        Make sure to set the 'enabled' member of fts to indicate that tuner as enabled
        ************************************************************'''       
        
        if fts.tuner_type == "RX_DIGITIZER":           
            # Note: Radio dataflow is already enabled 
            
            # start the vita49 source blocks
#             self.SV49[tuner_id].start()
#             self.DC[tuner_id].start()
#             self.RSink[tuner_id].start()
            print "deviceEnable(): Enable the given tuner  *********"
            
        else:
            # start the vita49 sink blocks
#             tx_id = tuner_id - self.numDdc
#             self.Tx_SV49[tx_id].start()
#             self.Tx_DC[tx_id].start()      
            print "deviceEnable(): Enable the given transmitter  *********"          

        # set the enabled flag
        fts.enabled = True
        self.frontend_tuner_allocation.allocation_id = self.tuner_allocation_ids[tuner_id].control_allocation_id
                                 
        return

    def deviceDisable(self,fts, tuner_id):
        '''
        ************************************************************
        modify fts, which corresponds to self.frontend_tuner_status[tuner_id]
        Make sure to reset the 'enabled' member of fts to indicate that tuner as disabled
        ************************************************************'''
        
        if fts.tuner_type == "RX_DIGITIZER":                      
#             # stop the vita49 source block
#             self.SV49[tuner_id].stop()
#             self.DC[tuner_id].stop()
#             self.RSink[tuner_id].stop()
            print "deviceDisable(): Disable the given tuner  *********"

        else:
#             # stop the vita49 sink block
#             tx_id = tuner_id - self.numDdc
#             self.Tx_SV49[tx_id].stop()
#             self.Tx_DC[tx_id].stop()
            print "deviceDisable(): Disable the given transmitter  *********"
             
        # clear the enabled flag
        fts.enabled = False
            
        return

    def deviceSetTuning(self,request, fts, tuner_id):
        '''
        ************************************************************
        modify fts, which corresponds to self.frontend_tuner_status[tuner_id]
        
        The bandwidth, center frequency, and sampling rate that the hardware was actually tuned
        to needs to populate fts (to make sure that it meets the tolerance requirement. For example,
        if the tuned values match the requested values, the code would look like this:
        
        fts.bandwidth = request.bandwidth
        fts.center_frequency = request.center_frequency
        fts.sample_rate = request.sample_rate
        
        return True if the tuning succeeded, and False if it failed
        ************************************************************'''
        print "deviceSetTuning(): Evaluate whether or not a tuner is added  *********"
        print "tuner_id=%d"%(tuner_id)
        
        if fts.tuner_type == "RX_DIGITIZER": #Receiver configuration
            # check for valid frequency
            if (self.freqRange[0] > request.center_frequency) or (self.freqRange[1] < request.center_frequency):
                print "Frequency out of range : %s"%(request.center_frequency)
                return False
                
            # check for valid bandwidth and tolerance
            #FIXME: CRD needs to return a bandwidth set
            if request.bandwidth > 0:
                if (self.ratesWbddc[-1]*self.bwfactor > request.bandwidth*(1+request.bandwidth_tolerance/100)) or \
                    (self.ratesWbddc[0]*self.bwfactor < request.bandwidth*(1-request.bandwidth_tolerance/100)):
                    print "Bandwidth out of range : %s"%(request.bandwidth)
                    return False
                
                # find closest bandwidth
                for index, rate in enumerate(self.ratesWbddc):
                    if rate*self.bwfactor >= request.bandwidth:
                        bandwidth = rate*self.bwfactor
                        samplerate = rate
                        filter_index = index
                    else:    
                        break
                    
            # check for valid sample rate
            elif request.sample_rate > 0:
                if (self.ratesWbddc[-1] > request.sample_rate*(1+request.sample_rate_tolerance/100)) or \
                    (self.ratesWbddc[0] < request.sample_rate*(1-request.sample_rate_tolerance/100)):
                    print "Samplerate out of range : %s"%(request.sample_rate)
                    return False
                
                #find closest sample rate
                for index, rate in enumerate(self.ratesWbddc):
                    if rate >= request.sample_rate:
                        bandwidth = rate*self.bwfactor
                        samplerate = rate
                        filter_index = index
                    else:    
                        break
                                
            else: #default to narrowest rate
                #FIXME: assume bandwidth is 80% of sample rate
                bandwidth = round(self.bwfactor*self.ratesWbddc[-1])
                samplerate = self.ratesWbddc[-1]                 
                filter_index = len(self.ratesWbddc)-1
                    
            
            # TODO: need RF frequency resource contention for nbddc, i.e. RF set on first nbddc then offset on second    
            
            # TODO: check availability of a DDC
            
            # calculate the coarse and fine tuning
            coarse = round(request.center_frequency/self.freqRes)
            coarse = coarse*self.freqRes
            fine = request.center_frequency-coarse            
          
            # program tuner
            confdict={cfgKeys.CONFIG_TUNER: {tuner_id+1:{cfgKeys.TUNER_FREQUENCY: coarse}}}
            self._log.debug("confdict : %s"%(confdict))
            self.radio.setConfiguration(confdict)
                        
            # program DDC
            # NOTE:for WBDDC there is no fine tuning
            ddc_confdict=self.confdict[cfgKeys.CONFIG_DDC][cfgKeys.CONFIG_WBDDC][tuner_id+1]
            ddc_confdict[cfgKeys.ENABLE]=1
            ddc_confdict[cfgKeys.DDC_DATA_PORT]=1 #FIXME: assign ports
            ddc_confdict[cfgKeys.DDC_RATE_INDEX]=filter_index
            ddc_confdict[cfgKeys.DDC_STREAM_ID]=41000+tuner_id
            ddc_confdict[cfgKeys.DDC_VITA_ENABLE]=1
            ddc_confdict[cfgKeys.DDC_UDP_DESTINATION]=tuner_id
            confdict={cfgKeys.CONFIG_DDC: { cfgKeys.CONFIG_WBDDC: {tuner_id+1:ddc_confdict}}}
            self._log.debug("confdict : %s"%(confdict))
            self.radio.setConfiguration(confdict)
            
            # set the frontend tuner status        
            fts.bandwidth = bandwidth
            fts.center_frequency = coarse
            fts.sample_rate = samplerate
            fts.port = 41000+tuner_id
            fts.interface = self.tenGbe1
            ethconf=crd.getInterfaceAddresses(fts.interface)
            fts.ip_address = ethconf[1]
            
#             # create new Sourcevita49, dataconverter, and sink if needed and connect them
#             if len(self.SV49) < (tuner_id+1):
#                 # create modules
#                 self.SV49.append(sb.launch("rh.SourceVITA49",execparams={"DEBUG_LEVEL":0}))
#                 self.DC.append(sb.launch("rh.DataConverter"))
#                 self.RSink.append(sb.launch("sink",execparams={"DEBUG_LEVEL":0,"lb_port":5000+tuner_id}))
#                             
#                 #create loopback port                
#                 #self.RPorts.append(bulkio.InShortPort("dataShortLB_in", maxsize=self.DEFAULT_QUEUE_SIZE))
#        
#                 # connect the modules (the connection knows the data type so it is unambiguous)
#                 self.SV49[tuner_id].connect(self.DC[tuner_id],usesPortName="dataShort_out")
#                 self.DC[tuner_id].connect(self.RSink[tuner_id],usesPortName="dataFloat_out")
#                 
#                 #connect loopback port
#                 #self.SV49[tuner_id].connect(self.Rports[tuner_id],usesPortName="dataShort_out")               
#                 
#                 # init sink so it has pointer to multi-out Port
#                 #self.DC[tuner_id].connect(self.port_loopbackFloat,usesPortName="dataFloat_out")
#                 
#                 # create a non-blocking socket to connect
#                 self.sock.append(socket.socket(socket.AF_INET,socket.SOCK_DGRAM))
#                 self.sock[tuner_id].setblocking(0)
#                 self.sock[tuner_id].bind(("127.0.0.1",5000+tuner_id))
#                  
#                 # create an sri for this stream
#                 self.sris.append(bulkio.sri.create(request.allocation_id))
#                         
#             # configure the SourceVita49 module
#             self.SV49[tuner_id].attachment_override.enabled=True
#             #FIXME - need to set 10gbe interface load balanced
#             self.SV49[tuner_id].interface="eth0"
#             self.SV49[tuner_id].interface=fts.interface
#             self.SV49[tuner_id].attachment_override.ip_address=fts.ip_address
#             self.SV49[tuner_id].attachment_override.port=fts.port
#             self.SV49[tuner_id].VITA49Processing_override.enable=True
#             self.SV49[tuner_id].VITA49Processing_override.VRL_frames=True
#             self.SV49[tuner_id].VITA49Processing_override.vector_size=1024
#             self.SV49[tuner_id].VITA49Processing_override.vita49_packet_size=4136        
#             self.SV49[tuner_id].VITA49Processing_override.byte_swap=True
            
            # refresh the configuration
            self.confdict=self.radio.getConfiguration()
            
            return True
        
        else: #Transmitter configuration
            # check for valid frequency
            if (self.txfreqRange[0] > request.center_frequency) or (self.txfreqRange[1] < request.center_frequency):
                print "Frequency out of range : %s"%(request.center_frequency)
                return False
                
            # check for valid bandwidth and tolerance
            #TODO: Is bandwidth irrelevant for DUC since set by source?
            if request.bandwidth > 0:
                if (self.ratesDuc[-1]*self.bwfactor > request.bandwidth*(1+request.bandwidth_tolerance/100)) or \
                    (self.ratesDuc[0]*self.bwfactor < request.bandwidth*(1-request.bandwidth_tolerance/100)):
                    print "Bandwidth out of range : %s"%(request.bandwidth)
                    return False
                 
                # find closest bandwidth
                for index, rate in enumerate(self.ratesDuc):
                    if rate*self.bwfactor >= request.bandwidth:
                        bandwidth = rate*self.bwfactor
                        samplerate = rate
                        filter_index = index
                    else:    
                        break
 
            elif request.sample_rate > 0:
                if (self.ratesDuc[-1] > request.sample_rate*(1+request.sample_rate_tolerance/100)) or \
                    (self.ratesDuc[0] < request.sample_rate*(1-request.sample_rate_tolerance/100)):
                    print "Samplerate out of range : %s"%(request.sample_rate)
                    return False
                 
                #find closest sample rate
                for index, rate in enumerate(self.ratesDuc):
                    if rate >= request.sample_rate:
                        bandwidth = rate*self.bwfactor
                        samplerate = rate
                        filter_index = index
                    else:    
                        break
                                 
            else: #default to narrowest rate
                #FIXME: assume bandwidth is 80% of sample rate
                bandwidth = round(self.bwfactor*self.ratesDuc[-1])
                samplerate = self.ratesDuc[-1]                 
                filter_index = len(self.ratesDuc)-1
            
            # TODO: need RF frequency resource contention for duc    
            
            # TODO: check availability of a DUC
            
            # calculate the coarse and fine tuning
            coarse = round(request.center_frequency/self.txfreqRes)
            coarse = coarse*self.txfreqRes
            fine = request.center_frequency-coarse  
         
            # program tuner
            tx_id = tuner_id - self.numDdc            
            confdict={cfgKeys.CONFIG_TX: {tx_id+1:{cfgKeys.TX_FREQUENCY: coarse}}}
            self._log.debug("confdict : %s"%(confdict))
            self.radio.setConfiguration(confdict)
                        
            # program DUC
            # FIXME: set DUC fine tuning
            duc_confdict=self.confdict[cfgKeys.CONFIG_DUC][cfgKeys.CONFIG_WBDUC][tx_id+1]
            duc_confdict[cfgKeys.DUC_RATE_INDEX]=filter_index
            duc_confdict[cfgKeys.DUC_TX_CHANNELS]=tx_id+1
            duc_confdict[cfgKeys.DUC_STREAM_ID]=42000+tx_id
            confdict={cfgKeys.CONFIG_DUC: { cfgKeys.CONFIG_WBDUC: {tx_id+1:duc_confdict}}}
            self._log.debug("confdict : %s"%(confdict))

            #FIXME: CRD is currently broken so have to compose duc command manually   
            #self.radio.setConfiguration(confdict)
            new_value = "duc %d, 1, %d, 0, %d, %d, 0, %d"%(tx_id+1,fine,filter_index,tx_id+1,42000+tx_id)
            self.rsp = self.radio.sendCommand("%s\n"%(new_value))
            self.cmd = new_value;
             
            # set the frontend tuner status        
            fts.bandwidth = bandwidth
            fts.center_frequency = coarse
            fts.sample_rate = samplerate
            fts.port = 42000+tx_id
            fts.interface = self.tenGbe1
            ethconf=crd.getInterfaceAddresses(fts.interface)
            ipparts = ethconf[1].split('.')              
            fts.ip_address=ipparts[0]+'.'+ipparts[1]+'.'+ipparts[2]+'.1'
                      
#             # create new Sinkvita49 and dataconverter if needed and connect them
#             # note: the transmitters at the end of the receivers in the list so the first
#             # transmitter is at id numDDc+1. This code instantiates the components only as needed. 
#             if len(self.Tx_SV49) < (tx_id+1):
#                 self.Tx_SV49.append(sb.launch("rh.SinkVITA49"))
#                 self.Tx_DC.append(sb.launch("rh.DataConverter"))
#                 self.Tx_DC[tx_id].connect(self.Tx_SV49[tx_id],usesPortName="dataShort_out")          
#             
#             # configure the SinkVita49 module 
#             self.Tx_SV49[tx_id].network_settings.enabled=True
#             self.Tx_SV49[tx_id].network_settings.port=fts.port
#             self.Tx_SV49[tx_id].network_settings.ip_address=fts.ip_address
#             #FIXME - need to set 10gbe interface load balanced
#             self.Tx_SV49[tx_id].network_settings.interface=fts.interface
#             self.Tx_SV49[tx_id].network_settings.use_udp_protocol=True
# 
#             self.Tx_SV49[tx_id].VITA49Encapsulation.enable_vrl_frames=True
#             self.Tx_SV49[tx_id].VITA49IFContextPacket.enable2=False
#             self.Tx_SV49[tx_id].advanced_configuration.force_transmit=True
#             self.Tx_SV49[tx_id].advanced_configuration.max_payload_size=4096        

            # refresh the configuration
            self.confdict=self.radio.getConfiguration()
                        
            return True

    def deviceDeleteTuning(self, fts, tuner_id):
        '''
        ************************************************************
        modify fts, which corresponds to self.frontend_tuner_status[tuner_id]
        return True if the tune deletion succeeded, and False if it failed
        ************************************************************'''
        print "deviceDeleteTuning(): Deallocate an allocated tuner  *********"
        print "tuner_id=%d"%(tuner_id)

        #TODO: should stop radio data flow on deallocate
                        
        return True

    '''
    *************************************************************
    Functions servicing the top level device properties
    *************************************************************'''
    def setCALF(self, id, old_value, new_value):
        # the CRD checks validity and returns true if successful        
        if self.radio.setCalibrationFrequency(new_value):
            self.calf = new_value;

    def setCMD(self, id, old_value, new_value):
        # send an arbitrary command and save the response string    
        self.rsp = self.radio.sendCommand("%s\n"%(new_value))
        self.cmd = new_value;
                
    '''
    *************************************************************
    Functions servicing the tuner control port
    *************************************************************'''
    def getTunerType(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].tuner_type

    def getTunerDeviceControl(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        if self.getControlAllocationId(idx) == allocation_id:
            return True
        return False

    def getTunerGroupId(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].group_id

    def getTunerRfFlowId(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].rf_flow_id


    def setTunerCenterFrequency(self,allocation_id, freq):
        self._log.debug("Frequency request : %d"%(freq))
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
#        if allocation_id != self.getControlAllocationId(idx):
#            raise FRONTEND.FrontendException(("ID "+str(allocation_id)+" does not have authorization to modify the tuner"))
        if freq<0: raise FRONTEND.BadParameterException()

        # set hardware to new value. Raise an exception if it's not possible        
        if self.frontend_tuner_status[idx].tuner_type == "RX_DIGITIZER": 
            confdict={cfgKeys.CONFIG_TUNER: {idx+1:{cfgKeys.TUNER_FREQUENCY: freq}}}
        else:
            tx_id = idx - self.numDdc            
            confdict={cfgKeys.CONFIG_TX: {tx_id+1:{cfgKeys.TX_FREQUENCY: freq}}}                    
        
        self._log.debug("confdict : %s"%(confdict))
        self.radio.setConfiguration(confdict)
        self.frontend_tuner_status[idx].center_frequency = freq        

    def getTunerCenterFrequency(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        #cep test
        self._log.debug("Frequency request : %d"%(idx))
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].center_frequency

    def setTunerBandwidth(self,allocation_id, bw):
        # retrive index and check control id
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
#        if allocation_id != self.getControlAllocationId(idx):
#            raise FRONTEND.FrontendException(("ID "+str(allocation_id)+" does not have authorization to modify the tuner"))
        
        # set hardware to new value. Raise an exception if it's not possible        
        request = frontend.frontend_tuner_allocation()
        request.bandwidth = bw
        
        if self.frontend_tuner_status[idx].tuner_type == "RX_DIGITIZER":        
            # check for valid bandwidth
            if bw<0: raise FRONTEND.BadParameterException()
            if (self.ratesWbddc[-1]*self.bwfactor > request.bandwidth*(1+request.bandwidth_tolerance/100)) or \
                (self.ratesWbddc[0]*self.bwfactor < request.bandwidth*(1-request.bandwidth_tolerance/100)):
                raise FRONTEND.BadParameterException("Bandwidth out of range : %s"%(request.bandwidth))
            
            # find closest bandwidth
            for index, rate in enumerate(self.ratesWbddc):
                if rate*self.bwfactor >= request.bandwidth:
                    bandwidth = rate*self.bwfactor
                    samplerate = rate
                    filter_index = index
                else:    
                    break
                
            # write to hardware
            ddc_confdict=self.confdict[cfgKeys.CONFIG_DDC][cfgKeys.CONFIG_WBDDC][idx+1]
            ddc_confdict[cfgKeys.DDC_RATE_INDEX]=filter_index
            confdict={cfgKeys.CONFIG_DDC: { cfgKeys.CONFIG_WBDDC: {idx+1:ddc_confdict}}}
            self._log.debug("confdict : %s"%(confdict))
            self.radio.setConfiguration(confdict)          
            
        else:
            # check for valid bandwidth
            if bw<0: raise FRONTEND.BadParameterException()
            if (self.ratesDuc[-1]*self.bwfactor > request.bandwidth*(1+request.bandwidth_tolerance/100)) or \
                (self.ratesDuc[0]*self.bwfactor < request.bandwidth*(1-request.bandwidth_tolerance/100)):
                raise FRONTEND.BadParameterException("Bandwidth out of range : %s"%(request.bandwidth))
            
            # find closest bandwidth
            for index, rate in enumerate(self.ratesDuc):
                if rate*self.bwfactor >= request.bandwidth:
                    bandwidth = rate*self.bwfactor
                    samplerate = rate
                    filter_index = index
                else:    
                    break
                
            # write to hardware
            tx_id = idx - self.numDdc  
            duc_confdict=self.confdict[cfgKeys.CONFIG_DUC][cfgKeys.CONFIG_WBDUC][tx_id+1]
            duc_confdict[cfgKeys.DUC_RATE_INDEX]=filter_index
            confdict={cfgKeys.CONFIG_DUC: { cfgKeys.CONFIG_WBDUC: {tx_id+1:duc_confdict}}}

            #FIXME: CRD is currently broken so have to compose duc command manually   
            #self.radio.setConfiguration(confdict)
            new_value = "duc %d, 1, %d, 0, %d, %d, 0, %d"%(tx_id+1,0,filter_index,tx_id+1,42000+tx_id)
            self.rsp = self.radio.sendCommand("%s\n"%(new_value))
            self.cmd = new_value;          
                                
        # save to tuner structure
        self.frontend_tuner_status[idx].bandwidth = bandwidth
        self.frontend_tuner_status[idx].sample_rate = samplerate
        del request
        
        # refresh the configuration
        self.confdict=self.radio.getConfiguration()
        
                    
    def getTunerBandwidth(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].bandwidth

    def setTunerAgcEnable(self,allocation_id, enable):
        raise FRONTEND.NotSupportedException("setTunerAgcEnable not supported")

    def getTunerAgcEnable(self,allocation_id):
        raise FRONTEND.NotSupportedException("getTunerAgcEnable not supported")

    def setTunerGain(self,allocation_id, gain):        
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        if gain<0: raise FRONTEND.BadParameterException()
                
        # set hardware to new value. Raise an exception if it's not possible        
        if self.frontend_tuner_status[idx].tuner_type == "RX_DIGITIZER": 
            confdict={cfgKeys.CONFIG_TUNER: {idx+1:{cfgKeys.TUNER_ATTENUATION: gain}}}
        else:
            tx_id = idx - self.numDdc            
            confdict={cfgKeys.CONFIG_TX: {tx_id+1:{cfgKeys.TX_ATTENUATION: gain}}}                    
        
        self._log.debug("confdict : %s"%(confdict))
        self.radio.setConfiguration(confdict)
        self.frontend_tuner_status[idx].attenuation = gain

    def getTunerGain(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].attenuation

    def setTunerReferenceSource(self,allocation_id, source):
        raise FRONTEND.NotSupportedException("setTunerReferenceSource not supported")

    def getTunerReferenceSource(self,allocation_id):
        raise FRONTEND.NotSupportedException("getTunerReferenceSource not supported")

    def setTunerEnable(self,allocation_id, enable):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
#        if allocation_id != self.getControlAllocationId(idx):
#            raise FRONTEND.FrontendException(("ID "+str(allocation_id)+" does not have authorization to modify the tuner"))
        # set hardware to new value. Raise an exception if it's not possible
        self.frontend_tuner_status[idx].enabled = enable

    def getTunerEnable(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].enabled

    def setTunerOutputSampleRate(self,allocation_id, sr):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
#        if allocation_id != self.getControlAllocationId(idx):
#            raise FRONTEND.FrontendException(("ID "+str(allocation_id)+" does not have authorization to modify the tuner"))

        # set hardware to new value. Raise an exception if it's not possible        
        request = frontend.frontend_tuner_allocation()
        request.sample_rate = sr

        if self.frontend_tuner_status[idx].tuner_type == "RX_DIGITIZER":     
            # check for valid sample rate
            if sr<0: raise FRONTEND.BadParameterException()
            if (self.ratesWbddc[-1] > request.sample_rate*(1+request.sample_rate_tolerance/100)) or \
                (self.ratesWbddc[0] < request.sample_rate*(1-request.sample_rate_tolerance/100)):
                print "Samplerate out of range : %s"%(request.sample_rate)
                return False
            
            #find closest sample rate
            for index, rate in enumerate(self.ratesWbddc):
                if rate >= request.sample_rate:
                    bandwidth = rate*self.bwfactor
                    samplerate = rate
                    filter_index = index
                else:    
                    break
                
            # write to hardware
            ddc_confdict=self.confdict[cfgKeys.CONFIG_DDC][cfgKeys.CONFIG_WBDDC][idx+1]
            ddc_confdict[cfgKeys.DDC_RATE_INDEX]=filter_index
            confdict={cfgKeys.CONFIG_DDC: { cfgKeys.CONFIG_WBDDC: {idx+1:ddc_confdict}}}
            self._log.debug("confdict : %s"%(confdict))
            self.radio.setConfiguration(confdict)          
                
        else: 
            # check for valid samplerate
            if sr<0: raise FRONTEND.BadParameterException()
            if (self.ratesDuc[-1] > request.sample_rate*(1+request.sample_rate_tolerance/100)) or \
                (self.ratesDuc[0] < request.sample_rate*(1-request.sample_rate_tolerance/100)):
                raise FRONTEND.BadParameterException("Samplerate out of range : %s"%(request.sample_rate))
            
            # find closest samplerate
            for index, rate in enumerate(self.ratesDuc):
                if rate >= request.sample_rate:
                    bandwidth = rate*self.bwfactor
                    samplerate = rate
                    filter_index = index
                else:    
                    break
                
            # write to hardware
            tx_id = idx - self.numDdc  
            duc_confdict=self.confdict[cfgKeys.CONFIG_DUC][cfgKeys.CONFIG_WBDUC][tx_id+1]
            duc_confdict[cfgKeys.DUC_RATE_INDEX]=filter_index
            confdict={cfgKeys.CONFIG_DUC: { cfgKeys.CONFIG_WBDUC: {tx_id+1:duc_confdict}}}
                            
            self._log.debug("confdict : %s"%(confdict))
            #FIXME: CRD is currently broken so have to compose duc command manually   
            #self.radio.setConfiguration(confdict)
            new_value = "duc %d, 1, %d, 0, %d, %d, 0, %d"%(tx_id+1,0,filter_index,tx_id+1,42000+tx_id)
            self.rsp = self.radio.sendCommand("%s\n"%(new_value))
            self.cmd = new_value;                 

        # save to tuner structure
        self.frontend_tuner_status[idx].bandwidth = bandwidth
        self.frontend_tuner_status[idx].sample_rate = samplerate
        del request
        
        # refresh the configuration
        self.confdict=self.radio.getConfiguration()

    def getTunerOutputSampleRate(self,allocation_id):
        idx = self.getTunerMapping(allocation_id)
        if idx < 0: raise FRONTEND.FrontendException("Invalid allocation id")
        return self.frontend_tuner_status[idx].sample_rate

    '''
    *************************************************************
    Functions servicing the RFInfo port(s)
    - port_name is the port over which the call was received
    *************************************************************'''
    def get_rf_flow_id(self,port_name):
        return "none"

    def set_rf_flow_id(self,port_name, id):
        pass

    def get_rfinfo_pkt(self,port_name):
        return frontend.RFInfoPkt()

    def set_rfinfo_pkt(self,port_name, pkt):
        pass

    '''
    *************************************************************
    Functions servicing the GPS port(s)
    - port_name is the port over which the call was received
    *************************************************************'''
    #TODO: Implement GPS readback from radio
    def get_gps_info(self,port_name):
        return frontend.GPSInfo()

    def set_gps_info(self,port_name, gps_info):
        pass

    def get_gps_time_pos(self,port_name):
        return frontend.GpsTimePos()

    def set_gps_time_pos(self,port_name, gps_time_pos):
        pass
      
if __name__ == '__main__':
    logging.getLogger().setLevel(logging.INFO)
    logging.debug("Starting Device")
    start_device(NDRFEI_i)

