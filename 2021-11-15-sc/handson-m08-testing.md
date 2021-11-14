---
layout: page
---
{%- include set-event-label-from-path -%}
{%- assign my-artifacts = site.data.bsswt[event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

{%- unless hands-on-repo-link -%}{%- assign hands-on-repo-link = "hands-on-repo-link (to be defined)" -%}{%- endunless -%}

# Hands-On Exercise: Test Driven Development

## Goals

Use an example project to try out using test driven development to add new functionality to a project.

## Prerequisites

* Access to a software development environment for C++ language with cmake
  * a C++ compiler
  * gnu make
  * cmake
  * git
* A fork of the {{ hands-on-repo-link }} repository in your account (covered in Git Workflows exercise)
   - Your fork of the tutorial repository should be cloned where you have the software development environment above

## Background

Test driven development (TDD) is a software development methodology that uses testing to
drive the development cycle, rather than writing tests as an afterthought. It is used
widely by the software engineering community, but can take some practice to get familiar with, 
particularly if more traditional approaches have been used in the past.

CMake is a system for build automation, testing, packaging and installation of software 
by using platform and compiler-independent configuration files. CMake is not a build system, 
but generates build files for an actual build system, such as Make. It enables cross-platform compatibility,
external library detection, code generation, configurable options, and more. CMake can
be used on projects of any size in order to employ best practice tools for
software development from the very start.

CMake makes TDD easy to use, since it provides a built-in testing framework. The example repository we have 
provided contains a `tdd-example` directory that we will be using to explore how to set up and use TDD on
a sample code.

## Setup Instructions

The following steps are for setting up testing for this code, which is usually only done once at the
start of the project. Once the project has been set up for TDD, these can be skipped.

**Step 1: Check that the code builds and runs**

Change to the `tdd-example` directory by running the command:
```
cd tdd-example
```

The `cmake` command is used to read the `CMakeLists.txt` configuration
file and generate the appropriate build files. The only argument is a 
path to the directory containing the configuration file:
```
cmake .
```

The `cmake` command will generate some output telling you what it is 
doing which you can safely ignore unless something goes wrong:
```
-- The CXX compiler identification is AppleClang 12.0.0.12000032
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: .../git/hello-numerical-world/tdd-example
```

The code can be built using the command:
```
make
```

This should geneate output that looks something like:
```
Scanning dependencies of target heat
[ 16%] Building CXX object CMakeFiles/heat.dir/args.C.o
[ 33%] Building CXX object CMakeFiles/heat.dir/exact.C.o
[ 50%] Building CXX object CMakeFiles/heat.dir/heat.C.o
[ 66%] Building CXX object CMakeFiles/heat.dir/ftcs.C.o
[ 83%] Building CXX object CMakeFiles/heat.dir/utils.C.o
[100%] Linking CXX executable heat
[100%] Built target heat
```

Finally, the code can be run with the following command: 
```
./heat alg=ftcs outi=0 maxt=-5e-8 ic="rand(0,0.2,2)"
```

The `alg=ftcs` argument
tells the code to use the FTCS algorithm. The `outi=0` argument enables disables
any output progress from being displayed. The `maxt=-5e-8` specifies the maximum
simulation time in seconds. Lastly the `ic="rand(0,0.2,2)"` argument sets the
initial condition to a random number.

Assuming all goes well, you should see the following output:
```
    runame="heat_results"
    alpha=0.2
    lenx=1
    dx=0.1
    dt=0.004
    maxt=-5e-08
    bc0=0
    bc1=1
    ic="rand(0,0.2,2)"
    alg="ftcs"
    savi=0
    save=0
    outi=0
    noout=0
Stopped after 001490 iterations for threshold 2.46636e-15
```
This will also create a directory called `heat_results` that contains a number
of output files. If you try running the code again without removing this directory,
you will see the message:
```
An entry "heat_results" already exists
```

**Step 2: Provide a test script:**

To use TDD, we need to run some tests. For this code, our test is going to check if the 
result is within an acceptable error bound once it reaches a steady state. There are many other
kinds of tests that could be used, so this is just one example.

For the purposes of this example, we have already written a test script that runs the code
and then checks that the results are acceptable and returns a suitable exit code if it is. 
The script is just a convenient way of doing this, there are many other ways that would also
work.

To make sure that the script works, you can try running it manually using the command:
```
sh check.sh ./heat ftcs
```

This should generate similar output to what we've seen before, however the last line will
indicate if the result was acceptable or not:
```
    runame="check_ftcs"
    alpha=0.2
    lenx=1
    dx=0.1
    dt=0.004
    maxt=-5e-08
    bc0=0
    bc1=1
    ic="rand(0,0.2,2)"
    alg="ftcs"
    savi=0
    save=0
    outi=0
    noout=0
Stopped after 001490 iterations for threshold 2.46636e-15
Error = 0
```

---
**Digging Deeper:**

To understand this `check.sh` script better, lets look a bit
deeper.  The file it's looking at is output by a command like,
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
(x and u(x) respectively) to determine whether they match. This
happens to work because the right-boundary condition equals
the material length.  Extending the checks will require
re-coding this comparison.

You can increase the sensitivity of the test by using a larger grid.
This will provide more data points along the curve above.  Change
the grid spacing and timestep to achieve a longer simulation.
How does it affect the test accuracy?

---

**Step 3: Create and configure the tests**

At this point we only have a script that runs a simple test. We 
need to configure `CMake` so that it uses this script when we tell
it to test the code. This is also a good starting point for setting
up continuous integration.

First, we need to create a directory to put our tests in, and then copy
(or move) the test script into the directory:
```
mkdir tests
cp check.sh tests/check.sh
```

Next we change into the `tests` directory and create a `CMake` configuration
file to tell it about the tests. `CMake` uses the name `CMakeLists.txt` for
its configuration files. You should be able to cut and paste the following code
to achieve this:

```
cd tests
cat > CMakeLists.txt <<EOF
enable_testing()
add_test(NAME ftcs COMMAND check.sh $<TARGET_FILE:heat> ftcs)
add_test(NAME upwind15 COMMAND check.sh $<TARGET_FILE:heat> upwind15)
EOF
```

The text between the first and second `EOF`s is what should go into the `CMakeLists.txt` file:

- The `enable_testing()` line just tells `CMake` to include the ability to run tests.
- The first `add_test()` line adds a test for the existing FTCS kernel. This is optional, but it will make sure
that our tests cover as much code as possible.
- The second `add_test()` line is adding a test for the new kernel (which doesn't exist yet.)

**Step 4: Enable the tests**

As `CMake` is only a build system generator, when any of it's configuration files are modified
we need to tell it to re-read them and re-generate the build system files. This can happen
automatically by just running the build, but in this case we've added some new files that it
doesn't know about, so we need to re-run the `cmake` command as follows:

```
cd ..
cmake -DBUILD_TESTS=ON .
cd tests
```

These commands will change to the parent directory containing the main configuration file,
re-run the `cmake` command with tests enabled, and change back to the `tests` directory.

The output will look similar to what was generated the first time the `cmake` command was run. If there
are any errors, check the contents of the `CMakeLists.txt` file in the `tests` directory are correct.

## Using TDD

**Step 1: Run the tests**

Once the setup is complete, you should be able to run the tests using the command (make sure you're in the `tests`
directory):
```
ctest
```

Since there is no code implementing the upwind15 kernel, you should get an error:
```
Test project /home/tutorial/hello-numerical-world/tdd-example/tests
    Start 1: ftcs
1/2 Test #1: ftcs .............................   Passed    0.44 sec
    Start 2: upwind15
2/2 Test #2: upwind15 .........................***Failed    0.01 sec

50% tests passed, 1 tests failed out of 2

Total Test time (real) =   0.46 sec

The following tests FAILED:
	  2 - upwind15 (Failed)
Errors while running CTest
```

This is expected, and a normal part of TDD!

**Step 2: Make the test succeed**

In order to make the new test pass, we need to implement the new kernel. For this code, we
need to add a few statements to the `heat.C` file.

First, change into the directory with the code:
```
cd ..
```

Edit `heat.C` with your favorite editor.
```
nano heat.C
```

At line 68, add a prototype for the new kernel.
```

extern bool
update_solution_upwind15(int n,
    Double *curr, Double const *last,
    Double alpha, Double dx, Double dt,
    Double bc_0, Double bc_1);
```

At (new) line 91, modify the assertion to verify the new kernel name.
```
     assert(strncmp(alg, "ftcs", 4)==0 || strncmp(alg, "upwind15", 8)==0);
```

At (new) line 133, modify the `if` statement to call the new kernel.
```
     if (!strcmp(alg, "ftcs"))
         return update_solution_ftcs(Nx, curr, last, alpha, dx, dt, bc0, bc1);
     else if (!strcmp(alg, "upwind15"))
         return update_solution_upwind15(Nx, curr, last, alpha, dx, dt, bc0, bc1);
```

In addition to modifying `heat.C` to *call* the kernel, we also need to add it to
the main `CMakeLists.txt` file to that it is included in the *build*.

Edit `CMakeLists.txt` and add the kernel to the `add_executable` statement at line 11 as follows.
```
add_executable(heat args.C
                    exact.C
                    heat.C
                    upwind15.C  #<<< Add new kernel
                    ftcs.C
                    utils.C)
```

Now build the code with the new kernel included.
```
make
```

Assuming you did this correctly, you should see something like this.
```
-- Configuring done
-- Generating done
-- Build files have been written to: /home/tutorial/hello-numerical-world/ttd-example
Scanning dependencies of target heat
[ 14%] Building CXX object CMakeFiles/heat.dir/heat.C.o
[ 28%] Building CXX object CMakeFiles/heat.dir/upwind15.C.o
[ 42%] Linking CXX executable heat
[100%] Built target heat
```

If you get any compile errors, check that you added the code correctly to `heat.C`. If 
`CMake` complains then check you added the kernel to the `CMakeLists.txt` correctly.

That's it! You're now ready to run the tests using the following commands.
```
cd tests
ctest
```

At this point the tests should now all pass.
```
Test project /home/tutorial/hello-numerical-world/tests
    Start 1: ftcs
1/2 Test #1: ftcs .............................   Passed    0.23 sec
    Start 2: upwind15
2/2 Test #2: upwind15 .........................   Passed    0.03 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.13 sec
```

**Step 3: Refactor the code**

Since this is a fairly simple example, refactoring is probably not necessary. However this
is a useful point to look at the changes you have made and make sure they conform to the
requirements of the project.

<span style="font-size:larger;"><b>Congratulations! You have successfully used TDD to add new functionality to your code.</b></span>

**Extra Credit** Add the `crankn` kernel to your code using the same process. Note,
`crankn` requires additional arguments to be passed. You can study the code in the
main directory to see what it needs.

**Extra Credit** Check out the original [ATPESC Hands-On Lesson](https://xsdk-project.github.io/MathPackagesTraining2020/lessons/hand_coded_heat/)
for ideas of additional functionality that you could add using TDD.


## Next Steps

Here are a few useful resources on how to use cmake's features.

* [CMake Tutorial Guide](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
* [Template for exporting a shared library with cmake](https://github.com/frobnitzem/lib0)
* [Template for Doxygen+Sphinx-Doc with cmake](https://code.ornl.gov/99R/cpp_docs)
* [codecov with cmake](https://github.com/codecov/example-cpp11-cmake)
* [BLT - cmake framework for build/link/test](https://github.com/LLNL/blt/)


## Conclusion

Hopefully this exercise has shown how easy it is to use TDD to
add new functionality to your project
We added tests to our build system and then used these tests
to ensure that the code we added worked correctly.


