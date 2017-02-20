extern crate cmake;

use cmake::Config;
use std::env;

fn main() {
    let out_dir = env::var( "OUT_DIR" ).unwrap();

    // Build CMake project
    Config::new( "" )
        .define( "CMAKE_INSTALL_PREFIX", out_dir )
        .build();
}
