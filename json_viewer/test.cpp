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
	std::cout << "A_Artillery/sigmaCount<=2.1" << '\n';
	std::cout << add_space("A_Artillery/sigmaCount<=2.1", (std::vector<char>){'=', '<', '>'}) << '\n';
	return 0;
}
