cmake_minimum_required(VERSION 3.21)
project(satellite_communication LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(ccsds_space_packet)
add_subdirectory(ccsds_space_packet_tests)
add_subdirectory(base_band_frame)
add_subdirectory(crc_library)
add_subdirectory(crc_library_tests)