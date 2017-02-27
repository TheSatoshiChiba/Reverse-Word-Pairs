pub mod attempt1;

use std::fs::File;
use std::time::{Duration, Instant};

trait AsMilliseconds {
    fn as_msecs( &self ) -> u64;
}

impl AsMilliseconds for Duration {
    fn as_msecs( &self ) -> u64 {
        ( self.as_secs() * 1000 ) + ( self.subsec_nanos() / 1_000_000 ) as u64
    }
}

pub fn run<F>( filename : &str, attempt : &F ) -> u64
    where F : Fn( &File ) -> usize {

    let file = File::open( filename ).unwrap();
    let now = Instant::now();
    let result = attempt( &file );

    now.elapsed().as_msecs()
}

pub fn repeat<F>( name : &str, filename : &str, count : u64, attempt : &F ) -> u64
    where F : Fn( &File ) -> usize {

    println!( "Starting repeated run of attempt {}. It will run {} time(s)", name, count );

    let mut time : u64 = 0;

    for _ in 0..count {
        time += run( filename, attempt );
    }

    let average = time / count;

    println!("Attempt {} stopped after {} runs with an average of {}ms", name, count, average );

    average
}

pub fn run_all<F>( attempts : &Vec<F>, count : u64, filename : &str ) -> Vec<u64>
    where F : Fn( &File ) -> usize {

    println!( "Running all {} attempts {} times.", attempts.len(), count );

    let mut id = 0;
    let mut results = Vec::new();
    for attempt in attempts {
        id += 1;
        let mut name = String::from( "#" );
        name.push_str( &id.to_string() );

        results.push( repeat( &name, filename, count, &attempt ) );
    }

    println!( "Finished all {} attempts. Results:", attempts.len() );

    results
}
