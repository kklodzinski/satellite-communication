#include "ccsds_space_packet.hpp"

namespace ccsds_space_packet
{

space_packet::space_packet(const std::vector<std::byte> &raw_data)
{
    std::memcpy(&primary_header, raw_data.data(), sizeof(primary_header_s));
    payload.insert(payload.begin(), raw_data.begin() + sizeof(primary_header_s), raw_data.end());
}
space_packet::space_packet(const primary_header_s &primary_header, const std::vector<std::byte> &payload)
    : primary_header(primary_header), payload(payload)
{
}
primary_header_s space_packet::get_primary_header()
{
    return primary_header;
}
std::vector<std::byte> space_packet::get_payload()
{
    return payload;
}
std::vector<std::byte> space_packet::get_raw_packet()
{
    std::vector<std::byte> output(sizeof(primary_header_s));
    uint32_t offset = sizeof(primary_header_s);
    std::memcpy(output.data(), &primary_header, offset);
    output.insert(output.end(), payload.begin(), payload.end());
    return output;
}
} // namespace ccsds_space_packet