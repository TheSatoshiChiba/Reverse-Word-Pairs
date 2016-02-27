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

#ifndef __REVERSE_WORD_PAIRS_ATTEMPTS_ATTEMPT_RESULT_H
#define __REVERSE_WORD_PAIRS_ATTEMPTS_ATTEMPT_RESULT_H

#include <chrono>
#include <unordered_map>

namespace rwp {
    typedef std::unordered_map< std::string, std::string > wordPairs_t;

    struct sTimeDuration {
        std::chrono::nanoseconds    nanoseconds;
        std::chrono::microseconds   microseconds;
        std::chrono::milliseconds   milliseconds;
        std::chrono::seconds        seconds;
    };

    struct sAttemptResult {
        sTimeDuration   algorithmDuration;
        sTimeDuration   readingDuration;
        sTimeDuration   completeDuration;
        wordPairs_t     pairs;
    };
}
#endif
