# SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: MIT

# Copyright (c) 2022 Daniel Aimé Valcour
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.24.1)
project(jm_debug
        VERSION 0.0.0.0
        DESCRIPTION "Journeyman's debugging library."
)
option(JM_DEBUG_BUILD_EXAMPLE "Build the jm_debug example project." ON)
add_library(${PROJECT_NAME} STATIC "")
add_library(jm::debug ALIAS ${PROJECT_NAME})
add_subdirectory(src)
target_include_directories(${PROJECT_NAME}
        PUBLIC
                "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
Include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        9.1.0
        FIND_PACKAGE_ARGS
)
FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG        v0.8.1
        FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(fmt magic_enum)
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
