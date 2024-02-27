#/bin/bash
#
# ipo-to-bsswt.sh source-file dest-dir
#
# Convert a bsswt-*.md event from the ideas-productivity website
# into an event.yml file for the bssw-tutorial website.
#
# This amounts to remove the delimiters for from the frontmatter to make it into pure YAML and changng the file extension.
#
# Arguments:
#   source-file: a bsswt event file fro the ideas-productivity site.
#   dest-dir: a directory where the YAML file containing the frontmatter will be left, generally 
#             it will be of the form _data/bsswt/YYYY-MM-DD-venue/. The new file
#             will be named event.yml
#
if [ $# -ne "2" ]; then
  echo "ERROR: incorrect number of arguments"
  echo "Usage: $0 source-file dest-dir"
  exit 1
fi

dest_file="$2/event.yml"

if [ ! -e "$1" ]; then
  echo "ERROR: source file $1 not found"
  exit 1
fi

if [ ! -d "$2" ]; then
  echo "ERROR: destination $2 either does not exist or is not a directory"
  exit 2
fi

# Drop anything before or after the delimiter ("---").  Also drop the delimeter itself.

awk 'BEGIN {delim=0} /---/ {++delim; next };  {if(delim % 2 == 1) print}' $1 > $dest_file