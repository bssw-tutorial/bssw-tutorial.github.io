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
      - `presentations.yml` maps the shorthand labels for presentations, used in agendas generated from the Google Sheets template (starting with `2021-08-12-atpesc`), to the full titles of the presentations.  They may change from one event to the next, as the modules evolve.  If a module has been presented under one title, you should create a *new* label for it if the title changes.  Otherwise there may be confusion, even though each event has its own `presentations.yml` file.
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

Building out the contents of the page for a tutorial event can be carried out incrementally, section by section, as appropriate, under the control of YAML metadata in the `<event-label>/index.md` file, for example:

```yaml
---
layout: bsswt-event-page
event-label: 2021-11-15-sc
# A typical initial tutorial page might include:
#         [description,acknowledgments]
# A typical complete tutorial page would include: 
#         [description,agenda,presentation-slides,how-to-participate,hands-on-exercises,stay-in-touch,resources-from-presentations,requested-citation,acknowledgments]
sections: [description,agenda,presentation-slides,hands-on-exercises,related-events,stay-in-touch,resources-from-presentations,requested-citation,acknowledgments]
---
```

The sections shown in the `sections` array above are typical, but not limiting.  Sections can be added or removed, and their order changed simply by changing the `sections` array contents.  They are included into the events `index.md` page in the order that they appear in the `sections` array. The scripting the builds the page looks for section content in two places: First in the `<event-label>/` directory and then in the `_include/` directory.  In this way, local versions of a section, which are tailored for the event will take precedence over the stock versions in `_includes/`.  For some sections, it does not make sense to have a stock version, while for others the stock version is parameterized in such a way that rarely is an event-specific version needed.

Section files are, by convention, named `section-<section-heading>.md` regardless of which location they are in.  They should contain Markdown and may also use Liquid scripting.  The first line of a section file must contain a line of Liquid script which adds the textual heading for the section to an array of those heading, where `Acknowledgments` is replaced with whatever heading text is appropriate.

```
{% assign headings = headings | push: "Acknowledgements" %}
```

Below are specific instructions on a section-by-section basis.

#### Description

This is usually the abstract or description of the tutorial, but can be whatever descriptive text is needed.  There is very brief stock description if you don't want to provide one tailored to the event.  The `description` section is usually included on the event page from the start (even at the Planned stage).

#### Acknowledgments

This is usually the funding acknowledgement.  There is a stock acknowledgment of ECP support that should suffice for all but the earliest tutorials.  The `acknowledgments` section is usually included on the event page from the start (even at the Planned stage).

#### Agenda

While the agenda can be defined manually, there is now scripting that can render a properly structured spreadsheet in the usual form in which present an agenda.  The spreadsheet, in our Google Drive workspace, is setup with formulas to simplify calculating times for each module.  It also supports hiding columns.  Presentation titles use shorthand labels which are defined in a `_data/bsswt/<event-label>/presentations.yml` file.  Presenters use GitHub IDs, and corresponding information should be provided in the `_people/` directory for affiliations, etc. Details instructions in the use of the agenda spreadsheet template can be found in the `TUTORIAL-HOWTO` document in Google Drive.

If the automatic agenda is sufficient for your needs, you can set it up with the following steps:

1) Download the spreadsheet as a CSV (comma-separated variable) format file and move it into `_data/bsswt/<event-label>/agenda.csv`.
2) Add the appropriate `_data/bsswt/<event-label>/presentations.yml` file to provide the full presentation titles.  This file only changes when new presentations are added or their titles change (in which case they should get a *new* label, since older tutorials will have used the older titles), so it is likely you can copy it from another recent event.
3) Add the `agenda` section to the `sections` array in the `<event-label>/index.md` metadata.
4) Make sure that all of your presenters have entries in the `_people/` folder.
5) Since you know the staffing, you can also add it to `_data/bsswt/<event-label>/event.yml` in the `presenter-ids` and `helper-ids` variables.

If you want to leverage the automatic agenda capability, but need to provide additional text along with the table, you can copy `_includes/section-agenda.md` to your `<event-label>/` directory and modify it.

#### Presentation-Slides

Our convention is to post the PDFs of the presentations to an archival service, like FigShare, and obtain a DOI for then to reference on the event page.  With FigShare, the DOI can be reserved once the record is started, well in advance of actual publication.  The DOI is captured in `_data/bsswt/<event-label>/artifacts.yml` with an entry of the form:

```yml
  - label: Presentation Slides
    format: FigShare
    doi: 10.6084/m9.figshare.16556628
```

The stock `section-presentation-slides.md` include file keys on an artifact entry labeled `Presentation Slides` and provides a link to the given DOI.  If the `Presentations Slides` artifact is not available, the stock version of the section will indicate that the presentations will be published shortly before the event.

Best practice is to reserve the DOI early in the process (it is also needed for the citation information on the licensing slide included in all of the presentations), add it to `artifacts.yml`, confirm locally that it is properly formatted, and then comment out the artifact entry until the presentations are published.  When uncommented, you should observe the `Presentation Slides` artifact (with the event's entry on the main page as well as at the top of the event page), as well as the seeing the proper DOI in the `Presentation Slides` section.

Best practice is to use the form of the DOI that always points to the latest version of the archival record.

The stock section does not accommodate a version history.  That could be added via a local section include file (starting from `_includes/section-presentation-slides.md`).  It is not clear how useful it is to tutorial participants to track the version history.  This is a possible future enhancement.

#### Resources-from-presentations

The purpose of this section is to list the resources (links) that are mentioned in the various presentations in a way that might be (a) easier to access, and (b) places them all together in a single place.  

The stock section (`_includes/section-resources-from-presentations.md`) usually provides what is desired here.  It depends on the following files:

* `_data/bsswt/<event-label>/presentations.yml` for the mapping of presentation labels to titles
* `_data/bsswt/<event-label>/agenda.csv` for the order of presentation

The resource listings themselves live in the event's directory: `<event-label>/presentation-resources/<presentation-label>.md`.  Each file contains a list of resources for the particular presentation of the filename.  By convention, the file starts with a comment to help identify which presentation the resources are for, and contains an unordered list of the resources in the same order as they're found in the presentation.  The resource files must change as the presentations evolve, so each event has its own copy.  The `presentation-resources` directory can usually be copied from most recent past tutorial as a starting point.

The stock definition of this section will process the resource files in the agenda order.  The rendered listing will have the module number and presentation title for each (generated by the section file) and include the content of the `<presentation-label>.md` file.  Resources for presentations not included on the agenda are not listed, and their resource files are simply ignored.  Thus it is safe to propagate the full set of `presentation-resources` from one tutorial to the next.