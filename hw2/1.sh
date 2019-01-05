#!/usr/bin/env bash

# Write to standard output
echo "hello world"

# Delete file if exists
[ -e "deleteme.txt" ] && rm "deleteme.txt"

# Create directory if not exists
mkdir -p "new_dir"

# Write date in file. It's not clear from your context which operator > or >> I should use for this task.
date > "new_dir/date.txt"
