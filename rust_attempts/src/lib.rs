//! A module for reverse-word-pairs attempts.

pub mod attempt1;

use std::io::Write;
use std::fs::File;
use std::time::{Duration, Instant};

/// The trait that returns the current struct as milliseconds.
trait AsMilliseconds {
    /// Returns the current struct as milliseconds.
    fn as_msecs( &self ) -> u64;
}

/// The `AsMilliseconds` trait implementation for `std::time::Duration`.
impl AsMilliseconds for Duration {
    /// Returns the current `std::time::Duration` as milliseconds.
    fn as_msecs( &self ) -> u64 {
        ( self.as_secs() * 1000 ) + ( self.subsec_nanos() / 1_000_000 ) as u64
    }
}

/// Flushes the standard console output.
fn flush_console() {
    std::io::stdout().flush().unwrap();
}

/// The result of a single attempt
struct AttemptResult {
    /// The number of found pairs
    pairs : usize,

    /// The runtime of the attempt in milliseconds
    runtime : u64,
}

/// Runs a single attempt against a specified file name.
///
/// #Arguments
///
/// * `filename` - The name of the file to use for this attempt.
/// * `attempt` - The attempt function of type `Fn( &File ) -> usize`.
fn run_attempt<F>( filename : &str, attempt : &F ) -> AttemptResult
    where F : Fn( &File ) -> usize {

    let file = File::open( filename ).unwrap();
    let now = Instant::now();
    let pairs = attempt( &file );
    let runtime = now.elapsed().as_msecs();

    AttemptResult { pairs : pairs, runtime : runtime }
}

/// Runs a single attempt a given number of times and returns the average result.
///
/// This function also returns the amount of word pairs found. If between any
/// run the number of found pairs differs it will return Err( &str ).
///
/// # Arguments
///
/// * `times` - The number of times the attempt will be run.
/// * `filename` - The name of the file to use for this attempt.
/// * `attempt` - The attempt function of type `Fn( &File ) -> usize`.
fn repeat_attempt<F>( times : u64, filename : &str, attempt : &F ) -> Result<( usize, u64 ), &'static str>
    where F : Fn( &File ) -> usize {

    let mut time : u64 = 0;
    let mut count : usize = 0;

    for _ in 0..times {
        print!( "." );

        let result = run_attempt( filename, attempt );

        time += result.runtime;

        if count == 0 {
            count = result.pairs;
        } else if result.pairs != count {
            return Err( "Found pairs different from previous run." );
        }

        flush_console();
    }

    Ok( ( count, time / times ) )
}

/// Runs a given vector of attempts a given number of times and prints the results to the console.
pub fn run<F>( attempts : &Vec<F>, times : u64, filename : &str )
    where F : Fn( &File ) -> usize {

    println!( "Running all {} attempts {} times.", attempts.len(), times );

    let mut id = 0;
    for attempt in attempts {
        id += 1;

        print!("Attempt #{}", id );
        match repeat_attempt( times, filename, &attempt ) {
            Ok( ( size, average ) ) => println!( "OK [Pairs: {}, Average: {}ms]", size, average ),
            _ => println!( "FAILED" )
        }
    }
}
