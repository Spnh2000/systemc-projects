cmake_minimum_required(VERSION 3.10)

project(moving_average)

# Remember only one sc_main() function should exist.

add_executable(moving_average
    moving_average_main.cpp
)

target_include_directories(moving_average
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY
            NAMES systemc
            PATHS
                /usr/local/systemc/lib
                /usr/local/systemc/lib64
                /usr/local/systemc/lib-linux64
            REQUIRED
)

target_link_libraries(moving_average
    PRIVATE ${SYSTEMC_LIBRARY}
)
