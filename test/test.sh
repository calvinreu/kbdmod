#! /bin/bash

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

echo "$input"

# run the program and echo input at it to get the output
output=$((sleep 0.1; echo "$input") | ../build/keyboard_modify.bin -c testing.yaml)

# load the expected output file
expected="$(cat expected_output.txt)"

echo "$output"
echo "$expected"

