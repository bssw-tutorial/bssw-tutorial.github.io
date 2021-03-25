---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: page
---
# Hands-On Exercise 0: Setting up the Prerequisites 

1. If you don't have a **GitHub** account already, please set one up (used starting in **exercise 2**)
   - Go to <https://github.com>
   - Click the "Sign Up" button
   - Complete the signup form
   - Verify your account, as requested
   - On the "Welcome to GitHub" page, scroll to the bottom and click on "Complete Setup"
   - Complete the email verification process
   - Login to GitHub with your new account

2. If you don't have a **Travis-CI** account already, please set one up (used in **exercise 8**)
   - Go to <https://travis-ci.com>
   - Click the "Sign Up" button
   - Choose "Sign up with GitHub"
   - On the  "Authorize Travis CI" page, click to "Authorize travis-pro"
   - On the "First time here?" page, click the "Activate all repositories using GitHub Apps" button
   - Select "All Repositories" (in general, you might want to be more selective in giving Travis-CI access to your repositories, but for now this is expedient).  Click "Approve & install"
   - On the Travis-CI page for your account, click "Activate" to activate the GitHub integration.

3. If you don't have a **Codecov.io** account already, please set one up (used in **exercise 8**)
   - Go to <https://codecov.io/>
   - Click the "Sign Up" button
   - Choose "Sign up with GitHub"
   - On the  "Authorize Codecov" page, click to "Authorize codecov"  

4. Though **exercise 3** can be completed entirely using the GitHub.com web interface, you might find it useful to get some experience with `git` on the command line in anticipation of later exercises (particularly exercises 7b and 7c).
   - You may want to do this exercise on the same system you plan to use for exercises 7b and 7c.
   - On Linux and Mac system, `git` should be available through your package manager if it is not already on your system.
   - On Windows systems, you have several options:
      - <https://gitforwindows.org/> is a command-line git client that can also work with the <https://tortoisegit.org/> graphical interface (we're not using TortoiseGit in these exercises, but it can be a convenient way to work with git on Windows systems).
      - Development platforms for Windows, such as  Cygwin or Msys2 also include git packages.  But these tend to be more work to install and configure so we don't recommend them unless you need other tools that they provide too (i.e., a complete unix-like development environment).

5. You'll need (access to) a basic development environment, supporting editing, compiling, and executing simple C++ language code, and a git installation (used in **exercise 7b and 7c**)
   - This may be available on your local system (especially Mac or Linux)
   - A remote development environment that you can access via ssh will also work fine.
   - The code you'll work with is very C-like, and the exercises don't require extensive knowledge of the language (i.e., Fortran programmers should not have much trouble).