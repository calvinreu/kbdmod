#! /bin/bash

# if $1==input, then return input

# Test script for the project
# cd into the script directory
cd "$(dirname "$0")"
# load the input file
input="$(cat input.txt)"
# remove hash lines from the input
input="$(echo "$input" | grep -v '#')"
# replace new line  with ' 50 '
input="${input//$'\n'/' 50 '}"
# add trailing q
input="$input"" q"

if [ "$1" == "input" ]; then
	echo "$input"
	exit 0
fi

#only to test script
#echo "$input"

# run the program and echo input at it to get the output
output=$((sleep 0.1; echo "$input") | ../build/kbdmod.bin -c testing.yaml)

#format the output
#remove 'read_event: '
output="${output//read_event: /}"
#remove 'write_event: '
output="${output//write_event: /}"
#save the output to a file
echo "$output" > output.txt

# compare the output with the expected output
./compare.out expected_output.txt output.txt

