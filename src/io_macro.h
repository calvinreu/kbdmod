#pragma once
#include "io.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals;
using std::chrono::system_clock;
using std::chrono::milliseconds;

inline bool debug_read_event(input_event *input)
{
	static std::vector<uint16_t> seq;
	std::string in;
	if (seq.size() == 0) {
		fprintf(stdout, "read_event: ");
		//read input
		std::getline(std::cin, in);
		//split string at spaces
		std::stringstream ss(in);
		std::string item;
		while (std::getline(ss, item, ' ')) {
			//check for quit
			if (item == "q")
				seq.push_back(UINT16_MAX);
			else
				seq.push_back(std::stoi(item));
		}
	}else{
		if (seq.size() == 1 && seq[0] == UINT16_MAX) {
			sleep_for(milliseconds(300));
			return false;
		}
		sleep_for(milliseconds(seq[0]));
		//remove sleep time from seq
		seq.erase(seq.begin(), seq.begin() + 1);
	}

	*input = {timeval{0,0}, seq[0], seq[1], seq[2]};
	seq.erase(seq.begin(), seq.begin() + 3);

	return true;
}


/* https://www.kernel.org/doc/html/latest/input/event-codes.html */
#define INPUT_VAL_PRESS 1
#define INPUT_VAL_RELEASE 0
#define INPUT_VAL_REPEAT 2//ignore

#ifndef OUTPUT_DELAY//delay between output sequence keys
#define OUTPUT_DELAY 15
#endif

//if DEBUG
#ifndef DEBUG
#define DEBUG 0
#endif
#if DEBUG
//write output to stdout
#define write_event__(x) {\
	fprintf(stdout, "write_event: %d %d %d\n",\
	x->type, x->code, x->value);\
}
//read input from stdin
#define read_event__(x) {return debug_read_event(x);}
#else
#define write_event__(x) {\
if (fwrite(x, sizeof(struct input_event), 1, stdout) != 1) \
	fprintf(stderr, "Error writing to stdout.\n"); \
syn_pause();\
}
#define read_event__(x) {\
	return fread(input, sizeof(struct input_event), 1, stdin) == 1;\
}
#endif
