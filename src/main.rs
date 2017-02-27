extern crate rust_attempts;

fn main() {
    let mut average : u64 = 0;
    let count = 100;

    for _ in 0..count {
        average += rust_attempts::run_attempt( "#1", rust_attempts::attempt1::run );
    }

    println!("Average of {} runs: {}ms", count, average / count );
}
