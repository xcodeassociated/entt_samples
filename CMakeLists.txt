cmake_minimum_required(VERSION 3.5)
project(entt_samples)

option(ENTT_ROOT "ENTT root directory" NONE)

set(MASTER_BUILD_TYPES "Debug Release RelWithDebInfo MinSizeRel")
string(REPLACE " " ";" MASTER_BUILD_TYPES_AVAILABLE ${MASTER_BUILD_TYPES})
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${MASTER_BUILD_TYPES_AVAILABLE})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

if (NOT MSVC)
    ## C++ 20 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb3")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -g")
else()
    set(CMAKE_CXX_STANDARD 17)

    message (STATUS "MSVC ${MSVC_VERSION}v")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /W2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /O2")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_MACOSX_RPATH OFF)
endif()

if (NOT ENTT_ROOT)
    message(STATUS "ENTT_ROOT not specified, setting defult: ${CMAKE_SOURCE_DIR}/entt")
    set(ENTT_ROOT "${CMAKE_SOURCE_DIR}/entt")
endif()

add_subdirectory(${ENTT_ROOT})
include_directories("${ENTT_ROOT}/src")

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} entt_overview)
