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
{% assign my-presenters = site.data.bsswt[event-label].event.presenter-ids %}
{% assign my-helpers = site.data.bsswt[event-label].event.helper-ids %}
{% assign my-deadlines = site.data.bsswt[event-label].event.deadlines %}

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities) > [post-delivery]({{ site.url }}/{{ event-label }}/utilities-after)

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
{% unless my-presenters %}
  {% capture msg %}`presenter-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}
{% unless my-deadlines %}
  {% capture msg %}`deadlines` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-warning.html msg=msg %}
{% endunless %}

# Help for Post-Delivery Follow-up

*Complete the [publication](./utilities-publication.html) steps and deliver the tutorial before these.*

## Issues for organizers

{% assign dp =  my-deadlines | find_exp: "d", "d.label == 'venue-presentations'" %}
{% assign dr =  my-deadlines | find_exp: "d", "d.label == 'venue-recordings'" %}


{% assign incomplete = false %}
{% unless my-organizers %}
  {% assign incomplete = true %}
  {% capture msg %}`organizer-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless presentation-order %}
  {% assign incomplete = true %}
  {% capture msg %}`presentation-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless module-order %}
  {% assign incomplete = true %}
  {% capture msg %}`module-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless site.prod_url %}
  {% assign incomplete = true %}
  {% include emit-error.html msg="`prod_url` not defined in file `_config.yml`" %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceding messages." %}
{% else %}
```shell
gh issue create \
    --repo bssw-tutorial/tutorial-management \
    --milestone "{{ event-label }}" \
    --title "{{ event-label }} post-delivery folow-up" \
    --assignee "{{ my-organizers | array_to_sentence_string: ',' | remove: ' ' }}" \
    --body-file - << EOF
- Collection and editing (if necessary) of recordings down to individual modules
{% for p in presentation-order %}
{%- capture m -%}{{ module-order[forloop.index0] }}{%- endcapture -%}
{%- capture mfill -%}{%- include emit-filled-number number=m template="00" -%}{%- endcapture -%}  - [ ] \`{{ mfill }}-{{ p }}\`
{% endfor %}- Upload recordings to YouTube (see <{{ site.prod_url }}{{ page.url }}#inputs-for-youtube-recordings-of-tutorial-modules>)
{% for p in presentation-order %}
{%- capture m -%}{{ module-order[forloop.index0] }}{%- endcapture -%}
{%- capture mfill -%}{%- include emit-filled-number number=m template="00" -%}{%- endcapture -%}  - [ ] \`{{ mfill }}-{{ p }}\`
{% endfor %}- [ ] Create YouTube playlist for tutorial (see <{{ site.prod_url }}{{ page.url }}#input-for-youtube-playlist>)
- Add individual recordings to playlist
{% for p in presentation-order %}
{%- capture m -%}{{ module-order[forloop.index0] }}{%- endcapture -%}
{%- capture mfill -%}{%- include emit-filled-number number=m template="00" -%}{%- endcapture -%}  - [ ] \`{{ mfill }}-{{ p }}\`
{% endfor %}- [ ] Update recording artifact in \`_data/bsswt/{{ event-label }}/event.yml\`
EOF

```
{% endif %}

---

## Inputs for YouTube recordings of tutorial modules

{% include extract-array-subset key="github-id" values=presenter-order source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset short=true %}
{% assign presenters = name_affiliation_array %}

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
{% unless my-event.startdate %}
  {% assign incomplete = true %}
  {% capture msg %}`startdate` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless presentation-order %}
  {% assign incomplete = true %}
  {% capture msg %}`presentation-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless module-order %}
  {% assign incomplete = true %}
  {% capture msg %}`module-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% capture citation %}{% include emit-citation.md %}{% endcapture %}

{% for p in presentation-order %}
{%- capture m -%}{{ module-order[forloop.index0] }}{%- endcapture -%}
{%- capture mfill -%}{%- include emit-filled-number number=m template="00" -%}{%- endcapture -%}
### Module {{ mfill }}-{{ p }}

**Title:** {{ my-presentations[p] }}

**Description:**
This presentation by {{ presenters[forloop.index0] }}, is module {{ mfill }} of...

{{ citation }}

For further information, visit <{{ site.prod_url }}/{{ event-label }}>.

**Tag:** Better Scientific Software tutorial

**Recording date:** {{ my-event.startdate | date: "%F" }}
{% endfor %}


---

## Input for Youtube playlist

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
{% unless my-presenters %}
  {% assign incomplete = true %}
  {% capture msg %}`presenter-ids` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}
{% unless site.people %}
  {% assign incomplete = true %}
  {% include emit-error.html msg="`people` collection not defined in directory `_people/`" %}
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

{% include extract-array-subset key="github-id" values=my-presenters source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset noaffil="true" %}


{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}

**Title:** {{ my-event.startdate | date: "%F" }}: {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}
    
**Description:**

For more information, visit <{{ site.prod_url }}/{{ event-label }}>

Tutorial Description

{{ description | strip_html | strip }}
{% endif %}

Requested Citation

{% include emit-citation.md %}
