cmake_minimum_required(VERSION 2.8.12)
project("DateExample")

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(--std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(--std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

message(STATUS "Configuring Date example...")
file(GLOB DATE_EXAMPLE_SOURCES_CXX "*.cxx")
file(GLOB DATE_EXAMPLE_SOURCES_CPP "*.cpp")

add_executable(DateExample ${DATE_EXAMPLE_SOURCES_CXX} ${DATE_EXAMPLE_SOURCES_CPP})
target_link_libraries(DateExample fastrtps fastcdr)
install(TARGETS DateExample
    RUNTIME DESTINATION examples/C++/DateExample/${BIN_INSTALL_DIR})
