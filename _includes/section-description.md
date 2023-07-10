{% assign headings = headings | push: "Description" %}

{% if my-event.description %}
{{ my-event.description | remove: '"' | markdownify }}
{% else %}
The BSSw tutorial focuses on issues of developer productivity, software sustainability, and reproducibility in scientific research software, particularly targeting high-performance computers.
{% endif %}
