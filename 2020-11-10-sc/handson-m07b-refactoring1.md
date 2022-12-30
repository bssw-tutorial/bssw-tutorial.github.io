---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---
# Hands-On Exercise 7b: Refactoring Part 1

## Goals
Refactor the code to enable addition of new integration methods without having to modify the source code.

## Prerequisites
* A [GitHub](https://github.com) account
* A fork of the [betterscientificsoftware/hello-numerical-world-sc20](https://github.com/betterscientificsoftware/hello-numerical-world-sc20) repository in your account (covered in exercise 3)
	- The files relevant to this exercise are:
		- Header files: `Double.H`, `heat.H`
		- Source file: `args.C`, `crankn.C`, `exact.C`, `ftcs.C`, `heat.C`, `upwind15.C`, `utils.C`
		- Build file: `makefile`
* Access to a basic software development environment for C++ languge
   - Your fork of the tutorial repository should be cloned in this working environment (covered in exercise 3)

## Background
In Module 7 of the tutorial presentations, we discuss the refactoring process. In this first refactoring exercise you are given a modular, well written code that supports multiple finite-difference schemes, your task is to refactor is so that another scheme can be added without having to modify the source code in future. 

## Instructions

The code currently has three different finite-difference schemes to update the solution to the heat equation: `crankn` (Crank-Nicolson), `ftcs` (forward-time central-space), and `upwind15` (upwind).  We'd like the code to be more flexible so that other approaches can be added to update the solution without having to modify the main heat equation driver every time.  More specifically, the `update_solution` interface needs to be generalized. 

### Baselining the Existing Application
All refactoring exercises should begin by checking the test coverage for the part of the code you'll be working on and gathering baseline results with the original code.

**Step 1.** In your working copy of the repository, in the `makefile`, add the `-coverage` flag to the rules to generate object files and to link the final `heat` application.

```
# Implicit rule for object files
%.o : %.C
	$(CXX) -coverage -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

# Linking the final heat app
heat: $(OBJ)
	$(CXX) -coverage -o heat $(OBJ) $(LDFLAGS) -lm
```

then build the `heat` application by typing  `make`.

**Step 2.** Run

```
./heat runame="ftcs_results"
gcov heat.C
cp heat.C.gcov heat-ftcs.C.gcov
```

and examine the resulting `heat-ftcs.C.gcov` file.  The output of gcov is a listing of the code annotated on the left with the following notations:
- a dash indicates a non-executable line, 
- a number indicates the number of time the line was executed, and 
- hash marks ("#####") indicate that the line was *never* exercised.
You'll notice that the calls to the `update_solution_upwind15` and `update_solution_crankn` routines were never exercised.

**Step 3.** Collect coverage and baseline results for the other update schemes.

```
./heat alg="upwind15" runame="upwind_results"
gcov heat.C
cp heat.C.gcov heat-upwind15.C.gcov

./heat alg="crankn" runame="crankn_results"
gcov heat.C
cp heat.C.gcov heat-crankn.C.gcov
```

Compare the three gcov output to convince yourself that between the three test cases you've run, you have good coverage for the regions of code on which you're going to work.

### Understanding the Refactoring Task

In the original code, the user passes an argument to the code to select the finite-difference scheme used on that execution.  Rather than pay the overhead of the tests required to do this on each iteration of the algorithm, we want to choose the finite-difference scheme at build time (producing different executables for each scheme).

*Note: This is admittedly a somewhat contrived scenario, but it has the virtue of being fairly localized and easy to explain.*

**Step 4.** Open `heat.C` in an editor and locate the interface declarations: `update_solution_ftcs`, `update_solution_upwind15`, and `update_solution_crankn` (L64-80). Note that the three interfaces are similar, but not identical. Specifically, the Crank-Nicolson routine takes different arguments.  

In `heat.C` find the `update_solution` routine that calls the three specific routines above (L143).  Note the branches based on string comparisons (slow, in performance-sensitive situations).

If you look at the implementations of the three updaters, in the files `ftcs.C`, `upwind15.C`, and `crankn.C`, you may notice that `crankn.C` also contains a second routine, `initialize_crankn`, with no analog in the other two files.  In the `initialize` routine in `heat.C` you can identify the call site for `initialize_crankn` (L106) and verify that there is no equivalent initialization step for the other two schemes.

### Carrying out the Refactoring

**Step 5.** First, we need to define a new generalized interface to the updaters that will work for all of them, which we'll call, simply `update_solution`.  So replace the original interface declarations (L64-80) with a single declaration, for `update_solution` that takes the union of the arguments required by the three updaters.

```
extern bool
update_solution(int n,
	Double *curr, Double const *last,
	Double alpha, Double dx, Double dt,
	Double const *cn_Amat,
	Double bc_0, Double bc_1);
```

and remove the old implementation of `update_solution`.

**Step 6.** Next, we need to change the implementations of the updaters to use the new interface (variables in the interface which are not used in the update scheme can simply be ignored).  Since we're going to end up with the same routine name in three different files, it might be helpful to our "future selves" to add comments to identify which finite-difference scheme each one implements, in case someone changes the names of the files.

**Step 7.** We also need to deal with `initialize_crankn`.  Since we're not going to be passing arguments in at run time to select the finite-difference scheme, we need to get rid of the `if` test that protects its invocation in `heat.C`.

But now we need to ensure that the dependency is satisfied no matter which updater is linked into the application.  So we need to add null implementations of `initialize_crankn` to the `ftcs.C` and `upwind15.C` files to satisfy that dependency. It is not necessary to generalize the name, but it is probably a good idea to add comments explaining why a do-nothing routine with a name that implies association with the Crank-Nicolson method appears in the file implementing the upwind scheme, for example.

```
void
initialize_crankn(init n,
	Double alpha, Double dx, Double dt,
	Double **cn_Amat)
{
}
```

**Step 8.** Finally, we need to modify the `makefile` to generate three different versions of the executable by linking against the three different updaters. *Note: this solution is not elegant, but it is functional.*

```
HDR = Double.H
SRC1 = heat.C utils.C args.C exact.C ftcs.C
SRC2 = heat.C utils.C args.C exact.C upwind15.C
SRC3 = heat.C utils.C args.C exact.C crankn.C
OBJ1 = $(SRC1:.C=.o)
OBJ2 = $(SRC2:.C=.o)
OBJ3 = $(SRC3:.C=.o)
GCOV1 = $(SRC1:.C=.C.gcov) $(SRC1:.C=.gcda) $(SRC1:.C=.gcno) $(HDR:.H=.H.gcov)
GCOV2 = $(SRC2:.C=.C.gcov) $(SRC2:.C=.gcda) $(SRC2:.C=.gcno) $(HDR:.H=.H.gcov)
GCOV3 = $(SRC3:.C=.C.gcov) $(SRC3:.C=.gcda) $(SRC3:.C=.gcno) $(HDR:.H=.H.gcov)
EXE1 = heat1
EXE2 = heat2
EXE3 = heat3
```

and build all three versions of the application by running 

```
make heat1 heat2 heat3
```

## Verifying Your Work

**Step 9.** In this case, the changes that you've made to the code should not change the computed results at all.  Verify this by running the new codes and comparing against the baseline results that you collected earlier.

```
./heat1 runame=“new_ftcs_results”
./heat2 runame=“new_upwind_results”
./heat3 runame=“new_crankn_results”
```