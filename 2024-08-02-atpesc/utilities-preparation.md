---
layout: default
---
{%- include set-event-label-from-path -%}
{%- assign my-event = site.data.bsswt[event-label].event -%}
{% if my-event.artifacts %}
  {% assign my-artifacts = my-event.artifacts %}
{% else %}
  {% assign my-artifacts = site.data.bsswt[event-label].artifacts %}
{% endif %}
{% include key-artifact-shorthands artifacts=my-artifacts %}
{% assign my-presentations = site.data.bsswt[event-label].presentations %}
{% assign my-agenda = site.data.bsswt[event-label].agenda %}
{% include set-presentation-order agenda=my-agenda presentations=my-presentations %}
{% assign my-organizers = site.data.bsswt[event-label].event.organizer-ids %}
{% if site.data.bsswt[event-label].event.presenters %}
  {% assign my-presenters-d = site.data.bsswt[event-label].event.presenters %}
  {% assign my-presenters = "" | split: "," %}
  {% for p in my-presenters-d %}{% assign my-presenters = my-presenters | push: p.github-id %}{% endfor %}
{% else %}
  {% assign my-presenters = site.data.bsswt[event-label].event.presenter-ids %}
{% endif %}
{% if site.data.bsswt[event-label].event.helpers %}
  {% assign my-helpers-d = site.data.bsswt[event-label].event.helpers %}
  {% assign my-helpers = "" | split: "," %}
  {% for p in my-helpers-d %}{% assign my-helpers = my-helpers | push: p.github-id %}{% endfor %}
{% else %}
  {% assign my-helpers = site.data.bsswt[event-label].event.helpers-ids %}
{% endif %}
{% assign my-deadlines = site.data.bsswt[event-label].event.deadlines %}

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities) > [preparation]({{ site.url }}/{{ event-label }}/utilities-preparation)

{% comment %}
  Check some high-level variables and issue warnings or errors where appropriate.
  Doing this after the breadcrumbs so the flow of the page makes sense.

  NOTE: `event-label` is central to everthing on this page, but we don't bother checking it because
  we're extracting it from the file's path information, which should never fail. (He says with fingers crossed)
{% endcomment %}

{% unless my-artifacts %}
  {% capture msg %}`artifacts` not defined in file `_data/bsswt/{{ event-label }}/event.yml` (preferred) or `_data/bsswt/{{ event-label }}/artifacts.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-presentations %}
  {% capture msg %}`presentations` not defined. Check file `_data/bsswt/{{ event-label }}/presentations.yml{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-agenda %}
  {% capture msg %}`agenda` not defined. Check file `_data/bsswt/{{ event-label }}/agenda.csv`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-organizers %}
  {% capture msg %}`organizer-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-presenters-d or my-presenters %}
  {% capture msg %}`presenters or presenter-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-deadlines %}
  {% capture msg %}`deadlines` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}

# Help for Tutorial Preparation

*Complete the [post-acceptance finalization](./utilities-finalization.html) steps before these.*

## Issues for organizers

{% assign incomplete = false %}
{% unless my-organizers %}
  {% assign incomplete = true %}
  {% capture msg %}`organizer-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless site.ghr-presentations %}
  {% assign incomplete = true %}
  {% include emit-error.html msg="`ghr-presentations` not defined in file `_config.yml`" %}
{% endunless %}
{% unless presentation-order and presentation-order.size > 0 %}
  {% assign incomplete = true %}
  {% capture msg %}`presentation-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless site.prod_url %}
  {% assign incomplete = true %}
  {% include emit-error.html msg="`prod_url` not defined in file `_config.yml`" %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
gh issue create \
    --repo bssw-tutorial/tutorial-management \
    --milestone "{{ event-label }}" \
    --title "{{ event-label }} content preparation" \
    --assignee "{{ my-organizers | join: ',' | remove: ' ' }}" \
    --label "event preparation" \
    --body-file - << EOF
- [ ] Reserve DOI
- [ ] In <{{ site.ghr-presentations }}/final-presentations/> create \`{{ event-label }}/doi.txt\` and record reserved DOI
- [ ] Update \`license-master.pptx\` citation in <{{ site.ghr-presentations }}>
{% for p in presentation-order %}- [ ] Update \`{{ p }}.pptx\` title and license slides; remove unneeded R&R numbers
{% endfor %}- [ ] Additional updates to \`intro.pptx\`
    - [ ] Update *About Us* slide (3) with presenters and helpers, including head-shots
    - [ ] Update *Hands-On Activities* slide (9) as appropriate
    - [ ] Update the *We want to Interact with You* slide (11) as appropriate
    - [ ] Add *Related Activities* slide as appropriate
    - [ ] Add agenda from <{{ site.prod_url }}/{{ event-label }}#agenda>
- [ ] Add issues needed for hands-on content development

Potentially useful reference information:
* [Detailed inputs for FigShare record]({{ site.prod_url }}{{ page.url }}#create-figshare-record-and-reserve-doi)
* [Citation]({{ site.prod_url }}/{{ event-label }}#requested-citation)
* [Agenda]({{ site.prod_url }}/{{ event-label }}#agenda) can be copy-pasted into PowerPoint
* [Title slide details]({{ site.prod_url }}{{ page.url }}#title-slide-details)

EOF

```
{% endif %}

## Issues for presenters

{% assign incomplete = false %}
{% unless my-deadlines %}
  {% assign incomplete = true %}
  {% capture msg %}`deadlines` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless presentation-order and presentation-order.size > 0 %}
  {% assign incomplete = true %}
  {% capture msg %}`presentation-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless presenter-order and presenter-order.size > 0%}
  {% assign incomplete = true %}
  {% capture msg %}`presenter-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% assign gh = "gh issue create --repo bssw-tutorial/presentations --milestone " 
    | append: event-label %}
{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}
{% capture prews %}https://github.com/bssw-tutorial/bssw-tutorial.github.io/tree/main/{{ event-label }}/presentation-resources{% endcapture %}
{% assign dp =  my-deadlines | find_exp: "d", "d.label == 'internal-presentations'" %}
{% assign dr =  my-deadlines | find_exp: "d", "d.label == 'internal-resource-links'" %}

