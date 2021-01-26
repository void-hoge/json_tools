#include <iostream>
#include <cassert>
#include "../filemanip.hpp"
#include "viewer.hpp"
using json = nlohmann::json;

int main(int argc, char const *argv[]) {
	assert(argc == 2);
	std::string filename = argv[1];
	std::string alldata;
	std::cerr << "reading " << filename << "..." << '\n';
	read_text_file(filename, alldata);
	std::cerr << "constructing data..." << '\n';
	json data = json::parse(alldata);

	viewer vw(data);
	std::string command;
	std::cerr << ">>> ";
	std::getline(std::cin, command);
	while (vw.manip(command, std::cout)) {
		std::cerr << ">>> ";
		std::getline(std::cin, command);
	}
	return 0;
}
