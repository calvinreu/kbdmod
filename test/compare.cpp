#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//main function
int main(int argc, char *argv[])
{
	bool same = true;
	if (argc != 3) {
		std::cout << "enter to files to compare as arguments" << std::endl;
		return 1;
	}
	std::ifstream file1(argv[1]);
	std::ifstream file2(argv[2]);
	if (!file1.is_open()) {
		std::cerr << "Could not open file: " << argv[1] << std::endl;
		return 1;
	}
	if (!file2.is_open()) {
		std::cerr << "Could not open file: " << argv[2] << std::endl;
		return 1;
	}

	std::string line1;
	std::string line2;
	while (std::getline(file1, line1) && std::getline(file2, line2)) {
		if (line1 != line2) {
			std::cout << "---------" << std::endl;
			std::cout << line1 << " : " << line2 << std::endl;
			std::cout << "---------" << std::endl;
			same = false;
		}else{
			std::cout << line1 << " : " << line2 << std::endl;
		}
	}
	while (std::getline(file1, line1)) {
		std::cout << line1 << std::endl;
		same = false;
	}
	while (std::getline(file2, line2)) {
		std::cout << line2 << std::endl;
		same = false;
	}
	file1.close();
	file2.close();
	if(same)
		return 0;
	else
		return 1;
}
