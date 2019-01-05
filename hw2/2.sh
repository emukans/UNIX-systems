#!/usr/bin/env bash

# Read numbers from files
a=$( cat "a" )
b=$( cat "b" )

# Save multiplication to file
echo $(( $a * $b )) > "c"
