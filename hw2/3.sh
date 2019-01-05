#!/usr/bin/env bash

searchfor="moveme"

if [ ! -d "$1" ]; then
  echo "Directory $1 does not exist" >&2
  exit
fi

# Search for text, then count number of lines, then trim spaces
number_of_lines=$( grep -ir $searchfor $1 | wc -l | tr -d '[:space:]' )
number_of_files=$( grep -lir $searchfor $1 | wc -l | tr -d '[:space:]' )

# Search for text, then move matched files
grep -lir $searchfor $1 | while read f; do mv "$f" $2; done

echo "Total lines matched: $number_of_lines"
echo "Total files moved: $number_of_files"
