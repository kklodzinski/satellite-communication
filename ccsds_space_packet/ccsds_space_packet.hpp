#ifndef CCSDS_SPACE_PACKET
#define CCSDS_SPACE_PACKET

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

namespace ccsds_space_packet
{
enum class packet_type_e : bool
{
    telemtery = 0,
    telecommands = 1
};

enum class secondary_header_flag_e : bool
{
    not_present = 0,
    present = 1
};

enum class sequence_flags_e : uint8_t
{
    contnuation_segment = 0b00,
    first_segment = 0b01,
    last_segment = 0b10,
    unsegmented = 0b11
};

struct [[gnu::packed]] primary_header
{
    uint8_t packet_version_number : 3;
    packet_type_e packet_type : 1;
    secondary_header_flag_e secondary_header_flag : 1;
    uint8_t APID : 11;
    sequence_flags_e sequence_flags : 2;
    uint16_t packet_sequence_count : 14;
    uint16_t packet_data_length;
};

class space_packet
{
  protected:
    primary_header space_packet_primary_header;
    std::vector<std::byte> space_packet_raw_packet;

  public:
    space_packet(std::vector<std::byte> raw_data);
    primary_header get_primary_header();
    std::vector<std::byte> get_raw_packet();
};

} // namespace ccsds_space_packet
#endif