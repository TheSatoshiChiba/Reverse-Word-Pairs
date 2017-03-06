//! This is the second reverse_word attempt.
//! It is only a simple improvement over the first one by changing the
//! reverse_word function a bit. The previous version would create a String
//! from an iterator via String::from_iter. from_iter doesn't know how big the
//! iterator is but we certainly do because of the &str parameter. This
//! method simply creates an empty string with a given capacity and pushes the
//! characters in one by one.

use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;
use std::collections::hash_map::Entry;

fn reverse_word( word : &str ) -> String {
    let mut result = String::with_capacity( word.len() );

    for c in word.chars().rev() {
        result.push( c );
    }

    result
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
