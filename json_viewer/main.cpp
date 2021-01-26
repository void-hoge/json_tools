#include <iostream>
#include <string>
#include <cassert>
#include "../filemanip.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(int argc, char const *argv[]) {
	assert(argc == 2);
	std::string filename = argv[1];
	std::string alldata;
	read_text_file(filename, alldata);
	json hoge = json::parse(alldata);
	// for (json::iterator it = hoge.begin(); it != hoge.end(); it++) {
	// 	write_text_file(it.key(), it->dump(4));
	// }
	for (json::iterator it = hoge.begin(); it != hoge.end(); ++it) {
		if (it.key().find("Yamato") != std::string::npos) {
			std::cout << it.key() << '\n';
		}
	}
	return 0;
}
