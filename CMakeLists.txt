cmake_minimum_required(VERSION 3.20)

project(ServeFlow CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies (via vcpkg toolchain). Crow bundles standalone asio.
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Threads REQUIRED)

# Shared model/service/util sources.
set(CORE_SOURCES
    src/models/MenuItem.cpp
    src/models/Customer.cpp
    src/models/OrderItem.cpp
    src/models/Order.cpp
    src/models/Payment.cpp
    src/models/CashPayment.cpp
    src/models/CardPayment.cpp
    src/models/UPIPayment.cpp
    src/services/MenuService.cpp
    src/services/OrderService.cpp
    src/utils/FileManager.cpp
)

# Console demo app
add_executable(serveflow src/main.cpp ${CORE_SOURCES})
target_include_directories(serveflow PRIVATE include)
target_link_libraries(serveflow PRIVATE nlohmann_json::nlohmann_json)

# REST API server (deployed target)
add_executable(serveflow_api src/api.cpp ${CORE_SOURCES})
target_include_directories(serveflow_api PRIVATE include)
target_link_libraries(serveflow_api PRIVATE
    Crow::Crow
    nlohmann_json::nlohmann_json
    Threads::Threads
)

# Windows needs the Winsock libraries; Linux/Docker does not.
if(WIN32)
    target_link_libraries(serveflow_api PRIVATE ws2_32 mswsock)
endif()
