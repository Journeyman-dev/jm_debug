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

/* Modified from debug_trap.h, copied from the Portable Snippets repository.
 * Created by Evan Nemerson <evan@nemerson.com>
 * URL: https://github.com/nemequ/portable-snippets
 */

#ifndef JM_DEBUG_BREAK_HPP
#define JM_DEBUG_BREAK_HPP

#if defined(__has_builtin) && !defined(__ibmxl__)
#  if __has_builtin(__builtin_debugtrap)
#    define JM_DEBUG_BREAK() __builtin_debugtrap()
#  elif __has_builtin(__debugbreak)
#    define JM_DEBUG_BREAK() __debugbreak()
#  endif
#endif
#if !defined(JM_BREAK)
#  if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#    define JM_DEBUG_BREAK() __debugbreak()
#  elif defined(__ARMCC_VERSION)
#    define JM_DEBUG_BREAK() __breakpoint(42)
#  elif defined(__ibmxl__) || defined(__xlC__)
#    include <builtins.h>
#    define JM_DEBUG_BREAK() __trap(42)
#  elif defined(__DMC__) && defined(_M_IX86)
     static inline void JM_DEBUG_BREAK(void) { __asm int 3h; }
#  elif defined(__i386__) || defined(__x86_64__)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__("int3"); }
#  elif defined(__thumb__)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__(".inst 0xde01"); }
#  elif defined(__aarch64__)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__(".inst 0xd4200000"); }
#  elif defined(__arm__)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__(".inst 0xe7f001f0"); }
#  elif defined (__alpha__) && !defined(__osf__)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__("bpt"); }
#  elif defined(_54_)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__("ESTOP"); }
#  elif defined(_55_)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP"); }
#  elif defined(_64P_)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__("SWBP 0"); }
#  elif defined(_6x_)
     static inline void JM_DEBUG_BREAK(void) { __asm__ __volatile__("NOP\n .word 0x10000000"); }
#  elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
#    define JM_DEBUG_BREAK() __builtin_trap()
#  else
#    include <signal.h>
#    if defined(SIGTRAP)
#      define JM_DEBUG_BREAK() raise(SIGTRAP)
#    else
#      define JM_DEBUG_BREAK() raise(SIGABRT)
#    endif
#  endif
#endif

namespace jm
{
     inline void debug_break() noexcept
     {
          JM_DEBUG_BREAK();
     }
}

#endif
