pub mod attempt1;

use std::io;
use std::io::Write;
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

fn run_attempt<F>( filename : &str, attempt : &F ) -> ( usize, u64 )
    where F : Fn( &File ) -> usize {

    let file = File::open( filename ).unwrap();
    let now = Instant::now();
    let result = attempt( &file );

    ( result, now.elapsed().as_msecs() )
}

fn repeat_attempt<F>( times : u64, filename : &str, attempt : &F ) -> Result<( usize, u64 ), &'static str>
    where F : Fn( &File ) -> usize {

    let mut time : u64 = 0;
    let mut count : usize = 0;

    for _ in 0..times {
        print!( "." );

        let ( c, ms ) = run_attempt( filename, attempt );

        time += ms;

        if count == 0 {
            count = c;
        } else if c != count {
            return Err( "Found pairs different from previous run." );
        }

        std::io::stdout().flush().unwrap();
    }

    Ok( ( count, time / times ) )
}

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
