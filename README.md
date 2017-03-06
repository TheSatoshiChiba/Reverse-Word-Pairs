Reverse-Word-Pairs
==================

This was my attempt at a programming challenge I did a few years ago. The goal was to find all reverse pairs in a text file, in the fastest way possible. I tried out a few ideas and measured the average runtime to find out which one would be the fastest and then used it in the main_final.cpp. If you can come up with a faster algorithm feel free to add it to this repository with a pull request.

This repository also contains a Rust version. For more information see the 'Rust Version' paragraph in this file.

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

Rust Version
------------
There is a rust version of this challenge now which can be build by running `cargo build` in the parent directory of this repository. The rust version comes in two parts. The main executable under `src/main.rs`. And the rust_attempts library which contains the basic attempts API and the attempts itself. The Attempts API is different from the C++ one as it only contains a single function that accepts a name, the number of times the attempts needs to run, the filename of the file that contains all the words and a function of type `Fn( &File ) -> usize` where the return value is the number of word pairs found. The function itself returns a `Result<AttemptResult>`. The only time this function fails is if the found word pairs differ between the runs. `AttemptResult` contains the number of word pairs found and the average runtime in milliseconds. To run the executable simply use `cargo run` in the parent directory of this repository.

Unlike the C++ version there is no file output. It is entirely console based.

To add a new attempt simply create a new module within the rust_attempts library with a public run function of type `Fn( &File ) -> usize` and pass it to the `rust_attempts::run` function in the main file. It will take care of the correct console output and time measurements.

Why Rust?
---------
So why exactly is there a Rust version in the same repository as the C++ version? Simply put I wanted to learn rust and this programming challenge seemed like the best way to start with it. But creating a new repository for a Rust version of this program seemed a bit redundant. So here we are :)

LICENSE
-------
See [LICENSE](LICENSE) file.
