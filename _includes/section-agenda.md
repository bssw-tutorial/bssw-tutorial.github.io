{% assign headings = headings | push: "Agenda" %}

{%- assign my-agenda = site.data.bsswt[page.event-label].agenda -%}
{%- assign my-presentations = site.data.bsswt[page.event-label].presentations -%}

{% if my-agenda and my-presentations %}
{%- include emit-agenda-table.html agenda=my-agenda presentations=my-presentations -%}
{% else %}
*The agenda will be added once it is finalized.*
{% endif %}
