cmake_minimum_required(VERSION 3.24)

project(luacxx
  VERSION 4.0.0
  LANGUAGES CXX
)

option(BUILD_TESTING "Enable unit tests" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Warnings (optional) ----
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# ---- Dependencies ----
find_package(Lua 5.2 REQUIRED)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.70 REQUIRED COMPONENTS unit_test_framework)

# ---- Library ----
add_library(luacxx)

target_sources(luacxx
  PRIVATE
    src/algorithm.cpp
    src/log.cpp
    src/error.cpp
    src/reference.cpp
    src/load.cpp
    src/stack.cpp
    src/thread.cpp
    src/convert/callable.cpp
    src/convert/const_char_p.cpp
    src/convert/char.cpp
    src/convert/numeric.cpp

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/luacxx/algorithm.hpp
      include/luacxx/log.hpp
      include/luacxx/stack.hpp
      include/luacxx/enum.hpp
      include/luacxx/link.hpp
      include/luacxx/index.hpp
      include/luacxx/error.hpp
      include/luacxx/global.hpp
      include/luacxx/load.hpp
      include/luacxx/range.hpp
      include/luacxx/reference.hpp
      include/luacxx/thread.hpp
      include/luacxx/type.hpp
      include/luacxx/value.hpp
      include/luacxx/convert/callable.hpp
      include/luacxx/convert/char.hpp
      include/luacxx/convert/char_p.hpp
      include/luacxx/convert/const_char_p.hpp
      include/luacxx/convert/numeric.hpp
      include/luacxx/convert/shared_ptr.hpp
      include/luacxx/convert/string.hpp
      include/luacxx/convert/vector.hpp
      include/luacxx/convert/void.hpp
      include/luacxx/std/vector.hpp
)

target_include_directories(luacxx
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${LUA_INCLUDE_DIR}
)

target_compile_features(luacxx PUBLIC cxx_std_20)

target_link_libraries(luacxx
  PUBLIC
    ${LUA_LIBRARIES}
  PRIVATE
    project_warnings
)

# ---- Tests ----
include(CTest)

if(BUILD_TESTING)
  enable_testing()

  add_executable(luacxx_test_main
    tests/main.cpp
    tests/main.hpp
    tests/luacxx_convert_vector.cpp
  )

  add_executable(luacxx_test_without_conversion
    tests/luacxx_without_conversions.cpp
    tests/main.hpp
  )

  target_link_libraries(luacxx_test_main
    PRIVATE
      luacxx
      Boost::unit_test_framework
      project_warnings
  )

  target_link_libraries(luacxx_test_without_conversion
    PRIVATE
      luacxx
      Boost::unit_test_framework
      project_warnings
  )

  add_test(NAME luacxx.test_main COMMAND luacxx_test_main)
  add_test(NAME luacxx.test_without_conversion COMMAND luacxx_test_without_conversion)
endif()

# ---- (Optional) Install rules for the library ----
# include(GNUInstallDirs)
# install(TARGETS myproj
#   EXPORT MyProjectTargets
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(EXPORT MyProjectTargets
#   NAMESPACE MyProject::
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyProject
# )
