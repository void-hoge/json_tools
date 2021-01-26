#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "../filemanip.hpp"

int main(int argc, char const *argv[]) {
	assert(argc == 2);
	std::string filename = argv[1];
	std::string data;
	read_text_file(filename, data);

	// std::cout << data << '\n';
	std::string::size_type start_pos = 0;
	while (data.at(start_pos) != '{') {
		start_pos++;
	}
	for (std::string::size_type i = start_pos; i < data.length(); i++) {
		std::string key;
		std::string value;
		if (data.at(i) == '\"') {
			int space_count = 0;
			int tmp = i-1;
			while (data.at(tmp) == ' ') {
				tmp--;
				space_count++;
			}
			i++;
			while (data.at(i) != '\"') {
				key += data.at(i);
				i++;
			}
			i++;
			int bracket_count = 0;
			while (bracket_count >= 0 && i < data.length()) {
				if (bracket_count == 0 && data.at(i) == ',') {
					break;
				}
				switch (data.at(i)) {
					case '[': {
						bracket_count++;
						break;
					}
					case ']': {
						bracket_count--;
						break;
					}
					case '{': {
						bracket_count++;
						break;
					}
					case '}': {
						bracket_count--;
						break;
					}
				}
				value += data.at(i);
				if (data.at(i) == '\n') {
					i+=space_count;
					if (i >= data.length()) {
						continue;
					}
				}
				i++;
			}
			write_text_file(key, value);
		}
	}
	return 0;
}
