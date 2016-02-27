/********************************************************
The MIT License (MIT)

Copyright (c) 2014, 2016 Daniel Drywa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
********************************************************/
#pragma once

#ifndef __REVERSE_WORD_PAIRS_ATTEMPTS_ATTEMPT_CLOCK_H
#define __REVERSE_WORD_PAIRS_ATTEMPTS_ATTEMPT_CLOCK_H

#include <chrono>
#include <memory>

#include "attemptResult.h"

namespace rwp {
    class CAttemptClock {
    private:
        typedef std::chrono::steady_clock       internal_clock_t;
        typedef internal_clock_t::time_point    time_point_t;

        time_point_t    start       = {};
        time_point_t    end         = {};
        bool            isRunning   = false;

    public:
        CAttemptClock() {
        }

        ~CAttemptClock() {
        }

        void Start() {
            if ( !isRunning ) {
                start = internal_clock_t::now();
                isRunning = true;
            }
        }

        void End() {
            if ( isRunning ) {
                end = internal_clock_t::now();
                isRunning = false;
            }
        }

        sTimeDuration GetDuration() const {
            sTimeDuration   result;
            auto            diff = end - start;

            result.nanoseconds  = std::chrono::duration_cast< std::chrono::nanoseconds >( diff );
            result.microseconds = std::chrono::duration_cast< std::chrono::microseconds >( diff );
            result.milliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( diff );
            result.seconds      = std::chrono::duration_cast< std::chrono::seconds >( diff );
            return result;
        }
    };

    typedef std::unique_ptr< CAttemptClock > attemptClock_t;
    inline attemptClock_t CreateAttemptClock() {
        return std::make_unique< CAttemptClock >();
    }
}

#endif
