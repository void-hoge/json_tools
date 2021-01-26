#pragma once

#include <fstream>
#include <string>

void write_text_file(const std::string filename, const std::string data) {
	std::ofstream file(filename+".json");
	file << '\"';
	file << filename;
	file << '\"';
	file << data;
	file.close();
}

void read_text_file(const std::string filename, std::string& data) {
	std::ifstream ifs(filename);
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	data = std::string(it, last);
	ifs.close();
}
