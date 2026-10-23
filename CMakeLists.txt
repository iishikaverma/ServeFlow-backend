cmake_minimum_required(VERSION 3.20)

project(ServeFlow)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header files
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/models/MenuItem.cpp
    src/models/Customer.cpp
)

# Create executable
add_executable(serveflow ${SOURCES})