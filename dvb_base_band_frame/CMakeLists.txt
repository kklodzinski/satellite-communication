#DVB_BASE_BAND_FRAME
file(GLOB_RECURSE DVB_BASE_BAND_FRAME_SOURCES "*.cpp")

# Add library target with all source files in the directory
add_library(dvb_base_band_frame ${DVB_BASE_BAND_FRAME_SOURCES})

target_link_libraries(dvb_base_band_frame PUBLIC crc_library)

target_include_directories(dvb_base_band_frame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})