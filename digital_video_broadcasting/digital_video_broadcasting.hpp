#ifndef DIGITAL_VIDEO_BROADCASTING
#define DIGITAL_VIDEO_BROADCASTING

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

namespace digital_video_broadasting
{
    enum class transport_stream_input_e : uint8_t
    {
        transport = 0b11,
        generic_packetized = 0b00,
        generic_continuous = 0b01,
        reserved = 0b10
    };

    enum class single_input_stream_e : bool
    {
        single = 0b1,
        multiple = 0b0
    };

    enum class constant_coding_and_modulation_e : bool
    {
        ccm = 0b1,
        acm = 0b0
    };

    enum class input_stream_synchronization_indicator_e : bool
    {
        active =0b1,
        not_active = 0b0
    };

    enum class null_packet_deletion_e : bool
    {
        active =0b1,
        not_active = 0b0
    };

    enum class transmition_roll_off_factor_e :  uint8_t
    {
        alpha_0_35 = 0b00,
        alpha_0_25 = 0b01,
        alpha_0_20 = 0b10,
        reserved = 0b11
    };

    struct [[gnu::packed]] matype_1_s
    {
        transport_stream_input_e transport_stream_input :2;
        single_input_stream_e single_input_stream_ :1;
        constant_coding_and_modulation_e constant_coding_and_modulation :1;
        input_stream_synchronization_indicator_e input_stream_synchronization_indicator :1;
        null_packet_deletion_e null_packet_deletion :1;
        transmition_roll_off_factor_e transmition_roll_off_factor :2;
    };
    

    class dvb
    {
    private:

    public:
        dvb(/* args */);
    };
}

#endif