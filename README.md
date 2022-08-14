# keyboard-configuartor

intercept keycodes and change them to emulate qmk/oryx zsa like behaviour with any keyboard

## TODO
 - fix taphold
 - add pipeline to validate functionallity working as intended
 - write configuration process to readme
 - some sort of examples and usage
 - add contributing


## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Installation
dependencies
 - yaml-cpp
 - evdev
 - interception-tools

build dependencies
 - cmake
 - make

 > cd tmp && git clone https://gitlab.com/input-configuration/keyboard_modify && cd keyboard_modify && ./install.sh

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Just create an issue or mail me

## Roadmap
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
probably not helpfull until there is a working alpha and pipeline

## License
this project is under the MIT license (c)Calvin Reu see LICENSE

## Project status
pre alpha
