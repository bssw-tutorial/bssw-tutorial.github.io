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

[Home]({{ site.url }}) > [{{ event-label }}]({{ site.url }}/{{ event-label }}) > [utilities]({{ site.url }}/{{ event-label }}/utilities)

# Help for Tutorial Preparation and Delivery

## Deadlines

{% assign my-deadlines-sorted = my-deadlines | sort: "due", "last" %}

| **Deadline** | **Label** | **Responsible** |
{% for d in my-deadlines-sorted %}{% if d.due %}| {{ d.due | default: "*none*" }} | {{ d.label }} | {{ d.responsible | inspect }} |
{% endif %}{% endfor %}

## Active Presentations

| **Presentation** | **Presenter** |
{% for p in presentation-order %}| {{ p }} | {{ presenter-order[forloop.index0] }} |
{% endfor %}

## Process

1. Post-acceptance finalization
2. [Preparation](./utilities-preparation.html)
3. Publication of tutorial assets
4. Delivering the tutorial
5. Post-delivery

---

Old stuff, in the process of being moved to child pages

## Create issues to record presentations

{% assign gh = "gh issue create --repo bssw-tutorial/presentations --milestone " 
    | append: event-label %}
{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}

```shell
{% for p in presentation-order %}
{{ gh }} \
    --title "{{ p }} recording due {{ site.data.bsswt[event-label].deadlines.recordings-internal }}" \
    --assignee {{ presenter-order[forloop.index0] }} \
    --body "The recording of <{{ prepo }}/{{ p }}.pptx> is due by {{ site.data.bsswt[event-label].deadlines.recordings-internal }}.  Please put both the recording and the unrendered pptx file (if appropriate) in the Google Drive folder."
{% endfor %}```


## Renaming presentation PDFs for publication

{% assign dest-dir = "final-presentations/" | append: event-label %}

```shell
mkdir {{ dest-dir }}

{% for p in presentation-order %}
{%- capture m -%}{{ module-order[forloop.index0] }}{%- endcapture -%}
{%- capture mfill -%}{%- include emit-filled-number number=m template="00" -%}{%- endcapture -%}
mv {{ p }}.pdf {{ dest-dir }}/{{ mfill }}-{{ p }}.pdf
{% endfor %}
```

## Tagging and creating release of presentations

```shell
cd {{ dest-dir}}
zip --update {{ event-label }}.zip *.pdf
# git commit new presentations
git tag -a 2021-08-12-atpesc -m "Software Productivity and Sustainability track at ATPESC 2021"
# Should be more systematic about this comment.
git push origin --tags
gh release create 2021-08-12-atpesc --title "2021-08-12 Software Productivity and Sustainability track @ Argonne Training Program on Extreme-Scale Computing (ATPESC) summer school"
# Asked for release notes and whether it is a prerelease.  Need to force those.
gh release upload 2021-08-12-atpesc 2021-08-12-atpesc.zip
```
