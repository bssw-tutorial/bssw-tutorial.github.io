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
targets and features (e.g. `fortran_std_08`) with source files.
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

**Step 1.** branch and confirm working build with make

When contemplating any changes, it's good practice to
finish what you're doing and start a new branch.
```
git status
```

If this shows changes, save them to a temporary branch.
If not, skip these three commands:
```
git checkout -b working
git commit -am "stashing some works in progress"
git checkout main
```

Now that you're on a clean copy of the main branch, create
a branch to write cmake changes into
```
git checkout -b cmake
make check
make clean
git status
```
The last two commands should show that the repository is building
with make, and then clean up.
Git's status will let you know if you have any files that aren't under
version control.  If so, they will show up in red, and
you're free to delete or leave them there and ignore them.


**Step 2.** create a CMakeLists.txt

Create a `CMakeLists.txt` file and type in the following:
```
cmake_minimum_required(VERSION 3.8)

project(heat VERSION 0.1 LANGUAGES CXX)

add_executable(heat args.C
                    crankn.C
                    exact.C
                    ftcs.C
                    heat.C
                    upwind15.C
                    utils.C)
target_compile_features(heat PUBLIC cxx_std_11)

install(TARGETS heat DESTINATION bin)
```

This file has two required elements at the top:

1. `cmake_minimum_required` -- setting the minimum cmake version required to understand this `CMakeLists.txt`.
   As you add cmake features, you should check when cmake introduced them.
   Obviously, you should increase the required version if the features are only available in newer cmake versions.

2. `project` -- setting the [`${CMAKE_PROJECT_NAME}`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_NAME.html) and [`${HEAT_VERSION_MAJOR}`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MAJOR.html)/MINOR/PATCH variables.

The next three lines declare an executable target, `heat`, add a feature to it,
and create a rule for installing it to `bin`.


**Step 3.** build with CMakeLists.txt

For the purpose of building, it's helpful to maintain a `build.sh` script that
does the following,
```
#!/bin/bash

inst="$PWD/inst"

mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$inst ..
make -j
make install
```

These steps create a build subdirectory, run cmake, make, and make install from it.
The install directory is set locally as well as `inst` within the source directory.
This script lets you quickly build and install during development.

Create and run the script above.  Try changing some of the cmake features,
delete the `build` directory, re-run `build.sh`, and inspect the build results.

An example of the kinds of features you can add to CMakeLists.txt
is included in the `cmake_step1` subdirectory.  There, an include
directory is added to the heat target, and a `configure_file`
directive is used to make the version number accessible to the program.

Although cmake can replace the `makefile`, an updated `makefile`
is also provided in `cmake_step1` so that the version number
is accessible to code compiled using the `makefile` route.
Both compilation methods work at this point.


**Step 4.** adapt test script and check manually

The `tests.mk` makefile runs `check.sh` when it tests that the
steady-state solution to the heat equation is a straight-line.

To understand this shell script better, we'll re-code it in another
language.  The file it's looking at is output by a command like,
`./heat runame=check outi=0 maxt=-5e-8 ic="rand(0,0.2,2)"`
which creates `check/check_soln_final.curve`.  This file
is formatted as follows:

```
# Temperature
       0        0
     0.1      0.1
     0.2      0.2
     0.3      0.3
     0.4      0.4
     0.5      0.5
     0.6      0.6
     0.7      0.7
     0.8      0.8
     0.9      0.9
       1        1
```

`check.sh` has the job of comparing the two columns
(x and u(x)) to determine whether they match. This
happens to work because the right-boundary condition equals
the material length.  Extending the checks will require
re-coding this comparison.

Rewrite `check.sh` using your favorite programming language,
and call the result from `tests/testDriver.sh`.
`testDriver.sh` should

1. accept a two arguments, the location of the `heat` program, and the
   name of the algorithm to run (ftcs, crankn, or upwind15)

2. run the heat program (to produce the output above)

3. run your comparison program

   optionally report on the status of the test

4. delete all outputs so the test can be re-run without false errors

