#include "init.h"
#include "input_loop.h"

extern std::vector<mapping> keyMapBase;

int main(int argc, char const *argv[])
{
    //run init
    init(argv, argc);

	//start event loop
    std::thread eventLoopThread(&TimerLoop);
    eventLoopThread.detach();

	//start input loop
	input_loop();

    return 0;
}
