#ifndef SINKVITA49_BASE_IMPL_BASE_H
#define SINKVITA49_BASE_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Component.h>
#include <ossie/ThreadedComponent.h>

#include <bulkio/bulkio.h>
#include "struct_props.h"

class SinkVITA49_base : public Component, protected ThreadedComponent
{
    public:
        SinkVITA49_base(const char *uuid, const char *label);
        ~SinkVITA49_base();

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void loadProperties();

    protected:
        // Member variables exposed as properties
        /// Property: network_settings
        network_settings_struct network_settings;
        /// Property: VITA49Encapsulation
        VITA49Encapsulation_struct VITA49Encapsulation;
        /// Property: VITA49IFDataPacket
        VITA49IFDataPacket_struct VITA49IFDataPacket;
        /// Property: VITA49IFContextPacket
        VITA49IFContextPacket_struct VITA49IFContextPacket;
        /// Property: advanced_configuration
        advanced_configuration_struct advanced_configuration;
        /// Property: connection_status
        connection_status_struct connection_status;

        // Ports
        /// Port: dataShort_in
        bulkio::InShortPort *dataShort_in;
        /// Port: dataFloat_in
        bulkio::InFloatPort *dataFloat_in;
        /// Port: dataChar_in
        bulkio::InCharPort *dataChar_in;
        /// Port: dataDouble_in
        bulkio::InDoublePort *dataDouble_in;
        /// Port: dataOctet_in
        bulkio::InOctetPort *dataOctet_in;
        /// Port: dataUshort_in
        bulkio::InUShortPort *dataUshort_in;
        /// Port: dataVITA49_out
        bulkio::OutVITA49Port *dataVITA49_out;

    private:
};
#endif // SINKVITA49_BASE_IMPL_BASE_H
