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
