# rw

This repo contains a collection of code/utilties/libraries that I have found
or found useful for my game development and graphics projects. I found myself writing common code
across all these projects so I decided to clean up and factor out the code into
a single repo which all current (and future) projects can use. This repo will also
continue to grow along with me.

The design of these libraries and choices of which functions to implement
are influenced by many great libraries I have seen and used (see
[Inspirations](#inspirations)). Although I have taken influence from these sources,
I have designed and coded my libraries to suit my needs and my tastes.

## Table of Contents  

- [Files](#files)
- [General Usage Instructions](#general-usage-instructions)
- [Inspirations](#inspirations)

## Files

| File           | Version | Description                                                        |
|----------------|---------|--------------------------------------------------------------------|
| rw_types.h     | 0.2.0   | Defines or redefines common types                                  |
| rw_math.h      | 0.2.0   | Math library for games/graphics                                    |
| rw_transform.h | 0.2.0   | Matrix transformation data structure and functions (pbrt inspired) |
| rw_time.h      | 0.2.0   | High resolution timer (nanoseconds) and other related utilities    |
| rw_memory.h    | 0.1.0   | Custom memory allocation                                           |

## General Usage Instructions

All files are designed to be single(ish)-file headers. Usage is like Sean Barrett's
[stb](https://github.com/nothings/stb) library. To reduce code repetition a little bit,
some libraries depend on others. For example, `rw_transform.h` depends on `rw_math.h`.

For specific usage instructions, please see the header block comment for the file of interest.

Generally, include the header file and define the library specific preprocessor value
to include the implementation as well. Note that including just the header file, will **NOT**
include the implementation. 

For example,
```
#define RWNAMESPACE_IMPLEMENTATION
#include <rw_mylib.h>
```

Other options in place of `RWNAMESPACE_IMPLEMENTATION` are: 
```
#define RWNAMESPACE_HEADER_ONLY
// OR
#define RWNAMESPACE_STATIC
```

Some libaries also have specific defines that can be included beforehand to
change some of the implementation details of the library.
For example (in `rw_math.h`),
```
// To use the fast inverse sqrt intrinsic, also include before
#define RWM_USE_MM_RSQRT
```

## TODO

rw_mesh.h - Migrate OBJ loader/mesh code from other projects here
rw_buffer.h - Dynamic buffers, ring buffers etc.
rw_sort.h - Various sorting algorithms
rw_hashtable.h - Hashtable

## Inspirations

- [Handmade Hero](https://handmadehero.org/)
- [nothings/stb](https://github.com/nothings/stb)
- [raysan5/raylib](https://github.com/raysan5/raylib)
- [koekeishiya/chunkwm](https://github.com/koekeishiya/chunkwm)
