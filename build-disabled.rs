// Copyright 2016 Mozilla Foundation. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// https://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or https://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

extern crate cheddar;

use std::io::prelude::*;
use std::fs::File;

fn replace(path: &str) -> std::io::Result<()> {
    let mut f = try!(File::open(path));
    let mut s = String::new();
    try!(f.read_to_string(&mut s));
    s = s.replace("uint16_t", "char16_t");
    s = s.replace("uintptr_t", "size_t");
    s = s.replace("#include <stdbool.h>",
                  "#include <stdbool.h>\n#include \"encoding_rs_statics.h\"");
    let mut f = try!(File::create(path));
    try!(f.write_all(s.as_bytes()));
    Ok(())
}

fn main() {
    println!("cargo:rerun-if-changed=src/lib.rs");
    
    let path = "target/include/encoding_rs.h";

    cheddar::Cheddar::new()
        .expect("could not read manifest")
        .insert_code("// Copyright 2015-2016 Mozilla Foundation. See the COPYRIGHT\n")
        .insert_code("// file at the top-level directory of this distribution.\n")
        .insert_code("//\n")
        .insert_code("// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or\n")
        .insert_code("// https://www.apache.org/licenses/LICENSE-2.0> or the MIT license\n")
        .insert_code("// <LICENSE-MIT or https://opensource.org/licenses/MIT>, at your\n")
        .insert_code("// option. This file may not be copied, modified, or distributed\n")
        .insert_code("// except according to those terms.\n")
        .insert_code("\n")
        .insert_code("// THIS IS A GENERATED FILE. PLEASE DO NOT EDIT.\n")
        .insert_code("// Instead, please regenerate using encoding_c/build.rs.\n")
        .run_build(path);

    match replace(path) {
        Ok(_) => {}
        Err(e) => println!("Performing replacements failed {}.", e),
    }
}
