---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: page
---
# Hands-On Exercise 8: Continuous Integration
## Goals
You'll establish a simple continuous integration workflow and then refine it, adding code coverage assessment

## Prerequisites
* A [GitHub](https://github.com) account
    - This exercise can be done entirely within the web interface to GotHub.
* A fork of the [betterscientificsoftware/hello-numerical-world-sc20](https://github.com/betterscientificsoftware/hello-numerical-world-sc20) repository in your account (covered in exercise 3)
* A [Travis-CI](https://travis-ci.com) account linked to your GitHub account
* A [Codecov](https://codecov.io) account linked to your GitHub account

## Background

A core idea of continuous integration is that CI checks are triggered by changes to the code, usually making or updating pull requests.  In this exercise, we're going to use the Travis CI service, which provides execution environments and resources on demand to run such tests.

Because understanding code coverage (how much of the code is exercised in the tests executed), we're also going to hook this CI check up to the Codecov.io service, which helps to visualize and track changes in code coverage as the code changes.

A video walk-through of (most of) this exercise is available at: <https://youtu.be/QE4RFp8lGiQ>
* This video was created by Mark Miller (LLNL) for tutorial at ATPESC earlier this year.  Where he refers to the repository as `hello-numerical-world-atpesc-2020`, substitute `hello-numerical-world-sc20`.


## Instructions

**Step 1.** You'll need to add a configuration file to your repository to tell Travis CI what should be done when it is invoked.  The file must be named `.travis.yml`.  Note the leading `.`.  In unix-like operating systems, this is a hidden file, that won't be displayed in directory listings by default.  But on Windows and in the GitHub web interface, such files are displayed by default.

```
language: c++

compiler:
  - gcc

script:
  - make check
```

The configuration file is written in the YAML markup language, which is pretty simple, but can be finicky with respect to indentation.  L1 and L3 of the file specify the environment that Travis CI needs to provide.  L6-L7 specify the command to execute when Travis is triggered.  Travis provides a rich set of capabilities.  You should peruse their documentation to learn more about them.

**Step 2.** Next you need to create a pull request to add this change to the upstream repository.  Travis is triggered by pull requests (among other things)

Once you create the pull request, you'll see GitHub performing a couple of checks.  One it always does is to look for conflicts between your PR and the base branch from which it was forked in the upstream repository (in case there were changes upstream that you haven't pulled into your fork yet).  And with the addition of the configuration file, the `make check` test is performed using the Travis CI service.  You'll often notice a short lag from the moment you click "Create pull request" to the moment the that checks start running.  But if it hasn't started running within about a minute, there's a good chance that there's a problem with your configuration file.

While the check is running, you will see a "Details" link that you can follow to drill into what's happening.  The immediate result of clicking on that link is a screen from GitHub summarizing what's happening.  At the bottom of the screen is a link "View more details on Travis CI".  If you follow that link, you should see the output of the `make check` execution, which includes building the heat equation code, running it with a specific set of inputs, and comparing the results with a "golden" set of results that's been deemed correct. If the check completes correctly on Travis (signaled by whatever script exiting with an exit code of 0), the pull request page will show that all checks passed, but will still provide a link to allow you to drill into the details.  Both GitHub and Travis keep logs from all these actions for some time.

If the check fails, the pull request page will show that, and the "Details" link will continue to be available to help you debug the problem.  You can see this situation for yourself by modifying something in the repository to intentionally introduce an error.  For example, you could change the `script` in the `.travis.yml` file to something nonexistent (Travis is otherwise pretty resilient to errors in configuration files, at least simple ones).  Or you could introduce a syntax error into one of the code files so that the compilation fails.  Or you could change the math in the code or the parameters in the `check` target of the `makefile` so that the results don't match the golden results.

### A Couple of Notes about GitHub

First, if you note carefully, the pull request that you create is not in your fork, but is in the upstream repository.  If you pay careful attention to the repository information at the top of the GitHub web interface, you will see that it differentiates between the upstream repository "betterscientificsoftware/hello-numerical-world-sc20" and your fork, which will have your username in place of "betterscientificsoftware" and beneath the repository name, it will have an annotation that it was forked from "betterscientificsoftware/hello-numerical-world-sc20".  You can navigate quickly back and forth between the upstream repository and your fork using that annotation (which will take from from your fork to the upstream repository) and the "Fork" button on the top right of the GitHub web interface.  If you're looking at the upstream version of a repository you've already forked, clicking the Fork button will take you straight to your fork.  If you're looking at your fork, clicking the annotation under the repository name will take you straight to the upstream repository.  **Things can be confusing if you're not in the repository you think you are.  Check often when you're working with pull requests.**

Second, until the pull request is merged upstream (or closed), further commits in your fork will be added to the existing pull request.  (If you think you might need to have multiple pull requests active at the same time from your fork, you should create each of them on a separate branch within your fork.)

### Adding Code Coverage Tracking

As mentioned, understanding how much of the code you're working with is covered by your testing is important for effective CI testing (really for *any* testing).  We're going to add coverage analysis to the build process and send the results to the Codecov.io service, which will track them for us.

**Step 3.** Login into your <https://codecov.io> account and add your "hello-numerical-world-sc20" repository to your account.

**Step 4.** Edit `.travis.yml` to add code coverage to the build, and reporting the results to Codecov.io:

```
language: c++

compiler:
  - gcc

script:
  - make CXXFLAGS=--coverage LDFLAGS="--coverage -lm" check

after_success:
  - bash <(curl -s https://codecov.io/bash)
```

The `after_success` block will update the CodeCov.io site with the coverage information from the check that just completed.  This bit of magic is documented in the [Quick Start](https://docs.codecov.io/docs) documentation on Codecov.io.  It is referred to as the "Codecov bash uploader".

Once you commit this change, it is added to your outstanding pull request.  If you switch to the upstream repository and go to your pull request, you'll see the results should now include code coverage information.  Note that the first time you upload to Codecov.io, it has no prior coverage information so it can't provide information about the *change* in coverage represented by the update to the pull request.

**Step 5.** Increase the code coverage by replacing `check` with `check_all` in the `.travis.yml` file.  Observe the changes via the Codecov.io report.  You can also examine the Travis CI logs to see the change in the execution time for the `check` and `check_all` test suites.

**Step 6.** *Extra credit*: Make the CI test file if code coverage drops from the previous version. (Hint: read the [codeco.io documentation](https://docs.codecov.io/docs).)