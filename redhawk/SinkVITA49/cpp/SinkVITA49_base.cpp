#include "SinkVITA49_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

SinkVITA49_base::SinkVITA49_base(const char *uuid, const char *label) :
    Component(uuid, label),
    ThreadedComponent()
{
    loadProperties();

    dataShort_in = new bulkio::InShortPort("dataShort_in");
    addPort("dataShort_in", dataShort_in);
    dataFloat_in = new bulkio::InFloatPort("dataFloat_in");
    addPort("dataFloat_in", dataFloat_in);
    dataChar_in = new bulkio::InCharPort("dataChar_in");
    addPort("dataChar_in", dataChar_in);
    dataDouble_in = new bulkio::InDoublePort("dataDouble_in");
    addPort("dataDouble_in", dataDouble_in);
    dataOctet_in = new bulkio::InOctetPort("dataOctet_in");
    addPort("dataOctet_in", dataOctet_in);
    dataUshort_in = new bulkio::InUShortPort("dataUshort_in");
    addPort("dataUshort_in", dataUshort_in);
    dataVITA49_out = new bulkio::OutVITA49Port("dataVITA49_out");
    addPort("dataVITA49_out", dataVITA49_out);
}

SinkVITA49_base::~SinkVITA49_base()
{
    delete dataShort_in;
    dataShort_in = 0;
    delete dataFloat_in;
    dataFloat_in = 0;
    delete dataChar_in;
    dataChar_in = 0;
    delete dataDouble_in;
    dataDouble_in = 0;
    delete dataOctet_in;
    dataOctet_in = 0;
    delete dataUshort_in;
    dataUshort_in = 0;
    delete dataVITA49_out;
    dataVITA49_out = 0;
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void SinkVITA49_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    Component::start();
    ThreadedComponent::startThread();
}

void SinkVITA49_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    Component::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void SinkVITA49_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    Component::releaseObject();
}

void SinkVITA49_base::loadProperties()
{
    addProperty(network_settings,
                network_settings_struct(),
                "network_settings",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(VITA49Encapsulation,
                VITA49Encapsulation_struct(),
                "VITA49Encapsulation",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(VITA49IFDataPacket,
                VITA49IFDataPacket_struct(),
                "VITA49IFDataPacket",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(VITA49IFContextPacket,
                VITA49IFContextPacket_struct(),
                "VITA49IFContextPacket",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(advanced_configuration,
                advanced_configuration_struct(),
                "advanced_configuration",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(connection_status,
                connection_status_struct(),
                "connection_status",
                "",
                "readwrite",
                "",
                "external",
                "property");

}


