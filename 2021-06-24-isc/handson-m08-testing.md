---
layout: default
title: "Testing Exercise"

date: 2021-05-20
layout: default

---

# Hands-On Exercise 8: Testing

## Goals
Use Documentation-Driven Development and Test-Driven Development
to build up a numerical solution of the heat equation.

$$
\partial u(x,t) / \partial t - \nabla^2 u(x,t) = q(x,t)
$$

which solves for the local energy $$ u(x,t) $$ given
an initial condition, $$ u(x,0) = u_0(x) $$, a source function,
$$ q(x,t) $$, and boundary conditions $$ u'(0,t) = 0 $$, $$ u'(1,t) = 0 $$.

This example sets the domain length to 1 by fixing the
choice of length-scale $$ x = x'/L $$, and sets the conductivity
to 1 by fixing the choice of time-scale, $$ t = \alpha t' $$.

We arbitrarily chose the boundary conditions so that
the solution should conserve energy,

$$
\int_0^1 u(x,t) \; dx = \int_0^1 u_0(x) \; dx + \int_0^t \int_0^1 q(x,t) \; dx dt
$$

Note also that the heat equation has an analytical solution,

$$
u(x,t) = \int_0^1 G(x-y,t) u_0(y) dy + \int_0^t \int_0^1 G(x-y, t-s) q(y,s) \; dy ds
$$

in terms of the some Green's function, $$G(x,t)$$, that can
be written analytically as a sum of Gaussians.  This could
be used to construct tests.


## Prerequisites

* Access to a software development environment for C++ langage
  * g++
  * gnu make
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

To start, clone the project template at:

   git clone https://

Change to this directory and create a `README.md`.
You should focus on the overall objectives of your project.
Something like:

    # Heat Equation
    
    This project will carry out time integration for
    heat conduction in 1D using the AMReX library:
    https://amrex-codes.github.io/amrex/docs_html/Basics.html

    Tests will verify that the data structures
    function as expected, and that the solution
    satisfies some key mathematical properties.

Next it's a good idea to add in a COPYING file that explicitly
states how you would like others to use (or not use) your project's
source code.
Since the existing COPYRIGHT is public domain, you can legally
delete it and replace it with your own.
There are many cut and paste examples you can use at
[https://opensource.org/licenses](opensource.org/licenses).


### Starting out iteration

Source code should always have a stable, reference,
working state.  Before making the example more complicated
let's run an "iteration zero" by checking that it builds.

1. Run a test compile and check that everything is working:

    make

This step will only succeed if you have mpi and a C++ compiler.


2. Add version control

Run make clean.  Then commit your changes to version control with:

    git add .
    git commit -am "Starting new project."


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
    a single scalar field, u, representing energy.
    The energy represents the value of the energy
    at the midpoint of the cell.
 
    The implied function will be piecewise linear
    with discrete jumps in the slope at the cell midpoints.
 
   
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

Commit these to the repository.  Note that test number 1
has already been included in the starting repository:

    #include <AMReX.H>

    int main (int argc, char* argv[]) {
        amrex::Initialize(argc, argv);

        amrex::Finalize();
        return 0;
    }

Enable it in the makefile and check that its completion fails.


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

2. Add amrex compile options to your top-level GNUmakefile by inserting (somewhere near the top):

   ```
   AMREX_CFLAGS = $(shell PKG_CONFIG_PATH=inst/lib/pkgconfig pkg-config amrex --cflags)
   AMREX_LDFLAGS = $(shell PKG_CONFIG_PATH=inst/lib/pkgconfig pkg-config amrex --libs)

   CXXFLAGS += $(AMREX_CFLAGS)
   LDFLAGS += $(AMREX_LDFLAGS)
   ```

3. If all goes well, test 1 should now pass.

### Iteration 2

At this point you should look carefully at both [AMReX's tutorial documentation](https://amrex-codes.github.io/amrex/docs_html/Basics.html#example-heatequation-ex1-c) and its [implementation code](https://github.com/AMReX-Codes/amrex-tutorials/blob/main/Basic/HeatEquation_EX1_C/Source/main.cpp).

Comparing agains the list of tests we had planned to do, these
two contain all the details we need.  The task here is to
start editing `tests/checkbox.cc` and add the appropriate
API calls and checks to convince ourselves (and the compiler)
that everything is working as it should.

Your `tests/checkbox.cc` should test out the amrex::Box, amrex::BoxArray classes
and their methods.  Because of the way the `tests/GNUMakefile` is set up,
the test should indicate errors by exiting with a nonzero return code.

I find it's helpful to use a macro for this.
For example,

    #define check(message, cond) if(!(cond)) { \
            std::cout << "Failed: "; errs += 1; \
        } else { \
            std::cout << "Passed: "; \
        } std::cout << message << std::endl;

    int errs = 0;

    ...

    ba.define(domain);
    check("Lower boundary is zero.", lbound(ba).x == 0);

    ...

    return errs;

Continue creating macros until you are satisfied the API works as expected.
Add the new files and commit the result.


### Iteration 3

Next we'll want to start adding features to our own code.
In production code, we would create a library from the files
in the `src/` directory and link it into all the tests.

For the purpose of this example, we'll just add all the code
into the `include/heat.hh` header.  This will keep the `src/heat.cc`
code simple -- create an object and run its functions.

All the important code will be present in that object
so we can test it from the `tests/`.

So, to the `include/heat.hh` file, add:

    using namespace amrex;
    class heatEq {
      public:
        BoxArray ba;
        Geometry geom;
        double energy();

        template <typename F>
        void init_u(MultiFab& u, F fn) {
            // call the function to init the box:
            // u(0) = fn(0.0);
        }
        double energy(const MultiFab& u) {
            // sum and scale u
            return 0.0;
        }
    };

Then create new programs in tests to exercise these objects.


### Conclusion

Hopefully this exercise has gotten you off to a great
start with a structured process for development.
Adding functionality takes thoughtful planning, time and effort.

Documentation provides a place to store your notes
sketched while planning.
Tests provide a way to document the discoveries you make about
your own designs as you're developing.
Doing both keeps clutter and distraction out of your finished product code.

