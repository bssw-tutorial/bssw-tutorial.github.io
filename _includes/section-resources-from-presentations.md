{% assign headings = headings | push: "Resources from Presentations" %}
{%- comment -%}
    Presentation resource files must be:
        1) in the presentation-resources subdirectory where the include is invoked
        2) named with the same labels as the presentations (.md suffix)
{%- endcomment -%}

{%- assign my-presentations = site.data.bsswt[page.event-label].presentations -%}
{%- assign my-agenda = site.data.bsswt[page.event-label].agenda -%}
{% include set-presentation-order agenda=my-agenda presentations=my-presentations %}

*Links from the tutorial presentations are listed here for convenience*

{% for p in presentation-order %}
* Module {{ module-order[forloop.index0] }}: {{ my-presentations[p] }}
    {% include_relative presentation-resources/{{ p }}.md %}
{% endfor %}
{%- comment -%}Clean up internal variables{%- endcomment -5}
{%- assign my-presentations = nil -%}
{%- assign my-agenda = nil -%}
{%- assign presentation-order = nil -%}
{%- assign module-order = nil -%}