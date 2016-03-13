/********************************************************
The MIT License (MIT)

Copyright (c) 2016 Daniel Drywa, Matt Champion

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

#include "attempt06.h"

namespace rwp {
    CAttempt06::CAttempt06() {
    }

    CAttempt06::~CAttempt06() {
    }

    std::string CAttempt06::GetName() const {
        return "(STL) Stores reversed words against a boolean.";
    }

    void CAttempt06::Run( const std::string &filename, sAttemptResult &result ) {
        std::unordered_map< std::string, bool > reversedWords;

        std::string word = {};
        std::ifstream file = {};
        std::unordered_map< std::string, bool >::iterator iter;

        completeClock->Start();
        readingClock->Start();
        file.open( filename, std::ios_base::in );
        if ( file.is_open() ) {
            algorithmClock->Start();
            while ( file >> word ) {
                // Attempt to find the word in the reversed words
                iter = reversedWords.find( word );
                if ( iter != std::end( reversedWords ) ) {
                    // If the current word is found the reverse of it must have
                    // been seen previously, change the boolean stored against
                    // it to true
                    iter->second = true;
                } else {
                    // If the the current word is not found store false against
                    // the reversed word
                    std::string reversedWord = std::string( word.rbegin(), word.rend() );
                    reversedWords[ reversedWord ] = false;
                }
            }
            algorithmClock->End();
        } else {
            std::cout << "Error: Couldn't open the input file: " << filename << std::endl;
        }
        file.close();
        readingClock->End();
        completeClock->End();

        // After the clock is stopped copy the map of reversed words to booleans
        // to the map of words to reversed words
        // The result file could be written directly from the reversed words to
        // boolean map
        auto &pairs = result.pairs;
        result.pairs.clear();
        for ( auto &pair : reversedWords ) {
            if ( pair.second ) {
                std::string unreversedWord = std::string( pair.first.rbegin(), pair.first.rend() );
                result.pairs[ unreversedWord ] = std::string( pair.first );
            }
        }

        result.algorithmDuration    = algorithmClock->GetDuration();
        result.readingDuration      = readingClock->GetDuration();
        result.completeDuration     = completeClock->GetDuration();
    }
}
