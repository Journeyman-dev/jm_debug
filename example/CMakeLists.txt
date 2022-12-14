# SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: MIT

add_executable(jm_debug_example "")
add_subdirectory(src)
target_link_libraries(jm_debug_example
    PUBLIC
        jm::debug    
)
set_target_properties(jm_debug_example
        PROPERTIES
        OUTPUT_NAME "jm_debug_example"
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
)