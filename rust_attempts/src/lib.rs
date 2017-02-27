pub mod attempt1;

use std::fs::File;
use std::time::Instant;

pub fn run_attempt<F>( name : &str, attempt : F ) -> u64
    where F : Fn( &File ) -> usize {

    println!( "Starting attempt {}", name );

    let file = File::open( "data/TheReverseWordTest.txt" ).unwrap();
    let now = Instant::now();
    let result = attempt( &file );
    let duration = now.elapsed();
    let time = ( duration.as_secs() * 1000 ) + ( duration.subsec_nanos() / 1_000_000 ) as u64;

    println!(
        "Finished attempt {} in {}ms with {} pairs found.",
        name,
        time,
        result );

    time
}

pub fn run_all( count : u32, file : &File ) {
}
