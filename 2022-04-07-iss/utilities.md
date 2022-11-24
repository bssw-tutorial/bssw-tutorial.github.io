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

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities)

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

# Help for Tutorial Preparation and Delivery

## Process

1. [Post-acceptance finalization](./utilities-finalization.html)
2. [Preparation](./utilities-preparation.html)
3. [Publication of tutorial assets](./utilities-publication.html)
4. Delivering the tutorial
5. [Post-delivery](./utilities-after.html)

## Deadlines

{% if my-deadlines %}
{% assign my-deadlines-sorted = my-deadlines | sort: "due", "last" %}

| **Deadline** | **Label** | **Responsible** |
{% for d in my-deadlines-sorted %}{% if d.due %}| {{ d.due | default: "*none*" }} | {{ d.label }} | {{ d.responsible | inspect }} |
{% endif %}{% endfor %}
{% else %}
  {% capture msg %}`deadlines` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endif %}

## Active Presentations

{% if my-agenda %}
| **Presentation** | **Presenter** |
{% for p in presentation-order %}| {{ p }} | {{ presenter-order[forloop.index0] }} |
{% endfor %}
{% else %}
  {% capture msg %}`presentation-order` not defined. Check file `_data/bsswt/{{ event-label }}/agenda.csv`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endif %}
