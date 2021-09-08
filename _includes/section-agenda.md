{% assign headings = headings | push: "Agenda" %}

{%- assign my-agenda = site.data.bsswt[page.event-label].agenda -%}
{%- assign my-presentations = site.data.bsswt[page.event-label].presentations -%}

{%- include emit-agenda-table.html agenda=my-agenda presentations=my-presentations -%}
