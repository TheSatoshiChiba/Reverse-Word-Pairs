pub mod attempt1;

use std::fs::File;
use std::time::Instant;

pub fn run<F>( name : &str, filename : &str, attempt : &F ) -> u64
    where F : Fn( &File ) -> usize {

    println!( "Starting attempt {}", name );

    let file = File::open( filename ).unwrap();
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

pub fn repeat<F>( name : &str, filename : &str, count : u64, attempt : &F ) -> u64
    where F : Fn( &File ) -> usize {

    println!( "Starting repeated run of attempt {}. It will run {} time(s)", name, count );

    let mut time : u64 = 0;

    for _ in 0..count {
        time += run( name, filename, attempt );
    }

    let average = time / count;

    println!("Attempt {} stopped after {} runs with an average of {}ms", name, count, average );

    average
}

pub fn run_all( count : u32, file : &File ) {
    // let mut attempts = Vec::new();
    // attempts.push( attempt1::run );

    // let mut id = 0;
    // for attempt in &attempts {
    //     id += 1;
    //     run( "Attempt #" + id, file, )
    // }
}
