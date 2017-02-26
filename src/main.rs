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

fn search_file( file : &File ) -> HashMap<String, u32> {
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

    pairs
}

fn main() {
    let file = File::open( "data/TheReverseWordTest.txt" ).unwrap();
    let pairs = search_file( &file );

    for ( key, count ) in pairs {
        println!(
            "{}/{} - {}",
            key,
            reverse_word( &key ),
            count );
    }
}