5. complete the shell script with `exit 0` for passing output
   and `exit 1` for failing tests.

There is a solution using the `awk` scripting language
in the `cmake_step2/tests` folder.  In this case,
exit is not used because the last program's exit code
is used as the exit code of the entire shell script.

For your own work, you might want to save your check's return
code to a shell variable, like

```
...

status=0 # ok
`dirname $0`/my_check check_$alg/check_${alg}_soln_final.curve || status=$?

...
exit $status
```

Of course, you should run your test driver manually -- ensuring that
it exits with 0 and 1 for good (and bad) output files, respectively.

---
Digging Deeper:

You can increase the sensitivity of the test by using a larger grid.
This will provide more data points along the curve above.  Change
the grid spacing and timestep to achieve a longer simulation.
How does it affect the test accuracy?

---


**Step 5.** invoke test script during tests/CMakeLists.txt

Now that the `testDriver.sh` script is working, it's time
to declare some tests by using [`enable_testing()`](https://cmake.org/cmake/help/latest/command/enable_testing.html) and [`add_test`](https://cmake.org/cmake/help/latest/command/add_test.html)
targets in the `CMakeLists.txt`.

Rather than put these directly into the main CMakeLists.txt,
you can use a modular approach.  Create `tests/CMakeLists.txt` with the following:
```
enable_testing()

# define a function to simplify adding tests
# (which consist of add_executable/target_link_libraries/add_test commands)
function(do_test alg)
  add_test(NAME ${alg}
           COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testDriver.sh $<TARGET_FILE:heat> ${alg})
endfunction(do_test)

do_test(ftcs)
do_test(crankn)
do_test(upwind15)
```

This enables testing, and adds all three tests.  The cmake
function here is doing the repetetive work of calling `add_test`,
so our cmake file can call it three times without repeating
tedious details.

Include this new file in the main `CMakeLists.txt`
by adding the line: `add_subdirectory(tests)`.

All set! You can now run `ctest` from the `build/tests`
subdirectory to run all the tests.

In fact, you can run tests every time you build by adding those
steps to the build.sh file:
```
...

cmake -DCMAKE_INSTALL_PREFIX=$inst ..
make -j
(cd tests && ctest)
make install
```

The `cmake_step2` subdirectory shows how to
add an option to disable building the tests.


**Extra Credit** Add an OpenMP compile flag to your build.

First, modify `heat.C` to `#include <omp.h>` at the top.
Next, have the `main` function print the current number
of processors:

```
printf("num_procs = %d\n", omp_get_num_procs());
```

This will only compile if the appropriate flags are passed
during build and link steps.

Next, modify CMakeLists.txt to use
[FindOpenMP](https://cmake.org/cmake/help/latest/module/FindOpenMP.html)
by adding the line `find_package(OpenMP 3.0 REQUIRED)`.
Note that the Find(...) modules are run in cmake using `find_package`.

Last, show cmake that the `heat` target requires OpenMP by adding the line,
`target_link_libraries(heat PUBLIC OpenMP::OpenMP_CXX)`.


**Extra Credit** Adapt the code coverage test to cmake.

Use the example [codecov with cmake](https://github.com/codecov/example-cpp11-cmake)
to add codecov functionality to your CMakeLists.txt.


## Next Steps

There are many additional resources on how to use cmake's features.
Here are a few useful 

* [CMake Tutorial Guide](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
* [Template for exporting a shared library with cmake](https://github.com/frobnitzem/lib0)
* [Template for Doxygen+Sphinx-Doc with cmake](https://code.ornl.gov/99R/cpp_docs)
* [codecov with cmake](https://github.com/codecov/example-cpp11-cmake)
* [BLT - cmake framework for build/link/test](https://github.com/LLNL/blt/)


## Conclusion

Hopefully this exercise has shown how easy it is to convert
an executable project over to cmake and ctest.
We created a `CMakeLists.txt`
by filling our source files and compile features.
Then extra features like including tests
were added one by one.


