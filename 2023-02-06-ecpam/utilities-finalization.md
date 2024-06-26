---
layout: default
---
{%- include set-event-label-from-path -%}
{%- assign my-event = site.data.bsswt[event-label].event -%}
{% if my-event.artifacts %}
  {% assign my-artifacts = my-event.artifacts %}
{% else %}
  {% assign my-artifacts = site.data.bsswt[event-label].artifacts %}
{% endif %}
{% include key-artifact-shorthands artifacts=my-artifacts %}
{% assign my-presentations = site.data.bsswt[event-label].presentations %}
{% assign my-agenda = site.data.bsswt[event-label].agenda %}
{% include set-presentation-order agenda=my-agenda presentations=my-presentations %}
{% assign my-organizers = site.data.bsswt[event-label].event.organizer-ids %}
{% assign my-presenters = site.data.bsswt[event-label].event.presenter-ids %}
{% assign my-helpers = site.data.bsswt[event-label].event.helper-ids %}
{% assign my-deadlines = site.data.bsswt[event-label].event.deadlines %}

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities) > [finalization]({{ site.url }}/{{ event-label }}/utilities-finalization)

{% comment %}
  Check some high-level variables and issue warnings or errors where appropriate.
  Doing this after the breadcrumbs so the flow of the page makes sense.

  NOTE: `event-label` is central to everthing on this page, but we don't bother checking it because
  we're extracting it from the file's path information, which should never fail. (He says with fingers crossed)
{% endcomment %}

{% unless my-artifacts %}
  {% capture msg %}`artifacts` not defined in file `_data/bsswt/{{ event-label }}/event.yml` (preferred) or `_data/bsswt/{{ event-label }}/artifacts.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-presentations %}
  {% capture msg %}`presentations` not defined. Check file `_data/bsswt/{{ event-label }}/presentations.yml{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-agenda %}
  {% capture msg %}`agenda` not defined. Check file `_data/bsswt/{{ event-label }}/agenda.csv`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-organizers %}
  {% capture msg %}`organizer-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-presenters %}
  {% capture msg %}`presenter-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-deadlines %}
  {% capture msg %}`deadlines` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}

# Help for Post-Acceptance Finalization of New Tutorial

{% unless my-organizers %}
**Step 0: Specify the organizers for the new tutorial.  Their GitHub IDs should be added to the `organizer-ids` field in the file `_data/bsswt/{{ event-label }}/event.yml`.  Everything on this page, and many things in the other phases of producing a tutorial are tasks for the organizers.**
{% endunless %}

## Add milestone to GitHub repositories

{% assign incomplete = false %}
{% unless my-event.startdate %}
  {% assign incomplete = true %}
  {% capture msg %}`startdate` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% comment %}
  Calculate a reasonable due date for the GitHub milestone.

  The timestamp returned will be 12:00:00am UTC (midnight), in other words,
  the very beginning of the day.  So we need to make it the end of the day
  (adding 23:59:59) and then shift it from UTC to AOE (UTC-12) because we don't know the actual time zone of the specified end date for the tutorial (and the
  milestone due date isn't critical).  There are 86400 seconds in a day.  So
  we add 84399 + 43200 seconds.
{% endcomment %}

{%- if my-event.enddate -%}
  {%- assign due = my-event.enddate | date: "%s" -%}
{%- else -%}
  {%- assign due = my-event.startdate | date: "%s" -%}
{%- endif -%}
{%- assign due = due | plus: 86399 | plus: 43200 -%}

**Note: The issues below will refer to this milestone, so this step should be completed before issues are generated in the bssw-tutorial repositories.**

