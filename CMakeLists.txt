project(plugin-manager)

cmake_minimum_required(VERSION 3.12)

find_package(Threads REQUIRED)

include_directories(
    service/include/
)

add_executable(plugin-manager-service service/src/main.cpp)

target_link_libraries(plugin-manager-service
    Threads::Threads
)
