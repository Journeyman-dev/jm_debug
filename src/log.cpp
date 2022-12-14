// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

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
