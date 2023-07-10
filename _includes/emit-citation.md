{% if my-presenters-d %}
  {% assign name_affiliation_array = "" | split: "," %}
  {% for p in my-presenters-d %}
    {% assign name_affiliation_array = name_affiliation_array | push: p.name %}
  {% endfor %}
{% else %}
  {% include extract-array-subset key="github-id" values=my-presenters source=site.people %}
  {% include set-name-affiliation-array people=extract_array_subset noaffil="true" %}
{% endif %}

{% if site.data.bsswt[event-label].event.artifacts %}
  {% assign my-artifacts = site.data.bsswt[event-label].event.artifacts %}
{% else %}
  {% assign my-artifacts = site.data.bsswt[event-label].artifacts %}
{% endif %}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

{% if my-presenters-d or my-presenter %}
  {% if my-event.venue and my-event.location and my-event.date and presentations-doi %}
{{ name_affiliation_array | array_to_sentence_string }}, {{ my-event.title }} {{ my-event.title-type }}, in {{ my-event.venue }}, {{ my-event.location }}, {{ my-event.date | date: "%Y" }}. {% if presentations-doi %}DOI: [{{ presentations-doi }}]({{ presentations-url }}).{% endif %}
  {% else %}
*Citation details not currently available.*
  {% endif %}
{% endif %}
{% comment %}Clean up local variables{% endcomment %}
{%- assign extract_array_subset = nil -%}
{%- assign name_affiliation_array = nil -%}
