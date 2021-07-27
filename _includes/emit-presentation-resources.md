{% comment %}
  emit-presentation-resources.md: Include presentation-resources files in agenda order

  arguments:
    `presentation-order`: array of presentation labels in agenda order
    `module-order`: array of presentation module numbers in agenda order
    `presentations`: associative array mapping shorthand labels for presentations to their titles
    `include-dir`: directory to look for resource files
{% endcomment %}

{% for p in include.presentation-order %}
* Module {{ include.module-order[forloop.index0] }}: {{ include.presentations[p] }}
    {% flexible_include {{ include.include-dir}}/{{ p }}.md do_not_escape='true' %}
{% endfor %}