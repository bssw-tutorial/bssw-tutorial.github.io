{% assign headings = headings | push: "Agenda" %}

{%- assign my-agenda = site.data.bsswt[page.event-label].agenda -%}
{%- assign my-presentations = site.data.bsswt[page.event-label].presentations -%}
{%- assign my-presenters-d = site.data.bsswt[page.event-label].event.presenters -%}

{% if my-agenda and my-presentations %}
  {% if my-presenters-d %}
    {%- include emit-agenda-table.html agenda=my-agenda presentations=my-presentations presenters=my-presenters-d -%}
  {% else %}
    {%- include emit-agenda-table.html agenda=my-agenda presentations=my-presentations -%}
  {% endif %}
{% else %}
*The agenda will be added once it is finalized.*
{% endif %}