{% comment %} 
  Reorganize the presenter/presentation arrays so that we can generate issues grouped by presenter
{% endcomment %}
{% include set-grouped-presentations presentations=presentation-order presenters=presenter-order %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
# Update presentations{% if dp.due %} by {{ dp.due }}{% endif %}
{%- for person in grouped-presenters -%}
  {%- assign presentations = grouped-presentations[forloop.index0] | split: ',' %}
gh issue create --repo bssw-tutorial/presentations --milestone "{{ event-label }}" \
    --title "{{ person }} for {{ event-label }}: Update presentations{% if dp.due %} by {{ dp.due }}{% endif %}" \
    --assignee "{{ person }}" \
    --label "event preparation" \
    --body-file - << EOF
{%- for q in presentations %}
- [ ] "Update <{{ prepo }}/{{ q }}.pptx>{% if dp.due %} by {{ dp.due }}{% endif %}"
{%- endfor %}
- [ ] "Remember to update <{{ prepo }}/presentations.yml if any titles change!"
EOF
{%- endfor %}

# Update resources linked from presentations{% if dr.due %} by {{ dr.due }}{% endif %}
{%- for person in grouped-presenters -%}
  {%- assign presentations = grouped-presentations[forloop.index0] | split: ',' %}
gh issue create --repo bssw-tutorial/bssw-tutorial.github.io --milestone "{{ event-label }}" \
    --title "{{ person }} for {{ event-label }}: Update resource links{% if dp.due %} by {{ dr.due }}{% endif %}" \
    --assignee "{{ person }}" \
    --label "event preparation" \
    --body-file - << EOF
{%- for q in presentations %}
- [ ] "Update <{{ prews }}/{{ q }}.md>{% if dr.due %} by {{ dr.due }}{% endif %}"
{%- endfor %}
EOF
{%- endfor %}
{% endif %}
```

## Issues for hands-on content

*To be defined*

---

## Create FigShare record and reserve DOI

{% if my-event.description %}
  {% capture description %}{{ my-event.description | remove: '"' }}{% endcapture %}
{% else %}
  {% capture description %}`description`` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
{% endif %}

Debug: description: {{ description }}

{%- capture f -%}section-acknowledgments-ecp.md{%- endcapture -%}
{% capture local %}{{ event-label }}/{{ f }}{% endcapture %}
{% capture default %}_includes/{{ f }}{% endcapture %}
{% capture local-exists %}{% file_exists {{ local }}  %}{% endcapture %}
{% capture default-exists %}{% file_exists {{ default }} %}{% endcapture %}
{%- if local-exists == "true" -%}
  {%- capture funding -%}{% include_relative {{ f }} %}{%- endcapture -%}
{%- elsif default-exists == "true" -%}
  {%- capture funding -%}{% include {{ f }} %}{%- endcapture -%}
{%- else -%}
  {% capture funding %}No file found for section acknowledgments-ecp: "{{ local }}" or "{{ default }}"{% endcapture %}
{%- endif -%}


{% assign incomplete = false %}
{% unless my-presenters-d %}
  {% assign incomplete = true %}
  {% capture msg %}`presenters`` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless my-event.title %}
  {% assign incomplete = true %}
  {% capture msg %}`title` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless my-event.venue %}
  {% assign incomplete = true %}
  {% capture msg %}`venue` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless my-event.startdate %}
  {% assign incomplete = true %}
  {% capture msg %}`startdate` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless site.prod_url %}
  {% assign incomplete = true %}
  {% include emit-error.html msg="`prod_url` not defined in file `_config.yml`" %}
{% endunless %}
{% unless site.ideas-url %}
  {% assign incomplete = true %}
  {% include emit-error.html msg="`ideas-url` not defined in file `_config.yml`" %}
{% endunless %}

{% if my-presenters-d %}
  {% include set-name-affiliation-array-d people=my-presenters-d noaffil="true" %}
{% endif %}


{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
1. Login and navigate to the `My Data` tab in your FigShare account
2. Click `Create a new item`. Complete the fields as below

**Title:** {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %} {{ my-event.startdate | date: "(%Y)" }}
    
**Authors:** <!-- note that we're not listing helpers here -->
{% if name_affiliation_array %}{% for p in name_affiliation_array %}`{{ p }}`{%- unless forloop.last -%}, {%- endunless -%}{%- endfor -%}{% endif %}

**Categories:** `Software Engineering`

**Item type:** `Presentation`

**Keywords:**
`software engineering`,
`software productivity`,
`software sustainability`,
`software reliability`,
`computational science and engineering software`,
`scientific software`,
`Better Scientific Software tutorial`

**Description:**
{{ description | strip_html | strip }}

**Funding:** <!-- this field doesn't allow newlines, so get rid of them -->
{{ funding | strip_html | normalize_whitespace | strip }}

**References:**
`{{ site.prod_url }}/{{ event-label }}`, 
{% if my-event.venue-url %}`{{ my-event.venue-url }}`, {% endif %}
`{{ site.ideas-url }}`

**License:** `CC BY 4.0`
{% endif %}

---

## Citation for `license-master` slide

{% include emit-citation.md %}

---

## Title slide details

*If you copy-paste from this page into PowerPoint, you will want to use the `copy-without-formatting`
option to ensure that you get the font from the PPT template rather than the font from the web site.*

{% assign incomplete = false %}
{% unless my-event.presenters %}
  {% assign incomplete = true %}
  {% capture msg %}`presenters` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% if my-presenters-d %}
{% include set-name-affiliation-array-d people=my-presenters-d noaffil="true" %}
{% endif %}
{% capture pnamafil %}{% include array-to-sentence array=name_affiliation_array
  if_empty="<em>to be announced</em>" %}{% endcapture %}

{%- assign name_affiliation_array = nil -%}
{% if my-helpers-d %}
{% include set-name-affiliation-array-d people=my-helpers-d noaffil="true" %}
{% endif %}
{% capture hnamafil %}{% include array-to-sentence array=name_affiliation_array if_empty=nil %}{% endcapture %}

{% comment %}
  We're going to assume that the first presentation is the intro deck
  that introduces the whole tutorial, and so should be treated separately.
{% endcomment %}

{% assign incomplete = false %}
{% unless presentation-order and presentation-order.size > 0 %}
  {% assign incomplete = true %}
  {% capture msg %}`presentation-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceding messages." %}
{% else %}
**People for `{{ presentation-order[0] }}.pptx` title slide:** {{ pnamafil }}
{% if hnamafil != "" %}<br>with help from {{ hnamafil }}{% endif %}
{% endif %}

{% assign incomplete = false %}
{% unless presenter-order %}
  {% assign incomplete = true %}
  {% capture msg %}`presenter-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless presentation-order and presentation-order.size > 0 %}
  {% assign incomplete = true %}
  {% capture msg %}`presentation-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
{% if my-presenters-d %}
| **Presentation** | **Presenter** | **Pronouns** | **Affiliation** |
  {% for pres in presentation-order %}{%- if forloop.first -%}{%- continue -%}{%- endif -%}
    {%- assign ghids = presenter-order[forloop.index0] | strip | remove: " " | split: "," -%}
      {%- assign n = "" | split: "," -%}
      {%- assign a = "" | split: "," -%}
      {%- assign pro = "" | split: "," -%}
      {%- for i in ghids -%}
        {%- assign j = my-presenters-d | where_exp: "item", "item.github-id == i" -%}
        {%- assign n = n | push: j[0].name -%}
        {%- assign a = a | push: j[0].affiliation -%}
        {%- assign pro = pro | push: j[0].pronouns | default: "*not given*" -%}
      {%- endfor -%}
| `{{ pres }}.pptx` | {{ n | array_to_sentence_string }} | {{ pro | array_to_sentence_string }} | {{ a | array_to_sentence_string }} |
  {% endfor %}
{% endif %}
{% endif %}

{% assign incomplete = false %}
{% unless my-event.title %}
  {% assign incomplete = true %}
  {% capture msg %}`title` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless my-event.venue %}
  {% assign incomplete = true %}
  {% capture msg %}`venue` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
**Event title:** {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}
{% endif %}

---

## Next steps

*Please proceed to [publication of tutorial assets](./utilities-publication.html) once these steps are complete.*
