#include "dvb_base_band_frame.hpp"
#include <gtest/gtest.h>

crc_library::crc<uint8_t, 0xD5, 0x00, false, false, 0x00> crc;
digital_video_broadasting::base_band_header_s base_band_header;
std::vector<std::byte> data_field{std::byte{0x1}, std::byte{0x2}, std::byte{0x3}, std::byte{0x4}, std::byte{0x5},
                                  std::byte{0x6}, std::byte{0x7}, std::byte{0x8}, std::byte{0x9}, std::byte{0xA}};

std::vector<std::byte> raw_data{std::byte{0x0F}, std::byte{0xFF}, std::byte{0xAA}, std::byte{0x47},
                                std::byte{0xFF}, std::byte{0xFF}, std::byte{0xBC},std::byte{0x1},  std::byte{0x2},
                                std::byte{0x3},  std::byte{0x4},  std::byte{0x5},  std::byte{0x6},
                                std::byte{0x7},  std::byte{0x8},  std::byte{0x9},  std::byte{0xA}};


TEST(DVB, CUSTOM_TEST)
{
    ASSERT_EQ(1,1);
}
int main(int argc, char **argv)
{
    digital_video_broadasting::matype_s matype;
    matype.transport_stream_input         = digital_video_broadasting::transport_stream_input_e::transport;
    matype.single_input_stream            = digital_video_broadasting::single_input_stream_e::single;
    matype.constant_coding_and_modulation = digital_video_broadasting::constant_coding_and_modulation_e::ccm;
    matype.input_stream_synchronization_indicator =
        digital_video_broadasting::input_stream_synchronization_indicator_e::not_active;
    matype.null_packet_deletion         = digital_video_broadasting::null_packet_deletion_e::not_active;
    matype.transmition_roll_off_factor  = digital_video_broadasting::transmition_roll_off_factor_e::alpha_0_20;
    matype.matype_2                     = 0b11111111;
    base_band_header.matype             = matype;
    base_band_header.user_packet_length = 0xA;
    base_band_header.data_field_length  = 0xA;
    base_band_header.user_packet_sync   = 0x47;
    base_band_header.sync_distance      = 65535;

    size_t header_size_without_crc = sizeof(digital_video_broadasting::base_band_header_s) - sizeof(digital_video_broadasting::base_band_header_s::crc_8);
    std::vector<std::byte> calculate_header_crc(header_size_without_crc);
    std::memcpy(calculate_header_crc.data(), &base_band_header, header_size_without_crc);
    base_band_header.crc_8 = crc.calculate_crc(calculate_header_crc);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}