1. Obtain an updated clone of the bssw-tutorial/tutorial-management repository
2. Add the following to the `milestones` section of `master-labels-milestones.json`
    {% if incomplete %}
      {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
    {% else %}
    ```json
      }, {      
        "title": "{{ event-label }}",
        "state": "open",
        "due_on": "{{ due | date: '%FT%T%:z' }}"
    ```
    {% endif %}
3. While editing the file, take a minute to update the state to `closed` for milestones for tutorials which have been completed (including any post-event follow-up)
4. `git commit -m "Added milestone for new event"; git push`
5. Run `npx github-sync-labels-milestones -t <pat> -c master-labels-milestones.json -v` where `<pat>` is your GitHub [Personal Access Token](https://docs.github.com/en/github/authenticating-to-github/keeping-your-account-and-data-secure/creating-a-personal-access-token)

*Reference for this procedure: <https://github.com/bssw-tutorial/tutorial-management/blob/main/Github-organization-structure-and-management.md#synchronizing-issues-and-milestones>*

## Main issue for post-acceptance finalization

{% assign incomplete = false %}
{% unless my-organizers %}
  {% assign incomplete = true %}
  {% capture msg %}`organizer-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
gh issue create \
  --repo bssw-tutorial/tutorial-management \
  --milestone "{{ event-label }}" \
  --title "{{ event-label }} post-acceptance finalization" \
  --assignee "{{ my-organizers | array_to_sentence_string: ',' | remove: ' ' }}" \
  --body-file - << EOF
- [ ] Add a milestone for the event to master-labels-milestones.json and synchronize repositories
- Internal and external awareness
  - [ ] Add issue the ideas-productivity/project-management
  - [ ] Add to main page and Events pages of <https://ideas-productivity.org/>, if appropriate
- Plan development activities
  - [ ] Finalize plans for content development
  - [ ] Finalize plans for hands-on, including necessary development
  - [ ] Set internal deadlines as needed
  - [ ] Capture internal and venue deadlines in \`deadines\` structure in \`_data/bsswt/{{ event-label }}/event.yml\`
- [ ] Start building event page in the tutorial website
- Plan staffing and agenda
  - [ ] Finalize presenters, set \`presenter-ids\` in \`_data/bsswt/{{ event-label }}/event.yml\`
  - [ ] Finalize helpers, set \`helper-ids\` in \`_data/bsswt/{{ event-label }}/event.yml\`
  - [ ] Finalize agenda, add \`_data/bsswt/{{ event-label }}/agenda.csv\` and \`_data/bsswt/{{ event-label }}/presentations.yml\`
- [ ] Transition from planned to scheduled, if necessary

EOF

```
{% endif %}

---

## Awareness issues

{% assign incomplete = false %}
{% unless my-event.startdate %}
  {% assign incomplete = true %}
  {% capture msg %}`startdate` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless my-event.title %}
  {% assign incomplete = true %}
  {% capture msg %}`title` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless my-event.venue %}
  {% assign incomplete = true %}
  {% capture msg %}`venue` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless my-organizers %}
  {% assign incomplete = true %}
  {% capture msg %}`organizer-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% comment %}
  The ideas-productivity/project-management repository uses a YYYY-MM convention
  in the naming of its milestones.  Let's accurately compute that based on the
  end date of the tutorial.  This is the same computation as we did above.
{% endcomment %}

{%- if my-event.enddate -%}
  {%- assign ms-date = my-event.enddate | date: "%s" -%}
{%- else -%}
  {%- assign ms-date = my-event.startdate | date: "%s" -%}
{%- endif -%}
{%- assign ms-date = ms-date | plus: 86399 | plus: 43200 -%}

{% capture description %}{% include emit-event-description event=my-event %}{% endcapture %}

{% capture body %}To be held {% if my-event.time %}{{ my-event.time }} {% endif %}{{ my-event.startdate | date: "%A %d %B %Y"}}{% if my-event.enddate %} - {{ my-event.enddate | date: "%A %d %B %Y"}}{% endif %}{% endcapture %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
gh issue create \
  --repo ideas-productivity/project-management \
  --milestone "Complete by {{ ms-date | date: '%Y-%m' }}" \
  --label "Outreach" --label "External Event" \
  --title "{{ description }}" \
  --assignee "{{ my-organizers | array_to_sentence_string: ',' | remove: ' ' }}" \
  --body "{{ body }}"

```
{% endif %}

