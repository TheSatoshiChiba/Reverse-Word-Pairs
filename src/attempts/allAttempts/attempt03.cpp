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
#include <algorithm>

#include "attempt03.h"

namespace rwp {
    CAttempt03::CAttempt03() {
    }

    CAttempt03::~CAttempt03() {
    }

    std::string CAttempt03::GetName() const {
        return "(STL)Sort while reading. Find later with std::find().";
    }

    void CAttempt03::Run( const std::string &filename, sAttemptResult &result ) {
        auto &pairs = result.pairs;
        pairs.clear();

        std::string             word        = {};
        std::string             revWord     = {};
        std::ifstream           file        = {};

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
        std::vector< std::string >::const_iterator iter;
        for ( auto &group : groups ) {
            while ( group.second.size() > 0 ) {
                word = group.second.back();
                group.second.pop_back();
                revWord.assign( word.rbegin(), word.rend() );
                iter = std::find( group.second.begin(), group.second.end(), revWord );
                if ( iter != group.second.end() ) {
                    result.pairs[ word ] = revWord;
                    group.second.erase( iter );
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
