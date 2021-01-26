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

std::string get_word(std::string str, int n) {
	// n番目(0~)の単語を返す。
	std::string res;
	std::string::iterator it = str.begin();
	for (int i = 0; it < str.end() && i < n; it++) {
		if (*it == ' ') {
			i++;
		}
	}
	while (*it == ' '){
		it++;
	}
	for (; it < str.end(); it++) {
		if (*it == ' ') {
			break;
		}
		res+=*it;
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
	std::string res = "root/";
	for (auto& i: this->name) {
		res += i;
		res += "/";
	}
	return res;
}

bool viewer::show_list(const std::string option, std::ostream& ros) {
	int count = 0;
	this->list.clear();
	for (json::iterator it = this->current->begin(); it != this->current->end(); it++) {
		if (it.key().find(get_word(option, 0)) != std::string::npos) {
			ros << std::left << std::setw(10) << count << std::right << it.key() << '\n';
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
		num = std::stoi(get_word(option, 0));
	} catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << "invalid_argument: " << option << '\n';
		return false;
	}
	if (num < this->list.size()) {
		name_obj tmp = list.at(num);
		if (tmp.pointer->is_object() == false) {
			std::cerr << tmp.name << " is not an object." << '\n';
		}else {
			this->current = tmp.pointer;
			this->brc.pointer.push_back(tmp.pointer);
			this->brc.name.push_back(tmp.name);
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
	}else if (this->current->find(get_word(option, 0)) != this->current->end()) {
		json* tmp = &(*this->current->find(get_word(option, 0)));
		if (tmp->is_object() == true) {
			this->list.clear();
			this->brc.pointer.push_back(current);
			this->current = tmp;
			this->brc.name.push_back(get_word(option, 0));
		}else {
			std::cerr << "Error: " << get_word(option, 0) << " is not an object." << '\n';
			return false;
		}
	}else {
		std::cerr << "Error: " << get_word(option, 0) << " key not found" << '\n';
	}
	return true;
}

bool viewer::back() {
	if (this->brc.get_pwd() != "root/") {
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
	if (get_word(option, 0) == "") {
		ros << current->dump(4) << '\n';
		return true;
	}else if (current->find(get_word(option, 0)) != current->end()) {
		ros << (*current->find(get_word(option, 0))).dump(4) << '\n';
	}else {
		std::cerr << "Error: " << '\"' << get_word(option, 0) << '\"' << " key not found." << '\n';
	}
	return true;
}

bool viewer::file_output(const std::string option) {
	std::ofstream ofs(get_word(option, 0));
	manip(remove_first_word(option), ofs);
	ofs.close();
	return true;
}

bool viewer::manip(const std::string command, std::ostream& ros) {
	std::string first = get_word(command, 0);
	if (first == "end" || first == "\0") {
		// 終了
		return false;
	}else if (first == "list") {
		// 今の場所から見える要素を表示
		this->show_list(get_word(command, 1), ros);
	}else if (first == "select") {
		// 直近で作ったlistから選んでそこに移動
		this->select(get_word(command, 1));
	}else if (first == "move") {
		this->move(get_word(command, 1));
		// 直接objectを指定して移動
	}else if (first == "pwd") {
		// 現在の場所を表示
		std::cout << this->brc.get_pwd() << '\n';
	}else if (first == "back") {
		// 一つ前に戻る
		this->back();
	}else if (first == "dump") {
		// 現在の場所からdump
		this->dump(get_word(command, 1), ros);
	}else if (first == "output") {
		// ファイルに書き出す。
		this->file_output(remove_first_word(command));
	}else {
		// コマンドが見つからなかった
		std::cerr << "Error: " << "Command not found." << '\n';
	}
	return true;
}
