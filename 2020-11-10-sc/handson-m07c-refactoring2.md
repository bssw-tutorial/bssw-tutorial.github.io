---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---
# Hands-On Exercise 7c: Refactoring Part 2

## Goals
Refactor a poorly structured code to a cleaner, more reusable version.

## Prerequisites
* A [GitHub](https://github.com) account
* A fork of the [betterscientificsoftware/hello-numerical-world-sc20](https://github.com/betterscientificsoftware/hello-numerical-world-sc20) repository in your account (covered in exercise 3)
	- The files relevant to this exercise are:
		- Header files: `Double.H`, `heat.H`
		- Source file: `heatAll.C`
* Access to a basic software development environment for C++ languge
   - Your fork of the tutorial repository should be cloned in this working environment (covered in exercise 3)

## Background
The code you worked with in exercise 7b was reasonably well structured.  But it didn't necessarily start out that way.  This exercise takes a step further back in time.  Suppose you've just inherited the code `heatAll.C` from a colleague who's left the project.  You don't even have a `makefile`! Your task is to take that original, poorly structured code into a cleaner, more reusable version.  The version of the heat equation code that you worked with in exercise 7a is one possible solution to this task.  But the real point of this exercise is to go through the process yourself to decide how to restructure the code to get the results you (or your boss) want.

## Instructions

**Step 1.** Create a new directory and copy `heatAll.C` into it. This will be your working area. Work in tandem with exercise 7a to plan and track your work.

**Step 2.** Create a `makefile` to build an executable from `heatAll.C`.  If you're not that familiar with makefiles, you might want to adapt the one in the main directory.  In this case all of the code is in the single file `heatAll.C`. Add the `-coverage` flag you used in the previous exercise.

**Step 3.** Run the executable with various permutations of input arguments, saving each output as a baseline for comparison until you have 100% coverage.

**Step 4.** Make a decision about how many files you wish to split the code into. 

A good rule of thumb is to start with a different file for each category of functions. An example would be to create an `integrate.C`, a `utils.C` and a `main.C` to which you copy from `heatAll.C` functions that belong in each category. 

**Step 5.** Make a decision about which variable and constants you wish to have available globally and which you wish to keep local. Create `.H` files for global variables.

**Step 6.** In each of the new `.C` file add `extern` interfaces for functions that are not in the same file, and `include` statements for any header files you might wish to include. 

**Step 7.** In the `makefile` replace existing filenames with the ones you have just created. 

**Step 8.** Compile and execute the refactored code in all permutations used in step 3 and verify against the corresponding baselines. If you are happy with the modularity of your refactored code you are done. If you wish to further modularize repeat steps 3-8 until you have the achieved your refactoring objectives.




