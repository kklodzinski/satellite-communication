file(GLOB_RECURSE CCSDS_SPACE_PACKET_SOURCES "*.cpp")

# Add library target with all source files in the directory
add_library(ccsds_space_packet ${CCSDS_SPACE_PACKET_SOURCES})
