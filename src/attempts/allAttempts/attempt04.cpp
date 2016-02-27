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
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

#include "attempt04.h"

namespace rwp {
    CAttempt04::CAttempt04() {
    }

    CAttempt04::~CAttempt04() {
    }

    std::string CAttempt04::GetName() const {
        return "(STL)find and sort while reading (map instead of unordered_map)";
    }

    void CAttempt04::Run( const std::string &filename, sAttemptResult &result ) {
        typedef std::map< std::string, std::string > map_t;
        result.pairs.clear();

        std::string     word    = {};
        std::string     revWord = {};
        std::ifstream   file    = {};
        map_t           pairs   = {};
        map_t::iterator iter;

        completeClock->Start();
        readingClock->Start();
        file.open( filename, std::ios_base::in );
        if ( file.is_open() ) {
            // The basic first algorithm attempt
            algorithmClock->Start();
            while ( file >> word ) {
                revWord.assign( word.rbegin(), word.rend() );
                iter = pairs.find( revWord );
                if ( iter != std::end( pairs ) ) {
                    iter->second = word;
                } else {
                    pairs[ word ] = "";
                }
            }
            algorithmClock->End();
        } else {
            std::cout << "Error: Couldn't open the input file: " << filename << std::endl;
        }
        file.close();
        readingClock->End();
        completeClock->End();

        for ( auto &pair : pairs ) {
            result.pairs[ pair.first ] = pair.second;
        }

        result.algorithmDuration    = algorithmClock->GetDuration();
        result.readingDuration      = readingClock->GetDuration();
        result.completeDuration     = completeClock->GetDuration();
    }
}
