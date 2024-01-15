#include "dvb_base_band_frame.hpp"
#include <gtest/gtest.h>

crc_library::crc<uint8_t, 0xD5, 0x00, false, false, 0x00> crc;
digital_video_broadasting::base_band_header_s base_band_header;
std::vector<std::byte> data_field{std::byte{0x1}, std::byte{0x2}, std::byte{0x3}, std::byte{0x4}, std::byte{0x5},
                                  std::byte{0x6}, std::byte{0x7}, std::byte{0x8}, std::byte{0x9}, std::byte{0xA}};

std::vector<std::byte> raw_data{std::byte{0x8F}, std::byte{0xFF}, std::byte{0x0A}, std::byte{0x00}, std::byte{0x0A},
                                std::byte{0x00}, std::byte{0x47}, std::byte{0xFF}, std::byte{0xFF}, std::byte{0x61},
                                std::byte{0x1},  std::byte{0x2},  std::byte{0x3},  std::byte{0x4},  std::byte{0x5},
                                std::byte{0x6},  std::byte{0x7},  std::byte{0x8},  std::byte{0x9},  std::byte{0xA}};

TEST(DVB, RAW_DATA_TO_HEADER)
{
    digital_video_broadasting::base_band_frame temporary(raw_data);
    digital_video_broadasting::base_band_header_s actual_header = temporary.get_base_band_header();

    ASSERT_EQ(actual_header.matype.transport_stream_input, base_band_header.matype.transport_stream_input);
    ASSERT_EQ(actual_header.matype.single_input_stream, base_band_header.matype.single_input_stream);
    ASSERT_EQ(actual_header.matype.constant_coding_and_modulation,
              base_band_header.matype.constant_coding_and_modulation);
    ASSERT_EQ(actual_header.matype.input_stream_synchronization_indicator,
              base_band_header.matype.input_stream_synchronization_indicator);
    ASSERT_EQ(actual_header.matype.null_packet_deletion, base_band_header.matype.null_packet_deletion);
    ASSERT_EQ(actual_header.matype.transmition_roll_off_factor, base_band_header.matype.transmition_roll_off_factor);
    ASSERT_EQ(actual_header.matype.matype_2, base_band_header.matype.matype_2);
    ASSERT_EQ(actual_header.user_packet_length, base_band_header.user_packet_length);
    ASSERT_EQ(actual_header.data_field_length, base_band_header.data_field_length);
    ASSERT_EQ(actual_header.user_packet_sync, base_band_header.user_packet_sync);
    ASSERT_EQ(actual_header.sync_distance, base_band_header.sync_distance);
    ASSERT_EQ(actual_header.crc_8, base_band_header.crc_8);
}

TEST(DVB, RAW_DATA_TO_DATA_FIELD)
{
    digital_video_broadasting::base_band_frame temporary(raw_data);
    std::vector<std::byte> actual_data_field = temporary.get_data_field();
    ASSERT_EQ(actual_data_field, data_field);
}

TEST(DVB, HEADER_AND_DATA_FIELD_TO_RAW_DATA)
{
    digital_video_broadasting::base_band_frame temporary(base_band_header, data_field);
    std::vector<std::byte> actual_raw_data =
        temporary.get_raw_packet(sizeof(digital_video_broadasting::base_band_header_s) + data_field.size());
    ASSERT_EQ(actual_raw_data, raw_data);
}

TEST(DVB, HEADER_AND_DATA_FIELD_TO_HEADER)
{
    digital_video_broadasting::base_band_frame temporary(base_band_header, data_field);
    digital_video_broadasting::base_band_header_s actual_header = temporary.get_base_band_header();

    ASSERT_EQ(actual_header.matype.transport_stream_input, base_band_header.matype.transport_stream_input);
    ASSERT_EQ(actual_header.matype.single_input_stream, base_band_header.matype.single_input_stream);
    ASSERT_EQ(actual_header.matype.constant_coding_and_modulation,
              base_band_header.matype.constant_coding_and_modulation);
    ASSERT_EQ(actual_header.matype.input_stream_synchronization_indicator,
              base_band_header.matype.input_stream_synchronization_indicator);
    ASSERT_EQ(actual_header.matype.null_packet_deletion, base_band_header.matype.null_packet_deletion);
    ASSERT_EQ(actual_header.matype.transmition_roll_off_factor, base_band_header.matype.transmition_roll_off_factor);
    ASSERT_EQ(actual_header.matype.matype_2, base_band_header.matype.matype_2);
    ASSERT_EQ(actual_header.user_packet_length, base_band_header.user_packet_length);
    ASSERT_EQ(actual_header.data_field_length, base_band_header.data_field_length);
    ASSERT_EQ(actual_header.user_packet_sync, base_band_header.user_packet_sync);
    ASSERT_EQ(actual_header.sync_distance, base_band_header.sync_distance);
    ASSERT_EQ(actual_header.crc_8, base_band_header.crc_8);
}

TEST(DVB, HEADER_AND_DATA_FIELD_TO_DATA_FIELD)
{
    digital_video_broadasting::base_band_frame temporary(base_band_header, data_field);
    std::vector<std::byte> actual_data_field = temporary.get_data_field();
    ASSERT_EQ(actual_data_field, data_field);
}

