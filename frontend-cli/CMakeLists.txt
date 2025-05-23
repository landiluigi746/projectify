cmake_minimum_required(VERSION 3.22)

project(projectify-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/vendor)

include(cmake/GetCPM.cmake)

CPMAddPackage(ftxui
    VERSION 6.0.2
    GITHUB_REPOSITORY ArthurSonzogni/FTXUI
)

CPMAddPackage(cpp-httplib
    GITHUB_REPOSITORY yhirose/cpp-httplib
    GIT_TAG master
    OPTIONS
    "HTTPLIB_USE_ZSTD_IF_AVAILABLE OFF"
)

CPMAddPackage(glaze
    GITHUB_REPOSITORY stephenberry/glaze
    GIT_TAG main
)

add_subdirectory(src)
