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
add_executable(tests crc_tests.cpp)

include(GoogleTest)

target_link_libraries(tests
PRIVATE
GTest::GTest
crc_library
--coverage)
gtest_discover_tests(tests)