TEST(DVB, RAW_DATA_TO_RAW_DATA)
{
    digital_video_broadasting::base_band_frame temporary(raw_data);
    std::vector<std::byte> actual_raw_data =
        temporary.get_raw_packet(sizeof(digital_video_broadasting::base_band_header_s) + data_field.size());
    ASSERT_EQ(actual_raw_data, raw_data);
}

TEST(DVB, HEADER_AND_DATA_FIELD_TO_RAW_DATA_WITH_PADDING)
{
    std::vector<std::byte> padded_raw_data(raw_data);
    std::vector<std::byte> padding(5, std::byte{0x0});

    padded_raw_data.insert(padded_raw_data.end(), padding.begin(), padding.end());

    digital_video_broadasting::base_band_frame temporary(base_band_header, data_field);
    std::vector<std::byte> actual_raw_data = temporary.get_raw_packet(padded_raw_data.size());

    ASSERT_EQ(actual_raw_data, padded_raw_data);
}

TEST(DVB, RAW_DATA_TO_RAW_DATA_WITH_PADDING)
{
    std::vector<std::byte> padded_raw_data(raw_data);
    std::vector<std::byte> padding(5, std::byte{0x0});

    padded_raw_data.insert(padded_raw_data.end(), padding.begin(), padding.end());

    digital_video_broadasting::base_band_frame temporary(raw_data);
    std::vector<std::byte> actual_raw_data = temporary.get_raw_packet(padded_raw_data.size());

    ASSERT_EQ(actual_raw_data, padded_raw_data);
}

TEST(DVB, INCORRECT_CRC)
{
    std::vector<std::byte> incorrect_raw_data(raw_data);
    incorrect_raw_data[0] = std::byte(0x9D);
    ASSERT_THROW(digital_video_broadasting::base_band_frame temporary(incorrect_raw_data), std::runtime_error);
}

TEST(DVB, RAW_DATA_TO_SCRAMBLED_DATA)
{
    digital_video_broadasting::base_band_frame temporary(raw_data);
    std::vector<std::byte> actual_scrambled_data = temporary.get_scrambled_packet(raw_data.size());

    prbs_lfsr::lfsr_library<uint16_t, 0b11, 0b100101010000000> lfsr;
    std::vector<uint16_t> lfsr_bits = lfsr.calculate_lsfr(raw_data.size() / sizeof(uint8_t));

    std::vector<std::byte> temp(raw_data.size(), std::byte(0x0));
    std::memcpy(temp.data(), lfsr_bits.data(), temp.size());

    std::vector<std::byte> scrambled_data;
    for (size_t i = 0; i < raw_data.size(); ++i)
    {
        scrambled_data.push_back(raw_data[i] ^ temp[i]);
    }

    ASSERT_EQ(actual_scrambled_data, scrambled_data);
}

TEST(DVB, HEADER_AND_DATA_FIELD_TO_SCRAMBLED_DATA)
{
    digital_video_broadasting::base_band_frame temporary(base_band_header, data_field);

    std::vector<std::byte> actual_scrambled_data =
        temporary.get_scrambled_packet(sizeof(digital_video_broadasting::base_band_header_s) + data_field.size());

    prbs_lfsr::lfsr_library<uint16_t, 0b11, 0b100101010000000> lfsr;
    std::vector<uint16_t> lfsr_bits = lfsr.calculate_lsfr(raw_data.size() / sizeof(uint8_t));

    std::vector<std::byte> temp(raw_data.size(), std::byte(0x0));
    std::memcpy(temp.data(), lfsr_bits.data(), temp.size());

    std::vector<std::byte> scrambled_data;
    for (size_t i = 0; i < raw_data.size(); ++i)
    {
        scrambled_data.push_back(raw_data[i] ^ temp[i]);
    }

    ASSERT_EQ(actual_scrambled_data, scrambled_data);
}

TEST(DVB, CUSTOM_TEST)
{
    size_t header_size_without_crc = sizeof(digital_video_broadasting::base_band_header_s) -
                                     sizeof(digital_video_broadasting::base_band_header_s::crc_8);
    std::vector<std::byte> calculate_header_crc(header_size_without_crc);
    std::memcpy(calculate_header_crc.data(), &base_band_header, header_size_without_crc);
    std::vector<std::byte> raw_data_comparison;
    raw_data_comparison.insert(raw_data_comparison.begin(), raw_data.begin(),
                               raw_data.begin() + header_size_without_crc);
    ASSERT_EQ(calculate_header_crc, raw_data_comparison);
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

    size_t header_size_without_crc = sizeof(digital_video_broadasting::base_band_header_s) -
                                     sizeof(digital_video_broadasting::base_band_header_s::crc_8);
    std::vector<std::byte> calculate_header_crc(header_size_without_crc);
    std::memcpy(calculate_header_crc.data(), &base_band_header, header_size_without_crc);
    base_band_header.crc_8 = crc.calculate_crc(calculate_header_crc);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}