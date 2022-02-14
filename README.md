# rpgp-ffi

This is mostly a recovery of the official ffi crate in the [rpgp/rpgp](github.com/rpgp/rpgp) repo,
which was removed at https://github.com/rpgp/rpgp/commit/acd03461abb4025e28f56bf385725f5cf61080b4.

## Build lib

`Cargo build --release`

This will produce a library in `./target/release` (exact name, or rather extension, is
platform dependant). You can then link the shared library. Also, a header file will
be produced here `./librpgp.h`, which contains the exported symbols and functions.
The header file is auto generated.

## Building example C program

To verify the library works, an example C program is here, which just calls some
exported methods. Building it **on linux**:

`gcc -I./header main.c ./target/release/librpgp_ffi.so -o test`

It can then be executed (`./test`), to verify everything works correctly.
