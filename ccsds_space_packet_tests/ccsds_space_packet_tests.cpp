#include "ccsds_space_packet.hpp"
#include <gtest/gtest.h>

ccsds_space_packet::primary_header_s primary_header;

std::vector<std::byte> payload(8, std::byte(0x00));

std::vector<std::byte> raw_data{std::byte(0xED), std::byte(0xFF), std::byte(0x07), std::byte(0x00), std::byte(0x08),
                                std::byte(0x00), std::byte(0x00), std::byte(0x00), std::byte(0x00), std::byte(0x00),
                                std::byte(0x00), std::byte(0x00), std::byte(0x00), std::byte(0x00)};

TEST(CCSDS, RAW_DATA_TO_PRIMARY_HEADER)
{
    ccsds_space_packet::space_packet temporary(raw_data);
    ccsds_space_packet::primary_header_s actual_header = temporary.get_primary_header();

    ASSERT_EQ(actual_header.packet_version_number, primary_header.packet_version_number);
    ASSERT_EQ(actual_header.packet_type, primary_header.packet_type);
    ASSERT_EQ(actual_header.secondary_header_flag, primary_header.secondary_header_flag);
    ASSERT_EQ(actual_header.APID, primary_header.APID);
    ASSERT_EQ(actual_header.sequence_flags, primary_header.sequence_flags);
    ASSERT_EQ(actual_header.packet_sequence_count, primary_header.packet_sequence_count);
    ASSERT_EQ(actual_header.packet_data_length, primary_header.packet_data_length);
}

TEST(CCSDS, RAW_DATA_TO_PAYLOAD)
{
    ccsds_space_packet::space_packet temporary(raw_data);
    ASSERT_EQ(temporary.get_payload(), payload);
}
TEST(CCSDS, RAW_DATA_TO_RAW_DATA)
{
    ccsds_space_packet::space_packet temporary(raw_data);
    ASSERT_EQ(temporary.get_raw_packet(), raw_data);
}

TEST(CCSDS, PRIMARY_HEADER_AND_PAYLOAD_TO_RAW_DATA)
{
    ccsds_space_packet::space_packet temporary(primary_header, payload);
    ASSERT_EQ(temporary.get_raw_packet(), raw_data);
}

TEST(CCSDS, PRIMARY_HEADER_AND_PAYLOAD_TO_PRIMARY_HEADER)
{
    ccsds_space_packet::space_packet temporary(primary_header, payload);
    ccsds_space_packet::primary_header_s actual_header = temporary.get_primary_header();

    ASSERT_EQ(actual_header.packet_version_number, primary_header.packet_version_number);
    ASSERT_EQ(actual_header.packet_type, primary_header.packet_type);
    ASSERT_EQ(actual_header.secondary_header_flag, primary_header.secondary_header_flag);
    ASSERT_EQ(actual_header.APID, primary_header.APID);
    ASSERT_EQ(actual_header.sequence_flags, primary_header.sequence_flags);
    ASSERT_EQ(actual_header.packet_sequence_count, primary_header.packet_sequence_count);
    ASSERT_EQ(actual_header.packet_data_length, primary_header.packet_data_length);
}

TEST(CCSDS, PRIMARY_HEADER_AND_PAYLOAD_TO_PAYLOAD)
{
    ccsds_space_packet::space_packet temporary(primary_header, payload);
    ASSERT_EQ(temporary.get_payload(), payload);
}

int main(int argc, char **argv)
{
    primary_header.packet_version_number = 0b101;
    primary_header.packet_type           = ccsds_space_packet::packet_type_e::telecommands;
    primary_header.secondary_header_flag = ccsds_space_packet::secondary_header_flag_e::not_present;
    primary_header.APID                  = 0b11111111111;
    primary_header.sequence_flags        = ccsds_space_packet::sequence_flags_e::unsegmented;
    primary_header.packet_sequence_count = 1;
    primary_header.packet_data_length    = 8;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}