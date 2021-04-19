#include <iostream>
#include <nlohmann/json.hpp>
#include "../filemanip.hpp"

using json = nlohmann::json;

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		throw std::runtime_error("Error: No input JSON file.");
	}
	std::string filename = argv[1];
	std::string rawdata;
	std::cerr << "Reading " << filename << "..." << '\n';
	read_text_file(filename, rawdata);
	std::cerr << "Constructing the data..." << '\n';
	json data = json::parse(rawdata);

	data.is_array();
	json converted;
	for (size_t i = 0; i < data.size(); i++) {
		converted["data"+i] = data[i];
	}
	write_text_file(argv[2], converted.dump(4));
	return 0;
}
