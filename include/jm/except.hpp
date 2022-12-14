// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef JM_EXCEPT_HPP
#define JM_EXCEPT_HPP

#include <fmt/format.h>
#include <stdexcept>
#include <jm/enum_class_formatter.hpp>

namespace jm
{
    // throw a runtime error, but fmt library style
    template<typename... Args>
    std::runtime_error runtime_error(const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        return std::runtime_error(fmt::format(fmt, std::forward<Args>(args)...));
    }
}

#endif
