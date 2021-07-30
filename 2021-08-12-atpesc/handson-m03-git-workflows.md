---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: page
hands-on-repo-org: bssw-tutorial
hands-on-repo-base: hello-numerical-world-2021-08-12-atpesc
---
# Hands-On Exercise 3: Git Workflows 
{%- capture hands-on-repo -%}{{ page.hands-on-repo-org }}/{{ page.hands-on-repo-base }}{%- endcapture -%}

## Goals
To fork a repo, create a branch and make a pull request

## Prerequisites
* A [GitHub](https://github.com) account
   - This exercise can actually be completed entirely via the GitHub.com web interface (UI), but we recommend using a command-line `git` client if you're interested in doing later exercises that can't be completed through the web UI.

## Instructions 
*Note: The screen shots and instructions below refer to the generic hello-numerical-world repository.  For this event, you will use **[{{ hands-on-repo }}]({{ site.github-url }}/{{ hands-on-repo }})** instead.*

**Step 1.** Fork the tutorial repository: [(fork example)](images/03-git-fork.png)
  - Go to the repository that you want to fork: [{{ hands-on-repo }}]({{ site.github-url }}/{{ hands-on-repo }}) 
  - Hit the fork button in the upper right corner 
  - Choose your personal account to fork into.  

The fork you have created lives in your personal area in GitHub, but has the same base name (and the same contents) as the original repository, e.g.,  <your username>/{{ page.hands-on-repo-base }} .

**Step 2.** Clone the fork (on command line)
  - Click on arrow next to code for path to clone. see [(clone example)](images/03-git-clone.png)   
  - Copy path to clipboard (use path in command below). 

```
   $git clone https://github.com/<your username>/{{ page.hands-on-repo-base }}.git
Cloning into '{{ page.hands-on-repo-base}}' ...
.
.
```

**Step 3.** Create branch  

```
   $cd {{ page.hands-on-repo-base }}
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
   @@ -22,7 +22,7 @@ is known as the _Diffusion Equation_ and also the [_Heat Equation_](
   s://en.w
    
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
   origin	https://github.com/<your username>/{{ page.hands-on-repo-base }}.git (fetch)
   origin	https://github.com/<your username>/{{ page.hands-on-repo-base }}.git (push)

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
   remote:      https://github.com/<your username>/{{ page.hands-on-repo-base }}/pull/new/issue-1000
   remote: 
   To github.com:<your username>/{{ page.hands-on-repo-base }}.git
    * [new branch]      issue-1000 -> issue-1000
```

**Step 7.** Issue pull request to upstream repository 
   - Visit your repository on github  
   - [compare branches](images/03-git-br-compare.png)  
   - [pull request](images/03-git-pr.png)  
   - [for pull request reviewer](images/03-git-pr-review.png)  
