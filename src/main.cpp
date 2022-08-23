#include "init.h"
#include "input_loop.h"

//print usage
inline void usage() {
    std::cout <<
    "Usage: \n"
    "-h, --help: print this help message\n"
    "-v, --version: print version\n"
    "-c, --config: specify config file\n";
}

int main(int argc, char const *argv[])
{
	//check for params
    if (argc == 1) {
        usage();
        fprintf(stderr, "No arguments provided.\n");
        exit(0);
    }

    string configPath;

    //parse params
    for (auto i = argv+1; i < argv+argc; i++) {
		if (strcmp(*i, "-h") == 0 || strcmp(*i, "--help") == 0) {
			usage();
			exit(0);
		} else if (strcmp(*i, "-v") == 0 || strcmp(*i, "--version") == 0) {
			std::cout << "Version: " << VERSION << std::endl;
			exit(0);
		} else if (strcmp(*i, "-c") == 0 || strcmp(*i, "--config") == 0) {
			configPath = *(i+1);
			i++;
		} else {
			fprintf(stderr, "Unknown argument: %s\n", *i);
			usage();
			exit(1);
		}
	}

    //run init
    init(configPath);

	//start event loop
    std::thread eventLoopThread(&TimerLoop);
    eventLoopThread.detach();

	//start input loop
	input_loop();

    return 0;
}
