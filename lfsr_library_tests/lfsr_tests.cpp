#include <gtest/gtest.h>
#include <lfsr_library/lfsr_library.hpp>

TEST(LFSR8, LFSR8)
{
    prbs_lfsr::lfsr_library<uint8_t, 0b11, 0b1001> lfsr;
    std::vector<uint8_t> expected_output{0b10110001, 0b11010010, 0b01110110, 0b10011011,
                                         0b10101100, 0b11110101, 0b00011111, 0b00100000};

    ASSERT_EQ(lfsr.calculate_lsfr(), expected_output);
}

TEST(LFSR8, LFSR8_PARTIAL)
{
    prbs_lfsr::lfsr_library<uint8_t, 0b11, 0b1001> lfsr;
    std::vector<uint8_t> expected_output{0b10110001, 0b11010010, 0b01110110};

    ASSERT_EQ(lfsr.calculate_lsfr(3), expected_output);
}
TEST(LFSR16, LFSR16_PARTIAL)
{
    prbs_lfsr::lfsr_library<uint16_t, 0b0001000010000001, 0b1101011100011011> lfsr;
    std::vector<uint16_t> expected_output{0b0001110010101111};
    ASSERT_EQ(lfsr.calculate_lsfr(1), expected_output);
}
TEST(LFSR16, LFSR16)
{
    std::vector<uint16_t> expected_output{
        0b0001110010101111, 0b1011000001110000, 0b1000000000110011, 0b1010001111011111, 0b1011011101110011,
        0b0011110100111110, 0b0100011001111010, 0b1101011001110110, 0b1000010101100010, 0b0001010100111011,
        0b0011101100010111, 0b1100110000110010, 0b1111101011100001, 0b1001001100011001, 0b1000011110100000,
        0b0101001010100011, 0b0011000000111000, 0b1010011000001011, 0b0001001010101000, 0b1100101001101011,
        0b0100101101111001, 0b0110000111010100, 0b1100011111001011, 0b1001101110111101, 0b1001110010111000,
        0b0100010011010111, 0b0101101011010111, 0b0100010100100111, 0b1010110000110010, 0b1001110010110111,
        0b1011110010100011, 0b1101000001001111, 0b0000011110110111, 0b1010011000000100, 0b1110101011011100,
        0b0100000011110011, 0b0000100111101001, 0b0110101111100010, 0b1011000110100000, 0b0110011111101101,
        0b0100010100011110, 0b0010100010000010, 0b0100110101110011, 0b1100100000010110, 0b1010100111011111,
        0b1011110111011100, 0b1001101000110010, 0b1010100111111001, 0b1100100110000101, 0b0101111011000110,
        0b0101100001101100, 0b1010010001111001, 0b0000100001111010, 0b1001110011111011, 0b0101010000010000,
        0b0101100110100110, 0b1110010010011101, 0b0111110111111100, 0b0100011110100101, 0b1100100111011100,
        0b1110100100111011, 0b1100100001011010, 0b0100000101101100, 0b0011010000110101, 0b0111100100011000,
        0b0111001000000001, 0b0110010011111100, 0b1101011111101001, 0b1011100010111110, 0b0000011111000001,
        0b1111100010110110, 0b1100111100100011, 0b0110100000010110, 0b0000001100100101, 0b1100110100010010,
        0b0110001000000011, 0b0101011011000100, 0b0111001111000001, 0b1000101110111111, 0b1010111010000000,
        0b1110000011111111, 0b0110100111010110, 0b1110110001100110, 0b1011010001111011, 0b0011101001000010,
        0b0011100011010011, 0b0110011100010001, 0b1111000011100111, 0b1111110011010100, 0b1101101100001001,
        0b1100001111010101, 0b0111111010000010, 0b0001111001101011, 0b1001001010001010, 0b0111000010111001,
        0b1011011100010011, 0b0000111001110011, 0b0000011110001000, 0b0100011111010110, 0b1100000010111101,
        0b0100101010110011, 0b0010000100110000, 0b1011001001001101, 0b0100000011100011, 0b0000000101110100,
        0b1111010001001010, 0b0111011000010000, 0b0111100110110111, 0b1101111110100010, 0b0010110001110011,
        0b0010011110011001, 0b0111110011101001, 0b1001000100110010, 0b0010101010001111, 0b1001010000000101,
        0b1100101001000100, 0b1010001000110110, 0b1101010000011101, 0b0000101000111011, 0b1010110100111110,
        0b1101111110101011, 0b1011000101100101, 0b0101011010100100, 0b0100000010001100, 0b1100101001001101,
        0b0011111100100000, 0b1010010100100000, 0b0011011001011110, 0b1111011001000001, 0b1100101000000100,
        0b1000000001000000, 0b1010101010111110, 0b0001010011111011, 0b1101010001010100, 0b1011010101011011,
        0b1010001010100000, 0b1111110100001110, 0b1001001101110000, 0b0010100111111011, 0b0110001001101100,
        0b1001110111111101, 0b1011100010101011, 0b0101100010001111, 0b1110000101101001, 0b1100100100011100,
        0b1000111110100001, 0b0100101110111111, 0b0110001000101100, 0b1011111110001011, 0b1100011000001000,
        0b0100011001001111, 0b1001100000000011, 0b1010001111101100, 0b1001110001100100, 0b1110000000010101,
        0b1011000111010000, 0b0101110000111101, 0b1001101101000100, 0b0111111010010010, 0b0001011011110110,
        0b0000110100100010, 0b1011011100001001, 0b1010100101001001, 0b1001010011001111, 0b0000001101111001,
        0b0010110100111100, 0b0111010001000010, 0b0111001001011110, 0b1011011001100011, 0b1011110001111010,
        0b0010001101011110, 0b0110101011000111, 0b0111111010010001, 0b0010010001000111, 0b0111000011110000,
        0b0000100001110011, 0b0000000111101101, 0b0010010100101101, 0b0110010111000011, 0b1011111111100010,
        0b0110100001010011, 0b0111011010000000, 0b0011010111000110, 0b1011110101001100, 0b1101011001000011,
        0b1100101100010111, 0b0011001110110101, 0b1011001001001000, 0b0001011100110000, 0b1000011100000011,
        0b0011010111000101, 0b1000111111111101, 0b1010101110010001, 0b0111010001101101, 0b1001101100010001,
        0b0000001110101010, 0b0111000110001010, 0b0001010111011101, 0b0010100111010100, 0b1000101100100011,
        0b0010100000110100, 0b0111010101011011, 0b0110111000001100, 0b1010001001111010, 0b0011110010101110,
        0b1000001111010010, 0b0100111000010100, 0b0000010001010011, 0b0001110000011100, 0b1101111110001011,
        0b1010000001011110, 0b0110100111110101, 0b1100111111101100, 0b1111011011111000, 0b0000101001011000,
        0b1010110011000010, 0b1110001110001011, 0b1001111110111111, 0b1011101111011111, 0b1010111011100110,
        0b1011011011010000, 0b1101001110000001, 0b0000001100110011, 0b1010000011101101, 0b0000011000001110,
        0b1110111110000001, 0b0011110011010010, 0b0111001011000111, 0b0110011100000100, 0b1010111110101001,
        0b1110010100001011, 0b1101110100110110, 0b0010010001100010, 0b0011011000011000, 0b1011000101010101,
        0b0100111100000010, 0b1110000001110101, 0b1000001010011101, 0b0001110111001111, 0b0000101011100100,
        0b0011101101001101, 0b0100100101111110, 0b0001011100000101, 0b1100100101110110, 0b0001001101001011,
        0b0000011010100010, 0b0111000010010011, 0b0000100110001111, 0b0011110111001101, 0b0000101111110111,
        0b1000100010111000, 0b0101000110001000, 0b0001010011001110, 0b1001101000100001, 0b1001001111010101,
        0b0010101111111111, 0b0010011000001100, 0b1110111010010010, 0b1000111100100111, 0b0110101000110001,
        0b0110010011001111, 0b1111110011111110, 0b0110010110010101, 0b1111000001101011, 0b0111001011111101,
        0b1101000100000101, 0b0000001110111111, 0b0010111011000100, 0b0000110000000010, 0b0010111111101011,
        0b0110110010010100, 0b0110000010101110, 0b1101101001100101, 0b1011001110000100, 0b0011001010110110,
        0b0000100100100000, 0b1001000001101110, 0b0100001101111000, 0b0111100011001000, 0b1001010111011111,
        0b1000001000111101, 0b0100100000011000, 0b1100100011110011, 0b1000100110101101, 0b1000011100011111,
        0b1111011110011101, 0b1110011100011111, 0b1001000111001011, 0b1100100010100101, 0b1100011000100100,
        0b1001110110110001, 0b0101000000011000, 0b1101000101100110, 0b0000001001000011, 0b0001001011100100,
        0b0010001011011000, 0b1100001010010000, 0b1000001011111110, 0b0001110000110011, 0b0011011011000100,
        0b0001010110010111, 0b1010010000000101, 0b1111100101101111, 0b1011010111101011, 0b1111111111101010,
        0b1010000010110001, 0b1110011000100000, 0b1111100111000000, 0b0001100001001000, 0b1011011101100101,
        0b0101000011000001, 0b0010001001110111, 0b0110111100110011, 0b1100101001110001, 0b1110110001000011,
        0b1111001010010011, 0b1000001101100100, 0b0111011000111100, 0b1010001001001001, 0b0001011110111001,
        0b0101111011111001, 0b1011100110111110, 0b1000111000011000, 0b0000001000111010, 0b1011010000100010,
        0b1000110110111111, 0b1010100011100101, 0b1000001000000100, 0b1100110010101000, 0b0001100100110111,
        0b1111110100011000, 0b1111111010001111, 0b0100110111110110, 0b1101101100101001, 0b1101001011101110,
        0b0100000111010011, 0b1001000100001011, 0b1010111000111111, 0b0100010111000001, 0b1011111011110001,
        0b1101101110100110, 0b0110111001110110, 0b0011011000001101, 0b1110111000011011, 0b0101011011011101,
        0b1110011001001010, 0b0110010100101010, 0b0101010101010101, 0b1010010111011010, 0b1110011011000101,
        0b1101100110110010, 0b0010001010001011, 0b1101101011001010, 0b0001111000100111, 0b0111101000111001,
        0b1111100101010000, 0b0101010000111001, 0b1101010110001011, 0b1010101011110001, 0b1100111011111001,
        0b0010000001101111, 0b1110100100001011, 0b1101000111111100, 0b1110000110010101, 0b0111110011100101,
        0b0101101111110111, 0b1101110111000101, 0b0110100111101111, 0b0110100011010110, 0b0110010110111111,
        0b0100111011110111, 0b0100000101000011, 0b1101110101111010, 0b1100110011010001, 0b1011111111110001,
        0b0101001001111111, 0b1001010011111010, 0b0100110100001100, 0b0000101110110010, 0b1111110100011101,
        0b1010100101011100, 0b1100101110000001, 0b0001101010100110, 0b0010101100000011, 0b1001001111110101,
        0b0011101011000100, 0b0001100101011101, 0b0110000111110010, 0b1011001110010010, 0b0101111101001001,
        0b0110110100101101, 0b0010100100101011, 0b0000110001101011, 0b1000000110110000, 0b0101110001011011,
        0b1100110101101011, 0b1100010011000101, 0b1111100110100011, 0b0001100110110100, 0b1000101101000101,
        0b0111111000011011, 0b1100111100001100, 0b1000000101011001, 0b1011011011101100, 0b0000000011100010,
        0b0101010010000000, 0b0001010111010111, 0b1000011001110011, 0b1000011111001100, 0b1010101100101011,
        0b1000011010000000, 0b1100101001000001, 0b1111010111100101, 0b0101001001101010, 0b1100101110110100,
        0b0101010011010011, 0b0000110110001101, 0b0001101010101010, 0b1110000111000110, 0b0110010010111111,
        0b1100011100101110, 0b1011101111001111, 0b1010011001111011, 0b0010100101111000, 0b0001010000110001,
        0b0001110101101001, 0b0011101001010001, 0b0000001011111111, 0b1000010101101011, 0b1000100000101101,
        0b0100101000101010, 0b1111000001010111, 0b1010000110011110, 0b1000011010110110, 0b1011011010000101,
        0b1010111010111001, 0b0110010001001111, 0b1011100000010010, 0b1001100011010011, 0b1100110111101011,
        0b1000000000101001, 0b0000010011100101, 0b0010010000110100, 0b0111100110010001, 0b1010101111111011,
        0b1110100010000111, 0b1101011000001100, 0b0001000100010101, 0b1100011110001110, 0b1110111000011000,
        0b0110010001101100, 0b1001101110011000, 0b1101101001010000, 0b1111110111110001, 0b0001010000111000,
        0b1000000001111111, 0b0100101101101100, 0b0011111010011010, 0b1101111000010100, 0b1001110110000010,
        0b0111101100001111, 0b0000110001001101, 0b1111010111101001, 0b1001100010101111, 0b0011110011111110,
        0b1010100100111001, 0b1010111100011111, 0b1101110100100011, 0b0111101100101100, 0b0010111111000111,
        0b1011011101101010, 0b1010100010110101, 0b1010100011101111, 0b0010110110100011, 0b1100000001000111,
        0b1001101000101000, 0b0000111011000011, 0b0101101011000010, 0b0001101001101001, 0b1011010111101101,
        0b1001101010001000, 0b0101101100010100, 0b1001100011010101, 0b1010100010001001, 0b0111101110001100,
        0b0111101000010000, 0b0111010101111101, 0b0001101001010101, 0b0110011010001110, 0b1100110100111011,
        0b1110111000101110, 0b0001100010101000, 0b1100000011000100, 0b1110110001110101, 0b1000000000000000};
    prbs_lfsr::lfsr_library<uint16_t, 0b0001000010000001, 0b1101011100011011> lfsr;
    std::vector<uint16_t> calculated_output = lfsr.calculate_lsfr();
    std::vector<uint16_t> pruned_calcualted_output;
    pruned_calcualted_output.push_back(calculated_output[calculated_output.size() - 5]);
    pruned_calcualted_output.push_back(calculated_output[calculated_output.size() - 4]);
    pruned_calcualted_output.push_back(calculated_output[calculated_output.size() - 3]);
    pruned_calcualted_output.push_back(calculated_output[calculated_output.size() - 2]);
    pruned_calcualted_output.push_back(calculated_output[calculated_output.size() - 1]);
    std::vector<uint16_t> pruned_expected_output;
    pruned_expected_output.push_back(expected_output[expected_output.size() - 5]);
    pruned_expected_output.push_back(expected_output[expected_output.size() - 4]);
    pruned_expected_output.push_back(expected_output[expected_output.size() - 3]);
    pruned_expected_output.push_back(expected_output[expected_output.size() - 2]);
    pruned_expected_output.push_back(expected_output[expected_output.size() - 1]);
    ASSERT_EQ(pruned_calcualted_output, pruned_expected_output);
}
TEST(LFSR32, LFSR32_PARTIAL)
{
    prbs_lfsr::lfsr_library<uint32_t, 0b0001000010000001, 0b1101011100011011> lfsr;
    std::vector<uint32_t> expected_output{0b00011101011010110000000111011000, 0b00011000111101100110110001011011};
    ASSERT_EQ(lfsr.calculate_lsfr(2), expected_output);
}

TEST(LFSR, INCORRECT_INITIAL_VALUE)
{
    prbs_lfsr::lfsr_library<uint32_t, 0b0001000010000001, 0> lfsr;
    ASSERT_THROW(lfsr.calculate_lsfr(), std::invalid_argument);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}