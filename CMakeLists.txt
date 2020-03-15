cmake_minimum_required(VERSION 3.16)
project(
        yala VERSION 1.0.0 LANGUAGES CXX
        HOMEPAGE_URL "https://github.com/mateka/yala"
        DESCRIPTION "Yet Another Linear Algebra library"
)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)


# Project dependencies


# Library definition
add_library(yala src/hello.cpp include/yala/hello.h)
add_library(${PROJECT_NAME}::yala ALIAS yala)
target_include_directories(
        yala
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
)
target_compile_features(yala INTERFACE cxx_std_20)
set_target_properties(
        yala
        PROPERTIES
            CXX_EXTENSIONS OFF
            CXX_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN YES

            SOVERSION ${PROJECT_VERSION_MAJOR}
            VERSION ${PROJECT_VERSION}
            $<IF:APPLE,,INSTALL_RPATH $ORIGIN>
)

include(GenerateExportHeader)
generate_export_header(yala EXPORT_FILE_NAME include/yala/yala_export.h)


# Install part
include(install/install)

add_subdirectory(bin)
add_subdirectory(tests)
