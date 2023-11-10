project(plugin-manager)

cmake_minimum_required(VERSION 3.12)

find_package(Threads REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(
    service/include/
    client/include/
)

add_executable(plugin-manager-service
    service/src/main.cpp
)

target_link_libraries(plugin-manager-service
    Threads::Threads
    spdlog::spdlog_header_only
)
