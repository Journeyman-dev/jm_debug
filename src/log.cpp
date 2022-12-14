// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

/*
    Copyright (c) 2022 Daniel Aimé Valcour
    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in
    the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <jm/log.hpp>
#include <jm/enum_class_formatter.hpp>
#include <string>
#include <optional>
#include <functional>
#include <fmt/format.h>
#include <chrono>

struct LogData
{
    std::optional<jm::message_callback> message_callback = std::nullopt;
    jm::LogLevel filter = jm::LogLevel::Trace;

    constexpr LogData() noexcept = default;
};

static LogData sLOG_DATA = LogData();

std::string_view jm::get_datetime_string()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto time_str = std::ctime(&time);
    // remove the newline at the end.
    if (time_str[0] != '\0')
    {
        time_str[24] = '\0';
    }
    return time_str;
}

void jm::set_message_callback(jm::message_callback callback)
{
    sLOG_DATA.message_callback = callback;
}

void jm::set_log_filter(jm::LogLevel filter)
{
    sLOG_DATA.filter = filter;
}

jm::LogLevel jm::get_log_filter()
{
    return sLOG_DATA.filter;
}

void jm::log_no_filter(jm::LogLevel level, std::string_view message)
{
    if (sLOG_DATA.message_callback.has_value())
    {
        sLOG_DATA.message_callback.value()(level, message);
    }
}

bool jm::filter_test(jm::LogLevel level)
{
    return level >= sLOG_DATA.filter;
}

void jm::log(jm::LogLevel level, std::string_view message)
{
    if (sLOG_DATA.message_callback.has_value() && filter_test(level))
    {
        sLOG_DATA.message_callback.value()(level, message);
    }
}

void jm::info(std::string_view message)
{
    jm::log(jm::LogLevel::Info, message);
}

void jm::trace(std::string_view message)
{
    jm::log(jm::LogLevel::Trace, message);
}

void jm::debug(std::string_view message)
{
    jm::log(jm::LogLevel::Debug, message);
}

void jm::warn(std::string_view message)
{
    jm::log(jm::LogLevel::Warning, message);
}

void jm::error(std::string_view message)
{
    jm::log(jm::LogLevel::Error, message);
}

void jm::crit(std::string_view message)
{
    jm::log(jm::LogLevel::Critical, message);
}
