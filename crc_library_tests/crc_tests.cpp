#include <crc_library/crc_library.hpp>
#include <gtest/gtest.h>
#include <vector>

std::vector<std::byte> data{std::byte{0x31}, std::byte{0x32}, std::byte{0x33}, std::byte{0x34}, std::byte{0x35},
                            std::byte{0x36}, std::byte{0x37}, std::byte{0x38}, std::byte{0x39}};

TEST(CRC8, CRC8)
{
    crc_library::crc<uint8_t, 0x07, 0x00, false, false, 0x00> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0xF4);
}
TEST(CRC8, CRC8REFIN)
{
    crc_library::crc<uint8_t, 0x07, 0x00, true, false, 0x00> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0x4);
}
TEST(CRC8, CRC8REFOUT)
{
    crc_library::crc<uint8_t, 0x07, 0x00, false, true, 0x00> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0x2F);
}
TEST(CRC8, CRC8REFOUTINIT)
{
    crc_library::crc<uint8_t, 0x07, 0x07, false, true, 0x00> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0x39);
}
TEST(CRC8, CRC8REFININIT)
{
    crc_library::crc<uint8_t, 0x07, 0x07, true, false, 0x00> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0x6C);
}
TEST(CRC8, CRC8REFININITXOR)
{
    crc_library::crc<uint8_t, 0x07, 0x07, true, false, 0x07> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0x6B);
}
TEST(CRC8, CRC8REFOUTINITXOR)
{
    crc_library::crc<uint8_t, 0x07, 0x07, false, true, 0x07> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0x3E);
}
TEST(CRC8, CRC8REFINREFOUTINITXOR)
{
    crc_library::crc<uint8_t, 0x07, 0x07, true, true, 0x07> crc8;

    ASSERT_EQ(crc8.calculate_crc(data), 0x31);
}
TEST(CRC16, CRC16)
{
    crc_library::crc<uint16_t, 0x1021, 0x0, false, false, 0x0000> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0x31C3);
}
TEST(CRC16, CRC16REFIN)
{
    crc_library::crc<uint16_t, 0x1021, 0x0, true, false, 0x0000> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0x9184);
}
TEST(CRC16, CRC16REFOUT)
{
    crc_library::crc<uint16_t, 0x1021, 0x0, false, true, 0x0000> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0xC38C);
}
TEST(CRC16, CRC16REFININIT)
{
    crc_library::crc<uint16_t, 0x1021, 0xC38C, true, false, 0x0000> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0xB09D);
}
TEST(CRC16, CRC16REFOUTINIT)
{
    crc_library::crc<uint16_t, 0x1021, 0xC38C, false, true, 0x0000> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0x5B08);
}
TEST(CRC16, CRC16REFININITXOR)
{
    crc_library::crc<uint16_t, 0x1021, 0xC38C, true, false, 0x5B08> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0xEB95);
}
TEST(CRC16, CRC16REFOUTINITXOR)
{
    crc_library::crc<uint16_t, 0x1021, 0xC38C, false, true, 0xEB95> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0xB09D);
}
TEST(CRC16, CRC16REFINREFOUTINITXOR)
{
    crc_library::crc<uint16_t, 0x1021, 0xC38C, true, true, 0xEB95> crc16;

    ASSERT_EQ(crc16.calculate_crc(data), 0x5298);
}
TEST(CRC32, CRC32)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0xCBF43926);
}
TEST(CRC32, CRC32REFIN)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0x0, true, false, 0x0> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0x11B4BFB4);
}
TEST(CRC32, CRC32REFOUT)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0x0, false, true, 0x0> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0xFE918591);
}
TEST(CRC32, CRC32REFININIT)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0xFFFFFFFF, true, false, 0x0> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0x9B63D02C);
}
TEST(CRC32, CRC32REFOUTINIT)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0xFFFFFFFF, false, true, 0x0> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0xE7676EC0);
}
TEST(CRC32, CRC32REFININITXOR)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0xFFFFFFFF, true, false, 0xFFFFFFFF> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0x649C2FD3);
}
TEST(CRC32, CRC32REFOUTINITXOR)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0xFFFFFFFF, false, true, 0xFFFFFFFF> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0x1898913F);
}
TEST(CRC32, CRC32REFINREFOUTINITXOR)
{
    crc_library::crc<uint32_t, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF> crc32;

    ASSERT_EQ(crc32.calculate_crc(data), 0xCBF43926);
}
TEST(CUSTOM, CUSTOMTEST)
{
    crc_library::crc<uint8_t, 0x0, 0x0, true, true, 0x0> crc_test;
    ASSERT_EQ(crc_test.calculate_crc(data), 0x0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}