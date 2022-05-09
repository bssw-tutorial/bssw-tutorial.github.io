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

# Help for Publication of Tutorial Assets

*Complete the [preparation](./utilities-preparation.md) steps before these.*

## Issues for organizers

{% assign dp =  my-deadlines | find_exp: "d", "d.label == 'venue-presentations'" %}
{% assign dr =  my-deadlines | find_exp: "d", "d.label == 'venue-recordings'" %}

```shell
gh issue create \
    --repo bssw-tutorial/tutorial-management \
    --milestone "{{ event-label }}" \
    --title "{{ event-label }} publication of assets" \
    --assignee "{{ my-organizers | array_to_sentence_string: '' }}" \
    --body-file - << EOF
- Quality control review of presentations (see <https://github.com/bssw-tutorial/presentations/blob/main/README.md#quality-control>)
{% for p in presentation-order %}  - [ ] \`{{ p }}.pptx\`
{% endfor %}- Generate PDFs of presentations
{% for p in presentation-order %}  - [ ] \`{{ p }}.pptx\`
{% endfor %}- [ ] Prepare release of presentation files (see <{{ site.prod_url }}{{ page.url }}#scripting-for-presentation-release)
- [ ] Publish presentation files on FigShare
- [ ] Update presentation DOI in \`_data/bsswt/{{ event-label }}/event.yml\`
{% if dp.due %}- [ ] Upload presentation files to venue **by {{ dp.due }}**{% endif %}
- Create hands-on code repository for event
  - [ ] Use [bssw-tutorial/hello-numerical-world])(https://github.com/bssw-tutorial/hello-numerical-world) as a *template* to create **bssw-tutorial**/hello-numerical-world-{{ event-label }} (not in your personal space!)
  - [ ] Delete the `.github/workflows` directory
  - [ ] Update hands-on repo URL in \`_data/bsswt/{{ event-label }}/event.yml\`
{% if dr.due %}- [ ] Upload recordings to venue **by {{ d.due }}**{% endif %}
EOF

```

{% assign dr =  my-deadlines | find_exp: "d", "d.label == 'internal-recordings'" %}

{% if dr.due %}
## Issues for presenters

{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}

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

---

## Scripting for presentation release

{% assign dest-dir = "final-presentations/" | append: event-label %}

{% capture description %}{{ my-event.date | date: "%F" }}: {{ my-event.title }}{% if my-event.title-type %} {{ my-event.title-type }}{% endif %} @ {{ my-event.venue }}{% if my-event.venue-type %} {{ my-event.venue-type }}{% endif %}{% endcapture %}

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