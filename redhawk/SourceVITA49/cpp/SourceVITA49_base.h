#ifndef SOURCEVITA49_BASE_IMPL_BASE_H
#define SOURCEVITA49_BASE_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Component.h>
#include <ossie/ThreadedComponent.h>

#include <bulkio/bulkio.h>
#include "struct_props.h"

class SourceVITA49_base : public Component, protected ThreadedComponent
{
    public:
        SourceVITA49_base(const char *uuid, const char *label);
        ~SourceVITA49_base();

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void loadProperties();

    protected:
        // Member variables exposed as properties
        /// Property: interface
        std::string interface;
        /// Property: streamID
        std::string streamID;
        /// Property: attachment_override
        attachment_override_struct attachment_override;
        /// Property: connection_status
        connection_status_struct connection_status;
        /// Property: VITA49Processing_override
        VITA49Processing_override_struct VITA49Processing_override;
        /// Property: advanced_configuration
        advanced_configuration_struct advanced_configuration;

        // Ports
        /// Port: dataVITA49_in
        bulkio::InVITA49Port *dataVITA49_in;
        /// Port: dataChar_out
        bulkio::OutCharPort *dataChar_out;
        /// Port: dataOctet_out
        bulkio::OutOctetPort *dataOctet_out;
        /// Port: dataShort_out
        bulkio::OutShortPort *dataShort_out;
        /// Port: dataUshort_out
        bulkio::OutUShortPort *dataUshort_out;
        /// Port: dataFloat_out
        bulkio::OutFloatPort *dataFloat_out;
        /// Port: dataDouble_out
        bulkio::OutDoublePort *dataDouble_out;

    private:
};
#endif // SOURCEVITA49_BASE_IMPL_BASE_H
