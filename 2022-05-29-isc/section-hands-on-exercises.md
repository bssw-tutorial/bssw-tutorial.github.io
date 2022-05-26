{% assign headings = headings | push: "Hands-On Exercises" %}

{%- assign my-event = site.data.bsswt[page.event-label].event -%}
{%- assign my-artifacts = site.data.bsswt[page.event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

### Introduction

The hands-on exercises for this {{ my-event.title-type | default: "event" }} are based around a simple numerical model using the one-dimensional heat equation.
{% if hands-on-repo %} The example is described briefly in the repository's [README]({{ hands-on-repo-url }}#readme) file, and in greater detail in the ATPESC [Hands-On lesson](https://xsdk-project.github.io/MathPackagesTraining2020/lessons/hand_coded_heat/).  The ATPESC version focuses on the numerical aspects of the model.
{% else %} The example is described some detail in the ATPESC [Hands-On lesson](https://xsdk-project.github.io/MathPackagesTraining2020/lessons/hand_coded_heat/).  That description focuses on the numerical aspects of the model.
{% endif %}
 But for this {{ my-event.title-type | default: "event" }}, we're focused on how to make the software better from a quality perspective, so **you don't need to understand the math to do these exercises**.

For the purposes of these hands-on exercises, you should imagine you've inherited an early version of the hello-numerical-world software from a colleague who's left the project, and you've been assigned to get it into better shape so that it can be used in the next [ATPESC](https://extremecomputingtraining.anl.gov/) summer school.

{% if hands-on-repo-link -%}
The repository you'll be working with is: **{{ hands-on-repo-link }}**.

*Note: most of the screenshots will refer to the generic "hello-numerical-world" repository rather than the one specifically for this event.*
{% else -%}
The repository link will be published shortly before the event.  Please check back.
{%- endif %}


### List of Hands-On Exercises
*Note that not every presentation module has exercises (yet).*
  * **[Setting up the Prerequisites](../{{ page.event-label }}/handson-m00-prerequisites.html).** Setup the accounts needed for these exercises.
  * **[Agile Methodologies](../{{ page.event-label }}/handson-m02-agile.html).**  You'll use GitHub issues and project boards to setup a simple "personal kanban" board.
  * **[Basic Git for Collaboration](../{{ page.event-label }}/handson-m03-git-workflows.html).** You'll fork our hello-numerical-world repository, create a feature branch, and make a pull request
  * **[Software Testing](../{{ page.event-label }}/handson-m08-testing.html).** You'll use an example project to try out using test driven development to add new functionality to a project
  * **[Continuous Integration](../{{ page.event-label }}/handson-m10-continuous-integration.html).** You'll establish a simple continuous integration workflow and then refine it, adding code coverage assessment

There are also activities associated with a couple of modules that we didn't have time to cover in this tutorial.  You are welcome to try them out too.
  * **[Agile Redux](../{{ page.event-label }}/handson-m06-agile-redux.html).**  You'll create epic, story, and task issues for the refactoring task and track them on a kanban board
  * **[Refactoring Scientific Software](../{{ page.event-label }}/handson-m11-refactoring1.html).**  You'll perform a small, well-defined refactoring exercise
