extern crate rust_attempts;

use std::fs::File;

fn main() {
    let mut attempts = vec![ rust_attempts::attempt1::run ];

    let results = rust_attempts::run_all( &attempts, 100, "data/TheReverseWordTest.txt" );
    let mut count = 0;
    for result in results {
        count += 1;
        println!( "Attempt #{} ran for an average of {}ms.", count, result );
    }
}
