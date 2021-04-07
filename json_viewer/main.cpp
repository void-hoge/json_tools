#include <iostream>
#include <cassert>
#include "../filemanip.hpp"
#include "viewer.hpp"
using json = nlohmann::json;

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		throw std::runtime_error("Error: No input JSON file.");
	}
	std::string filename = argv[1];
	std::string alldata;
	std::cerr << "Reading " << filename << "..." << '\n';
	read_text_file(filename, alldata);
	std::cerr << "Constructing the data..." << '\n';
	json data = json::parse(alldata);

	viewer vw(data);
	std::string command;
	std::cerr << vw.current_pos() << "> ";
	std::getline(std::cin, command);
	while (vw.manip(command, std::cout)) {
		std::cerr << vw.current_pos() << "> ";
		std::getline(std::cin, command);
	}
	return 0;
}
