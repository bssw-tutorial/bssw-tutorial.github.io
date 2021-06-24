---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: page
---
# Hands-On Exercise 2: Agile Methodologies

## Goals
Use GitHub issues and project boards to setup a simple "personal kanban" board

## Prerequisites
* A [GitHub](https://github.com) account
   - This exercise can be done entirely within the web interface of GitHub.com

## Background
In Agile Methodologies lesson of the tutorial presentations, we discuss some approaches to project (and personal) management based on Agile principles.  In this exercise, we want to take some of the ideas from the presentation and show how they can be implemented in the GitHub.com platform.  GitHub.com is an easily (and freely) available platform that is widely used by software development teams.  It is just one of the many environments that can support these kinds of needs, so feel free to explore others and decide what best meets your needs. (And realize that your needs may well change over time.)

## Instructions 

### Where to Do the Work

This exercise comprises several different tasks that in the real world might have different targets.  The team policy document and the initiation checklist are most relevant for a multi-person team or research group.  The kanban board and associated issues might be used on a personal basis or for a project.  To simplify things for this exercise, we suggest using a freshly created repository in your GitHub area.   Once you understand the concepts and GitHub tools, you can implement the same ideas in other repositories as needed.  For a personal kanban board, you may want to keep it private, or be very selective in who you give access to (spouse or partner, supervisor, etc.).  But for purposes of this exercise, we encourage you to make the repository **public** so that we can view and provide feedback if requested.

### Creating a New Repository

**Step 1.** Login to your GitHub account.  There are two ways to create a new repository.  One is the "+" symbol on the upper right side of the screen.  The other is the green "New" button next to the word Repositories at the top of the left-hand navigation panel that lists your repositories and teams (if you don't have any repositories yet, it may be an even more prominent green button labeled "Create repository").
   - Enter a name for your repository.  For example, "Issues" or "Personal Kanban".
   - As discussed above, we encourage you to make this repository **public**, though in real situations, there may be reasons to keep it private.
   - It is convenient to initialize the repository with a README, but don't add a .gitignore file or a license (all of these can, of course, be added at any later time too)
   - Click "Create repository"

If you're not familiar with the GitHub web interface, you might want to take a few minutes now to explore your new repository.  Of course the only thing it contains is a `README.md` file, but you can check out the different functionality that GitHub provides, etc.

### Defining a Team Policy

A best practice for collaborative communities (whether they're collaborating on software or other things) is to set expectations for the behavior of people in the community towards each other.  These are often referred to as team policies or codes of conduct.  A team policy can be captured in a document in a shared repository or other collaborative space.

Think about a code of conduct that would be appropriate for a project you're involved in or your research group.  Some questions to consider include:
* How do team *members* support the team?
* How does the *team* support its members?
You may want to explore codes of conduct used by other teams similar to yours.  For example, https://www.contributor-covenant.org/ is a widely used policy for open source software development projects.

We'll use GitHub's web interface to capture the policy.  But remember that such policies should be living documents -- be ready to revisit and update them to try to address negative situations that might not have been adequately dealt with, or to capture positive practices.

**Step 2.** In your repository, go to the "Code" tab.
- Click the "Add file" button to create a new file for the policy.
- Give the file an appropriate name, such as `CODE-OF-CONDUCT` or `TeamPolicy` (to use Markdown rather than plain text, add a `.md` suffix to the filenname).
- In the text area, enter the text of your policy
- The fields beneath the "Commit new file" heading will comprise the commit message for your new file.  It is a good practice to provide informative commit messages for all commits, but it is not required.
- Click "Commit new file" to complete the commit.

If you need to edit the file after you commit it, that's also possible in the GitHub web interface.
- Click on the file of interest in the Code tab's file browser to view it.
- On the top right margin of the text area, you will see several buttons.  Click the pencil icon to edit the file in the web interface.

### The Basics of GitHub Issues

Issues, sometimes referred to as "tickets" or other terms, can be used for many things.  The term "issue" derives from the idea of using them to track problems users encounter with a code, and help manage their resolution.  But they can also be used to manage work on a project, in which case an issue might descript a task that needs to be done.

**Step 3.** In your repository, go to the "Issues" tab.  Think about a project you're working on where you have a couple of tasks that need to be done.
- Click the green "New issue" button near the top right of the screen
   - Give the issue a title that reflects the first task you need to do.  In the body, provide a short description of the task.  Click "Submit new issue".
   - Repeat until you have two or three issues in your repository.

### An Initiation Checklist

Checklists are very useful tools, for example to on-board (or off-board) people into a project.   Think about some steps that would be useful for newcomers to a project you're involved in.

While you could create a separate issue for each checklist item, GitHub Flavored Markdown (the common name for the dialect of Markdown that GitHub understands) supports **checklists**, which are rendered with checkable boxes as the list markers.
- The Markdown is `- [ ] item text` where the "-" is the usual markup for an unordered list and spaces are required in the second, fourth, and sixth positions: `-2[4]6item text`.  The checklist can appear at any level of indentation.
- When the checklist is rendered in the web user interface, items can be checked or unchecked with a click of the mouse.  Note that there is no audit trail for checklist actions (i.e. you don't know who checked/unchecked them, or when it happened.) 

**Step 4.** In the Issues tab, click on "New issue".
- Create an on-boarding checklist with at least two or three items on it.  Make sure to give it an informative title.

**Step 5.** Review your list of issues.  You should see both the task issues and the on-boarding issue.  View the on-boarding issue.  Note that the checklist is rendered as checkable boxes.  You can check and uncheck items to try it out.


### Kanban Board

Select Projects tab
Click New Project
Use title 
Team Kanban board
Add these columns:
Backlog, Ready, In progress, In review, Done.
Click on +Add cards (upper right).
Move each issue to the proper Kanban column

### A Kanban Board

Next, we're going to setup a simple kanban board that you can use to manage the project you've been creating issues for.

**Step 6.** Go to the Project tab in your repository and create a project.  We suggest calling it "Project Management".  Provide a description if you like.  For the Template, select "Basic Kanban".  Click "Create project".  The result should be a project board with columns labeled "To do", "In progress", and "Done".
   - The To do column starts out with three "notes", which take up a lot of space.  You may want to give them a quick read and then delete them by clicking the ellipsis (three dots) menu and selecting "Delete Note" on each.

**Step 7.** Add the issues you have created to the project board by clicking the "+ Add cards" button on the top right of the project board, next to the filter widget.  The default search in the popup ("is:open") should display the issues you've created.  One by one, drag each of them to the To do column of the project board.  Remember that creating new issues doesn't automatically add them to the project board, you have to do this manually. (There are good reasons that this is the default behavior, and there are ways to change it, using automations built into the project board (more below) or GitHub Actions.)
- *Extra credit*: There is a way to add a new issue to a project board while you're creating it, on the New issue screen.  Can you find it?

**Step 8.** Add an "In Review" column to your project board.  
- Click "+ Add column" to create the new column, and name it "In Review".
- Drag it between the "In Progress" and "Done" columns.

**Step 9.** Drag the issues to the appropriate columns on the board.

**Step 10.** Suppose you've finished a task.  Dragging it to the Done column indicates that, and scanning the Done column can give you reminders about the work you've completed when it comes time to report to your supervisor, for example.  But it is also useful to *close* tickets that are done so that, by default, they will no longer appear on the list of issues in the Issues tab or in searches there or on the project board.
- To close an issue from the project board, click on its title to open a side panel on the right that shows a summary.  At the bottom of the summary are two large buttons.  One takes you to the full issue, which is convenient if you need to review it more carefully ot make more extensive revisions.  The other will close the issue.  You can click "Close issue" right there, without having to go to the full issue view to close it.  Notice that on the kanban board, the icon to the left of the issue title changes to include a check mark to indicate that it is done.

**Step 11.** Project board automations. GitHub offers a few built-in "automations" to help you manage project boards.  One of them is to automatically place newly-created issues in a particular column on the project board.  Another is to automatically move issues (also pull requests) to a particular column when they are closed.
- Let's start with the "To do" column. Access the automation menu, open the ellipsis (three dots) menu opposite the column title and selecting Manage automations.
   - Notice the first selection is the "preset" for the type of behavior you want the automation to use for that column.  You'll notice that the default is "To do", just like the column name.  But being able to select the preset in this way means that you're not tied to a specific column name to get the automation behavior you want.  So you could call this column "Backlog" or something else and still give it the "To do" behavior.
   - The To do preset allows you to select behaviors for both new and reopened issues and pull requests.  You should select the behaviors that make the most sense for the way your project works.  Some considerations...
      - If you have multiple project boards for a single project, you may need more sophistication in directing new issues (pull requests) to different boards, in which case you probably need to investigate GitHub Actions (beyond the scope of this exercise).
      - A common occurrence is that someone inadvertently closes and issue and then will notice and immediately reopen it.  In such cases, you probably want the issue to stay in the column it was in when it was closed.  You can, of couse, manually drag those to To do or whatever column is appropriate.
      - If you have also setup a "Done" automation that moves closed issues to the Done column, the above scenario may become moot.  In which case you may actually prefer that reopened issues get moved to the To do column rather than getting lost among the things that really are done in the Done column.
      - For pull requests, in some projects, the protocol is to start with an issue and expect that each pull request will be directly associated with an issue.  In situations like that, you may prefer for new pull requests to be moved into the In progress column rather than To do.
   - Once you've configured the automation as you want, click "Update automation".  Note that you can always update or remove automations if you find that they're not working well for you.
- Next. let's open the Manage automations menu for the "Done" column.
   - In this case, we want the "Done" preset.  Select the behaviors you want for issues and pull requests that are marked as closed.  In our experience, all three of the available behaviors will make sense for many projects.
- Experiment with creating and closing issues to verify that the automation is behaving as you expect.  Try closing issues in different columns of the board.  Note that there may be a short lag between creating or closing the issue (pull request) and the automation moving it, so give it half a minute or so.
- *Extra credit*: In the discussion above, we mentioned a scenario where your project wants new *issues* to appear in the To do column, but new *pull requests* to appear in the In progress column.  How would you implement that with automations?

*Note: GitHub is not always completely self-consistent.  For example, the preset for an "In progress" column refers to other automations to do with approvals.  But we've never seen such presets in any of our work. Our guess is that perhaps they're implementing additional features and parts may have "leaked" into their production environments.  Hopefully we'll see the full functionality soon.*

## Putting it into Practice

You already know enough about the GitHub tools to put them to work in your project and/or your personal life (the concept of managing your own activities through a "personal kanban" approach). As you've seen, kanban is a lightweight process to get started with.  There are no hard and fast rules.  You can tailor your process to the needs of your particular project (or your own life). Also, if you forget to maintain your kanban board for a while, or get overwhelmed with other things, it is easy to resume and get yourself (or your team) back on track.