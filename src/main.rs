extern crate rust_attempts;

fn main() {
    let mut attempts = vec![ rust_attempts::attempt1::run ];

    rust_attempts::run( &attempts, 100, "data/TheReverseWordTest.txt" );
}
