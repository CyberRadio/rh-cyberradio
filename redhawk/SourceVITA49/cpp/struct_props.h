#ifndef STRUCTPROPS_H
#define STRUCTPROPS_H

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

*******************************************************************************************/

#include <ossie/CorbaUtils.h>
#include <CF/cf.h>
#include <ossie/PropertyMap.h>

struct attachment_override_struct {
    attachment_override_struct ()
    {
        enabled = true;
        ip_address = "127.0.0.1";
        vlan = 0;
        port = 41000;
        use_udp_protocol = true;
    };

    static std::string getId() {
        return std::string("attachment_override");
    };

    bool enabled;
    std::string ip_address;
    unsigned short vlan;
    CORBA::Long port;
    bool use_udp_protocol;
};

inline bool operator>>= (const CORBA::Any& a, attachment_override_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("attachment_override::enabled")) {
        if (!(props["attachment_override::enabled"] >>= s.enabled)) return false;
    }
    if (props.contains("attachment_override::ip_address")) {
        if (!(props["attachment_override::ip_address"] >>= s.ip_address)) return false;
    }
    if (props.contains("attachment_override::vlan")) {
        if (!(props["attachment_override::vlan"] >>= s.vlan)) return false;
    }
    if (props.contains("attachment_override::port")) {
        if (!(props["attachment_override::port"] >>= s.port)) return false;
    }
    if (props.contains("transportMethod_override::use_udp_protocol")) {
        if (!(props["transportMethod_override::use_udp_protocol"] >>= s.use_udp_protocol)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const attachment_override_struct& s) {
    redhawk::PropertyMap props;
 
    props["attachment_override::enabled"] = s.enabled;
 
    props["attachment_override::ip_address"] = s.ip_address;
 
    props["attachment_override::vlan"] = s.vlan;
 
    props["attachment_override::port"] = s.port;
 
    props["transportMethod_override::use_udp_protocol"] = s.use_udp_protocol;
    a <<= props;
}

inline bool operator== (const attachment_override_struct& s1, const attachment_override_struct& s2) {
    if (s1.enabled!=s2.enabled)
        return false;
    if (s1.ip_address!=s2.ip_address)
        return false;
    if (s1.vlan!=s2.vlan)
        return false;
    if (s1.port!=s2.port)
        return false;
    if (s1.use_udp_protocol!=s2.use_udp_protocol)
        return false;
    return true;
}

inline bool operator!= (const attachment_override_struct& s1, const attachment_override_struct& s2) {
    return !(s1==s2);
}

struct connection_status_struct {
    connection_status_struct ()
    {
    };

    static std::string getId() {
        return std::string("connection_status");
    };

    bool input_enabled;
    std::string input_ip_address;
    unsigned short input_port;
    unsigned short input_vlan;
    CORBA::ULong packets_missing;
    double input_sample_rate;
    double data_throughput;
    bool waiting_for_context_packet;
};

inline bool operator>>= (const CORBA::Any& a, connection_status_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("connection_status::input_enabled")) {
        if (!(props["connection_status::input_enabled"] >>= s.input_enabled)) return false;
    }
    if (props.contains("connection_status::input_ip_address")) {
        if (!(props["connection_status::input_ip_address"] >>= s.input_ip_address)) return false;
    }
    if (props.contains("connection_status::input_port")) {
        if (!(props["connection_status::input_port"] >>= s.input_port)) return false;
    }
    if (props.contains("connection_status::input_vlan")) {
        if (!(props["connection_status::input_vlan"] >>= s.input_vlan)) return false;
    }
    if (props.contains("connection_status::packets_missing")) {
        if (!(props["connection_status::packets_missing"] >>= s.packets_missing)) return false;
    }
    if (props.contains("connection_status::input_sample_rate")) {
        if (!(props["connection_status::input_sample_rate"] >>= s.input_sample_rate)) return false;
    }
    if (props.contains("connection_status::data_throughput")) {
        if (!(props["connection_status::data_throughput"] >>= s.data_throughput)) return false;
    }
    if (props.contains("connection_status::waiting_for_context_packet")) {
        if (!(props["connection_status::waiting_for_context_packet"] >>= s.waiting_for_context_packet)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const connection_status_struct& s) {
    redhawk::PropertyMap props;
 
    props["connection_status::input_enabled"] = s.input_enabled;
 
    props["connection_status::input_ip_address"] = s.input_ip_address;
 
    props["connection_status::input_port"] = s.input_port;
 
    props["connection_status::input_vlan"] = s.input_vlan;
 
    props["connection_status::packets_missing"] = s.packets_missing;
 
    props["connection_status::input_sample_rate"] = s.input_sample_rate;
 
    props["connection_status::data_throughput"] = s.data_throughput;
 
    props["connection_status::waiting_for_context_packet"] = s.waiting_for_context_packet;
    a <<= props;
}

inline bool operator== (const connection_status_struct& s1, const connection_status_struct& s2) {
    if (s1.input_enabled!=s2.input_enabled)
        return false;
    if (s1.input_ip_address!=s2.input_ip_address)
        return false;
    if (s1.input_port!=s2.input_port)
        return false;
    if (s1.input_vlan!=s2.input_vlan)
        return false;
    if (s1.packets_missing!=s2.packets_missing)
        return false;
    if (s1.input_sample_rate!=s2.input_sample_rate)
        return false;
    if (s1.data_throughput!=s2.data_throughput)
        return false;
    if (s1.waiting_for_context_packet!=s2.waiting_for_context_packet)
        return false;
    return true;
}

inline bool operator!= (const connection_status_struct& s1, const connection_status_struct& s2) {
    return !(s1==s2);
}

struct VITA49Processing_override_struct {
    VITA49Processing_override_struct ()
    {
        enable = false;
        VRL_frames = true;
        processing_efficient = true;
        real_complex_type = 1;
        data_item_format = 3LL;
        repeating = 1;
        channel_tag_size = 0;
        event_tag_size = 0;
        vector_size = 1024;
        byte_swap = true;
    };

    static std::string getId() {
        return std::string("VITA49Processing_override");
    };

    bool enable;
    bool VRL_frames;
    bool processing_efficient;
    CORBA::Long real_complex_type;
    CORBA::LongLong data_item_format;
    CORBA::ULong repeating;
    CORBA::ULong channel_tag_size;
    CORBA::ULong event_tag_size;
    CORBA::ULong vector_size;
    bool byte_swap;
};

inline bool operator>>= (const CORBA::Any& a, VITA49Processing_override_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("VITA49Processing_override::enable")) {
        if (!(props["VITA49Processing_override::enable"] >>= s.enable)) return false;
    }
    if (props.contains("transportMethod_override::VRL_frames")) {
        if (!(props["transportMethod_override::VRL_frames"] >>= s.VRL_frames)) return false;
    }
    if (props.contains("VITA49Processing_override::processing_efficient")) {
        if (!(props["VITA49Processing_override::processing_efficient"] >>= s.processing_efficient)) return false;
    }
    if (props.contains("VITA49Processing_override::real_complex_type")) {
        if (!(props["VITA49Processing_override::real_complex_type"] >>= s.real_complex_type)) return false;
    }
    if (props.contains("VITA49Processing_override::data_item_format")) {
        if (!(props["VITA49Processing_override::data_item_format"] >>= s.data_item_format)) return false;
    }
    if (props.contains("VITA49Processing_override::repeating")) {
        if (!(props["VITA49Processing_override::repeating"] >>= s.repeating)) return false;
    }
    if (props.contains("VITA49Processing_override::channel_tag_size")) {
        if (!(props["VITA49Processing_override::channel_tag_size"] >>= s.channel_tag_size)) return false;
    }
    if (props.contains("VITA49Processing_override::event_tag_size")) {
        if (!(props["VITA49Processing_override::event_tag_size"] >>= s.event_tag_size)) return false;
    }
    if (props.contains("VITA49Processing_override::vector_size")) {
        if (!(props["VITA49Processing_override::vector_size"] >>= s.vector_size)) return false;
    }
    if (props.contains("VITA49Processing_override::byte_swap")) {
        if (!(props["VITA49Processing_override::byte_swap"] >>= s.byte_swap)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const VITA49Processing_override_struct& s) {
    redhawk::PropertyMap props;
 
    props["VITA49Processing_override::enable"] = s.enable;
 
    props["transportMethod_override::VRL_frames"] = s.VRL_frames;
 
    props["VITA49Processing_override::processing_efficient"] = s.processing_efficient;
 
    props["VITA49Processing_override::real_complex_type"] = s.real_complex_type;
 
    props["VITA49Processing_override::data_item_format"] = s.data_item_format;
 
    props["VITA49Processing_override::repeating"] = s.repeating;
 
    props["VITA49Processing_override::channel_tag_size"] = s.channel_tag_size;
 
    props["VITA49Processing_override::event_tag_size"] = s.event_tag_size;
 
    props["VITA49Processing_override::vector_size"] = s.vector_size;
 
    props["VITA49Processing_override::byte_swap"] = s.byte_swap;
    a <<= props;
}

inline bool operator== (const VITA49Processing_override_struct& s1, const VITA49Processing_override_struct& s2) {
    if (s1.enable!=s2.enable)
        return false;
    if (s1.VRL_frames!=s2.VRL_frames)
        return false;
    if (s1.processing_efficient!=s2.processing_efficient)
        return false;
    if (s1.real_complex_type!=s2.real_complex_type)
        return false;
    if (s1.data_item_format!=s2.data_item_format)
        return false;
    if (s1.repeating!=s2.repeating)
        return false;
    if (s1.channel_tag_size!=s2.channel_tag_size)
        return false;
    if (s1.event_tag_size!=s2.event_tag_size)
        return false;
    if (s1.vector_size!=s2.vector_size)
        return false;
    if (s1.byte_swap!=s2.byte_swap)
        return false;
    return true;
}

inline bool operator!= (const VITA49Processing_override_struct& s1, const VITA49Processing_override_struct& s2) {
    return !(s1==s2);
}

struct advanced_configuration_struct {
    advanced_configuration_struct ()
    {
        buffer_size = 4096000;
        corba_transfersize = 0;
        poll_in_time = 100;
        vita49_packet_size = 4136;
    };

    static std::string getId() {
        return std::string("advanced_configuration");
    };

    CORBA::Long buffer_size;
    CORBA::ULong corba_transfersize;
    CORBA::ULong poll_in_time;
    CORBA::ULong vita49_packet_size;
};

inline bool operator>>= (const CORBA::Any& a, advanced_configuration_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("buffer_size")) {
        if (!(props["buffer_size"] >>= s.buffer_size)) return false;
    }
    if (props.contains("corba_transfersize")) {
        if (!(props["corba_transfersize"] >>= s.corba_transfersize)) return false;
    }
    if (props.contains("poll_in_time")) {
        if (!(props["poll_in_time"] >>= s.poll_in_time)) return false;
    }
    if (props.contains("vita49_packet_size")) {
        if (!(props["vita49_packet_size"] >>= s.vita49_packet_size)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const advanced_configuration_struct& s) {
    redhawk::PropertyMap props;
 
    props["buffer_size"] = s.buffer_size;
 
    props["corba_transfersize"] = s.corba_transfersize;
 
    props["poll_in_time"] = s.poll_in_time;
 
    props["vita49_packet_size"] = s.vita49_packet_size;
    a <<= props;
}

inline bool operator== (const advanced_configuration_struct& s1, const advanced_configuration_struct& s2) {
    if (s1.buffer_size!=s2.buffer_size)
        return false;
    if (s1.corba_transfersize!=s2.corba_transfersize)
        return false;
    if (s1.poll_in_time!=s2.poll_in_time)
        return false;
    if (s1.vita49_packet_size!=s2.vita49_packet_size)
        return false;
    return true;
}

inline bool operator!= (const advanced_configuration_struct& s1, const advanced_configuration_struct& s2) {
    return !(s1==s2);
}

#endif // STRUCTPROPS_H
