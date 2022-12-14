// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef JM_LOG_HPP
#define JM_LOG_HPP

#include <string>
#include <functional>
#include <fmt/format.h>
#include <jm/enum_class_formatter.hpp>

namespace jm
{
    enum class LogLevel
    {
        // Log information about things that occur very frequently such as every frame in a game loop.
        Trace = 0,
        // Log extra info about tasks being executed to aid in debugging that isn't logged in most situations.
        Debug = 1,
        // Log helpful information that explains things about a user's device or other significant information.
        Info = 2,
        // Log something that is not desirable but also not an error.
        Warning = 3,
        // Log a error that doesn't cause a crash.
        Error = 4,
        // Log a critical message meaning the program is crashing.
        Critical = 5,
    };
    using message_callback = std::function<void(jm::LogLevel, std::string_view)>;
    std::string_view get_datetime_string();
    void set_message_callback(jm::message_callback callback);
    void set_log_filter(jm::LogLevel filter);
    jm::LogLevel get_log_filter();
    bool filter_test(jm::LogLevel level);
    void log_no_filter(jm::LogLevel level, std::string_view message);
    void log(jm::LogLevel LogLevel, std::string_view message);
    template<typename... Args>
    void log(jm::LogLevel level, const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        if (filter_test(level))
        {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            jm::log_no_filter(level, message);
        }
    }
    void trace(std::string_view message);
    template<typename... Args>
    void trace(const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        if (filter_test(jm::LogLevel::Trace))
        {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            jm::log_no_filter(jm::LogLevel::Trace, message);
        }
    }
    void debug(std::string_view message);
    template<typename... Args>
    void debug(const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        if (filter_test(jm::LogLevel::Debug))
        {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            jm::log_no_filter(jm::LogLevel::Debug, message);
        }
    }
    void info(std::string_view message);
    template<typename... Args>
    void info(const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        if (filter_test(jm::LogLevel::Info))
        {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            jm::log_no_filter(jm::LogLevel::Info, message);
        }
    }
    void warn(std::string_view message);
    template<typename... Args>
    void warn(const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        if (filter_test(jm::LogLevel::Warning))
        {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            jm::log_no_filter(jm::LogLevel::Warning, message);
        }
    }
    void error(std::string_view message);
    template<typename... Args>
    void error(const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        if (filter_test(jm::LogLevel::Error))
        {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            jm::log_no_filter(jm::LogLevel::Error, message);
        }
    }
    void crit(std::string_view message);
    template<typename... Args>
    void crit(const fmt::format_string<Args...>& fmt, Args&&...args)
    {
        if (filter_test(jm::LogLevel::Critical))
        {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            jm::log_no_filter(jm::LogLevel::Critical, message);
        }
    }
}

#endif
