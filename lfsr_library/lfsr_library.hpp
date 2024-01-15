#ifndef LFSR_LIBRARY
#define LFSR_LIBRARY

#include <array>
#include <vector>
#include <cstdint>
#include <optional>
#include <stdexcept>

namespace prbs_lfsr
{

template <class T>
concept valid_lfsr_type = std::same_as<T, uint32_t> || std::same_as<T, uint16_t> || std::same_as<T, uint8_t>;

template <valid_lfsr_type T, T xor_polynomial, T initial_value> class lfsr_library
{
  private:
    static constexpr T T_bit_size = sizeof(T) * 8;
    // PRECOMPUTE PARITY BITS, Alternativly you could use __builtin_parity(x) but this approach is way more fun
    static constexpr std::array<T, 256> create_LUT() noexcept
    {
        std::array<T, 256> table;
        for (int i = 0; i < table.size(); ++i)
        {
            T parity = 0;
            T byte   = i;
            while (byte)
            {
                parity ^= (byte & 0b1);
                byte >>= 1;
            }
            table[i] = parity;
        }
        return table;
    }
    static constexpr std::array<T, 256> lookup_table = create_LUT();

  public:
    std::vector<T> calculate_lsfr(std::optional<T> size_of_output = std::nullopt)
    {
        if (initial_value == 0)
        {
            throw std::invalid_argument("Initial value cannot be equal to 0!");
        }

        std::vector<T> output;
        T state_value = initial_value;
        T new_block   = 0;

        for (T i = 0; !(size_of_output.has_value()) || i < size_of_output.value() * T_bit_size; ++i)
        {
            T parity = 0;
            T temp   = state_value;
            T temp_xor_map = xor_polynomial;
            while (temp)
            {
                T lookup_value = temp & 0xFF & temp_xor_map;
                parity ^= lookup_table[lookup_value];
                temp >>= sizeof(uint8_t)*8; // Shift by one byte;
                temp_xor_map >>= sizeof(uint8_t)*8;
            }

            new_block = (new_block << 1) ^ parity;

            if ((i + 1) % T_bit_size == 0)
            {
                output.push_back(new_block);
                new_block = 0;
            }
            
            state_value = (parity << T_bit_size - 1) | (state_value >> 1);

            if (!size_of_output.has_value() && state_value == initial_value)
            {
                if (new_block != 0)
                {
                    new_block<<= (T_bit_size-(i+1)%T_bit_size);
                    output.push_back(new_block);
                }
                break;
            }
        }
        return output;
    }
};

} // namespace prbs_lfsr
#endif