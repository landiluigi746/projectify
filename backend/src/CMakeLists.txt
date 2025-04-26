file(GLOB_RECURSE PROJECTIFY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(projectify ${PROJECTIFY_SOURCES})

target_include_directories(projectify PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

target_link_libraries(
    projectify
    PRIVATE
    ZLIB::ZLIB
    Crow::Crow
    taocpp::taopq
    fmt
    spdlog
    sodium
    jwt-cpp::jwt-cpp
)

set(OPTIONS_WARNINGS -Wall -Wpedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OPTIONS_OPTIMIZATION -O2)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPTIONS_OPTIMIZATION -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(OPTIONS_OPTIMIZATION -O2 -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(OPTIONS_OPTIMIZATION -Os)
endif()

message(STATUS "Compiler options: ${OPTIONS_WARNINGS} ${OPTIONS_OPTIMIZATION}")

target_compile_options(projectify PRIVATE ${OPTIONS_WARNINGS} ${OPTIONS_OPTIMIZATION})

target_precompile_headers(
    projectify
    PRIVATE
    <string>
    <string_view>
    <format>
    <regex>
    <optional>
    <utility>
    <memory>
    <mutex>
    <exception>
    <vector>
    <unordered_map>
    <chrono>
    ${CMAKE_SOURCE_DIR}/cfg/Config.hpp
)
