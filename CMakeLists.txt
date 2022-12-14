# SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.24.1)
project(jm_debug
        VERSION 0.0.0.0
        DESCRIPTION "Journeyman's debugging library."
)
option(JM_DEBUG_BUILD_EXAMPLE "Build the jm_debug example project." ON)
option(JM_DEBUG_AUTO_FETCH "Fetch the dependencies of jm_debug automatically using FetchContent if the targets don't already exist." ON)
add_library(${PROJECT_NAME} STATIC "")
add_library(jm::debug ALIAS ${PROJECT_NAME})
add_subdirectory(src)
target_include_directories(${PROJECT_NAME}
        PUBLIC
                "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
if (NOT TARGET fmt::fmt)
        if (JM_DEBUG_AUTO_FETCH)
                message(STATUS "fmt::fmt is required link library of jm_debug and was not found. Fetching with FetchContent.")
                Include(FetchContent)
                FetchContent_Declare(
                fmt
                GIT_REPOSITORY https://github.com/fmtlib/fmt
                GIT_TAG        9.1.0
                )
                set(FMT_DOC OFF)
                set(FMT_INSTALL OFF)
                set(FMT_TEST OFF)
                set(FMT_FUZZ OFF)
                set(FMT_CUDA_TEST OFF)
                set(FMT_OS ON)
                set(FMT_MODULE OFF)
                set(FMT_SYSTEM_HEADERS OFF)
                FetchContent_MakeAvailable(fmt)
        else()
                message(SEND_ERROR "fmt::fmt is required link library of jm_debug and was not found.")
        endif()
endif()
if (NOT TARGET magic_enum::magic_enum)
        if (JM_DEBUG_AUTO_FETCH)
                message(STATUS "magic_enum::magic_enum is required link library of jm_debug and was not found. Fetching with FetchContent.")
                FetchContent_Declare(
                magic_enum
                GIT_REPOSITORY https://github.com/Neargye/magic_enum
                GIT_TAG        v0.8.1
                )
                set(MAGIC_ENUM_OPT_ENABLE_NONASCII OFF)
                set(MAGIC_ENUM_OPT_BUILD_EXAMPLES OFF)
                set(MAGIC_ENUM_OPT_BUILD_TESTS OFF)
                set(MAGIC_ENUM_OPT_INSTALL OFF)
                FetchContent_MakeAvailable(magic_enum)
        else()
                message(SEND_ERROR "magic_enum::magic_enum is a required link library of jm_debug and was not found.")
        endif()

endif()
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            fmt::fmt
            magic_enum::magic_enum
)
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "jm_debug"
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
)
if (JM_DEBUG_BUILD_EXAMPLE)
        add_subdirectory(example)
endif()
