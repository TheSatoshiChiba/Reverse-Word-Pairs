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

int main( int argc, char const *argv[] ) {
    typedef std::unordered_map< std::string, std::string > wordPairs_t;

    std::string             word        = {};
    std::string             revWord     = {};
    std::ifstream           inFile      = {};
    wordPairs_t::iterator   iter;
    wordPairs_t             pairs;

    // Read and sort
    inFile.open( "data/TheReverseWordTest.txt", std::ios_base::in );
    if ( inFile.is_open() ) {
        // The basic first algorithm attempt
        while ( inFile >> word ) {
            revWord.assign( word.rbegin(), word.rend() );
            iter = pairs.find( revWord );
            if ( iter != std::end( pairs ) ) {
                iter->second = word;
            } else {
                pairs[ word ] = "";
            }
        }
    } else {
        std::cout << "Error: Couldn't open the input file: data/TheReverseWordTest.txt" << std::endl;
    }
    inFile.close();

    // Write
    std::ofstream ofFile;
    std::string name = "data/result_final.txt";
    ofFile.open( name, std::ios_base::out );
    if ( !ofFile.is_open() ) {
        std::cout << "Couldn't write result file!" << std::endl;
    } else {
        for ( auto &pair : pairs ) {
            if ( pair.second != "" ) {
                ofFile << pair.first << " " << pair.second << std::endl;
            }
        }
    }
    ofFile.close();
    return 0;
}
