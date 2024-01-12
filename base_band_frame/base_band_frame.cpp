#include "base_band_frame.hpp"
namespace digital_video_broadasting
{
base_band_frame::base_band_frame(const std::vector<std::byte> &raw_data)
{
    // Get the header from the bytes
    std::memcpy(&base_band_header, raw_data.data(), sizeof(base_band_header_s));

    // Check if the crc is correct
    size_t header_size_without_crc = sizeof(base_band_header_s) - sizeof(base_band_header_s::crc_8);
    std::vector<std::byte> check_header_crc(header_size_without_crc);
    std::memcpy(check_header_crc.data(), &base_band_header, header_size_without_crc);
    if (crc.calculate_crc(check_header_crc) != base_band_header.crc_8)
    {
        throw std::runtime_error("CRC check failed!");
    }
    // Get the data_field from the bytes without the padding
    data_field.insert(data_field.begin(), raw_data.begin(), raw_data.begin() + base_band_header.data_field_length);
}

base_band_frame::base_band_frame(const base_band_header_s &header, const std::vector<std::byte> &data)
    : base_band_header(header), data_field(data)
{
    // Set the data_filed_length based on the provided data_filed
    base_band_header.data_field_length = data_field.size();
    // Calculate and set the crc_8 value in header
    size_t header_size_without_crc = sizeof(base_band_header_s) - sizeof(base_band_header_s::crc_8);
    std::vector<std::byte> calculate_header_crc(header_size_without_crc);
    std::memcpy(calculate_header_crc.data(), &base_band_header, header_size_without_crc);
    base_band_header.crc_8 = crc.calculate_crc(calculate_header_crc);
}

base_band_header_s base_band_frame::get_base_band_header()
{
    return base_band_header;
}

std::vector<std::byte> base_band_frame::get_data_field()
{
    return data_field;
}

std::vector<std::byte> base_band_frame::get_raw_packet(const uint &packet_length)
{
    uint32_t offset = sizeof(base_band_header_s);
    std::vector<std::byte> output(sizeof(offset));
    std::memcpy(output.data(), &base_band_header, offset);
    output.insert(output.end(), data_field.begin(), data_field.end());
    if (output.size() != packet_length)
    {
        std::vector<std::byte> padding(output.size() - packet_length, std::byte(0x0));
        output.insert(output.end(), padding.begin(), padding.end());
    }
    return output;
}

} // namespace digital_video_broadasting