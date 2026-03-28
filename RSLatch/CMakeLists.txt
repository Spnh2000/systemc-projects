cmake_minimum_required(VERSION 3.10)

project(rslatch)

# Remember only one sc_main() function should exist.

add_executable(rslatch
    rslatch_main.cpp
)

target_include_directories(rslatch
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

target_link_libraries(rslatch
    PRIVATE ${SYSTEMC_LIBRARY}
)
