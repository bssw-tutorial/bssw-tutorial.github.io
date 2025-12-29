---
layout: default
---
{%- include set-event-label-from-path -%}
{%- assign my-event = site.data.bsswt[event-label].event -%}
{% if my-event.artifacts %}
  {% assign my-artifacts = my-event.artifacts %}
{% else %}
  {% assign my-artifacts = site.data.bsswt[event-label].event.artifacts %}
{% endif %}
{% include key-artifact-shorthands artifacts=my-artifacts %}
{% assign my-presentations = site.data.bsswt[event-label].presentations %}
{% assign my-agenda = site.data.bsswt[event-label].agenda %}
{% include set-presentation-order agenda=my-agenda presentations=my-presentations %}
{% assign my-organizers = site.data.bsswt[event-label].event.organizer-ids %}
{% assign my-presenters = site.data.bsswt[event-label].event.presenter-ids %}
{% assign my-helpers = site.data.bsswt[event-label].event.helper-ids %}
{% assign my-deadlines = site.data.bsswt[event-label].event.deadlines %}

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities) > [preparation]({{ site.url }}/{{ event-label }}/utilities-preparation)

# Help for Tutorial Preparation

## Issues for organizers

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

Potentially useful reference information:
* [Detailed inputs for FigShare record]({{ site.prod_url }}{{ page.url }}#create-figshare-record-and-reserve-doi)
* [Citation]({{ site.prod_url }}/{{ event-label }}#requested-citation)
* [Agenda]({{ site.prod_url }}/{{ event-label }}#agenda) can be copy-pasted into PowerPoint
* [Title slide details]({{ site.prod_url }}{{ page.url }}#title-slide-details)

EOF

gh issue create \
    --repo bssw-tutorial/tutorial-management \
    --milestone "{{ event-label }}" \
    --title "{{ event-label }} build website" \
    --assignee "{{ my-organizers | array_to_sentence_string: '' }}" \
    --body-file - << EOF
- Update event details
  - [ ] artifacts: presentation doi
  - [ ] artifacts: hands-on code repo
- Update event page sections    
  - [ ] description
  - [x] agenda *requires \`_data/bsswt/{{ event-label }}/agenda.csv\`*
  - [x] presentation-slides
  - [ ] how-to-participate
  - [ ] hands-on-exercises
  - [ ] stay-in-touch
  - [ ] resources-from-presentations
  - [x] requested-citation
  - [x] acknowledgments-ecp
- [ ] Tag website repository
EOF

```

## Issues for presenters

{% assign gh = "gh issue create --repo bssw-tutorial/presentations --milestone " 
    | append: event-label %}
{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}
{% capture prews %}https://github.com/bssw-tutorial/bssw-tutorial.github.io/tree/main/{{ event-label }}/presentation-resources{% endcapture %}
{% assign dp =  my-deadlines | find_exp: "d", "d.label == 'internal-presentations'" %}
{% assign dr =  my-deadlines | find_exp: "d", "d.label == 'internal-resource-links'" %}

{% if my-agenda %}
```shell
# Update presentations{% if dp.due %} by {{ dp.due }}{% endif %}
{% for p in presentation-order %}
gh issue create --repo bssw-tutorial/presentations --milestone "{{ event-label }}" \
    --title "Update {{ p }} presentation{% if dp.due %} by {{ dp.due }}{% endif %}" \
    --assignee {{ presenter-order[forloop.index0] }} \
    --body "Update <{{ prepo }}/{{ p }}.pptx>{% if dp.due %} by {{ dp.due }}{% endif %}"
{% endfor %}
# Update resources from presentations{% if dr.due %} by {{ dr.due }}{% endif %}
{% for p in presentation-order %}
gh issue create --repo bssw-tutorial/bssw-tutorial.github.io --milestone "{{ event-label }}" \
    --title "Update {{ p }} resources{% if dr.due %} by {{ dr.due }}{% endif %}" \
    --assignee {{ presenter-order[forloop.index0] }} \
    --body "Update <{{ prews }}/{{ p }}.md>{% if dr.due %} by {{ dr.due }}{% endif %}"
{% endfor %}```
{% else %}
**Need `_data/bsswt/{{ event-label }}/agenda.csv`**
{% endif %}

---

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

---

## Citation for `license-master` slide

*See requested citation on [event page](./index.html#requested-citation)*

---

## Title slide details

*If you copy-paste from this page into PowerPoint, you will want to use the `copy-without-formatting`
option to ensure that you get the font from the PPT template rather than the font from the web site.*

{% comment %}
  We really ought to verify that we have all the needed data for this, but so many
  distinct items go into this, it probably needs to be done in stages.
{% endcomment %}

{% include extract-array-subset key="github-id" values=my-event.presenter-ids source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset noaffil=true %}
{% capture pnamafil %}{% include array-to-sentence array=name_affiliation_array 
  if_empty="<em>to be announced</em>" %}{% endcapture %}

{% include extract-array-subset key="github-id" values=my-event.helper-ids source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset noaffil=true %}
{% capture hnamafil %}{% include array-to-sentence array=name_affiliation_array if_empty=nil %}{% endcapture %}

{% comment %}
  We're going to assume that the first presentation is the intro deck
  that introduces the whole tutorial, and so should be treated separately.
{% endcomment %}

**People for `{{ presentation-order[0] }}.pptx` title slide:** {{ pnamafil }}
{% if hnamafil != "" %}<br>with help from {{ hnamafil }}{% endif %}

{% include extract-array-subset key="github-id" values=presenter-order source=site.people %}
{% include set-name-affiliation-array people=extract_array_subset noaffil=true %}
{% assign presenters = name_affiliation_array %}
{% include set-name-affiliation-array people=extract_array_subset noname=true %}
{% assign affiliations = name_affiliation_array %}

{%- assign pronouns = "" | split: "," -%}
{%- for p in extract_array_subset -%}
  {%- comment -%} If the person-id is not in people, skip it{%- endcomment -%}
  {%- unless p[0] -%}{%- continue -%}{%- endunless -%}
  {%- capture pafil -%}{{ p[0].pronouns | default: "*unknown*" }}{%- endcapture -%}
  {%- assign pronouns = pronouns | push: pafil -%}
{%- endfor -%}

| **Presentation** | **Presenter** | **Pronouns** | **Affiliation** |
{% for p in presentation-order %}{% if forloop.first %}{% continue %}{% endif %}| `{{ p }}.pptx` | {{ presenters[forloop.index0] }} | {{ pronouns[forloop.index0] }} | {{ affiliations[forloop.index0] }} |
{% endfor %}

**Event title:** {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}

---

## Scripting to tag website repository

{% capture description %}{{ my-event.startdate | date: "%F" }}: {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}{% endcapture %}

```shell
# In local working copy of bssw-tutorial/bssw-tutorial.github.io repository

# Tag repo
git tag -a {{ event-label}} -m "{{ description }}"
git push origin --tags

```

## Scripting to remove tag 

For when we have to update the repository.

```shell
# In local working copy of bssw-tutorial/bssw-tutorial.github.io repository

# Delete local and remote tags
git tag -d {{ event-label }}
git push --delete origin {{ event-label }}

```