---

## Issue to track development of tutorial web page

{% assign incomplete = false %}
{% unless my-organizers %}
  {% assign incomplete = true %}
  {% capture msg %}`organizer-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
gh issue create \
  --repo bssw-tutorial/bssw-tutorial.github.io \
  --milestone "{{ event-label }}" \
  --title "{{ event-label }} web page" \
  --assignee "{{ my-organizers | array_to_sentence_string: ',' | remove: ' ' }}" \
  --body-file - << EOF
- Inital creation of event web page
  - [x] Add event to \`_data/tutorials.csv\`
  - [x] Create event data directory \`_data/bsswt/{{ event-label }}\`
  - [x] Create event data file \`_data/bsswt/{{ event-label }}/event.yml\` as a copy of \`_data/event-template.yml\`
  - [x] Add basic information to event data file
  - [x] Create event directory \`{{ event-label }}\`
  - [x] Copy \`index.md\` and \`utilities*.md\` from previous event
  - [ ] In \`{{ event-label }}/index.md\` update \`event-label\` and \`sections\` appropriately
- [ ] Transition from planned to scheduled, if necessary
- Data needed
  - In \`_data/bsswt/{{ event-label }}/event.yml\`
    - [ ] Scheduled \`startdate\`, \`enddate\`, and \`time\`
    - [x] \`organizer-ids\`
    - [ ] \`presenter-ids\`, \`helper-ids\`
    - In \`artifacts\`
      - [ ] conference registration URL (if appropriate)
      - [ ] doi
      - [ ] hands-on code repository
    - [ ] \`deadlines\`
  - [ ] \`_data/bsswt/{{ event-label }}/agenda.csv\`
  - [ ] \`_data/bsswt/{{ event-label }}/presentations.yml\`
- Sections needed in \`{{ event-label }}/index.md\`
  - [x] description (usually local)
  - [x] agenda
  - [x] presentation-slides
  - [ ] how-to-participate (usually local)
  - [ ] hands-on-exercises (usually local)
  - [ ] stay-in-touch
  - [ ] related-events (local, if appropriate to context)
  - [ ] resources-from-presentations
  - [x] requested-citation
  - [x] acknowledgments-ecp
- Additional files needed in \`{{ event-label }}\` directory
  - [ ] Copy and update \`presentation-resources\` directory
  - [ ] Copy and update \`handson-*\` files and \`images\` directory

EOF

```
{% endif %}

---

## Transition from planned event to scheduled

{%- if my-event.enddate -%}
  {%- assign due = my-event.enddate | date: "%s" -%}
{%- else -%}
  {%- assign due = my-event.startdate | date: "%s" -%}
{%- endif -%}
{%- assign due = due | plus: 86399 | plus: 43200 -%}

There are numerous places where changes are required to shift a an event from "planned" to "scheduled".

1. `_data/tutorials.csv` both date and status
2. `_data/bsswt/<event-label>` (event data directory) name change
3. `<event-label>` (event directory) name change
4. `<event-label>/index.md` change `event-label` in metadata
5. Update milestone definitions in `bssw-tutorial/tutorial-management repository/master-labels-milestones.json` and install the updated milestones in the tutorial working repositories (see [above](#add-milestone-to-github-repositories)). `title` should be updated with the new event label.  A new `previousTitles` field should be added with the original event label. The `due_on` date should still be reasonable as long as the scheduled date is within the range of dates originally specified at the planned stage, but can be updated if preferred.
    {% if incomplete %}
      {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
    {% else %}
    ```json
      }, {      
        "title": "{{ event-label }}",
        "previousTitles": ["<original-event-label>"],
        "state": "open",
        "due_on": "{{ due | date: '%FT%T%z' }}"
    ```
    {% endif %}

---

## Next steps

*Please proceed to [preparation](./utilities-preparation.html) once these steps are complete.*
