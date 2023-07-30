#/bin/bash
#
# event-to-collection.sh source-dir dest-dir
#
# Convert an event.yml from the bssw-tutorial website into 
# a bsswt-*.md for the ideas-productivity website.
#
# This amounts to adding the delimiters for the YAML as frontmatter and changng the file extension.
#
# Arguments:
#   source-dir: a directory containing an event.yml file.  The last term in the directory path is
#               assumed to be the tutorial event label, in the form YYYY-MM-DD-event
#   dest-dir:   a directory where the ideas-productivity file is to be generated.  The
#               generated file will be named bsswt-YYYY-MM-DD-event.md
#
if [ $# -ne "2" ]; then
  echo "ERROR: incorrect number of arguments"
  echo "Usage: $0 source-dir dest-dir"
  exit 1
fi

event_label=`basename $1`
dest_file="$2/bsswt-${event_label}.md"

if [ ! -d "$2" ]; then
  echo "ERROR: destination $2 either does not exist or is not a directory"
  exit 2
fi

if [ -s "$1/event.yml" ]; then
  echo "---" > ${dest_file}         # Delimiter for YAML frontmatter in Jekyll Markdown files
  cat $1/event.yml >> ${dest_file}  # The contents of the event.yml file
  echo >> ${dest_file}              # In case the YML file lacks a trailing newline
  echo "---" >> ${dest_file}        # Delimiter for YAML frontmatter in Jekyll Markdown files
  echo >> ${dest_file}
else
  echo "ERROR: $1/event.yml does not exist or is empty"
  exit 3
fi