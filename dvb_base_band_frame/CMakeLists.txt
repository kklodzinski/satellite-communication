file(GLOB_RECURSE DIGITAL_VIDEO_BROADCASTING_SOURCES "*.cpp")

# Add library target with all source files in the directory
add_library(base_band_frame ${DIGITAL_VIDEO_BROADCASTING_SOURCES})

target_include_directories(base_band_frame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(base_band_frame PRIVATE crc_library)