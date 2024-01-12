#include "dvb_base_band_frame.hpp"
#include <gtest/gtest.h>

crc_library::crc<uint8_t, 0xD5, 0x00, false, false, 0x00> crc;
digital_video_broadasting::base_band_header_s base_band_header;
std::vector<std::byte> data_field{std::byte{0x1}, std::byte{0x2}, std::byte{0x3}, std::byte{0x4}, std::byte{0x5},
                                  std::byte{0x6}, std::byte{0x7}, std::byte{0x8}, std::byte{0x9}, std::byte{0xA}};

std::vector<std::byte> raw_data{std::byte{0x8F}, std::byte{0xFF}, std::byte{0x0A}, std::byte{0x00}, std::byte{0x0A}, std::byte{0x00}, std::byte{0x47}, std::byte{0xFF}, std::byte{0xFF}, std::byte{0x61},std::byte{0x1}, std::byte{0x2}, std::byte{0x3}, std::byte{0x4}, std::byte{0x5},
                                  std::byte{0x6}, std::byte{0x7}, std::byte{0x8}, std::byte{0x9}, std::byte{0xA}};

TEST(DVB, RAW_DATA_TO_PRIMARY_HEADER)
{
    digital_video_broadasting::base_band_frame temporary(raw_data);
    digital_video_broadasting::base_band_header_s actual_header = temporary.get_base_band_header();

    ASSERT_EQ(actual_header.matype.transport_stream_input, base_band_header.matype.transport_stream_input);
    ASSERT_EQ(actual_header.matype.single_input_stream, base_band_header.matype.single_input_stream);
    ASSERT_EQ(actual_header.matype.constant_coding_and_modulation, base_band_header.matype.constant_coding_and_modulation);
    ASSERT_EQ(actual_header.matype.input_stream_synchronization_indicator, base_band_header.matype.input_stream_synchronization_indicator);
    ASSERT_EQ(actual_header.matype.null_packet_deletion, base_band_header.matype.null_packet_deletion);
    ASSERT_EQ(actual_header.matype.transmition_roll_off_factor, base_band_header.matype.transmition_roll_off_factor);
    ASSERT_EQ(actual_header.matype.matype_2, base_band_header.matype.matype_2);
    ASSERT_EQ(actual_header.user_packet_length, base_band_header.user_packet_length);
    ASSERT_EQ(actual_header.data_field_length, base_band_header.data_field_length);
    ASSERT_EQ(actual_header.user_packet_sync, base_band_header.user_packet_sync);
    ASSERT_EQ(actual_header.sync_distance, base_band_header.sync_distance);
    ASSERT_EQ(actual_header.crc_8, base_band_header.crc_8);
}

TEST(DVB, CUSTOM_TEST)
{
    size_t header_size_without_crc = sizeof(digital_video_broadasting::base_band_header_s) - sizeof(digital_video_broadasting::base_band_header_s::crc_8);
    std::vector<std::byte> calculate_header_crc(header_size_without_crc);
    std::memcpy(calculate_header_crc.data(), &base_band_header, header_size_without_crc);
    std::vector<std::byte> raw_data_comparison;
    raw_data_comparison.insert(raw_data_comparison.begin(), raw_data.begin(), raw_data.begin()+header_size_without_crc);
    ASSERT_EQ(calculate_header_crc,raw_data_comparison);
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