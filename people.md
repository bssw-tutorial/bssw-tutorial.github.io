---
layout: page
---
## List of Tutorial Staff
{%- assign tutorials = "" | split: "," -%}
{%- for t in site.data.tutorials -%}
  {%- assign my-event = site.data.bsswt[t.event-label].event -%}
  {%- assign when = my-event.date | date: "%s" -%}
  {%- assign value = my-event.date | append: "," | append: t.event-label -%}
  {%- assign tutorials = tutorials | push: value -%}
{%- endfor -%}
{% assign event-labels = "" | split: "," %}
{% assign sorted = tutorials | sort | reverse %}
{% for item in sorted %}
  {% assign event-label = item | split: "," | last %}
  {% assign event-labels = event-labels | push: event-label %}
{% endfor %}

*As presenters, unless noted.*

<ul style="list-style: none">
{% for participant in site.people %}
  <li style="margin-top: 1em">
    <a href="{{ site.baseurl }}{{ participant.url }}">
  	  <strong>{{ participant.firstname }} {{ participant.lastname }},</strong>
	</a>
    {% if participant.affiliations %}
      {{ participant.affiliations | array_to_sentence_string | markdownify |
          remove: "<p>" | remove: "</p>" }}
    {% endif %}
  </li> 

  {%- assign presented-in = "" | split: "," -%}
  {%- assign helped-in = "" | split: "," -%}
  {% for event-label in event-labels %}
    {%- assign my-event = site.data.bsswt[event-label].event -%}
      {%- if my-event.presenter-ids contains participant.github-id -%}
        {%- assign presented-in = presented-in | push: event-label -%}
      {%- elsif my-event.helper-ids contains participant.github-id -%}
      {%- assign helped-in = presented-in | push: event-label -%}
    {%- endif -%}
  {%- endfor -%}

  {%- if presented-in.size > 0 -%}
    {% include emit-events-ul.html event-labels=presented-in artifacts=false %}
  {%- endif -%}

  {%- if helped-in.size > 0 -%}
  <p><strong>Helper:</strong></p>
    {% include emit-events-ul.html event-labels=helped-in artifacts=false %}
  {%- endif -%}

{% endfor %}
</ul>
