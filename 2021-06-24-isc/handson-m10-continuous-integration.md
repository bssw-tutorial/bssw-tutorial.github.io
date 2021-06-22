---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: page
---
# Hands-On Exercise 8: Continuous Integration
## Goals
You'll establish a simple continuous integration workflow and then refine it, adding code coverage assessment.

## Prerequisites
* A [GitHub](https://GitHub.com) account
    - This exercise can be done entirely within the web interface to GitHub and Codecov.
* A fork of the [betterscientificsoftware/hello-numerical-world](https://github.com/betterscientificsoftware/hello-numerical-world) repository in your account (covered in exercise 3)
* A [Codecov](https://codecov.io) account linked to your GitHub account

## Background

A core idea of continuous integration is that CI checks are triggered by changes to the code, usually making or updating pull requests.  In this exercise, we're going to use the GitHub actions service, which provides execution environments and resources on demand to run such tests.

Complementary to testing, code coverage tells you how many lines of the code are exercised in the tests executed.
We're also going to hook this CI check up to the Codecov.io service.
Then we'll visualize and track changes in code coverage as the code changes.

A video walk-through of (most of) this exercise is available at: <https://youtu.be/QE4RFp8lGiQ>
* This video was created by Mark Miller (LLNL) for tutorial at ATPESC 2020.  Where he refers to the repository as `hello-numerical-world-atpesc-2020`, substitute `hello-numerical-world-<...>`.
* The original exercise used Travis CI, which requires setting up an extra account. This version uses GitHub's action service instead.


## Instructions

You'll need to add a configuration file to your repository to signal GitHub's CI to take action.  The file must be placed inside the `.GitHub/actions` folder.  Note the leading `.`.  In unix-like operating systems, this is a hidden file, that won't be displayed in directory listings by default.  But on Windows and in the GitHub web interface, such files are displayed by default.

**Step 1.** Rather than type the file by hand, navigate to "Actions" on your GitHub project.  Then click "Skip this and set up a workflow yourself".  This brings you to an editor for `.GitHub/workflows/main.yml`.  Any filename will do, so we'll rename it `check.yml`.  Under the `jobs/build/steps` section, change the two run lines as follows:


```

...

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v2

      - name: Build the project with code coverage flags.
        run: make CXXFLAGS=--coverage LDFLAGS="--coverage -lm" check

      - name: Upload results to codecov.io
        run: bash <(curl -s https://codecov.io/bash)
```

These bash-shell commands execute the make and codecov.io upload steps.

The configuration file is written in the YAML markup language, which is pretty simple,
but interprets indentation levels as nesting of data elements.

The first section (not shown) sets the conditions for running the jobs listed next.
The dashes before each line are interpreted as list elements.
Values within each section that don't start with `-`, `[`, or `{`
are interpreted as strings (or numbers if numeric).
Thus, an equivalent syntax for the steps section would be:

```

'steps': [ {'uses': "actions/checkout@v2"}
         , {'name': "Build the project with code coverage flags.",
             'run': "make CXXFLAGS=--coverage LDFLAGS='--coverage -lm' check"}
         , {'name': "Upload results to codecov.io",
             'run': "bash <(curl -s https://codecov.io/bash)"}
         ]
```

jobs specify the command to execute when the job is triggered.
It's worthwhile to read the documentation on other keys that can go into `steps`.
Those can do things like setting up conda environments for python much more
easily than manually entering `run` commands.  GitHub's examples can also help.


**Step 2.** Next you need to create a commit to add this file to your copy of the repository.
GitHub's editor has you typing into a document with a big, green `Start Commit' button.

Click that to bring up a dialogue box asking for a commit message and an optional comment.
The commit message should be a one-line description of what was changed.

You also have the option of committing directly to the main branch or starting a new branch.

To show the full process, click the second radio button (Create a new branch for this commit and start a pull request).
A random branch name is automatically created, which is fine.  Submit the form by pressing the green
"Propose New File" button.

**Step 3.** Next you need to create a pull request to add this change to the upstream repository.
These pull requests (PR-s) are part of the GitHub website - and are not present in the command-line git tool.
In gitlab, they are called "Merge Requests" instead.

In our case, GitHub has already created the pull-request, and you are now viewing it.
All pull requests for a repository are available under its "Pull requests"
navigation button.  Click `Merge pull request` at the bottom to merge the PR.

**Step 4.**  Observe test results

Looking at this pull request, you'll see it records GitHub performing a couple of checks.  One it always does is to look for conflicts between your PR and the base branch from which it was forked in the upstream repository (in case there were changes upstream that you haven't pulled into your fork yet).

With the addition of the configuration file, the tests in `check.yml` are performed.  You'll often notice a short lag from the moment you click "Create pull request" to the moment the that checks start running.  Usually, this is shown by an orange icon saying `some checks in progress`.

All the checks are visible from the repository's `Actions` nav-bar.
If your check yml has a syntax error, the editor would have told you so as you were typing.
If it got through anyway, GitHub's check action status will tell you that yaml syntax was the problem.

After the test has completed, there's a direct link to "Show all checks"
The immediate result of clicking on that link is a screen from GitHub summarizing what's happening.
The left bar shows all the `jobs` defined in your `workflows/*.yml` files.  For each,
the right bar can be expanded to show the text output from each job step.
GitHub keeps logs of all these runs for some time.

If the check fails, the pull request page will show that, and the "Details" link will continue to be available to help you debug the problem.  You can see this situation for yourself by modifying something in the repository to intentionally introduce an error.  For example, you could change the `make` command in the `check.yml` file to make something nonexistent.  Or you could introduce a syntax error into one of the code files so that the compilation fails.  Or you could change the math in the code or the parameters in the `check` target of the `makefile` so that the results don't match the golden results.


---
Note on Pull-requests::

When creating pull-requests, you should look carefully at the target repository.
In this tutorial, your repository was not created by a "fork" from an upstream
repository.  So your pull-request went directly to your "main" branch.

When you are contributing to an outside project, however,
you have the option of sending your pull-request to any branch
of your own or the `upstream` repository.

**Things can be confusing if you're not in the repository you think you are.**
Pull-requests can involve two separate repositories.  Check often when you're working with pull requests.

Second, until the pull request is merged upstream (or closed),
further commits in your fork will be added to the existing pull request.
(If you think you might need to have multiple pull requests active at the
same time from your fork, you should create each of them on a separate branch within your fork.)

---

### Adding Code Coverage Tracking

As mentioned, understanding how much of the code you're working with is covered by your testing is important for effective CI testing (really for *any* testing).  We're going to add coverage analysis to the build process and send the results to the Codecov.io service, which will track them for us.

**Step 5.** Login into your <https://codecov.io> account and add your "hello-numerical-world" repository to your account.

**Step 6.** Go to your repository's Actions page and view the last action.  Click the top-right button to "Re-run jobs".
This will fire off the `make check` and codecov uploads again.

This time, your codecov results will land on codecov.io.
This bit of magic is documented in the [Quick Start](https://docs.codecov.io/docs) documentation on Codecov.io.  It is referred to as the "Codecov bash uploader".

Note that the first time you upload to Codecov.io, it has no prior coverage information so it can't
provide information about the *change* in coverage represented by the update to the pull request.
As you commit more changes to the code itself, each pull request should now contain a small codecov summary,
including changes in coverage.

**Step 7.** Increase the code coverage by replacing `check` with `check_all` in the `check.yml` file.  Observe the changes via the Codecov.io report.  You can also examine the CI logs to see the change in the execution time for the `check` and `check_all` test suites.

**Step 8.** *Extra credit*: Make the CI test fail if code coverage drops from the previous version. (Hint: read the [codeco.io documentation](https://docs.codecov.io/docs).)  This failing tests will encourage contributors to your project to continually increase code coverage as they add code.
