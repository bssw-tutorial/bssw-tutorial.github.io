---
layout: page
---
# Helpers for 2021-08-12-atpesc tutorial

{%- include set-event-label-from-path -%}

{%- assign my-artifacts = site.data.bsswt[event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}
{%- assign my-presentations = site.data.bsswt[event-label].presentations -%}
{%- assign my-agenda = site.data.bsswt[event-label].agenda -%}
{%- include set-presentation-order agenda=my-agenda presentations=my-presentations -%}

## Create issues for presentation updates

{% assign gh = "gh issue create --repo bssw-tutorial/presentations --milestone " 
    | append: event-label %}
{% assign prepo = "https://github.com/bssw-tutorial/presentations/blob/master" %}

```shell
{% for p in presentation-order %}
{{ gh }} ^
    --title "Updates to {{ p }} presentation due {{ site.data.bsswt[event-label].deadlines.final-presentations }}" ^
    --assignee {{ presenter-order[forloop.index0] }} ^
    --body "The final version of <{{ prepo }}/{{ p }}.pptx> is due by {{ site.data.bsswt[event-label].deadlines.final-presentations }}"
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
cd {{ dest-dir}}
zip --update {{ event-label }}.zip *.pdf
# git commit new presentations
# git tag
# gh release upload
```