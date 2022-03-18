{% assign headings = headings | push: "Agenda" %}

This tutorial comprises *two* conference sessions.  The first session, 9:00am-11:20am MDT, will be a series of presentations.
The second session, 1:20pm-3:40pm MDT, will be more open-ended, depending on the interests of the participants.  There will be opportunities to:
* Gain some experience with hands-on activities the presentations (guided or independent); 
* Deeper Q&A based on the presentations; or 
* Discussion of experiences and challenges with software development faced by participants in their own projects.
We will use Zoom breakout rooms to be able to accommodate multiple interests in so far as we can staff them.

{%- assign my-agenda = site.data.bsswt[page.event-label].agenda -%}
{%- assign my-presentations = site.data.bsswt[page.event-label].presentations -%}

{%- include emit-agenda-table.html agenda=my-agenda presentations=my-presentations -%}
