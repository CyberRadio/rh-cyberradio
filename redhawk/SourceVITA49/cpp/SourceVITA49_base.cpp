#include "SourceVITA49_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

SourceVITA49_base::SourceVITA49_base(const char *uuid, const char *label) :
    Component(uuid, label),
    ThreadedComponent()
{
    loadProperties();

    dataVITA49_in = new bulkio::InVITA49Port("dataVITA49_in");
    addPort("dataVITA49_in", dataVITA49_in);
    dataChar_out = new bulkio::OutCharPort("dataChar_out");
    addPort("dataChar_out", dataChar_out);
    dataOctet_out = new bulkio::OutOctetPort("dataOctet_out");
    addPort("dataOctet_out", dataOctet_out);
    dataShort_out = new bulkio::OutShortPort("dataShort_out");
    addPort("dataShort_out", dataShort_out);
    dataUshort_out = new bulkio::OutUShortPort("dataUshort_out");
    addPort("dataUshort_out", dataUshort_out);
    dataFloat_out = new bulkio::OutFloatPort("dataFloat_out");
    addPort("dataFloat_out", dataFloat_out);
    dataDouble_out = new bulkio::OutDoublePort("dataDouble_out");
    addPort("dataDouble_out", dataDouble_out);
}

SourceVITA49_base::~SourceVITA49_base()
{
    delete dataVITA49_in;
    dataVITA49_in = 0;
    delete dataChar_out;
    dataChar_out = 0;
    delete dataOctet_out;
    dataOctet_out = 0;
    delete dataShort_out;
    dataShort_out = 0;
    delete dataUshort_out;
    dataUshort_out = 0;
    delete dataFloat_out;
    dataFloat_out = 0;
    delete dataDouble_out;
    dataDouble_out = 0;
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void SourceVITA49_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    Component::start();
    ThreadedComponent::startThread();
}

void SourceVITA49_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    Component::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void SourceVITA49_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    Component::releaseObject();
}

void SourceVITA49_base::loadProperties()
{
    addProperty(interface,
                "eth1",
                "interface",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(streamID,
                "streamID",
                "streamID",
                "streamID",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(attachment_override,
                attachment_override_struct(),
                "attachment_override",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(connection_status,
                connection_status_struct(),
                "connection_status",
                "",
                "readonly",
                "",
                "external",
                "configure");

    addProperty(VITA49Processing_override,
                VITA49Processing_override_struct(),
                "VITA49Processing_override",
                "",
                "readwrite",
                "",
                "external",
                "configure");

    addProperty(advanced_configuration,
                advanced_configuration_struct(),
                "advanced_configuration",
                "",
                "readwrite",
                "",
                "external",
                "configure");

}


