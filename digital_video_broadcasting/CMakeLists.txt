file(GLOB_RECURSE DIGITAL_VIDEO_BROADCASTING_SOURCES "*.cpp")

# Add library target with all source files in the directory
add_library(digital_video_broadcasting ${DIGITAL_VIDEO_BROADCASTING_SOURCES})

target_include_directories(digital_video_broadcasting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(digital_video_broadcasting PRIVATE crc_library)