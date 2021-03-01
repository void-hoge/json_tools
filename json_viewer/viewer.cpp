#include "viewer.hpp"
#include <fstream>

std::string remove_space(std::string str) {
	for (std::string::iterator it = str.begin(); it < str.end(); it++) {
		if (*it == ' ') {
			str.erase(it);
		}
	}
	return str;
}

std::string get_first_word(std::string& str, std::vector<char> separators) {
	if (str == "") {
		return std::string("");
	}
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
	// 最初にseparatorに到達するまで読む
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
	// 止まった部分以降を読む
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

std::string remove_first_word(std::string str) {
	std::string res;
	std::string::size_type tmp = 0;
	// 最初のスペースがある場合、読み飛ばす。
	while (tmp < str.length() && str.at(tmp) == ' ') {
		tmp++;
	}
	// 1単語目を読み飛ばす
	while (tmp < str.length() && str.at(tmp) != ' ') {
		tmp++;
	}
	// スペースがある場合、読み飛ばす。
	while (tmp < str.length() && str.at(tmp) == ' ') {
		tmp++;
	}
	// 残りを書き込む
	while (tmp < str.length()) {
		res+=str.at(tmp);
		tmp++;
	}
	return res;
}

std::string branch::get_pwd() const{
	std::string res;
	for (auto& i: this->name) {
		res += "/";
		res += i;
	}
	return res;
}

bool viewer::show_list(const std::string option, std::ostream& ros) {
	int count = 0;
	this->list.clear();
	for (json::iterator it = this->current->begin(); it != this->current->end(); it++) {
		if (it.key().find(get_word(option, 0, (std::vector<char>){' '})) != std::string::npos) {
			std::cerr << std::left << std::setw(10) << count;
			ros << std::right << it.key() << '\n';
			count++;
			this->list.push_back(name_obj(it.key(), &(*it)));
		}
	}
	return true;
}

bool viewer::select(const std::string option) {
	int num;
	if (this->list.empty() == true) {
		std::cerr << "Error: " << "There is no list." << '\n';
		return false;
	}
	try {
		num = std::stoi(get_word(option, 0, (std::vector<char>){' '}));
	} catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << "invalid_argument: " << option << '\n';
		return false;
	}
	if (num < this->list.size() && num >= 0) {
		name_obj tmp = list.at(num);
		if (tmp.pointer->is_object() == false) {
			std::cerr << tmp.name << " is not an object." << '\n';
		}else {
			this->brc.pointer.push_back(current);
			this->brc.name.push_back(tmp.name);
			this->current = tmp.pointer;
			this->list.clear();
		}
	}else {
		std::cerr << "Error: " << num << " is out of range." << '\n';
	}
	return true;
}

bool viewer::move(const std::string option) {
	if (option == "") {
		this->list.clear();
		this->current = &data;
		this->brc.pointer.clear();
		this->brc.name.clear();
	}else if (this->current->find(get_word(option, 0, (std::vector<char>){' '})) != this->current->end()) {
		json* tmp = &(*this->current->find(get_word(option, 0, (std::vector<char>){' '})));
		if (tmp->is_object() == true) {
			this->list.clear();
			this->brc.pointer.push_back(current);
			this->current = tmp;
			this->brc.name.push_back(get_word(option, 0, (std::vector<char>){' '}));
		}else {
			std::cerr << "Error: " << get_word(option, 0, (std::vector<char>){' '}) << " is not an object." << '\n';
			return false;
		}
	}else {
		std::cerr << "Error: " << get_word(option, 0, (std::vector<char>){' '}) << " key not found" << '\n';
	}
	return true;
}

bool viewer::back() {
	if (this->brc.get_pwd() != "") {
		this->list.clear();
		if (this->brc.pointer.empty() == true) {
			this->current = &data;
		}else {
			this->current = brc.pointer.back();
		}
		this->brc.pointer.pop_back();
		this->brc.name.pop_back();
		return true;
	}else {
		std::cerr << "Error: " << "You are in the root." << '\n';
		return false;
	}
}

bool viewer::dump(std::string option, std::ostream& ros) {
	if (get_word(option, 0, (std::vector<char>){' '}) == "") {
		if (this->list.empty()) {
			std::cerr << "Error: " << "There is no list." << '\n';
			return false;
		}
		for (int i = 0; i < this->list.size(); i++) {
			ros << "\"" << this->list[i].name << "\": ";
			ros << this->list[i].pointer->dump(4);
			if (i != this->list.size()-1) {
				ros << ",";
			}
			ros << "\n";
		}
		return true;
	}else if (current->find(get_word(option, 0, (std::vector<char>){' '})) != current->end()) {
		ros << (*current->find(get_word(option, 0, (std::vector<char>){' '}))).dump(4) << '\n';
	}else {
		std::cerr << "Error: " << '\"' << get_word(option, 0, (std::vector<char>){' '}) << '\"' << " key not found." << '\n';
	}
	return true;
}

bool viewer::file_output(const std::string option) {
	std::ofstream ofs(get_word(option, 0, (std::vector<char>){' '}));
	manip(remove_first_word(option), ofs);
	ofs.close();
	return true;
}

bool viewer::manip(const std::string command, std::ostream& ros) {
	std::string first = get_word(command, 0, (std::vector<char>){' '});
	if (first == "end" || first == "\0") {
		// 終了
		return false;
	}else if (first == "list") {
		// 今の場所から見える要素を表示
		this->show_list(get_word(command, 1, (std::vector<char>){' '}), ros);
	}else if (first == "select") {
		// 直近で作ったlistから選んでそこに移動
		this->select(get_word(command, 1, (std::vector<char>){' '}));
	}else if (first == "move") {
		this->move(get_word(command, 1, (std::vector<char>){' '}));
		// 直接objectを指定して移動
	}else if (first == "pwd") {
		// 現在の場所を表示
		std::cout << this->brc.get_pwd() << '\n';
	}else if (first == "back") {
		// 一つ前に戻る
		this->back();
	}else if (first == "dump") {
		// 現在の場所からdump
		this->dump(get_word(command, 1, (std::vector<char>){' '}), ros);
	}else if (first == "output") {
		// ファイルに書き出す。
		this->file_output(remove_first_word(command));
	}else {
		// コマンドが見つからなかった
		std::cerr << "Error: " << "Command not found." << '\n';
	}
	return true;
}

std::string viewer::current_pos() const {
	return this->brc.get_pwd()+" ";
}
