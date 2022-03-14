# bssw-tutorial.github.io

This is the source for <https://bssw-tutorial.github.io>, which is the primary web presence for the Better Scientific Software tutorials, produced by the [IDEAS Productivity](https://ideas-productivity.org) project.

## Overview 

This is plain vanilla Jekyll site, currently using the default Minima theme, which uses some structured data and a fair amount of Liquid scripting to present a web site hosting a subspace for each tutorial presentation (since 2021; eventually we'll incorporate the back catalog).  The main page lists all of the tutorials, categorized into

- Scheduled tutorials: events which have specific dates and times assigned and are open to registration.
- Planned tutorials: events which have been accepted by the hosting venue (e.g., a conference), but which have not yet been assigned a particular date and time.
- Past tutorials: events which have already taken place.

Events appear in the appropriate section based on the information in their `_data` files (primarily dates).  Of course the site must be rebuilt for changes to appear.

Each tutorial event is given a page of its own, and can have child pages as needed.

## Conventions

Each tutorial is given an "**event label**", which is used in many different contexts, both in the file structure of the repository and in the scripting that builds the site.  The event label is comprised of the event date in ISO 8601 format (`YYYY-MM-DD`) and a shorthand tag, usually based on the hosting venue (e.g., `atpesc`, `ecpam`, or `sc`).

Events often start as "planned" rather than "scheduled", meaning that the specific date of the tutorial is not known.  The convention in this case is to start with an event label based on the hosting venue (i.e., the first day of the conference, or the first day of the tutorials, if known) and then change the label to the correct date once it is known.  This is a bit inconvenient, as it requires changes in several places in the repository, but we prefer to have the final event label represent the actual date of the tutorial.

## Rebuilding

The site uses plugins that aren't blessed for GitHub Pages, and is rebuilt and deployed using the [Build and deploy jekyll site](https://github.com/bssw-tutorial/bssw-tutorial.github.io/actions/workflows/github-pages.yml) action.  This action is triggered by commits to be main, and can also be triggered manually (a `workflow_dispatch` trigger).

You can track the progress of the action on the [Actions](https://github.com/bssw-tutorial/bssw-tutorial.github.io/actions) tab of the repository.

It might be reasonable to automatically rebuild on a schedule to ensure that tutorials progress from the Scheduled list to the Past list, but at present, the events are infrequent enough that automating this seems to be overkill -- simpler just to remember to rebuild after the event.

## Repository Structure

The overall folder and file structure is largely that of a typical Jekyll site tree, but we mention some of the primary features to help those who might not be that familiar with Jekyll and to point out specific aspects of this site.

- Event directories (e.g., `2021-03-25-iss`) contain files associated with a specific tutorial event.  The contents of each event's directories will differ based on the specific needs of that tutorial, but generally, you might find:
  - Files pertaining to the hands-on activities, starting with `handson`.
  - `index.md` in which the YAML block specifies the assembly of the event's main page (details below).
  - Content blocks which are included into the `index.md` page to produce the event's main page, starting with `section`.  Section files in the event directory are specific to the event.  Generic content blocks are found in the top level `_includes` directory.
- `_data` is a standard Jekyll directory that for this site contains key metadata files for each of the events.  We use the separate `_data` directory rather than top-of-file YAML in a Jekyll collection structure because much of the information is needed in multiple files and in collections the top-of-file metadata is only available within that file.  Within this directory, you will find:
  - `bsswt` is a folder which holds all of the data files for all of the tutorial events.  It was put in the hierarchy with the idea that at some future time, we might want to put (at least the metadata) for different types of events together, in which case it might be convenient to group it by the type of event (`bsswt` is BSSw tutorial).  At present, this extra level serves no purpose.
    - Event directories (e.g., `2021-03-25-iss`) contain the metadata files for the specific tutorial event.  The event directory here the main event directory must use same event labels.
      - `artifacts.yml` contains a list of artifacts associated with the event.  Artifacts are highlighted in the event entry on the site's main page and also near the top of the individual event page.  During the tutorial this provides quick access to links that participants might need.  After the tutorial, this provides links to the archival artifacts that participants or other site visitors might want to explore.  Note that some artifacts useful *before or during* the tutorial might not be useful afterwards (e.g., links to the registration page), while others may only be available (or published) after the event (e.g., recordings/playlists, Q&A documents).
      - `deadlines.yml` contains internal deadlines for preparations for the event.  Used in generating issues.  Not clear yet whether this is useful.
      - `event.yml` contains the primary metadata about the event.
      - `presentations.yml` maps the shorthand labels for presentations, used in agendas generated from the Google Sheets template (starting with `2021-08-12-atpesc`), to the full titles of the presentations.  They may change from one event to the next, as the modules evolve.
- `_includes` is a standard Jekyll directory that holds reusable content and scripts that are used throughout the site.  An important constituent of this directory are generic content blocks which can be used in the assembly of the main pages for individual tutorial events, which, by convention, start with `section`.  Where event-specific content is needed, it will be in the event directory.
- `_layout` is a standard Jekyll directory that holds templates for different types of pages generated by the site.
- `_people` is a Jekyll collection, in this case, information about the presenters and helpers for the tutorials.
- `_plugins` is a standard Jekyll directory for plugins to the Jekyll system.  This site uses several plugins which are not part of the standard GitHub Pages collection of plugins, which necessitates having our own [build and deployment mechanism](#rebuilding).
- `reference-files` holds copies files that aren't part of the site directly, but which we might want to keep our own copies of, for example, the sources to the plugins that we use.
- `dev.md` is not currently used.
- `index.md` is the source for the main page of the web site.
- `people.md` is the source for a "people page" to provide more information about the people who present and help with tutorials.  This is currently rather rudimentary and is not linked in as an official part of the site.

## Creating a New Tutorial Event

This section will walk you through the lifecycle of a tutorial event.

### Creating a Planned Event

1) Add the event to `_data/tutorials.csv`.  The `event-label` list should be kept in lexical (chornological) order.  The possible `status` values are `planned` or `scheduled`. (Scheduled events become past events based on the date.)

2) Create a directory in `_data/bsswt/` corresponding to the `event-label`.

3) Create a `_data/bsswt/<event-label>/event.yml` file and populate it with the appropriate information. (Or copy from a recent event and modify.)  The core information for a *planned* event is:

