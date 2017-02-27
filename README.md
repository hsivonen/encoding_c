# encoding_c

[![Apache 2 / MIT dual-licensed](https://img.shields.io/badge/license-Apache%202%20%2F%20MIT-blue.svg)](https://github.com/hsivonen/encoding_rs/blob/master/COPYRIGHT)

encoding_c is an FFI wrapper for [encoding_rs](https://github.com/hsivonen/encoding_rs).

## Licensing

Please see the file named
[COPYRIGHT](https://github.com/hsivonen/encoding_rs/blob/master/COPYRIGHT).

## C/C++ Headers

Upon building, a generated C header is produced into `target/include`.
Additionally, `include/encoding_rs_statics.h` is needed for C usage.

`include/encoding_rs_cpp.h` is a sample C++ API built on top of the C API using
GSL and the C++ standard library. Since C++ project typically roll their own
string classes, etc., it's probably necessary for C++ projects to manually
adapt the header to their replacements of standard-library types.

## Release Notes

### 0.5.0

* Initial release of encoding_c. (I.e. first release with FFI in a distinct
  crate.)

