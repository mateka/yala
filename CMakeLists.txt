cmake_minimum_required(VERSION 3.16)
project(
        yala VERSION 1.0.0 LANGUAGES CXX
        HOMEPAGE_URL "https://github.com/mateka/yala"
        DESCRIPTION "Yet Another Linear Algebra library"
)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Enable BUILD_TESTING option
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()


# Project dependencies
include(FetchContent)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR YALA_BUILD_TESTING) AND BUILD_TESTING)
    FetchContent_Declare(
            catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.11.1
    )
    FetchContent_MakeAvailable(catch2)
endif()


# Library definition
add_library(
    yala
    src/hello.cpp
    include/yala/constexpr_math.h
    include/yala/vec.h
    include/yala/normal.h
    include/yala/matrix.h
)
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

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR YALA_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
