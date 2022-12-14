// SPDX-FileCopyrightText: 2022 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <fmt/format.h>
#include <jm/log.hpp>
#include <jm/except.hpp>
#include <jm/debug_break.hpp>

int main()
{
    jm::set_message_callback(
        [](jm::LogLevel level, std::string_view message)
        {
            fmt::print("[{}] {}\n", level, message);
        }
    );
    jm::set_log_filter(jm::LogLevel::Info);
    jm::info("Logging started on {}.", jm::get_datetime_string());
    jm::info("This is an info log.");
    jm::debug("This is a debug log that wont show because of the filter.");
    jm::set_log_filter(jm::LogLevel::Debug);
    jm::debug("This log will show now because of the filter change.");
    jm::info("The current log filter is {}.", jm::get_log_filter());
    enum class OperatingSystem
    {
        Windows,
        Mac,
        Linux
    };
    jm::info("My favorite operating system is {}.", OperatingSystem::Linux);
    try
    {
        throw jm::runtime_error("this is a fancy std::{}.", "runtime_error");
    }
    catch(const std::exception& e)
    {
        jm::error("Log the exception!");
        jm::crit(e.what());
    }
    jm::info("Following this is a debug break that works with most compilers:");
    jm::debug_break();
    return 0;
}