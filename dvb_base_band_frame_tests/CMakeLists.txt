cmake_minimum_required(VERSION 3.21)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
add_executable(dvb_base_band_frame_tests dvb_base_band_frame_tests.cpp)

include(GoogleTest)

target_link_libraries(dvb_base_band_frame_tests
PRIVATE
GTest::GTest
dvb_base_band_frame
--coverage)
gtest_discover_tests(dvb_base_band_frame_tests)