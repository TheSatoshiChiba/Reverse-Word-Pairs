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

#ifndef __REVERSE_WORD_PAIRS_ATTEMPT_MANAGER_H
#define __REVERSE_WORD_PAIRS_ATTEMPT_MANAGER_H

#include <vector>
#include <memory>
#include "attempt.h"

namespace rwp {
    class CAttemptManager final {
    public:
        CAttemptManager();
        ~CAttemptManager();

        CAttemptManager( const CAttemptManager& ) = delete;
        CAttemptManager& operator=( const CAttemptManager& ) = delete;

        CAttemptManager( CAttemptManager &&other );
        CAttemptManager& operator=( CAttemptManager &&other );

        void AddAttempt( attempt_t &&attempt );
        void RunAttempts() const;

    private:
        std::vector< attempt_t > attempts;
    };

    typedef std::unique_ptr< CAttemptManager > attemptManager_t;

    inline attemptManager_t CreateAttemptManager() {
        return std::make_unique< CAttemptManager >();
    }
}
#endif
