{% assign headings = headings | push: "Requested Citation" %}

{% assign my-event = site.data.bsswt[page.event-label].event %}
{% assign my-presenters = my-event.presenter-ids %}

The requested citation the overall tutorial is: 

{% include emit-citation.md %}
{% if presentations-status == "reserved" %}
*Note that the DOI will become active once the presentations are published.*
{% endif %}
Individual modules may be cited as *Speaker*, *Module Title*, in {{ my-event.title}} {{ my-event.title-type }}…
{% comment %}Clean up local variables{% endcomment %}
{%- assign extract_array_subset = nil -%}
{%- assign name_affiliation_array = nil -%}
