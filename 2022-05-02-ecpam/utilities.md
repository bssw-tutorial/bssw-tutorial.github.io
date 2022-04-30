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

# Help for Tutorial Preparation and Delivery

## Process

1. Post-acceptance finalization
2. [Preparation](./utilities-preparation.html)
3. [Publication of tutorial assets](./utilities-publication.html)
4. Delivering the tutorial
5. Post-delivery

## Deadlines

{% assign my-deadlines-sorted = my-deadlines | sort: "due", "last" %}

| **Deadline** | **Label** | **Responsible** |
{% for d in my-deadlines-sorted %}{% if d.due %}| {{ d.due | default: "*none*" }} | {{ d.label }} | {{ d.responsible | inspect }} |
{% endif %}{% endfor %}

## Active Presentations

| **Presentation** | **Presenter** |
{% for p in presentation-order %}| {{ p }} | {{ presenter-order[forloop.index0] }} |
{% endfor %}
