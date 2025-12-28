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

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities) > [publication]({{ site.url }}/{{ event-label }}/utilities-publication)

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

# Help for Publication of Tutorial Assets

*Complete the [preparation](./utilities-preparation.html) steps before these.*

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
    --title "{{ event-label }} publication of assets" \
    --assignee "{{ my-organizers | array_to_sentence_string: ',' | remove: ' ' }}" \
    --body-file - << EOF
- Quality control review of presentations (see <https://github.com/bssw-tutorial/presentations/blob/main/README.md#quality-control>)
{% for p in presentation-order %}  - [ ] \`{{ p }}.pptx\`
{% endfor %}- Generate PDFs of presentations
{% for p in presentation-order %}  - [ ] \`{{ p }}.pptx\`
{% endfor %}- [ ] Prepare release of presentation files (see <{{ site.prod_url }}{{ page.url }}#scripting-for-presentation-release>)
- [ ] Publish presentation files on FigShare
- [ ] Update presentation DOI in \`_data/bsswt/{{ event-label }}/event.yml\`
{% if dp.due %}- [ ] Upload presentation files to venue **by {{ dp.due }}**{% endif %}
- [ ] Tag presentation repository
- Create hands-on code repository for event (see <{{ site.prod_url }}{{ page.url }}#scripting-to-create-hands-on-code-repository>)
- [ ] Update hands-on repo URL in \`_data/bsswt/{{ event-label }}/event.yml\`
{% if dr.due %}- [ ] Upload recordings to venue **by {{ d.due }}**{% endif %}
- [ ] Tag web site repository
EOF

```
{% endif %}



{% assign dr =  my-deadlines | find_exp: "d", "d.label == 'internal-recordings'" %}

{% if dr.due %}
## Issues for presenters

{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}

{% assign incomplete = false %}
{% unless presentation-order %}
  {% assign incomplete = true %}
  {% capture msg %}`presentation-order` not defined. Check files `_data/bsswt/{{ event-label }}/agenda.csv` and `_data/bsswt/{{ event-label }}/presentations.yml`{% endcapture %}
  {% include emit-error.html msg=msg %}
{% endunless %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
# Record presentations by {{ dr.due }}
{% for p in presentation-order %}
gh issue create \
    --repo bssw-tutorial/presentations \
    --milestone "{{ event-label }}" \
    --title "Record {{ p }} presentation, due {{ dr.due }}" \
    --assignee {{ presenter-order[forloop.index0] }} \
    --body "The recording of <{{ prepo }}/{{ p }}.pptx> is due by **{{ dr.due }}**.  Please put both the recording and the unrendered pptx file (if appropriate) in the Google Drive folder."
{% endfor %}```
{% endif %}
{% endif %}


---

## Scripting for presentation release

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

{% assign dest-dir = "final-presentations/" | append: event-label %}

{% capture description %}{{ my-event.startdate | date: "%F" }}: {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}{% endcapture %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
# In local working copy of bssw-tutorial/presentations repository
# Ensure destination directory exists and copy/move files there
mkdir -p {{ dest-dir }}
cp presentations.yml {{ dest-dir }}
{% for p in presentation-order %}
{%- capture m -%}{{ module-order[forloop.index0] }}{%- endcapture -%}
{%- capture mfill -%}{%- include emit-filled-number number=m template="00" -%}{%- endcapture -%}
mv {{ p }}.pdf {{ dest-dir }}/{{ mfill }}-{{ p }}.pdf
{% endfor %}
# Add and commit new files and tag repository
cd {{ dest-dir }}
git add *.pdf presentations.yml
git commit -m "Capturing presentations for {{ event-label }}"
git push

# Create archive
zip --update {{ event-label }}.zip *.pdf

# Tag repo
git tag -a {{ event-label}} -m "{{ description }}"
git push origin --tags

# Create release and add zip archive
gh release create {{ event-label }} --title "{{ description }}" --notes "{{ description }}"
gh release upload {{ event-label }} {{ event-label }}.zip

```
{% endif %}

## Scripting to remove tag and release

For when we have to update the presentations.

```shell
# In local working copy of bssw-tutorial/presentations repository
# Delete release (--yes overrides confirmation request)
gh release delete {{ event-label }} --yes

# Delete local and remote tags
git tag -d {{ event-label }}
git push --delete origin {{ event-label }}

# Start over at "tag repo" step above to create new release
```
---

## Scripting to create hands-on code repository

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

{% capture description %}Hands-on repository for {{ my-event.startdate | date: "%F" }} {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}{% endcapture %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```
# In a directory in which it is "safe" to clone a git repository...

gh repo create bssw-tutorial/hello-numerical-world-{{ event-label }} \
  --public --template bssw-tutorial/hello-numerical-world \
  --description "{{ description }}"

git clone {{ site.github-url }}/bssw-tutorial/hello-numerical-world-{{ event-label }}
cd hello-numerical-world-{{ event-label }}
git rm -r .github
git commit -m "Removing development-related workflows from student repository"
git push

```
{% endif %}

---

## Scripting to tag website repository

{% assign incomplete = false %}
{% unless my-event.startdate %}
  {% assign incomplete = true %}
  {% capture msg %}`startdate` not defined in file `_data/bsswt/{{ event-label }}/event.yml`{% endcapture %}
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

{% capture description %}{{ my-event.startdate | date: "%F" }}: {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}{% endcapture %}

{% if incomplete %}
  {% include emit-error.html msg="Cannot generate due to missing information. See preceeding messages." %}
{% else %}
```shell
# In local working copy of bssw-tutorial/bssw-tutorial.github.io repository

# Tag repo
git tag -a {{ event-label}} -m "{{ description }}"
git push origin --tags

```
{% endif %}

## Scripting to remove tag 

For when we have to update the repository.

```shell
# In local working copy of bssw-tutorial/bssw-tutorial.github.io repository

# Delete local and remote tags
git tag -d {{ event-label }}
git push --delete origin {{ event-label }}

```
