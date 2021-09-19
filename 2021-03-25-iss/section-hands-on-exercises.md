{% assign headings = headings | push: "Hands-On Exercises" %}

{%- assign my-event = site.data.bsswt[page.event-label].event -%}
{%- assign my-artifacts = site.data.bsswt[page.event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

### Introduction

The hands-on exercises for this {{ my-event.title-type }} are based around a simple numerical model using the one-dimensional heat equation.  The example is described briefly in the repository's [README]({{ site.github-url }}/{{ hands-on-repo }}#readme) file, and in greater detail in the ATPESC [Hands-On lesson](https://xsdk-project.github.io/MathPackagesTraining2020/lessons/hand_coded_heat/).  The ATPESC version focuses on the numerical aspects of the model.  But for this {{ my-event.title-type }}, we're focused on how to make the software better from a quality perspective, so **you don't need to understand the math to do these exercises**.

For the purposes of these hands-on exercises, you should imagine you've inherited an early version of the hello-numerical-world software from a colleague who's left the project, and you've been assigned to get it into better shape so that it can be used in the next [ATPESC](https://extremecomputingtraining.anl.gov/) summer school.

The repository you'll be working with is on GitHub: **[{{ hands-on-repo }}]({{ site.github-url }}/{{ hands-on-repo }})**.
*Note: most of the screenshots will refer to the generic "hello-numerical-world" repository rather than the one specifically for this tutorial.*

### List of Hands-On Exercises
*Note that the exercise numbers align with the presentation modules.  Not every module has exercises (yet).*
* **[Exercise 0: Setting up the Prerequisites](../{{ page.event-label }}/handson-m00-prerequisites.html)**. Setup the accounts needed for these exercises.
* **[Exercise 2: Agile Methodologies](../{{ page.event-label }}/handson-m02-agile.html).**  You'll use GitHub issues and project boards to setup a simple "personal kanban" board.
* **[Exercise 3: Git Workflows](../{{ page.event-label }}/handson-m03-git-workflows.html).** You'll fork our hello-numerical-world repository, create a feature branch, and make a pull request
* **[Exercise 7a: Agile Redux](../{{ page.event-label }}/handson-m07a-agile-redux.html).**  You'll create epic, story, and task issues for the refactoring task and track them on a kanban board
* **[Exercise 7b: Refactoring Part 1](../{{ page.event-label }}/handson-m07b-refactoring1.html).**  You'll perform a small, well-defined refactoring exercise
* **[Exercise 7c: Refactoring Part 2](../{{ page.event-label }}/handson-m07c-refactoring2.html).**  You'll perform a a more open-ended refactoring exercise
* **[Additional Exercise: Continuous Integration](../{{ page.event-label }}/handson-m08-continuous-integration.html).** You'll establish a simple continuous integration workflow and then refine it, adding code coverage assessment