cmake_minimum_required(VERSION 3.10)
project(aes_ofb_project)

set(CMAKE_CXX_STANDARD 17)

# Include directory
include_directories(include)

# Source files
set(SOURCES 
    src/aes.cpp
    src/ofb.cpp
    src/utils.cpp
    src/main.cpp
)

# Executable
add_executable(aes_ofb ${SOURCES})