cmake_minimum_required(VERSION 3.24)
project(luacxx-counter-binding LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(luacxx CONFIG REQUIRED)

add_executable(luacxx-counter-binding
  main.cpp
  counter_lua.cpp
)

target_link_libraries(luacxx-counter-binding PRIVATE luacxx::luacxx)
