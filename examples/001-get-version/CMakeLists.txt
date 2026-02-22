cmake_minimum_required(VERSION 3.24)
project(luacxx-get-versions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(luacxx CONFIG REQUIRED)

add_executable(luacxx-get-versions main.cpp)
target_link_libraries(luacxx-get-versions PRIVATE luacxx::luacxx)
