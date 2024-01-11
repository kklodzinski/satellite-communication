#include <array>
#include <cstdint>
#include <span>

namespace crc_library
{

template <class T>
concept valid_crc_type = std::same_as<T, uint32_t> || std::same_as<T, uint16_t> || std::same_as<T, uint8_t>;

template <valid_crc_type T, T polynomial, T initial_value, bool reflection_in, bool reflection_out, T final_xor>
class crc
{
  private:
    static constexpr T size = sizeof(T) * 8;
    static constexpr std::array<T, 256> create_LUT() noexcept
    {
        std::array<T, 256> table;
        for (int byte = 0; byte < 256; ++byte)
        {
            T remainder = byte;
            for (size_t bit = size; bit > 0; --bit)
            {
                if (remainder & (1 << (size - 1)))
                {
                    remainder = (remainder << 1) ^ polynomial;
                }
                else
                {
                    remainder = (remainder << 1);
                }
            }
            table[byte] = remainder;
        }
        return table;
    }
    static constexpr std::array<T, 256> lookup_table = create_LUT();
    static constexpr T reverse_bits(T num, T size) noexcept
    {
        T count       = sizeof(num) * 8 - 1;
        T reverse_num = num;
        num >>= 1;
        while (num)
        {
            reverse_num <<= 1;
            reverse_num |= num & 1;
            num >>= 1;
            count--;
        }
        reverse_num <<= count;
        reverse_num >>= sizeof(num) * 8 - size;
        return reverse_num;
    }

  public:
    static constexpr T calculate_crc(std::span<const std::byte> data) noexcept
    {
        T crc = initial_value;
        for (size_t i = 0; i < data.size(); i++)
        {
            uint8_t byte;
            if (reflection_in)
            {
                T reversed = reverse_bits(static_cast<T>(data[i]), size) >> (size - 8);
                byte       = reversed ^ (crc >> (size - 8));
            }
            else
            {
                byte = static_cast<T>(data[i]) ^ (crc >> (size - 8));
            }
            crc = (crc << 8) ^ lookup_table[byte];
        }
        if (reflection_out)
        {
            return (reverse_bits(crc, size) ^ final_xor);
        }
        else
        {
            return (crc ^ final_xor);
        }
    }
};
} // namespace crc_library