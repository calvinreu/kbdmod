# kbdmod

[![pipeline status](https://gitlab.com/calvinreu/kbdmod/badges/main/pipeline.svg)](https://gitlab.com/calvinreu/kbdmod/-/commits/main)
[![AUR](https://img.shields.io/aur/version/kbdmod)](https://aur.archlinux.org/packages/kbdmod)
[![Latest Release](https://gitlab.com/calvinreu/kbdmod/-/badges/release.svg)](https://gitlab.com/calvinreu/kbdmod/-/releases)

intercept keycodes and change them to emulate qmk/oryx zsa like behaviour with any keyboard meaning you can assign macros, OSMs and normal keys to single tap, double tap, hold or tap and then hold of a key. Create multiple keyboard layers and cycle between them or enable autoshift to automaticly add a shift key for normal keys which are held down to improve writing comfort.

a lot of this project is from [dual-function-keys](https://gitlab.com/interception/linux/plugins/dual-function-keys) a great project worth checking out

## Installation
dependencies
 - yaml-cpp
 - evdev
 - interception-tools

build dependencies
 - cmake
 - make

 > cd tmp && git clone https://gitlab.com/calvinreu/kbdmod && cd kbd && ./install.sh

## Configuration
There are two parts to be configured: kbdmod and udevmon, which launches kbdmod.

See [examples](https://gitlab.com/calvinreu/kbdmod/-/blob/main/doc/examples.md) which contains kbdmod configurations.

### udevmon
This yaml file resides in `/etc/interception/udevmon.d/Keyboard1.yaml`
to get the keyboard name use
> sudo libinput list-devices | grep Device | grep eyboard

```yaml
- JOB: "intercept -g $DEVNODE | kbdmod -c /etc/interception/kbdmod/configname
  DEVICE:
    NAME: "Keyboard name"
- JOB: ...
```

### kbdmod

This yaml file conventionally resides in `/etc/interception/kbdmod`.

You can use raw (integer) keycodes, however it is easier to use the `#define`d strings from [input-event-codes.h](https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h).

```yaml
#unmapped keys should behave as usual
TIMING:
	# max amount of ms to qualify as a tap default = 200
    TAP_MILLISEC: <integer>
FEATURES:
	# add numbers togethere to get desired behaviour
	# enable from start on 1
	# autoshift every digit 2
	# every letter 4
	# every special character 8
	# for example 3 for digits and at start enabled
  	AUTOSHIFT: <integer>

MAPPINGS:
	#naming of layer
	baselayer:
		#required to create mapping
    	- KEY: <integer | string>
    	  TAP: [ <integer | string>, ... ]
		#optional options of mapping
    	  HOLD: [ <integer | string>, ... ]
		  DOUBLETAP: [ <integer | string>, ... ]
		  TAPHOLD: [ <integer | string>, ... ]
		  #OSM means modify next sequence for output for example add a shift or control
		  TAP_OSM: bool
		  DOUBLETAP_OSM: bool
		  HOLD_OSM: bool
		  TAPHOLD_OSM: bool
		- KEY: <integer | string>
		  #create command mappings which do not emulate keypresses but run some programm internal command
		  CMD:
		  	#options are
			#SWITCH_LAYER
			#SWITCH_LAYER_OSM (switch layer only for one key press)
		  	TYPE: <string>
			#only necessary when type is smth_layer_smth
			LAYER: otherlayer
    	- KEY: ...
	otherlayer:
		- KEY: ...
	...
```

## Usage
to get a bit of inspiration what you could do with this look for zsa oryx on youtube note that layers are not supported yet

## Support
Just create an issue or mail me

## Contributing
Contributions are very welcome for improvements. Testing your code yourself should be done either by using the project activly with the new code or by using test_manual script. If your merge request adds some new feature which is not yet in the config please change the manual_testing.yaml for quick checks the test.sh can be helpfull but its not a complete test.
PS: please follow the editorconfig
## Debuging
to debug build the project with the DEBUG flag in cmake
use the console and the sequences from test/combinations.txt for testing
this is a part of the vscode debuger options but they should be easy to convert to any other debuger as well
```json
"program": "${workspaceFolder}/build/keyboard_modify.bin",
"args": ["-c", "${workspaceFolder}/test/testing.yaml"],
```

## License
this project is under the MIT license (c)Calvin Reu see LICENSE

## Project status
first functional version the project is currently under active development contributions and suggestions are welcome

## Roadmap
 - config creator would be nice if it has a gui web based
 - support for mouse output through keyboard
 - led control of capslock, numlock and scrlck leds

