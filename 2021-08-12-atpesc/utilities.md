---
layout: page
---
# Helpers

{%- include set-event-label-from-path -%}

{% assign my-artifacts = site.data.bsswt[event-label].artifacts %}
{% include key-artifact-shorthands artifacts=my-artifacts %}
{% assign my-presentations = site.data.bsswt[event-label].presentations %}
{% assign my-agenda = site.data.bsswt[event-label].agenda %}
{% include set-presentation-order agenda=my-agenda presentations=my-presentations %}
{% assign my-presenters = site.data.bsswt[event-label].event.presenter-ids %}
{% assign my-helpers = site.data.bsswt[event-label].event.helper-ids %}
{% assign my-event = site.data.bsswt[event-label].event %}

## Create issues for presentation updates

{% assign gh = "gh issue create --repo bssw-tutorial/presentations --milestone " 
    | append: event-label %}
{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}

```shell
{% for p in presentation-order %}
{{ gh }} \
    --title "Updates to {{ p }} presentation due {{ site.data.bsswt[event-label].deadlines.final-presentations }}" \
    --assignee {{ presenter-order[forloop.index0] }} \
    --body "The final version of <{{ prepo }}/{{ p }}.pptx> is due by {{ site.data.bsswt[event-label].deadlines.final-presentations }}"
{% endfor %}```

## Renaming presentation PDFs for publication

{% assign dest-dir = "final-presentations/" | append: event-label %}

```shell
mkdir {{ dest-dir }}

{% for p in presentation-order %}
{%- capture m -%}{{ module-order[forloop.index0] }}{%- endcapture -%}
{%- capture mfill -%}{%- include emit-filled-number number=m template="00" -%}{%- endcapture -%}
mv {{ p }}.pdf {{ dest-dir }}/{{ mfill }}-{{ p }}.pdf
{% endfor %}
```

## Data for FigShare record

Title: {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %} {{ my-event.startdate | date: "(%Y)" }}

<!-- note that we're not listing helpers here -->
Authors:
{% include extract-array-subset key="github-id" values=my-presenters source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset noaffil="true" %}
{% if name_affiliation_array %}
  {% for p in name_affiliation_array %}
* {{ p }}
  {%- endfor -%}
{% endif %}

Categories: Software Engineering

Item type: Presentation

Keywords:

* software engineering
* software productivity
* software sustainability
* software reliability
* computational science and engineering software
* scientific software
* Better Scientific Software tutorial

<!-- Should include same description as event -->
Description: Presentations from the Software Productivity track at the 2021 Argonne Training Program for Extreme Scale Computing (ATPESC).

<!-- Should be generalized to use the same ack as the event -->
Funding: This work was supported by the U.S. Department of Energy Office of Science, Office of Advanced Scientific Computing Research (ASCR), and by the Exascale Computing Project (17-SC-20-SC), a collaborative effort of the U.S. Department of Energy Office of Science and the National Nuclear Security Administration.

<!-- this will be localhost when testing locally.  Can we make it always be
     the production URL? -->
References: {{ site.url }}/events/{{ event-label }}.html

License: CC BY 4.0

## Tagging and creating release of presentations

```shell
cd {{ dest-dir}}
zip --update {{ event-label }}.zip *.pdf
# git commit new presentations
git tag -a 2021-08-12-atpesc -m "Software Productivity and Sustainability track at ATPESC 2021"
# Should be more systematic about this comment.
git push origin --tags
gh release create 2021-08-12-atpesc --title "2021-08-12 Software Productivity and Sustainability track @ Argonne Training Program on Extreme-Scale Computing (ATPESC) summer school"
# Asked for release notes and whether it is a prerelease.  Need to force those.
gh release upload 2021-08-12-atpesc 2021-08-12-atpesc.zip
```
