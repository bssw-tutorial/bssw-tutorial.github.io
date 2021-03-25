---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: page
---
# Hands-On Exercise 3: Git Workflows 

## Goals
To fork a repo, create a branch and make a pull request

## Prerequisites
* A [GitHub](https://github.com) account
   - This exercise can actually be completed entirely via the GitHub.com web interface (UI), but we recommend using a command-line `git` client if you're interested in doing later exercises that can't be completed through the web UI (e.g., exercises 7b and 7c)

## Instructions 
*Note: The screen shots linked below show forking hello-numerical-world; for this tutorial fork hello-numerical-world-sc20 instead.*

**Step 1.** Fork repository hello-numerical-world-sc20: [(fork example)](images/03-git-fork.png)  
  - Click on the following link bellow and hit the fork button in the upper right corner:  
[hello-numerical-world-sc20](https://github.com/betterscientificsoftware/hello-numerical-world-sc20)
  - Choose your personal repo to fork into.  
  - Click on arrow next to code for path to clone. see [(find path to clone example)](images/03-git-path-to-clone.png)  
  - Click on ssh.  
  - Copy path to clipboard (use path in command below).  

**Step 2.** Clone the fork (on command line)  

```
   $git clone git@github.com:<your repo name>/hello-numerical-world-sc20.git 
Cloning into 'hello-numerical-work-sc20' ...
.
.
```

**Step 3.** Create branch  

```
   $cd hello-numerical-world-sc20
   $git checkout -b issue-1000
   Switched to a new branch 'issue-1000'
```

**Step 4.** Make Modification (use your favorite editor)  

```
   $vi README.md
   $ git diff
   diff --git a/README.md b/README.md
   index 3cd1a3c..b44c57e 100644
   --- a/README.md
   +++ b/README.md
   @@ -22,7 +22,7 @@ is known as the _Diffusion Equation_ and also the [_Heat Equation_](https://en.w
    
    ### Simplifying Assumptions
    
   -To make the problem tractable for this lesson, we make some simplifying assumptions...
   +To make the problem tractable for this lesson, we make some simplifying assumptions:
```

```
   $ git add README.md 
   $ git commit -m "Replace ... with :"
   [issue-1000 2271b74] Replace ... with :
    1 file changed, 1 insertion(+), 1 deletion(-)
```

**Step 5.** Useful git commands to check repo

```
   $git remote -vv
   origin	git@github.com:<your repo name>/hello-numerical-world-sc20.git (fetch)
   origin	git@github.com:<your repo name>/hello-numerical-world-sc20.git (push)

   $git branch
   * issue-1000
     main
```

**Step 6.** Push change to fork

```
   $ git push origin issue-1000
   Enumerating objects: 5, done.
   Counting objects: 100% (5/5), done.
   Delta compression using up to 8 threads
   Compressing objects: 100% (3/3), done.
   Writing objects: 100% (3/3), 300 bytes | 300.00 KiB/s, done.
   Total 3 (delta 2), reused 0 (delta 0)
   remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
   remote: 
   remote: Create a pull request for 'issue-1000' on GitHub by visiting:
   remote:      https://github.com/<your repo name>/hello-numerical-world-sc20/pull/new/issue-1000
   remote: 
   To github.com:<your repo name>/hello-numerical-world-sc20.git
    * [new branch]      issue-1000 -> issue-1000
```

**Step 7.** Issue pull request to upstream repository 
   - Visit your repository on github  
   - [compare branches](images/03-git-br-compare.png)  
   - [pull request](images/03-git-pr.png)  
   - [for pull request reviewer](images/03-git-pr-review.png)  