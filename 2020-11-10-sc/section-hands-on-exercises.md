{% assign headings = headings | push: "Hands-On Exercises" %}

### Introduction

The hands-on exercises for this tutorial are based around a simple numerical model using the one-dimensional heat equation.  The example is described briefly in the repository's [README](https://github.com/betterscientificsoftware/hello-numerical-world-sc20#readme) file, and in greater detail in the ATPESC [Hands-On lesson](https://xsdk-project.github.io/MathPackagesTraining2020/lessons/hand_coded_heat/).  The ATPESC version focuses on the numerical aspects of the model.  But for the Better Scientific Software tutorial, we're focused on how to make the software better from a quality perspective, so **you don't need to understand the math to do these exercises**.

For the purposes of the BSSw hands-on exercises, you should imagine you've inherited an early version of the hello-numerical-world software from a colleague who's left the project, and you've been assigned to get it into better shape so that it can be used in the next [ATPESC](https://extremecomputingtraining.anl.gov/) summer school.

The repository you'll be working with is on GitHub: [betterscientificsoftware/hello-numerical-world-sc20](https://github.com/betterscientificsoftware/hello-numerical-world-sc20).
*Note: most of the screenshots will refer to the generic "hello-numerical-world" repository rather than the one specifically for this tutorial.*

### List of Hands-On Exercises
*Note that the exercise numbers align with the presentation modules.  Not every module has exercises (yet).*
* **[Exercise 0: Setting up the Prerequisites](handson-m00-prerequisites.md)**. Setup the accounts needed for these exercises.
* **[Exercise 2: Agile Methodologies](handson-m02-agile.md).**  You'll use GitHub issues and project boards to setup a simple "personal kanban" board.
* **[Exercise 3: Git Workflows](handson-m03-git-workflows.md).** You'll fork our hello-numerical-world repository, create a feature branch, and make a pull request
* **[Exercise 7a: Agile Redux](handson-m07a-agile-redux.md).**  You'll create epic, story, and task issues for the refactoring task and track them on a kanban board
* **[Exercise 7b: Refactoring Part 1](handson-m07b-refactoring1.md).**  You'll perform a small, well-defined refactoring exercise
* **[Exercise 7c: Refactoring Part 2](handson-m07c-refactoring2.md).**  You'll perform a a more open-ended refactoring exercise
* **[Exercise 8: Continuous Integration](handson-m08-continuous-integration.md).** You'll establish a simple continuous integration workflow and then refine it, adding code coverage assessment
