---
layout: default
title: "Testing Part 1 Exercise"

date: 2021-05-20
layout: default

---

# Hands-On Exercise 8: Testing Part 1

## Goals
Use Documentation-Driven Development and Test-Driven Development
to build up a numerical solution of the heat equation.

$$
k \nabla^2 u(x,t) = \partial u(x,t) / \partial t
$$

## Prerequisites

* Access to a software development environment for C++ langage
  * g++
  * cmake
  * documentation
  * python3 with sphinx
  * git


## Background

Test-driven development and documentation-driven development are practices
that emphasize the importance of understanding requirements for software
*before writing full implementations*.

Used literally, they imply that tests and/or documentation for the software
gets written before the software.  In practice, software development is iterative.
When using test and documentation-driven development, the tests and documentation
are never far behind the implementation, but can be way out in-front.


## Instructions

We'll write the beginnings of a heat diffusion equation that will
follow the "library-based" solution of the
[BSSW heat equation tutorial](https://github.com/betterscientificsoftware/hello-heat-equation).

### Starting development

To start, let's use boilerplate code for a cmake project
building with documentation and tests:

    git clone https://github.com/frobnitzem/lib0
    mv lib0 heat
    cd heat
    bash customize.sh heat


Follow the first suggestion printed out by that script and create any
copyright type you wish by writing the COPYING file
(see https://opensource.org/licenses for cut and paste examples).


### Writing a README.md

For now, you should focus on the overall objectives of
your project.  Something like:

    # Heat Equation
    
    This project will carry out time integration for
    heat conduction in 1D using the AMReX library:
    https://amrex-codes.github.io/amrex/docs_html/Basics.html

    Tests will verify that the data structures
    function as expected, and that the solution
    satisfies some key mathematical properties.


### Starting out iteration

Source code should always have a stable, reference,
working state.  Before making the example more complicated
let's run an "iteration zero" by checking that it builds.

1. Run a test compile and check that everything is working:

    vi build.sh   # It runs cmake, then make from a build dir.
                  # change LOCALROOT to
                  # LOCALROOT=$PWD/inst

    bash build.sh # test compile

This step will only succeed if you have cmake 3.17 and above
and a C++ compiler.


2. Add version control

Delete the `build` and `inst` directories created in the last step:

    git init
    git add .
    git commit -am "Initial commit."


### Planning

We want this example to be as simple as possible while still
showing how to hook into feature-rich libraries and state
of the art development tools.

This tutorial is about planning and the development
process more than writing codes.  Right now, the project
is a seed of an idea.  It sits at the center of an
infinite graph of possibilities.  You can
map these with a web:

* increase accuracy as much as possible
  - investigate higher-order finite elements
  - compare mathematical frameworks
  - investigate implicit time-stepping schemes
  
* increase parallel speed and efficiency
  - investigate data structures and layouts promoting local access patterns
  - plan for network communication steps
  - investigate overlapping compute/communication, multi-precision, etc.

* increase code readability and maintainability
  - list out repeated operations and use cases
  - define high-level operations
  - investigate mathematical structure of the problem

* build an easy-to-use documentation system
  - investigate documentation build systems
  - compare effort/visual appeal
  - add readthedocs integration, doc. build status, etc.
  - develop examples and use cases in multiple languages

* use the most advanced testing framework
  - compare C++ testing libraries for syntax
  - investigate compatible frameworks based on your upstream libraries
  - list out all possible use cases of the scenario and plan tests extensively

* demonstrate all the concepts in the AMReX library

* compare all mathematical, numerical, and algorithmic methods for solving this equation

* provide the best logical cross-over between dimensions

* use the heat equation as a sub-solver in a larger network of equations


Getting this advanced is, of course, a bit silly
for a 1D heat equation example.

Obviously, we can't do all these things.
I do not advise that you attempt to do so either.
It absolutely wouldn't make sense.

Instead of getting overwhelmed and over-worked,
focus on what you actually need.

### Planning - re-do

Let's keep just a few things in each major category above.
Documentation-driven development means we now write these into the
documentation.

Add a note in the README.md to check docs/README.md
Add a docs/README.md with the following:

    # Heat Documentation

    src/heat.cc creates a 1D Cartesian grid
    with uniform spacing.  Each grid-cell contains
    a single scalar field, energy.
    The energy represents the value of the energy
    at the midpoint of the cell.
 
   
    Functions will be provided to compute:

    1. the total energy on the grid

    2. the value of the energy at the next timestep,
       given the current energy

    3. initialization of the grid from a function and bounds

    4. creation of a grid object


    # Tests to be included

    1. tests to ensure AMReX can be called as a library

    2. tests of the grid object size and storage

    3. tests of the energy function

    4. tests of the initialization

    5. integration tests of the energy vs. time

    6. comparison of the time-dependent solution with
       an analytical result

Commit these to the repository, and write test number 1.
Check that its compilation fails.


### Iteration 1

1. Install amrex:

   ```
   PREFIX=$PWD
   mkdir inst && cd inst
   curl -O https://github.com/AMReX-Codes/amrex/releases/download/21.05/amrex-21.05.tar.gz
   tar xzf amrex-21.05.tar.gz
   cd amrex
   ./configure --prefix=$PREFIX --dim=1
   make -j
   make install
   ```

   Note: In a more advanced development environment, you might
   choose to `spack install amrex` instead of locally installing.

2. Add that path to the cmake options in `build.sh` using
   `-DCMAKE_PREFIX_PATH="/path/to/amrex"`.

3. Add `FindPackage(amrex)` to your `CMakeLists.txt` file,
   and add a line, `add_libraries(heat amrex::CXX)`.

4. If all goes well, test 1 should now pass.

