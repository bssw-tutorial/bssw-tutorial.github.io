---
layout: page
---
{%- include set-event-label-from-path -%}
{%- assign my-artifacts = site.data.bsswt[event-label].event.artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

{%- unless hands-on-repo-link -%}{%- assign hands-on-repo-link = "hands-on-repo-link (to be defined)" -%}{%- endunless -%}
{%- unless hands-on-repo-dir -%}{%- assign hands-on-repo-dir = "hands-on-repo-dir (to be defined)" -%}{%- endunless -%}

# Hands-On Exercise: Agile Redux

## Goals
Create epic, story, and task issues for the refactoring exercises and track them on a kanban board

## Prerequisites
* A [GitHub](https://github.com) account
* A fork of the {{ hands-on-repo-link }} repository in your account (covered in Git Workflows exercise)
   - This exercise can be done entirely within the web interface of GitHub.com

## Background
In the tutorial presentations, we will discuss the refactoring process.  In the [refactoring](../handson-m11-refactoring1.html) exercise, your task will be to actually refactor some code you've inherited.  But before we start on the code, we're going to make a plan in the form of GitHub issues that we can use to track the plan to completion.  You may want to read through that exercise before starting this one, to get a better feel for the assignments.  In the refactoring exercise, we encourage you to use the setup you'll create here (issues and project board) to track your progress.

We're going to consider the refactoring effort to be at the level of an "epic", and break it down into several "stories", each consisting of several tasks.  In the usual definitions, epics are high-level objectives, stories should represent increments of value to the customer, and tasks are the step necessary to complete the story.

## Instructions 

### Where to Do the Work

We're going to be working with issues to manage development work on the {{ hands-on-repo-dir }} repository. You forked this repository (made a copy in your own GitHub account) in an earlier exercise  But if you check the tabs for your fork, you will see that Issues is missing.  In the "default" fork-pull request model of interaction, you and your team would be working on issues in the upstream repository, where everyone can easily see and update them.  So, by default, when GitHub forks a repository, it disables the Issues on the resulting fork.

In this case, everyone doing the exercise is doing the same tasks, which wouldn't normally happen in a coordinated project.  So to avoid the confusion of everyone using the upstream repository's issues and project boards, we recommend that in this case you do one of the following instead.
   - Use the issues-only repository you created for exercise 2 (or create another issues-only repository in your account).
   - You can enable issues in your fork of the {{ hands-on-repo-dir }} repository by going into the Setting tab, scrolling down to the Features section, and checking the box next to Issues.

### Working with GitHub Issues

**Step 1.** In your chosen workspace, create an issue corresponding to the epic.  Feel free to enter whatever you feel is appropriate.  Here is what we used when we did this exercise ourselves.
   - **Title:** Epic: Refactor code for enhanced modularity
   - **Description:** The heat equation code needs refactoring to improve modularity. Specifically, there are utilities that could be generalized and used with for other applications. Also, the integration function is currently hard-coded. In the future, we want to use alternative integration functions, so we should generalize the interface for this function.

We suggest breaking the epic into two stories, representing distinct results that the customer would find useful. Each of these stories will need its own GitHub issue.  Each issue should include a definition of done -- how will we know when the work of the story is completed -- and the individual tasks needed to do to the work.

**Step 2.** Create a GitHub issue for the first story
   - **Title:** Story: Separate out utilities
   - **Body:**
      - Definition of done: 
         - Unit tests pass
         - Code review completed
         - Integration/system tests pass
         - Utility performance is at least 95% of pre-separation performance
         - Utility usability demonstrated outside of heat equation application
      - Tasks required
         - *define the tasks you think are required*

**Step 3.** Create a GitHub issue for the second story
   - **Title:** Story: Separate out the integration function
   - **Body:**
      - Definition of done: *define this for yourself*
      - Tasks required
         - Task 1: Add testing for integration function to protect functionality during refactor
            - Needed testing should be specified
         - Task 2: Generalize interface to allow alternative implementations
         - Task 3: Expose current integration function through the new interface & run tests

### Some Tips for GitHub Issues

* While it is natural to add comments to issues, it is also sometimes useful to **edit the body of an existing issue**. You can do this through the ellipsis (three dots) menu on the top right side of the box containing the body of the issue.
* GitHub Flavored Markdown (the common name for the dialect of Markdown that GitHub understands) supports **checklists**, which are rendered with checkable boxes as the list markers.
   - The Markdown is `- [ ] item text` where the "-" is the usual markup for an unordered list and spaces are required in the second, fourth, and sixth positions: `-2[4]6item text`.  The checklist can appear at any level of indentation.
   - When the checklist is rendered in the web user interface, items can be checked or unchecked with a click of the mouse.  Note that there is no audit trail for checklist actions (i.e. you don't know who checked/unchecked them, or when it happened.)
* You can **cross-reference** issues (and pull requests) by their number, e.g., `#23`.  Such cross-references will be rendered as links to the item referenced, and hovering over the link will provide a preview of the item.
* GitHub starts each repository with a small set of default **labels** that can be applied to issues (and pull requests), but it is also possible to define your own (and remove the pre-defined ones) if you want.
   - If you're looking at a specific issue, you will see the Labels widget in the column of widgets to the right of the body of the issue.  Clicking on the gear opens the current list of labels and allows you to assign them to the issue you're looking at, as appropriate.  At the bottom of the label list is an option to Edit the labels, which takes you into a new view of all of the labels in the repository and allows you to add, remove, or change them.
   - The other way to access this list of labels is from the listing of all issues in the repository.  Just above the list is a row with a filter widget, buttons to edit the labels and milestones for the repository, and a button to create a new issue.

Unfortunately, GitHub issues don't support hierarchies of issues, such as epic-story-task.  If you don't have many issues, you might be able to keep them straight.  But in a long-running project with active development and many issues it might be hard to keep track of the relationships.  There are a couple of strategies you can use, individually or in combination to help make things a little easier (you may come up with additional approaches).
   - Limit the hierarchy of issues to two levels (epic and story) by using checklists within the story to manage the individual tasks (you could also use them for the done criteria).
   - You can identify issues as epic or story (or task if you're using issues at that level) using labels or by prefixing the issue titles with their level, as we've suggested in the instructions above.  Note that this identifies the level of the issue, but it does little to help you connect which story issues are related to which epic issues.
   - You can use the cross-referencing capability to add notes to the bodies of the issues to connect them.
      - For example, you might establish the convention that the first line of the body of a story always references the parent epic.
      - And in the body of the epic, you might list the stories that comprise it, with a cross-reference to the issue number followed by the issue title.

**Step 4.** Use cross-references, labels, and checklists to make the issues you created above better interlinked and easier to manage.  For things like this, we recommend editing the body of the issues rather than adding comments to the issues.

### Working with GitHub Project (Kanban) Boards

Next, we're going to setup a simple kanban board that you can use to track the progress of your refactoring work in refactoring exercise.

**Step 5.** Go to the Project tab in your chosen workspace and create a project.  We suggest calling it "Project Management".  Provide a description if you like.  For the Template, select "Basic Kanban".  Click "Create project".  The result should be a project board with columns labeled "To do", "In progress", and "Done".
   - The To do column starts out with three "notes", which take up a lot of space.  You may want to give them a quick read and then delete them by clicking the ellipsis (three dots) menu and selecting "Delete Note" on each.

**Step 6.** Add the issues you have created to the project board by clicking the "+ Add cards" button on the top right of the project board, next to the filter widget.  The default search in the popup ("is:open") should display the issues you've created.  One by one, drag each of them to the To do column of the project board.

**Step 7.** While you're working on the refactoring exercise, use the project board and issues to track your progress.