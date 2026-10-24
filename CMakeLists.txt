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
    src/models/OrderItem.cpp
    src/models/Order.cpp
    src/models/Payment.cpp
    src/models/CashPayment.cpp
    src/models/CardPayment.cpp
    src/models/UPIPayment.cpp
    src/services/MenuService.cpp
)

# Create executable
add_executable(serveflow ${SOURCES})