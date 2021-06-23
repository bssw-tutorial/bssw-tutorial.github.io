---
layout: default
title: "Testing Walk-Through"

date: 2021-06-20
layout: default

---

# Hands-On Exercise 8: Testing Walk-Through

## Goals

Implement a cmake build and test process for an example project.


## Prerequisites

* Access to a software development environment for C++ language with cmake
  * g++
  * gnu make
  * cmake
  * git


## Background

Projects should start as simple, small units that build up as
development progresses.  Makefiles are a simple solution to store
compilation rules, but lack advanced features other than
those available by manually setting make-variables.

CMake enables cross-platform compatibility,
external library detection, code generation,
and configurable options.
Cross-platform compatibility is achieved by
associating attributes (e.g. `target_link_libraries`) with
targets and features (e.g. `fortran_std_08`)
with source files.
CMake translates those attributes into
build-flags and build programs instead of
directly setting them.
It also defaults to out-of-source
compilation and has a rudimentary method
for distributing libraries.

When the project is large enough
to warrant these extra features,
developers usually adopt automake
or cmake to handle the additional build complexity.

The example repository we have provided is just large enough
to warrant this change.  There are seven C-source files,
two headers, and about 80 lines of shell and makefile
devoted to testing.


## Instructions


## Conclusion

Hopefully this exercise has shown how easy it is to convert
an executable project over to cmake and ctest.
We created a `CMakeLists.txt`
by filling our source files and compile features.
Then extra features like including tests
were added one by one.


