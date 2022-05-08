{% assign headings = headings | push: "Presentation Slides" %}

{%- assign my-artifacts = site.data.bsswt[page.event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

{% if presentations-doi %}
The latest version of the slides will always be available at **<{{ presentations-url }}>**. 

Note that these files may include additional slides that will not be discussed during the tutorial, but questions are welcome.
{% else %}
*The presentations will be published shortly before the event.*
{% endif %}
