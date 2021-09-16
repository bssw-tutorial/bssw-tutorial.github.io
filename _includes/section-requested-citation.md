{% assign headings = headings | push: "Requested Citation" %}

{% assign my-event = site.data.bsswt[page.event-label].event %}
{% assign my-presenters = my-event.presenter-ids %}
{% include extract-array-subset key="github-id" values=my-presenters source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset noaffil="true" %}
{%- assign my-artifacts = site.data.bsswt[page.event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

{% if my-presenters and my-event.title and my-event.venue and my-event.location and my-event.date %}
The requested citation the overall tutorial is: 

{{ name_affiliation_array | array_to_sentence_string }}, {{ my-event.title }} {{ my-event.title-type }}, in {{ my-event.venue }}, {{ my-event.location }}, {{ my-event.date | date: "%Y" }}. {% if presentations-doi %}DOI: [{{ presentations-doi }}]({{ presentations-url }}).{% endif %}

Individual modules may be cited as *Speaker*, *Module Title*, in {{ my-event.title}} {{ my-event.title-type }}…
{% else %}
*To be announced*
{% endif %}
{% comment %}Clean up local variables{% endcomment %}
{%- assign extract_array_subset = nil -%}
{%- assign name_affiliation_array = nil -%}
