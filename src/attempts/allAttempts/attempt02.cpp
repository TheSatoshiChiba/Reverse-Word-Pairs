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
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "attempt02.h"

namespace rwp {
    CAttempt02::CAttempt02() {
    }

    CAttempt02::~CAttempt02() {
    }

    std::string CAttempt02::GetName() const {
        return "(STL)Sort while reading. Find later.";
    }

    void CAttempt02::Run( const std::string &filename, sAttemptResult &result ) {
        auto &pairs = result.pairs;
        pairs.clear();

        std::string             word        = {};
        std::string             revWord     = {};
        std::ifstream           file        = {};
        wordPairs_t::iterator   iter;

        std::unordered_map< std::size_t, std::vector< std::string > > groups;

        completeClock->Start();
        readingClock->Start();
        file.open( filename, std::ios_base::in );
        if ( file.is_open() ) {
            while ( file >> word ) {
                groups[ word.size() ].push_back( word );
            }
        } else {
            std::cout << "Error: Couldn't open the input file: " << filename << std::endl;
        }
        file.close();
        readingClock->End();

        algorithmClock->Start();
        for ( auto &group : groups ) {
            while ( group.second.size() > 0 ) {
                word    = group.second.back();
                group.second.pop_back();
                for ( auto &candidate : group.second ) {
                    if ( candidate.back() == word.front() ) {
                        revWord.assign( candidate.rbegin(), candidate.rend() );
                        if ( revWord == word ) {
                            result.pairs[ word ] = candidate;
                            break;
                        }
                    }
                }
            }
        }
        algorithmClock->End();
        completeClock->End();

        result.algorithmDuration = algorithmClock->GetDuration();
        result.readingDuration = readingClock->GetDuration();
        result.completeDuration = completeClock->GetDuration();
    }
}
