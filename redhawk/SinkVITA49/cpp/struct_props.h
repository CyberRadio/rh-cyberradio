#ifndef STRUCTPROPS_H
#define STRUCTPROPS_H

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

*******************************************************************************************/

#include <ossie/CorbaUtils.h>
#include <CF/cf.h>
#include <ossie/PropertyMap.h>

struct network_settings_struct {
    network_settings_struct ()
    {
        enable = true;
        ip_address = "127.0.0.1";
        port = 42000;
        vlan = 0;
        use_udp_protocol = true;
        interface = "eth0";
    };

    static std::string getId() {
        return std::string("network_settings");
    };

    bool enable;
    std::string ip_address;
    CORBA::Long port;
    unsigned short vlan;
    bool use_udp_protocol;
    std::string interface;
};

inline bool operator>>= (const CORBA::Any& a, network_settings_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("network_settings::enable")) {
        if (!(props["network_settings::enable"] >>= s.enable)) return false;
    }
    if (props.contains("network_settings::ip_address")) {
        if (!(props["network_settings::ip_address"] >>= s.ip_address)) return false;
    }
    if (props.contains("network_settings::port")) {
        if (!(props["network_settings::port"] >>= s.port)) return false;
    }
    if (props.contains("network_settings::vlan")) {
        if (!(props["network_settings::vlan"] >>= s.vlan)) return false;
    }
    if (props.contains("network_settings::use_udp_protocol")) {
        if (!(props["network_settings::use_udp_protocol"] >>= s.use_udp_protocol)) return false;
    }
    if (props.contains("network_settings::interface")) {
        if (!(props["network_settings::interface"] >>= s.interface)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const network_settings_struct& s) {
    redhawk::PropertyMap props;
 
    props["network_settings::enable"] = s.enable;
 
    props["network_settings::ip_address"] = s.ip_address;
 
    props["network_settings::port"] = s.port;
 
    props["network_settings::vlan"] = s.vlan;
 
    props["network_settings::use_udp_protocol"] = s.use_udp_protocol;
 
    props["network_settings::interface"] = s.interface;
    a <<= props;
}

inline bool operator== (const network_settings_struct& s1, const network_settings_struct& s2) {
    if (s1.enable!=s2.enable)
        return false;
    if (s1.ip_address!=s2.ip_address)
        return false;
    if (s1.port!=s2.port)
        return false;
    if (s1.vlan!=s2.vlan)
        return false;
    if (s1.use_udp_protocol!=s2.use_udp_protocol)
        return false;
    if (s1.interface!=s2.interface)
        return false;
    return true;
}

inline bool operator!= (const network_settings_struct& s1, const network_settings_struct& s2) {
    return !(s1==s2);
}

struct VITA49Encapsulation_struct {
    VITA49Encapsulation_struct ()
    {
        enable_crc = false;
        enable_vrl_frames = true;
    };

    static std::string getId() {
        return std::string("VITA49Encapsulation");
    };

    bool enable_crc;
    bool enable_vrl_frames;
};

inline bool operator>>= (const CORBA::Any& a, VITA49Encapsulation_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("VITA49Encapsulation::enable_crc")) {
        if (!(props["VITA49Encapsulation::enable_crc"] >>= s.enable_crc)) return false;
    }
    if (props.contains("VITA49Encapsulation::enable_vrl_frames")) {
        if (!(props["VITA49Encapsulation::enable_vrl_frames"] >>= s.enable_vrl_frames)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const VITA49Encapsulation_struct& s) {
    redhawk::PropertyMap props;
 
    props["VITA49Encapsulation::enable_crc"] = s.enable_crc;
 
    props["VITA49Encapsulation::enable_vrl_frames"] = s.enable_vrl_frames;
    a <<= props;
}

inline bool operator== (const VITA49Encapsulation_struct& s1, const VITA49Encapsulation_struct& s2) {
    if (s1.enable_crc!=s2.enable_crc)
        return false;
    if (s1.enable_vrl_frames!=s2.enable_vrl_frames)
        return false;
    return true;
}

inline bool operator!= (const VITA49Encapsulation_struct& s1, const VITA49Encapsulation_struct& s2) {
    return !(s1==s2);
}

struct VITA49IFDataPacket_struct {
    VITA49IFDataPacket_struct ()
    {
        enable = true;
        enable_stream_identifier = true;
        enable_class_identifier = true;
        embed_time_stamp = true;
        enable_trailer = true;
    };

    static std::string getId() {
        return std::string("VITA49IFDataPacket");
    };

    bool enable;
    bool enable_stream_identifier;
    bool enable_class_identifier;
    bool embed_time_stamp;
    bool enable_trailer;
};

inline bool operator>>= (const CORBA::Any& a, VITA49IFDataPacket_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("VITA49IFDataPacket::enable")) {
        if (!(props["VITA49IFDataPacket::enable"] >>= s.enable)) return false;
    }
    if (props.contains("VITA49IFDataPacket::enable_stream_identifier")) {
        if (!(props["VITA49IFDataPacket::enable_stream_identifier"] >>= s.enable_stream_identifier)) return false;
    }
    if (props.contains("VITA49IFDataPacket::enable_class_identifier")) {
        if (!(props["VITA49IFDataPacket::enable_class_identifier"] >>= s.enable_class_identifier)) return false;
    }
    if (props.contains("VITA49IFDataPacket::embed_time_stamp")) {
        if (!(props["VITA49IFDataPacket::embed_time_stamp"] >>= s.embed_time_stamp)) return false;
    }
    if (props.contains("VITA49IFDataPacket::enable_trailer")) {
        if (!(props["VITA49IFDataPacket::enable_trailer"] >>= s.enable_trailer)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const VITA49IFDataPacket_struct& s) {
    redhawk::PropertyMap props;
 
    props["VITA49IFDataPacket::enable"] = s.enable;
 
    props["VITA49IFDataPacket::enable_stream_identifier"] = s.enable_stream_identifier;
 
    props["VITA49IFDataPacket::enable_class_identifier"] = s.enable_class_identifier;
 
    props["VITA49IFDataPacket::embed_time_stamp"] = s.embed_time_stamp;
 
    props["VITA49IFDataPacket::enable_trailer"] = s.enable_trailer;
    a <<= props;
}

inline bool operator== (const VITA49IFDataPacket_struct& s1, const VITA49IFDataPacket_struct& s2) {
    if (s1.enable!=s2.enable)
        return false;
    if (s1.enable_stream_identifier!=s2.enable_stream_identifier)
        return false;
    if (s1.enable_class_identifier!=s2.enable_class_identifier)
        return false;
    if (s1.embed_time_stamp!=s2.embed_time_stamp)
        return false;
    if (s1.enable_trailer!=s2.enable_trailer)
        return false;
    return true;
}

inline bool operator!= (const VITA49IFDataPacket_struct& s1, const VITA49IFDataPacket_struct& s2) {
    return !(s1==s2);
}

struct VITA49IFContextPacket_struct {
    VITA49IFContextPacket_struct ()
    {
        enable = false;
        enable_stream_identifier = true;
        stream_identifier_offset = 0;
        enable_class_identifier = true;
        class_identifier = "DEFAULT";
        embed_time_stamp = true;
        enable_device_identifier = true;
        device_identifier = "FF-FF-FA:1301";
        enable_trailer = true;
    };

    static std::string getId() {
        return std::string("VITA49IFContextPacket");
    };

    bool enable;
    bool enable_stream_identifier;
    CORBA::Long stream_identifier_offset;
    bool enable_class_identifier;
    std::string class_identifier;
    bool embed_time_stamp;
    bool enable_device_identifier;
    std::string device_identifier;
    bool enable_trailer;
};

inline bool operator>>= (const CORBA::Any& a, VITA49IFContextPacket_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("VITA49IFContextPacket::enable")) {
        if (!(props["VITA49IFContextPacket::enable"] >>= s.enable)) return false;
    }
    if (props.contains("VITA49IFContextPacket::enable_stream_identifier")) {
        if (!(props["VITA49IFContextPacket::enable_stream_identifier"] >>= s.enable_stream_identifier)) return false;
    }
    if (props.contains("VITA49IFContextPacket::stream_identifier_offset")) {
        if (!(props["VITA49IFContextPacket::stream_identifier_offset"] >>= s.stream_identifier_offset)) return false;
    }
    if (props.contains("VITA49IFContextPacket::enable_class_identifier")) {
        if (!(props["VITA49IFContextPacket::enable_class_identifier"] >>= s.enable_class_identifier)) return false;
    }
    if (props.contains("VITA49IFContextPacket::class_identifier")) {
        if (!(props["VITA49IFContextPacket::class_identifier"] >>= s.class_identifier)) return false;
    }
    if (props.contains("VITA49IFContextPacket::embed_time_stamp")) {
        if (!(props["VITA49IFContextPacket::embed_time_stamp"] >>= s.embed_time_stamp)) return false;
    }
    if (props.contains("VITA49IFContextPacket::enable_device_identifier")) {
        if (!(props["VITA49IFContextPacket::enable_device_identifier"] >>= s.enable_device_identifier)) return false;
    }
    if (props.contains("VITA49IFContextPacket::device_identifier")) {
        if (!(props["VITA49IFContextPacket::device_identifier"] >>= s.device_identifier)) return false;
    }
    if (props.contains("VITA49IFContextPacket::use_trailer")) {
        if (!(props["VITA49IFContextPacket::use_trailer"] >>= s.enable_trailer)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const VITA49IFContextPacket_struct& s) {
    redhawk::PropertyMap props;
 
    props["VITA49IFContextPacket::enable"] = s.enable;
 
    props["VITA49IFContextPacket::enable_stream_identifier"] = s.enable_stream_identifier;
 
    props["VITA49IFContextPacket::stream_identifier_offset"] = s.stream_identifier_offset;
 
    props["VITA49IFContextPacket::enable_class_identifier"] = s.enable_class_identifier;
 
    props["VITA49IFContextPacket::class_identifier"] = s.class_identifier;
 
    props["VITA49IFContextPacket::embed_time_stamp"] = s.embed_time_stamp;
 
    props["VITA49IFContextPacket::enable_device_identifier"] = s.enable_device_identifier;
 
    props["VITA49IFContextPacket::device_identifier"] = s.device_identifier;
 
    props["VITA49IFContextPacket::use_trailer"] = s.enable_trailer;
    a <<= props;
}

inline bool operator== (const VITA49IFContextPacket_struct& s1, const VITA49IFContextPacket_struct& s2) {
    if (s1.enable!=s2.enable)
        return false;
    if (s1.enable_stream_identifier!=s2.enable_stream_identifier)
        return false;
    if (s1.stream_identifier_offset!=s2.stream_identifier_offset)
        return false;
    if (s1.enable_class_identifier!=s2.enable_class_identifier)
        return false;
    if (s1.class_identifier!=s2.class_identifier)
        return false;
    if (s1.embed_time_stamp!=s2.embed_time_stamp)
        return false;
    if (s1.enable_device_identifier!=s2.enable_device_identifier)
        return false;
    if (s1.device_identifier!=s2.device_identifier)
        return false;
    if (s1.enable_trailer!=s2.enable_trailer)
        return false;
    return true;
}

inline bool operator!= (const VITA49IFContextPacket_struct& s1, const VITA49IFContextPacket_struct& s2) {
    return !(s1==s2);
}

struct advanced_configuration_struct {
    advanced_configuration_struct ()
    {
        force_transmit = true;
        max_payload_size = 1024;
        endian_representation = 0;
        number_of_buffers = 10;
        use_bulkio_sri = false;
        time_between_context_packets = 1;
        number_of_packets_in_burst = 150;
        throttle_time_between_packet_bursts = 100;
        byte_swap = true;
    };

    static std::string getId() {
        return std::string("advanced_configuration");
    };

    bool force_transmit;
    CORBA::Long max_payload_size;
    CORBA::Long endian_representation;
    CORBA::ULong number_of_buffers;
    bool use_bulkio_sri;
    CORBA::Long time_between_context_packets;
    CORBA::Long number_of_packets_in_burst;
    CORBA::Long throttle_time_between_packet_bursts;
    bool byte_swap;
};

inline bool operator>>= (const CORBA::Any& a, advanced_configuration_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("advanced_configuration::force_transmit")) {
        if (!(props["advanced_configuration::force_transmit"] >>= s.force_transmit)) return false;
    }
    if (props.contains("advanced_configuration::max_payload_size")) {
        if (!(props["advanced_configuration::max_payload_size"] >>= s.max_payload_size)) return false;
    }
    if (props.contains("advanced_configuration::endian_representation")) {
        if (!(props["advanced_configuration::endian_representation"] >>= s.endian_representation)) return false;
    }
    if (props.contains("advanced_configuration::number_of_buffers")) {
        if (!(props["advanced_configuration::number_of_buffers"] >>= s.number_of_buffers)) return false;
    }
    if (props.contains("advanced_configuration::use_bulkio_sri")) {
        if (!(props["advanced_configuration::use_bulkio_sri"] >>= s.use_bulkio_sri)) return false;
    }
    if (props.contains("advanced_configuration::time_between_context_packets")) {
        if (!(props["advanced_configuration::time_between_context_packets"] >>= s.time_between_context_packets)) return false;
    }
    if (props.contains("advanced_configuration::number_of_packets_in_burst")) {
        if (!(props["advanced_configuration::number_of_packets_in_burst"] >>= s.number_of_packets_in_burst)) return false;
    }
    if (props.contains("advanced_configuration::throttle_time_between_packet_bursts")) {
        if (!(props["advanced_configuration::throttle_time_between_packet_bursts"] >>= s.throttle_time_between_packet_bursts)) return false;
    }
    if (props.contains("byte_swap")) {
        if (!(props["byte_swap"] >>= s.byte_swap)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const advanced_configuration_struct& s) {
    redhawk::PropertyMap props;
 
    props["advanced_configuration::force_transmit"] = s.force_transmit;
 
    props["advanced_configuration::max_payload_size"] = s.max_payload_size;
 
    props["advanced_configuration::endian_representation"] = s.endian_representation;
 
    props["advanced_configuration::number_of_buffers"] = s.number_of_buffers;
 
    props["advanced_configuration::use_bulkio_sri"] = s.use_bulkio_sri;
 
    props["advanced_configuration::time_between_context_packets"] = s.time_between_context_packets;
 
    props["advanced_configuration::number_of_packets_in_burst"] = s.number_of_packets_in_burst;
 
    props["advanced_configuration::throttle_time_between_packet_bursts"] = s.throttle_time_between_packet_bursts;
 
    props["byte_swap"] = s.byte_swap;
    a <<= props;
}

inline bool operator== (const advanced_configuration_struct& s1, const advanced_configuration_struct& s2) {
    if (s1.force_transmit!=s2.force_transmit)
        return false;
    if (s1.max_payload_size!=s2.max_payload_size)
        return false;
    if (s1.endian_representation!=s2.endian_representation)
        return false;
    if (s1.number_of_buffers!=s2.number_of_buffers)
        return false;
    if (s1.use_bulkio_sri!=s2.use_bulkio_sri)
        return false;
    if (s1.time_between_context_packets!=s2.time_between_context_packets)
        return false;
    if (s1.number_of_packets_in_burst!=s2.number_of_packets_in_burst)
        return false;
    if (s1.throttle_time_between_packet_bursts!=s2.throttle_time_between_packet_bursts)
        return false;
    if (s1.byte_swap!=s2.byte_swap)
        return false;
    return true;
}

inline bool operator!= (const advanced_configuration_struct& s1, const advanced_configuration_struct& s2) {
    return !(s1==s2);
}

struct connection_status_struct {
    connection_status_struct ()
    {
    };

    static std::string getId() {
        return std::string("connection_status");
    };

    CORBA::Long packet_size;
};

inline bool operator>>= (const CORBA::Any& a, connection_status_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("connection_status::packet_size")) {
        if (!(props["connection_status::packet_size"] >>= s.packet_size)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const connection_status_struct& s) {
    redhawk::PropertyMap props;
 
    props["connection_status::packet_size"] = s.packet_size;
    a <<= props;
}

inline bool operator== (const connection_status_struct& s1, const connection_status_struct& s2) {
    if (s1.packet_size!=s2.packet_size)
        return false;
    return true;
}

inline bool operator!= (const connection_status_struct& s1, const connection_status_struct& s2) {
    return !(s1==s2);
}

#endif // STRUCTPROPS_H
