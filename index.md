---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---
# The Better Scientific Software (BSSw) Tutorial

The BSSw tutorial focuses on issues of developer productivity, software sustainability, and reproducibility in scientific research software, particularly targeting high-performance computers.

We first presented a version of this tutorial in 2016, and since then we have been working continually to refine and expand it.  We present it most often as part of conferences, but we are open to a wide range of venues, both in person (circumstances permitting) and online.

*Last update: {{ "now" | date: "%F" }}*

## Scheduled Tutorials

*These pages provide details for tutorial participants and others interested, including the latest presentations, hands-on activities, and other resources. In most cases, participation requires registration with the hosting venue, and may require a fee.*

{% assign sequence = site.events | where: "status", "scheduled" | sort: "date" %}
{% for event in sequence %}

* {% if forloop.first %}**{% endif %}{{ event.date | date: "%F" }}: [{{ event.title }}{% if event.title-type %} {{ event.title-type }}{% endif %} @ {{ event.venue }}{% if event.venue-type %} {{ event.venue-type }}{% endif %}]({{ event.url }}){%if event.location %} ({{ event.location }}){% endif %}{% if forloop.first %}**{% endif %}
{% endfor %}

## Planned Tutorials

*These events are in the planning stage. Dates shown are associated with the hosting venue, not the specific dates of our tutorial. Additional details will be provided as they become available.*

{% assign sequence = site.events | where: "status", "planned" | sort: "date" %}
{% for event in sequence %}

* {{ event.date | date: "%F" }}: [{{ event.title }}{% if event.title-type %} {{ event.title-type }}{% endif %} @ {{ event.venue }}{% if event.venue-type %} {{ event.venue-type }}{% endif %}]({{ event.url }}){%if event.location %} ({{ event.location }}){% endif %}
{% endfor %}

## Past Tutorials

See the IDEAS Productivity [Events](https://ideas-productivity.org/events/) page for tutorials prior to 2021 (as well as other IDEAS events, which may also be of interest).  For most past tutorials, the presentation slides have been archived and are linked from the Events page.

## Acknowledgements

The BSSw tutorial is produced by the [IDEAS Productivity project](https://ideas-productivity.org).

This work was supported by the U.S. Department of Energy Office of Science, Office of Advanced Scientific Computing Research (ASCR), and by the Exascale Computing Project (17-SC-20-SC), a collaborative effort of the U.S. Department of Energy Office of Science and the National Nuclear Security Administration.