```yaml
title: tutorial title, in quotes, e.g., "Better Scientific Software" (required)
title-type: the label associated with the event, e.g., "tutorial" or "track" (required)
title-url: a URL to link the tutorial title to, e.g., the conference program page (optional)
date: the starting date of the conference (since we don't yet know the actual schedule), e.g., 2021-11-15 (required)
end-date: the ending date of the conference (since we don't yet know the actual schedule) (optional)
venue: the name of the hosting venue (e.g., conference), in quotes, e.g., "The International Conference for High-Performance Computing, Networking, Storage, and Analysis (SC21)" (required)
venue-type: the label associated with the venue, e.g., "conference" or "workshop" (optional)
venue-url: A URL to linke the venue to, e.g., https://sc21.supercomputing.org/ (optional)
location: the geographic local or the event, in quotes, e.g., "St. Louis, Missouri and online" (optional)
```

4) Create the top level event directory, using the same `event-label` you've been using in the `_data` folder.

5) Create an `index.md` file and populate it with the appropriate information.  This file usually consists only of a YAML metadata block which defines the sequence of content sections to include.  An example of this file is shown below.  As stated in the comments within the file, initially you usually only include the `description` and `acknowledgement` sections.  Sections are included in the order listed in the `sections` variable. *Note: Older events may include a `redirect_from` variable, which is used to accommodate a restructuring of the web site while ensuring that older URLs which have been advertised in various places remain valid.  It should not be needed for new events.*

```yaml
---
layout: bsswt-event-page
event-label: 2021-11-15-sc
# A typical initial tutorial page might include:
#         [description,acknowledgments]
# A typical complete tutorial page would include: 
#         [description,agenda,presentation-slides,how-to-participate,hands-on-exercises,stay-in-touch,resources-from-presentations,requested-citation,acknowledgments]
sections: [description,agenda,presentation-slides,hands-on-exercises,related-events,stay-in-touch,resources-from-presentations,requested-citation,acknowledgments]
# Still outstanding: how-to-participate,
---
```

6) Create a `section-description.md` file in the event directory and populate it with the description or abstract for the tutorial event.  The description is unique to each event, so there is currently no generic description block in the `_includes` directory (but maybe there should be).  The file must start with the following line, which provides the section heading on the assembled page.

```
{% assign headings = headings | push: "Description" %}
```

7) **If needed** create a `section-acknowledgements.md` file in the event directory and populate it with the appropriate sponsorship acknowledgement.  The generic `_includes/section-acknowledgements.md` will be used is there is no file in the event directory to supersede it. The generic file contains the standard IDEAS-ECP acknowledgement, which applies to most of our tutorials.  If you create your own acknowledgement section for the event, it must begin with the following line to set the section heading for the assembled page.

```
{% assign headings = headings | push: "Acknowledgements" %}
```

### Transitioning to a Scheduled Event

Once you have a firm day and time for the event, you will need to update the relevant directory names and metadata entries.  There is no particular minimum requirements for the event page content to make the transition from planned to scheduled.  Initially, this change is simply about where in the main page list the event appears.  You can add content to the event page at any time, following the guidance in [Filling Out the Event Page](#filling-out-the-event-page), below.

1) In `_data/tutorials.csv` adjust the event label to reflect the actual event date, and change the status to `scheduled`. 

2) In `_data/bsswt/` rename the event directory to reflect the actual event date (same as the event label, above).

3) In `_data/bsswt/<event-label>/event.yml` update the metadata as appropriate.  If your event is on a single day, you can comment out the `end-date` key.  The `time` field is free-form.  Make sure to include the time zone along with the time.  Convention is to always use the natural time zone of the hosting venue.

4) Rename the top level event directory to reflect the actual event date (same as the event label).

5) In `<event-label>/index.md` update the `event-label` value to reflect the new event label.

### Filling Out the Event Page
