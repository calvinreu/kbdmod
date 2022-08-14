# kbdmod

intercept keycodes and change them to emulate qmk/oryx zsa like behaviour with any keyboard meaning you can assign macros, OSMs and normal keys to single tap, double tap, hold or tap and then hold of a key

a lot of this project is from [dual-function-keys](https://gitlab.com/interception/linux/plugins/dual-function-keys) also a great project worth checking out

## Installation
dependencies
 - yaml-cpp
 - evdev
 - interception-tools

build dependencies
 - cmake
 - make

 > cd tmp && git clone https://gitlab.com/input-configuration/keyboard_modify && cd keyboard_modify && ./install.sh

## Configuration
There are two parts to be configured: kbdmod and udevmon, which launches kbdmod.

See [examples](https://gitlab.com/interception/linux/plugins/dual-function-keys/-/tree/master/doc/examples.md) which contains kbdmod and udevmon.yaml configurations.

### keyboard_modify

This yaml file conventionally resides in `/etc/interception/kbdmod`.

You can use raw (integer) keycodes, however it is easier to use the `#define`d strings from [input-event-codes.h](https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h).

```yaml
#unmapped keys should behave as usual
TIMING:
	# max amount of ms to qualify as a tap default = 200
    TAP_MILLISEC: <integer>

MAPPINGS:
	#required to create mapping
    - KEY: <integer | string>
      TAP: [ <integer | string>, ... ]
	#optional options of mapping
      HOLD: [ <integer | string>, ... ]
	  DOUBLETAP: [ <integer | string>, ... ]
	  TAPHOLD: [ <integer | string>, ... ]
	  TAP_OSM: bool
	  DOUBLETAP_OSM: bool
	  HOLD_OSM: bool
	  TAPHOLD_OSM: bool
    - KEY: ...
```

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Just create an issue or mail me

## Roadmap
 - remove unecessary delays
 - config creator would be nice if it has a gui web based
 - pipeline for gui when done
 - general options for something like autoshift
 - support for mouse output through keyboard
 - layer system
 - led control for layers usw

## Contributing
### debuging
to debug build the project with the DEBUG flag in cmake
use the console and the sequences from test/combinations.txt for testing
this is a part of the vscode debuger options but they should be easy to convert to any other debuger as well
```json
"program": "${workspaceFolder}/build/keyboard_modify.bin",
"args": ["-c", "${workspaceFolder}/test/testing.yaml"],
```
Note: the manual testing script does not work yet it is supposed to enable this program on your system and disable it after 20s

### contributing
Contributions are very welcome for improvements with the current features a working pipeline is enough to get a commit merged though testing your code yourself would be nice for implementation of new features even if they are on the roadmap please create an issue so the details can be resolved contributing examples would be very welcome.
PS: please follow the editorconfig

## License
this project is under the MIT license (c)Calvin Reu see LICENSE

## Project status
first functional version the project is currently under active development contributions and suggestions are welcome
