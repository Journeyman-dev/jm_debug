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
