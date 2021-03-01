#include <iostream>
#include <string>
#include <vector>


std::string get_first_word(std::string& str, std::vector<char> separators) {
	std::string res;
	std::string::iterator it = str.begin();
	// 最初のseparatorを読み飛ばす。
	while (true){
		bool frag = false;
		for (char a: separators) {
			if (*it == a) {
				frag = true;
				break;
			}
		}
		if (frag) {
			it++;
			if (it == str.end()) {
				return res;
			}
			continue;
		}else {
			break;
		}
	}
	while (true) {
		bool frag = false;
		for (char a: separators) {
			if (*it == a) {
				frag = true;
			}
		}
		if (frag == false) {
			res+=*it;
			it++;
			if (it == str.end()) {
				break;
			}
		}else {
			break;
		}
	}
	std::string remain;
	while (it != str.end()) {
		remain+=*it;
		it++;
	}
	str = remain;
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

int main(int argc, char const *argv[]) {
	std::string a;
	std::getline(std::cin, a, '\n');
	for (int i = 0; i < 4; i++) {
		// std::cout << get_first_word(a, (std::vector<char>){' ', '='}) << '\n';
		std::cout << get_word(a, i, (std::vector<char>){' ', '='}) << '\n';
	}
	return 0;
}
