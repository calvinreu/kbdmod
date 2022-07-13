#include <iostream>
#include <string.h>
#include <linux/input.h>
#include <libevdev-1.0/libevdev/libevdev.h>

using std::string;

//this function is copied from
//https://gitlab.com/interception/linux/plugins/dual-function-keys
//convert event code to string
inline int event_code(const string code) {

    int ret = libevdev_event_code_from_name(EV_KEY, code.c_str());
    if (ret == -1)
        ret = strtol(code.c_str(), NULL, 10);

    // KEY_RESERVED is invalid
    if (ret == 0)
        fprintf(stderr, "%s is an invalid key code\n", code.c_str());

    return ret;
}

int main(int argc, char **argv) {

	//check for params
	if (argc == 1) {
		std::cout << "No arguments provided." << std::endl;
		exit(1);
	}

	input_event ev;
	ev.code = event_code(argv[1]);
	ev.value = atoi(argv[2]);
	ev.type = EV_KEY;

	if (fwrite(&ev, sizeof(input_event), 1, stdout) != 1) {
		std::cout << "Error writing to stdout" << std::endl;
		exit(1);
	}
}
