---
layout: page
---
{%- include set-event-label-from-path -%}
{% assign my-artifacts = site.data.bsswt[event-label].artifacts %}
{% include key-artifact-shorthands artifacts=my-artifacts %}
{% assign my-presentations = site.data.bsswt[event-label].presentations %}
{% assign my-agenda = site.data.bsswt[event-label].agenda %}
{% include set-presentation-order agenda=my-agenda presentations=my-presentations %}
{% assign my-organizers = site.data.bsswt[event-label].event.organizer-ids %}
{% assign my-presenters = site.data.bsswt[event-label].event.presenter-ids %}
{% assign my-helpers = site.data.bsswt[event-label].event.helper-ids %}
{% assign my-event = site.data.bsswt[event-label].event %}
{% assign my-deadlines = site.data.bsswt[event-label].event.deadlines %}

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities) > [preparation]({{ site.url }}/{{ event-label }}/utilities-preparation)

# Help for Tutorial Preparation

## Create issue for initial preparation (organizers)

```shell
gh issue create \
    --repo bssw-tutorial/tutorial-management \
    --milestone "{{ event-label }}" \
    --title "{{ event-label }} initial preparation" \
    --assignee "{{ my-organizers | array_to_sentence_string: '' }}" \
    --body-file - << EOF
- [ ] Reserve DOI
- [ ] In <{{ site.ghr-presentations }}/final-presentations/> create \`{{ event-label }}/doi.txt\` and record reserved DOI
- [ ] Update \`license-master.pptx\` citation in <{{ site.ghr-presentations }}>
- [ ] Update \`agenda-master.pptx\` agenda in <{{ site.ghr-presentations }}>
- [ ] Update \`overview.pptx\` (or equivalent) with new agenda from \`agenda-master.pptx\` in <{{ site.ghr-presentations }}>
{% for p in presentation-order %}- [ ] Update \`{{ p }}.pptx\` title and license slides; remove unneeded R&R numbers
{% endfor %}- [ ] Additional updates to \`intro.pptx\`
    - Update About Us slide (3) with presenters and helpers, including head-shots
    - Update Hands-On Activities slide (9) as appropriate
    - Update the We want to Interact with You slide (11) as appropriate
EOF

```

## Create FigShare record and reserve DOI

{% include extract-array-subset key="github-id" values=my-presenters source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset noaffil="true" %}

{%- capture f -%}section-description.md{%- endcapture -%}
{% capture local %}{{ event-label }}/{{ f }}{% endcapture %}
{% capture default %}_includes/{{ f }}{% endcapture %}
{% capture local-exists %}{% file_exists {{ local }}  %}{% endcapture %}
{% capture default-exists %}{% file_exists {{ default }} %}{% endcapture %}
{%- if local-exists == "true" -%}
  {%- capture description -%}{% include_relative {{ f }} %}{%- endcapture -%}
{%- elsif default-exists == "true" -%}
  {%- capture description -%}{% include {{ f }} %}{%- endcapture -%}
{%- else -%}
  {% capture description %}No file found for section description: "{{ local }}" or "{{ default }}"{% endcapture %}
{%- endif -%}

{%- capture f -%}section-acknowledgments.md{%- endcapture -%}
{% capture local %}{{ event-label }}/{{ f }}{% endcapture %}
{% capture default %}_includes/{{ f }}{% endcapture %}
{% capture local-exists %}{% file_exists {{ local }}  %}{% endcapture %}
{% capture default-exists %}{% file_exists {{ default }} %}{% endcapture %}
{%- if local-exists == "true" -%}
  {%- capture funding -%}{% include_relative {{ f }} %}{%- endcapture -%}
{%- elsif default-exists == "true" -%}
  {%- capture funding -%}{% include {{ f }} %}{%- endcapture -%}
{%- else -%}
  {% capture funding %}No file found for section acknowledgments: "{{ local }}" or "{{ default }}"{% endcapture %}
{%- endif -%}

1. Login and navigate to the `My Data` tab in your FigShare account
2. Click `Create a new item`. Complete the fields as below

**Title** `{{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %} {{ my-event.date | date: "(%Y)" }}`
    
**Authors** <!-- note that we're not listing helpers here -->
{% if name_affiliation_array %}{% for p in name_affiliation_array %}`{{ p }}`{%- unless forloop.last -%}, {%- endunless -%}{%- endfor -%}{% endif %}

**Categories** `Software Engineering`

**Item type** `Presentation`

**Keywords**
`software engineering`,
`software productivity`,
`software sustainability`,
`software reliability`,
`computational science and engineering software`,
`scientific software`,
`Better Scientific Software tutorial`

**Description**
```
{{ description | strip_html | strip }}
```

**Funding**
```
{{ funding | strip_html | strip }}
```

**References**
`{{ site.url }}/{{ event-label }}`, 
{% if my-event.venue-url %}`{{ my-event.venue-url }}`, {% endif %}
`{{ site.ideas-url }}`

**License** `CC BY 4.0`

---

## Create issues for individual presentation updates

{% assign gh = "gh issue create --repo bssw-tutorial/presentations --milestone " 
    | append: event-label %}
{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}
{% assign d =  my-deadlines | find_exp: "d", "d.label == 'internal-presentations'" %}

```shell
{% for p in presentation-order %}
gh issue create --repo bssw-tutorial/presentations --milestone "{{ event-label }}" \
    --title "Update {{ p }} presentation{% if d.due %} by {{ d.due }}{% endif %}" \
    --assignee {{ presenter-order[forloop.index0] }} \
    --body "Update <{{ prepo }}/{{ p }}.pptx>{% if d.due %} by {{ d.due }}{% endif %}"
{% endfor %}```
