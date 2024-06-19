{% assign headings = headings | push: "Presentation Slides" %}

{%- assign my-artifacts = site.data.bsswt[page.event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

{% if presentations-doi %}
{% if presentations-status == "reserved" %}
The slides *will be* published at {{ presentations-url }}.

*Note that the DOI will become active once the presentations are published.*
{% else %}
The latest version of the slides will always be available at **<{{ presentations-url }}>**. 

Note that these files may include additional slides that will not be discussed during the tutorial, but questions are welcome.
{% endif %}
{% else %}
*The presentations will be published shortly before the event.*
{% endif %}

### Supplementary Materials

Due to technical difficulties, we were unable to present the "Managing Computational Experiments" module.  The following two videos, from our [2022 ATPESC tutorial](https://bssw-tutorial.github.io/2022-08-11-atpesc/), taken together, are very similar to what we intended to present in this tutorial.

* [Lab Notebooks for Computational Mathematics, Sciences, & Engineering](https://www.youtube.com/watch?v=OpzofH8U0Bs&list=PLcbxjEfgjpO9OeDu--H9_XqyxPj3MkjdN&index=85) (Jared O'Neal, ANL)
* [Managing Computational Experiments](https://www.youtube.com/watch?v=14UwpmvA56k&list=PLcbxjEfgjpO9OeDu--H9_XqyxPj3MkjdN&index=86) (Jared O'Neal and Anshu Dubey, ANL)