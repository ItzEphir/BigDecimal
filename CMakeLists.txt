cmake_minimum_required(VERSION 3.25)
project(BigDecimal)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests test.cpp
        src/BigDecimal.cpp
        include/BigDecimal.h
        src/StringHelper.cpp
        include/StringHelper.h
        src/StringHelperTests.cpp
        src/BigDecimalTests.cpp
)

target_link_libraries(tests GTest::gtest GTest::gtest_main)

add_test(NAME Tests COMMAND tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        BigDecimal main.cpp
        src/BigDecimal.cpp
        include/BigDecimal.h
        src/StringHelper.cpp
        include/StringHelper.h
)
