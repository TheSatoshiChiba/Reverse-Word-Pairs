extern crate rust_attempts;

use rust_attempts::run;

fn main() {
    run( "hash_map_1", 100, "data/TheReverseWordTest.txt", &rust_attempts::attempt1::run );
    run( "hash_map_2", 100, "data/TheReverseWordTest.txt", &rust_attempts::attempt2::run );
}
