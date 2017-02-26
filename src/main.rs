mod attempt {
    pub mod attempt1 {
        use std::fs::File;
        use std::io::prelude::*;
        use std::iter::FromIterator;
        use std::collections::HashMap;
        use std::collections::hash_map::Entry;

        fn reverse_word( word : &str ) -> String {
            String::from_iter( word.chars().rev() )
        }

        fn insert_word_pair( pairs : &mut HashMap<String, bool>, word : &str ) {
            if let Entry::Occupied( mut x ) = pairs.entry( String::from( word ) ) {
                *x.get_mut() = true;
                return;
            }

            pairs.entry( reverse_word( &word ) ).or_insert( false );
        }

        pub fn run( file : &File ) -> usize {
            let mut pairs : HashMap<String, bool> = HashMap::new();
            let mut word = String::with_capacity( 1024 );

            for byte in file.bytes() {
                let c = char::from( byte.unwrap() );

                if c.is_whitespace() {
                    insert_word_pair( &mut pairs, &word );
                    word.clear();
                } else {
                    word.push( c );
                }
            }

            pairs.iter().filter( |x| *x.1 ).count()
        }
    }
}

use std::fs::File;
use std::time::{Duration, Instant};

fn run_attempt<F>( name : &str, attempt : F ) -> u64
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

fn main() {
    let mut average : u64 = 0;
    let count = 100;

    for _ in 0..count {
        average += run_attempt( "#1", attempt::attempt1::run );
    }

    println!("Average of {} runs: {}ms", count, average / count );
}
