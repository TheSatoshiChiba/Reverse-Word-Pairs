extern crate rust_attempts;

use rust_attempts::run;

fn main() {
    run( "hash_map_1", 10, "data/TheReverseWordTest.txt", &rust_attempts::attempt1::run );
    //run( "hash_map_2", 10, "data/TheReverseWordTest.txt", &rust_attempts::attempt2::run );
}
