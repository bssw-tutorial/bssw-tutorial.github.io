{% assign headings = headings | push: "Hands-On Activities" %}

{%- assign my-event = site.data.bsswt[page.event-label].event -%}
{%- assign my-artifacts = site.data.bsswt[page.event-label].artifacts -%}
{%- include key-artifact-shorthands artifacts=my-artifacts -%}

### Introduction

The hands-on activities for this {{ my-event.title-type | default: "event" }} are involve the use of a large language model (LLM) to generate tests and code according to specifications (prompts) you will develop.  Participation in these activities is encouraged, but not required.  After interested participants have been given some time to try the exercise on their own, the instructor will review their prompts and code with the class and these materials will be made available to all participants.

Attendees can participate in the hands-on section in two modes: using the LLM's **web interface**, or using **CodeScribe**, a tool that enables using chat-completion through the API interface of the LLM. The main objectives of the hands-on can met by using the web interface. The advantage of using CodeScribe is to get exposure to the chat-completion technique, and getting to know a tool that can be very handy for writing code.

### Advance preparation

If you wish to participate in the hands-on activities, we strongly encourage you to do a bit of preparation **before the tutorial starts**.  This is especially true if you want to use CodeScribe, which may require some advance interaction with the tool developers to integrate new LLM APIs.

#### Preparation for using the LLM **web interface**

1. You will need access to an LLM chat tool.  The instructor will be using [ChatGPT](https://chatgpt.com/), but any comparable LLM, including institutionally-supported tools, should work.

#### Preparation for using **CodeScribe**

*It is important that you do this preparation with enough lead time that we can assist you if necessary **before SC25 starts**.  **We will not be able to provide any support for CodeScribe usage issues during the tutorial itself**.*

1. You will need API access to an LLM tool. This is a level beyond the web interface and it incurs an extra charge on some platforms. However many institutionally-supported LLMs offer API access at no additional cost.  Participants will be responsible for any additional costs incurred. The instructor will be using [ChatGPT](https://chatgpt.com/), but any comparable LLM should work.  CodeScribe also supports the freely downloadable Llama model: Codellama 7B 2023 release.

2. CodeScribe is a Python code, so you will need a working Python installation on a system that you will be able to access during the tutorial (remote access is fine).

3. Download and install CodeScribe from <https://github.com/adubey64/CodeScribe>
  a. Installation instructions are provided in the README file: <https://github.com/adubey64/CodeScribe?tab=readme-ov-file#installation>
  b. You are encouraged to watch the two tutorials on the installation and use of CodeScribe in this Box folder: <https://anl.app.box.com/folder/336154643880?s=zv3zdbphqprdz8rjh1c84xpeqd8yg32u>.  They are 19 minutes and 11 minutes long, respectively. The tutorials were prepared before "generate" command was added to the tool, so there is no mention of it in either tutorial, but it works like the "translate" command.

4. You will need to integrate your CodeScribe installation with your the API of your LLM of choice. It may be necessary for participants to add support for their custom models to CodeScribe. They should look at the file <https://github.com/adubey64/CodeScribe/blob/development/code_scribe/lib/_llm.py>, copy the class most closely resembling the target model and create a PR. With enough lead time we will try our best to help make it work.

### During the tutorial

At an appropriate point in the tutorial, we will make available the prompts the instructor used and the generated code for your reference.  Links will be provided here.
