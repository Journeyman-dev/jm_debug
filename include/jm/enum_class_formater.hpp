// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef JM_ENUM_CLASS_FORMAT_HPP
#define JM_ENUM_CLASS_FORMAT_HPP

#include <fmt/format.h>
#include <magic_enum.hpp>
#include <type_traits>

template <typename T>
requires magic_enum::is_scoped_enum<T>::value
struct fmt::formatter<T>
{
  template <typename ParseContext> constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }
  template <typename FormatContext> auto format(T const& value, FormatContext& ctx)
  {
    return fmt::format_to(ctx.out(), "{}", magic_enum::enum_name(value));
  }
};

#endif
