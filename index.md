---
layout: home
---
# The Better Scientific Software (BSSw) Tutorial

The BSSw tutorial focuses on issues of developer productivity, software sustainability, and reproducibility in scientific research software, particularly targeting high-performance computers.

We first presented a version of this tutorial in 2016, and since then we have been working continually to refine and expand it.  We present it most often as part of conferences, but we are open to a wide range of venues, both in person (circumstances permitting) and online.  [Contact us](mailto:{{ site.email }}?subject=BSSw tutorial question) for more information.

In the listings below, each tutorial event has its own page, providing details specific to that tutorial, including agenda, presentations, hands-on activities, and other resources.  Quick links are also provided to key tutorial artifacts, where available.

{% comment %}
  Break up events into three groups: scheduled, planned, and past.
  The master list of tutorials (site.data.tutorials) indicates whether they are scheduled or planned.
  The end date of scheduled tutorials (compared to date at build time) determines whether they are past.
  Events that don't have an explicit enddate entry are assumed to occur in a single day, so use date entry instead.
{% endcomment %}
{%- assign today = 'now' | date: "%s" | plus: 0 -%}  
{%- assign scheduled = "" | split: "," -%}
{%- assign planned = "" | split: "," -%}
{%- assign past = "" | split: "," -%}
{%- for t in site.data.tutorials -%}
    {%- assign my-event = site.data.bsswt[t.event-label].event -%}
    {%- if my-event.enddate -%}
      {%- assign when = my-event.enddate | date: "%s" -%}
    {%- else -%}
       {%- assign when = my-event.date | date: "%s" -%}
    {%- endif -%}
    {% comment %} 
      The timestamp returned will be 12:00:00am UTC. We need to shift to 11:59:59pm AOE. 
      So add 23:59:59 + 12:00:00 to it.  86400 seconds per day.
    {% endcomment %}
    {%- assign when = when | plus: 86399 | plus: 43200 -%}
      
    {% comment %} value is for sorting and is always based on *start* date {% endcomment %}
    {%- assign value = my-event.date | append: "," | append: t.event-label -%}
    {%- if when < today -%}
        {%- assign past = past | push: value -%}
    {%- elsif t.status == "scheduled" -%}
        {%- assign scheduled = scheduled | push: value -%}
    {%- elsif t.status == "planned" -%}
        {%- assign planned = planned | push: value -%}
    {%- endif -%}
{%- endfor -%}

{% comment %}
    SCHEDULED tutorials are those which have been accepted and we have specific dates.
    If we don't have any scheduled tutorials on the books, we want to point out that
    some of our past tutorials have recordings available.
{% endcomment %}
## Scheduled Tutorials

{% if scheduled.size > 0 %}
*Note: In most cases, participation in these tutorials requires registration with the hosting venue, and may require a fee.*

  {% assign event-labels = "" | split: "," %}
  {% assign sorted = scheduled | sort %}
  {% for item in sorted %}
    {% assign event-label = item | split: "," | last %}
    {% assign event-labels = event-labels | push: event-label %}
  {% endfor %}
  {% include emit-events-ul.html event-labels=event-labels highlight=true %}
{% else %}
*We do not currently have any tutorials scheduled.  Check back periodically for updates.  Also, some of our [past tutorials](#past-tutorials) have recordings available.*
{% endif %}

{% comment %}
    PLANNED tutorials are those which have been accepted, but we don't know the exact dates yet.
    If we don't have any planned tutorials, we'll just skip the entire section.
{% endcomment %}

{% assign event-labels = "" | split: "," %}
{% assign sorted = planned | sort %}
{% for item in sorted %}
  {% assign event-label = item | split: "," | last %}
  {% assign event-labels = event-labels | push: event-label %}
{% endfor %}

{% if event-labels.size > 0 %}
## Planned Tutorials

*These events are confirmed, but specific dates have not yet been determined.  The dates shown are those for the hosting venue. Once the presentation date is known, these events will move to the [Scheduled Tutorials](#scheduled-tutorials) section.*

{% include emit-events-ul.html event-labels=event-labels %}
{% endif %}

{% comment %}
    If there are no past tutorials on this site (unlikely), we'll just refer to the older listings
    on the i-p.o web site.
{% endcomment %}
## Past Tutorials

{% if past.size > 0 %}
  {% assign event-labels = "" | split: "," %}
  {% assign sorted = past | sort | reverse %}
  {% for item in sorted %}
    {% assign event-label = item | split: "," | last %}
    {% assign event-labels = event-labels | push: event-label %}
  {% endfor %}
  {% include emit-events-ul.html event-labels=event-labels %}
{% endif %}

## Acknowledgements

The BSSw tutorial is produced by the [IDEAS Productivity project](https://ideas-productivity.org).

This work was supported by the U.S. Department of Energy Office of Science, Office of Advanced Scientific Computing Research (ASCR), and by the Exascale Computing Project (17-SC-20-SC), a collaborative effort of the U.S. Department of Energy Office of Science and the National Nuclear Security Administration.

*Built {{ page.last_modified_at | date: '%F' }} from commit [{{ site.github.build_revision | truncate: 7, "" }}]({{ site.github.repository_url }}/commit/{{ site.github.build_revision }})*
