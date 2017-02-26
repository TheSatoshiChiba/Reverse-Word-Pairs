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

        fn insert_word_pair( pairs : &mut HashMap<String, u32>, word : &str ) {
            if let Entry::Occupied( mut x ) = pairs.entry( String::from( word ) ) {
                *x.get_mut() += 1;
                return;
            }

            pairs.entry( reverse_word( &word ) ).or_insert( 0 );
        }

        pub fn run( file : &File ) -> usize {
            let mut pairs : HashMap<String, u32> = HashMap::new();
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

            pairs.iter().filter( |x| *x.1 > 0 ).count()
        }
    }
}

use std::fs::File;

fn run_attempt<F>( name : &str, attempt : F )
    where F : Fn( &File ) -> usize {

    println!( "Starting attempt {}", name );
    let file = File::open( "data/TheReverseWordTest.txt" ).unwrap();

    let result = attempt( &file );
    println!(
        "Finished attempt {} in {}ms with {} pairs found.",
        name,
        0,
        result );
}

fn main() {
    run_attempt( "#1", attempt::attempt1::run );


    // let pairs = search_file( &file );
    // let mut pair_count = 0;

    // for ( key, count ) in pairs {
    //     pair_count += 1;
    //     print!(
    //         "[{}/{} - {}]",
    //         key,
    //         reverse_word( &key ),
    //         count );
    // }
    // println!( "" );
    // println!( "Pairs: {}", pair_count );
}
