#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string get_first_word(std::string& str, std::vector<char> separators) {
	std::string res;
	std::string remained;
	std::string::size_type i = 0;
	for (; i < str.length(); i++) {
		if (std::find(separators.begin(), separators.end(), (char)str.at(i)) != separators.end()) {
			// separatorが見つかった
			break;
		}
		res += str.at(i);
	}
	i++;
	for (; i < str.length(); i++) {
		remained += str.at(i);
	}
	str = remained;
	return res;
}

std::string get_word(std::string str, int n, std::vector<char> separators) {
	// n番目(0~)の単語を返す。
	std::string res;
	for (int i = 0; i <= n; i++) {
		res = get_first_word(str, separators);
	}
	return res;
}

std::vector<std::string> separate_words(std::string str, std::vector<char> separators) {
	std::vector<std::string> res;
	while(str != "") {
		res.push_back(get_first_word(str, separators));
	}
	return res;
}

std::string add_space (std::string str, std::vector<char> separators) {
	std::string res;
	for (std::string::size_type i = 0; i < str.length(); i++) {
		if (std::find(separators.begin(), separators.end(), str.at(i)) != separators.end()) {
			res+=' ';
			for (; i < str.length(); i++) {
				if (std::find(separators.begin(), separators.end(), str.at(i)) == separators.end()) {
					break;
				}
				res+=str.at(i);
			}
			res+=' ';
		}
		res+=str.at(i);
	}
	return res;
}

int main(int argc, char const *argv[]) {
	try {
		double a = std::stod("263");
		std::cout << a << '\n';
	}catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
	return 0;
}
