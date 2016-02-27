Reverse-Word-Pairs
==================

This was my attempt at a programming challenge I did a few years ago. The goal was to find all reverse pairs in a text file, in the fastest way possible. I tried out a few ideas and measured the average runtime to find out which one would be the fastest and then used it in the main_final.cpp. If you can come up with a faster algorithm feel free to add it to this repository with a pull request.

The Attempts
------------
You can find all attempts in the folder src/attempts/allAttempts/

* The first attempt is sorting while reading from the file. So the file handle is open the entire time.
* The fourth attempt is the same as the first but with a std::map instead of the std::unordered_map.
* The second and the thrid attempt were a try to see if sorting/pairing after the reading would be faster.

Why STL?
--------
There is a notion among some programmers that the STL is to slow but to me it is integral part of modern C++. This is why I used it in all my attempts. If you can come up with an attempt that is not using the STL then feel free to send me a pull request and I'll add it to the attempts.

Why open source?
----------------
This was only a programming challenge for a job interview, so why open source it? The answer is simple: I want others to be able to learn from it. This solution got me to the next step of the interview process at a well known gaming company, which for obvious reasons I can not name.

LICENSE
-------
See [LICENSE](LICENSE) file.
