Reverse-Word-Pairs
==================

This was my attempt at a programming challenge I did a few years ago. The goal was to find all reverse pairs in a text file, in the fastest way possible. I tried out a few ideas and measured the average runtime to find out which one would be the fastest and then used it in the main_final.cpp. If you can come up with a faster algorithm feel free to add it to this repository with a pull request.

The Attempts
------------
You can find all attempts in the folder src/attempts/allAttempts/

* The first attempt is sorting while reading from the file. So the file handle is open the entire time.
* The fourth attempt is the same as the first but with a std::map instead of the std::unordered_map.
* The second and the third attempt were a try to see if sorting/pairing after the reading would be faster.

Why STL?
--------
There is a notion among some programmers that the STL is too slow but to me it is integral part of modern C++. This is why I used it in all my attempts. If you can come up with an attempt that is not using the STL then feel free to send me a pull request and I'll add it to the attempts.

Why open source?
----------------
This was only a programming challenge for a job interview, so why open source it? The answer is simple: I want others to be able to learn from it. This solution got me to the next step of the interview process at a well known gaming company, which for obvious reasons I can not name.

Adding new attempts
-------------------
* A new attempt should be placed in the src/attempts/allAttempts directory. A glob is used to include the header and source files.
* A new attempt must implement the IAttempt class.
* An instance of the new attempt must be added to the attemptManager object in the src/main.cpp file.
* Three clocks are provided by the IAttempt class, the algorithmClock, readingClock and completeClock. The algorithmClock should run when checking words. The readingClock should run when reading words from the file. The completeClock should run when either clock is running.

LICENSE
-------
See [LICENSE](LICENSE) file.
