extern crate rust_attempts;

use std::fs::File;

fn main() {
    rust_attempts::repeat( "#1", "data/TheReverseWordTest.txt", 100, &rust_attempts::attempt1::run );
}
