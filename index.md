---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---
{%- assign today = 'now' | date: "%s" -%}
# The Better Scientific Software (BSSw) Tutorial

The BSSw tutorial focuses on issues of developer productivity, software sustainability, and reproducibility in scientific research software, particularly targeting high-performance computers.

We first presented a version of this tutorial in 2016, and since then we have been working continually to refine and expand it.  We present it most often as part of conferences, but we are open to a wide range of venues, both in person (circumstances permitting) and online.  [Contact us](mailto:{{ site.email }}?subject=BSSw tutorial question) for more information.

In the listings below, each tutorial event has its own page, providing details specific to that tutorial, including agenda, presentations, hands-on activities, and other resources.  Quick links are also provided to key tutorial artifacts, where available.

## Scheduled Tutorials

*Note: In most cases, participation in these tutorials requires registration with the hosting venue, and may require a fee.*

<ul>
{%- assign first = true -%}
{% assign sequence = site.events | where: "status", "scheduled" | sort: "date" %}
{% for event in sequence %}
{%- assign when = event.date | date: "%s" -%}
{% if when < today %}{% continue %}{% endif %}
<li style="margin-top: 1em">{% if first %}<strong>{% endif %}{{ event.date | date: "%F" }}: <a href="{{ event.url }}">{{ event.title }}{% if event.title-type %} {{ event.title-type }}{% endif %} @ {{ event.venue }}{% if event.venue-type %} {{ event.venue-type }}{% endif %}</a>{%if event.location %} ({{ event.location }}){% endif %}{% if first %}</strong>{%- assign first = false -%}{% endif %}</li>
{%- assign my-artifacts = site.data.bsswt[event.directory].artifacts -%}
{% if my-artifacts %}
    <ul>
    <li>{{ my-artifacts | size | pluralize: "Artifact:", "Artifacts:" }} {% include emit-artifacts.html artifacts=my-artifacts format="row" %}</li>
    </ul>
{% endif %}
{% endfor %}
{% if first %}
<li style="margin-top: 1em"><em>No events currently scheduled.</em></li>
{% endif %}
</ul>

## Planned Tutorials

*These events are confirmed, but dates have not yet been determined.  The dates shown are those for the hosting venue. Events will be updated as more information becomes available.*

<ul>
{%- assign first = true -%}
{% assign sequence = site.events | where: "status", "planned" | sort: "date" %}
{% for event in sequence %}
<li style="margin-top: 1em">{{ event.date | date: "%F" }}: <a href="{{ event.url }}">{{ event.title }}{% if event.title-type %} {{ event.title-type }}{% endif %} @ {{ event.venue }}{% if event.venue-type %} {{ event.venue-type }}{% endif %}</a>{%if event.location %} ({{ event.location }}){% endif %}{%- assign first = false -%}</li>
{%- assign my-artifacts = site.data.bsswt[event.directory].artifacts -%}
{% if my-artifacts %}
    <ul>
    <li>{{ my-artifacts | size | pluralize: "Artifact:", "Artifacts:" }} {% include emit-artifacts.html artifacts=my-artifacts format="row" %}</li>
    </ul>
{% endif %}
{% endfor %}
{% if first %}
<li style="margin-top: 1em"><em>No events currently in planning.</em></li>
{% endif %}
</ul>

## Past Tutorials

<ul>
{%- assign first = true -%}
{% assign sequence = site.events | where: "status", "scheduled" | sort: "date" | reverse %}
{% for event in sequence %}
{%- assign when = event.date | date: "%s" -%}
{% if when >= today %}{% continue %}{% endif %}
<li style="margin-top: 1em">{{ event.date | date: "%F" }}: <a href="{{ event.url }}">{{ event.title }}{% if event.title-type %} {{ event.title-type }}{% endif %} @ {{ event.venue }}{% if event.venue-type %} {{ event.venue-type }}{% endif %}</a>{%if event.location %} ({{ event.location }}){% endif %}{%- assign first = false -%}</li>
{%- assign my-artifacts = site.data.bsswt[event.directory].artifacts -%}
{% if my-artifacts %}
    <ul>
    <li>{{ my-artifacts | size | pluralize: "Artifact:", "Artifacts:" }} {% include emit-artifacts.html artifacts=my-artifacts format="row" %}</li>
    </ul>
{% endif %}
{% endfor %}
{% if first %}
<li style="margin-top: 1em"><em>No past events available.</em></li>
{% endif %}
</ul>

See the IDEAS Productivity [Events](https://ideas-productivity.org/events/) page for tutorials prior to 2021 (as well as other IDEAS events, which may also be of interest).  For most past tutorials, the presentation slides have been archived and are linked from the Events page.

## Acknowledgements

The BSSw tutorial is produced by the [IDEAS Productivity project](https://ideas-productivity.org).

This work was supported by the U.S. Department of Energy Office of Science, Office of Advanced Scientific Computing Research (ASCR), and by the Exascale Computing Project (17-SC-20-SC), a collaborative effort of the U.S. Department of Energy Office of Science and the National Nuclear Security Administration.

*Last updated: {{ page.last_modified_at | date: '%F' }}*
