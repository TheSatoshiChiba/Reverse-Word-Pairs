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
#include <cstdint>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>

#include "attemptManager.h"

namespace rwp {
    CAttemptManager::CAttemptManager() :
        attempts() {
    }

    CAttemptManager::~CAttemptManager() {
    }

    CAttemptManager::CAttemptManager( CAttemptManager &&other ) :
        attempts( std::move( other.attempts ) ) {
    }

    CAttemptManager& CAttemptManager::operator=( CAttemptManager &&other ) {
        std::swap( attempts, other.attempts );
        return *this;
    }

    void CAttemptManager::AddAttempt( attempt_t &&attempt ) {
        attempts.push_back( std::move( attempt ) );
    }

    void CAttemptManager::RunAttempts() const {
        sAttemptResult  result;
        std::ofstream   file;
        std::uint32_t   count   = 0;
        std::string     name    = {};
        std::string     inputf  = "data/TheReverseWordTest.txt";

        for ( auto &attempt : attempts ) {
            if ( attempt ) {
                ++count;
                std::cout << "Attempt #" << count << " \"" << attempt->GetName() << "\"" << std::endl;
                // We run every attempt 100 times to see variation in timing
                for ( std::uint32_t i = 0; i < 100; ++i ) {
                    attempt->Run( inputf, result );
                    std::cout << " -> Algo " << i << ": nanosec( "
                            << result.algorithmDuration.nanoseconds.count()
                            << " ) microsec( "
                            << result.algorithmDuration.microseconds.count()
                            << " ) millisec( "
                            << result.algorithmDuration.milliseconds.count()
                            << " ) sec( "
                            << result.algorithmDuration.seconds.count()
                            << " ). " << std::endl;
                    std::cout << " -> Read " << i << ": nanosec( "
                            << result.readingDuration.nanoseconds.count()
                            << " ) microsec( "
                            << result.readingDuration.microseconds.count()
                            << " ) millisec( "
                            << result.readingDuration.milliseconds.count()
                            << " ) sec( "
                            << result.readingDuration.seconds.count()
                            << " ). " << std::endl;
                    std::cout << " -> All  " << i << ": nanosec( "
                            << result.completeDuration.nanoseconds.count()
                            << " ) microsec( "
                            << result.completeDuration.microseconds.count()
                            << " ) millisec( "
                            << result.completeDuration.milliseconds.count()
                            << " ) sec( "
                            << result.completeDuration.seconds.count()
                            << " ). " << std::endl;
                }

                // Write Output of the last pass
                name = "data/result_" + std::to_string( count ) + ".txt";
                file.open( name, std::ios_base::out );
                if ( !file.is_open() ) {
                    std::cout << "Couldn't write result file!" << std::endl;
                } else {
                    for ( auto &pair : result.pairs ) {
                        if ( pair.second != "" ) {
                            file << pair.first << " " << pair.second << std::endl;
                        }
                    }
                }
                file.close();

                std::cout << "Output filename: " << name << std::endl;
                std::cout << std::endl;
            }
        }
    }
}
