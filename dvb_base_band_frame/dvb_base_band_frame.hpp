#ifndef BASE_BAND_FRAME
#define BASE_BAND_FRAME

#include <crc_library/crc_library.hpp>
#include <lfsr_library/lfsr_library.hpp>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace digital_video_broadasting
{
enum class transport_stream_input_e : uint8_t
{
    transport          = 0b11,
    generic_packetized = 0b00,
    generic_continuous = 0b01,
    reserved           = 0b10
};

enum class single_input_stream_e : bool
{
    single   = 0b1,
    multiple = 0b0
};

enum class constant_coding_and_modulation_e : bool
{
    ccm = 0b1,
    acm = 0b0
};

enum class input_stream_synchronization_indicator_e : bool
{
    active     = 0b1,
    not_active = 0b0
};

enum class null_packet_deletion_e : bool
{
    active     = 0b1,
    not_active = 0b0
};

enum class transmition_roll_off_factor_e : uint8_t
{
    alpha_0_35 = 0b00,
    alpha_0_25 = 0b01,
    alpha_0_20 = 0b10,
    reserved   = 0b11
};

struct [[gnu::packed]] matype_s
{
    transport_stream_input_e transport_stream_input                                 : 2;
    single_input_stream_e single_input_stream                                       : 1;
    constant_coding_and_modulation_e constant_coding_and_modulation                 : 1;
    input_stream_synchronization_indicator_e input_stream_synchronization_indicator : 1;
    null_packet_deletion_e null_packet_deletion                                     : 1;
    transmition_roll_off_factor_e transmition_roll_off_factor                       : 2;
    uint8_t matype_2                                                                : 8;
};

struct [[gnu::packed]] base_band_header_s
{
    matype_s matype;
    uint16_t user_packet_length;
    uint16_t data_field_length;
    uint8_t user_packet_sync;
    uint16_t sync_distance;
    uint8_t crc_8;
};

class base_band_frame
{
  protected:
    crc_library::crc<uint8_t, 0xD5, 0x00, false, false, 0x00> crc;
    base_band_header_s base_band_header;
    std::vector<std::byte> data_field;

  public:
    base_band_frame(const std::vector<std::byte> &raw_data);
    base_band_frame(const base_band_header_s &base_band_header, const std::vector<std::byte> &data_field);
    base_band_header_s get_base_band_header();
    std::vector<std::byte> get_data_field();
    std::vector<std::byte> get_raw_packet(const size_t &packet_length);
    std::vector<std::byte> get_scrambled_packet(const size_t &packet_length);
};
} // namespace digital_video_broadasting

#endif