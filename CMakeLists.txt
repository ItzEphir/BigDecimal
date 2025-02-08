cmake_minimum_required(VERSION 3.25)
project(BigDecimal)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        BigDecimal main.cpp
        src/BigDecimal.cpp
        include/BigDecimal.h
)
