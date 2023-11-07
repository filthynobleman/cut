![CMake multi-platform](https://github.com/filthynobleman/cut/actions/workflows/cmake-multi-platform.yml/badge.svg)

# CUT: a C++ Utility Toolkit
*CUT* is a C++ library designed to provide a set of general purpose tools to ease the producetion of codebases and cut depelopment time (pun intended).  
While I'm developing the library to conduct research projects under Windows environment, I'm trying to do my best for keeping it general and making it cross-platform.


## Building and installing
### Library
At the current state, CUT is a static library that needs to be built and installed.  

The building process is carried out with [CMake](https://cmake.org/), and the only requirement is a C++ compiler that supports the [C++11 standard](https://en.cppreference.com/w/cpp/compiler_support/11).  

Create a build directory, build the library and install it as follows
```sh
mkdir build
cd build
cmake .. [OPTIONS]
cmake --build . --config release --parallel
cmake --install .
```

Relevant options for the configuration are
| Option | Value | Meaning |
|--------|-------|---------|
| -DBUILD_SAMPLES | **ON** or **OFF** (default is **OFF**) | Builds the demo applications. |
| -DCMAKE_INSTALL_PREFIX | Path string (default is system dependent) | Determines where the library is installed |

The install process produces a directory `<install>/include/cut`, containing the header files of the library, and a directory `<install>/lib`, containing the static library file. The directory `<install>` is the directory specified during the configuration process (or the system default, if not specified).  
If the configuration was run with the option of building the samples, the executables can be found in the build directory (`Test<Feature>` for Unix environments and `Release/Test<Feature>.exe` for Windows environments).


### Documentation
I try to keep the library well-documented with [Doxygen](https://www.doxygen.nl/) support. The documentation can be produced with the command
```sh
doxygen CUTDoc.doxy
```
The documentation is produced in the directory `doc`, and can be accessed by opening the file `doc/html/index.html` with any web browser.  
While not strictly necessary, installing [GraphViz](https://graphviz.org/) before building the documentation is highly recommended


## Overview
This section provides an overview of the main features in this library.

### Memory handling
The library provides templated wrappers for many low-level memory handling functions, such as `malloc` and `calloc`.  
These new versions are mean to make the code more readable, and throw exceptions instead of returning null pointers.

### Exceptions and fast checks
The library implements a set of exceptions for common cases, like null pointers, failed assertions, and out of bounds accesses. The exception are conveniently wrapped into macros, resulting in a more readable code and more detailed and meaningful error messages.

### Time
The library provides intuitive interfaces to handle timestamps and timers.

### Logging
The library provides a convenient interface for logging operations.

### Algorithms & data structures
This is the most useful (and continuously growing) portion of the library.  
Here are provided a set of algorithms and data structure that are either unavailable in the [STL](https://en.wikipedia.org/wiki/Standard_Template_Library), or highly inefficient because of their generality.