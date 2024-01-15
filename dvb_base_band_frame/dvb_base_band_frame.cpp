#include "dvb_base_band_frame.hpp"
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
        std::string error_message = "CRC check failed! ";
        throw std::runtime_error(error_message);
    }
    uint32_t offset = sizeof(base_band_header_s);
    // Get the data_field from the bytes without the padding
    data_field.insert(data_field.begin(), raw_data.begin() + offset,
                      raw_data.begin() + offset + base_band_header.data_field_length);
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

std::vector<std::byte> base_band_frame::get_raw_packet(const size_t &packet_length)
{
    uint32_t offset = sizeof(base_band_header_s);
    std::vector<std::byte> output(offset);
    std::memcpy(output.data(), &base_band_header, sizeof(base_band_header_s));
    output.insert(output.end(), data_field.begin(), data_field.end());
    if (output.size() != packet_length)
    {
        std::vector<std::byte> padding(packet_length - output.size(), std::byte(0x0));
        output.insert(output.end(), padding.begin(), padding.end());
    }
    return output;
}

std::vector<std::byte> base_band_frame::get_scrambled_packet(const size_t &packet_length)
{
    std::vector<std::byte> output;

    std::vector<std::byte> raw_packet = base_band_frame::get_raw_packet(packet_length);
    prbs_lfsr::lfsr_library<uint16_t, 0b11, 0b100101010000000> lfsr;
    std::vector<uint16_t> lfsr_bits =  lfsr.calculate_lsfr(packet_length/sizeof(uint16_t)); //get correct number of bits
    
    std::vector<std::byte> temp(packet_length,std::byte(0x0));
    std::memcpy(temp.data(), lfsr_bits.data(), temp.size());

    for(size_t i =0; i< raw_packet.size();++i)
    {
        output.push_back(raw_packet[i]^temp[i]);
    }

    return output;
}

} // namespace digital_video_broadasting