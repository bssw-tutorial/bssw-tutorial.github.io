---
layout: page
---
# Hands-On Exercise: Setting up the Prerequisites 

1. If you don't have a **GitHub** account already, please set one up (used starting in **exercise 2, agile**)
   - Go to <https://github.com>
   - Click the "Sign Up" button
   - Complete the signup form
   - Verify your account, as requested
   - On the "Welcome to GitHub" page, scroll to the bottom and click on "Complete Setup"
   - Complete the email verification process
   - Login to GitHub with your new account
   - Optional:
      - Enable two factor authorization (2FA), or setup ssh keys, to use the command line to push to fork.
        -  [Github 2FA](https://docs.github.com/en/authentication/securing-your-account-with-two-factor-authentication-2fa/configuring-two-factor-authentication)
        - [Github ssh keys](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)

2. If you don't have a **Codecov.io** account already, please set one up (used in **exercise 8, testing**)
   - Go to <https://codecov.io/>
   - Click the "Sign Up" button
   - Choose "Sign up with GitHub"
   - On the  "Authorize Codecov" page, click to "Authorize codecov"  

3. Though **exercise 3** can be completed entirely using the GitHub.com web interface, you might find it useful to get some experience with `git` on the command line in anticipation of later exercises (particularly during **exercise 11, refactoring**).
   - You may want to do this exercise on the same system you plan to use for **refactoring** exercises.
   - On Linux and Mac system, `git` should be available through your package manager if it is not already on your system.
   - On Windows systems, you have several options:
      - <https://gitforwindows.org/> is a command-line git client that can also work with the <https://tortoisegit.org/> graphical interface (we're not using TortoiseGit in these exercises, but it can be a convenient way to work with git on Windows systems).
      - Development platforms for Windows, such as  Cygwin or Msys2 also include git packages.  But these tend to be more work to install and configure so we don't recommend them unless you need other tools that they provide too (i.e., a complete unix-like development environment).

4. You'll need (access to) a development environment, supporting editing, compiling, and executing simple python, C++, or Fortran08 language code, and a git installation (used in **exercise 8, testing**)
   - This may be available on your local system (especially Mac or Linux)
   - A remote development environment that you can access via ssh will also work fine.
   - python3 virtual-environments (venv module) are used for the python example
   - cmake is used for C++ and Fortan examples
