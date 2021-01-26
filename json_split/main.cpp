#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

void makefile(std::string filename, std::string data) {
	std::ofstream file(filename+".json");
	file << '\"';
	file << filename;
	file << '\"';
	file << data;
	file.close();
}

int main(int argc, char const *argv[]) {
	assert(argc == 2);
	std::string filename = argv[1];
	std::ifstream ifs(filename);
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string data(it, last);

	// std::cout << data << '\n';
	std::vector<std::string> hoge;
	std::string::size_type start_pos = 0;
	while (data.at(start_pos) != '{') {
		start_pos++;
	}
	for (std::string::size_type i = start_pos; i < data.length(); i++) {
		std::string key;
		std::string value;
		if (data.at(i) == '\"') {
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
				i++;
			}
			makefile(key, value);
		}
	}
	return 0;
}
