#! /bin/bash


# Remove # from the input file
input=$(grep -v '#' input.txt)

# send input
function send_input() {
	#send key_code
	echo "$(./test.bin "$(echo $1 | cut -d ':' -f 1)" "1")"
	#sleep release_delay
	sleep $(echo $1 | cut -d ':' -f 3)
	#send key_code release
	echo "$(./test.bin "$(echo $1 | cut -d ':' -f 1)" "0")"
}

#input format is: key_code:press_delay:release_delay
# send input events
function input_loop() {
	for i in $input; do
		#sleep press_delay
		sleep $(echo $i | cut -d ':' -f 2)
		#send input
		send_input $i &
	done
}

input_loop | ../build/keyboard_modify.bin -c testing.yaml > output.txt
