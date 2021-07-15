---
layout: page
---
## List of Tutorial Staff

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

{% assign w = site.events | where: "presenter-ids", participant.github-id | sort: "event-id" | reverse %}
{% assign x = site.events | where: "helper-ids", participant.github-id | sort: "event-id" | reverse %}

  <ul style="list-style: none">
    {% if w != empty %}
      {% for w2 in w %}
      <li style="list-style: none">{{ w2.event-id }}. 
        <strong><a href="{{ site.baseurl }}{{ w2.url }}">{{ w2.title }}</a></strong> ({{ w2.date | date: "%F" }})</li>
    {% endfor %}
  {% endif %}
  {% if x != empty %}
      {% for x2 in x %}
      <li style="list-style: none">{{ x2.event-id }}. 
        <strong><a href="{{ site.baseurl }}{{ x2.url }}">{{ x2.title }}</a></strong> ({{ x2.date | date: "%F" }}) <em>Helper</em></li>
    {% endfor %}
  {% endif %}

  </ul>

{% endfor %}
</ul>
