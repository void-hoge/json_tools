#include "viewer.hpp"
#include <fstream>

std::string add_tab(std::string str, int num_of_space) {
	std::string buf;
	for (std::string::iterator it = str.begin(); it < str.end(); it++) {
		if (*it == '\n') {
			buf+=*it;
			for (int i = 0; i < num_of_space; i++) {
				buf+=' ';
			}
		}else {
			buf+=*it;
		}
	}
	return buf;
}

std::string remove_space(std::string str) {
	for (std::string::iterator it = str.begin(); it < str.end(); it++) {
		if (*it == ' ') {
			str.erase(it);
		}
	}
	return str;
}

std::string get_first_word(std::string& str, std::vector<char> separators) {
	std::string res;
	std::string remained;
	std::string::size_type i = 0;
	for (; i < str.length(); i++) {
		if (std::find(separators.begin(), separators.end(), (char)str.at(i)) != separators.end()) {
			// separatorが見つかった
			i++;
			break;
		}
		res += str.at(i);
	}
	while (i < str.length() && std::find(separators.begin(), separators.end(), (char)str.at(i)) != separators.end()) {
		i++;
	}
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

std::string is_string (std::string str) {
	if (*(str.begin()) == '\"'&& *(str.end()-1) =='\"') {
		str.pop_back();
		str.erase(0, 1);
		return str;
	}else {
		return "";
	}
}

std::vector<std::vector<std::string>> separate_conditions(std::vector<std::string> str) {
	if ((str.size() % 4) != 3) {
		return std::vector<std::vector<std::string>>();
	}
	std::vector<std::vector<std::string>> res;
	res.resize((str.size()/4)+1);
	for (size_t i = 0; i < res.size(); i++) {
		for (size_t j = 0; j < 3; j++) {
			res[i].push_back(str[i*4+j]);
		}
	}
	return res;
}

std::vector<std::string> get_logic_arrary(std::vector<std::string> str) {
	std::vector<std::string> res;
	for (size_t i = 0; i < str.size(); i++) {
		if ((i%4) == 3) {
			res.push_back(str[i]);
		}
	}
	return res;
}

template<typename T>
bool compare (T a, T b, std::string op) {
	if (op == "=") {
		if (a == b) {
			return true;
		}
		return false;
	}
	if (op == "<") {
		if (a < b) {
			return true;
		}
		return false;
	}
	if (op == ">") {
		if (a > b) {
			return true;
		}
		return false;
	}
	if (op == "<=") {
		if (a <= b) {
			return true;
		}
		return false;
	}
	if (op == ">=") {
		if (a >= b) {
			return true;
		}
		return false;
	}
	if (op == "!=") {
		if (a != b) {
			return true;
		}
		return false;
	}
	return false;
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
	if (this->current->is_array()) {
		std::cerr << "You are in an array." << '\n';
		for (json::iterator it = this->current->begin(); it != this->current->end(); it++) {
			std::cerr << std::left << std::setw(10) << count;
			std::cerr << " " << get_datatype(&(*it));
			ros << '\n';
			count++;
			this->list.push_back(name_obj("", &(*it)));
		}
	}else {
		for (json::iterator it = this->current->begin(); it != this->current->end(); it++) {
			if (it.key().find(get_word(option, 0, (std::vector<char>){' '})) != std::string::npos) {
				std::cerr << std::left << std::setw(10) << count << std::left << std::setw(10) << get_datatype(&(*it));
				ros << it.key() << '\n';
				count++;
				this->list.push_back(name_obj(it.key(), &(*it)));
			}
		}
	}
	return true;
}

std::string viewer::get_datatype(json* ptr) const {
	if (ptr->is_array()) {
		return "array";
	}else if (ptr->is_boolean()) {
		return "boolean";
	}else if (ptr->is_null()) {
		return "null";
	}else if (ptr->is_number()) {
		return  "number";
	}else if (ptr->is_object()) {
		return "object";
	}else if (ptr->is_string()) {
		return "string";
	}
	return "";
}

bool viewer::is_fulfill(json* pointer, const std::vector<std::string> separated_option) const{
	// separated_option
	// 0:hoge/poyo
	// 1:=
	// 2:100, "hoge" ext...
	auto directories = separate_words(separated_option[0], (std::vector<char>){'/', '[', ']'});
	// directories
	// 0:hoge
	// 1:poyo
	for (size_t i = 0; i < directories.size(); i++) {
		if (pointer->is_array() == true) {
			try {
				int array_num = std::stoi(directories[i]);
				pointer = &(*pointer).at(array_num);
			}catch (std::exception& e) {
				// 配列だが、数字として認識されていない。
				std::cerr << e.what() << '\n';
				return false;
			}
		}else {
			if (pointer->contains(directories[i]) == true) {
				pointer = &((*pointer)[directories[i]]);
			}else {
				return false;
			}
		}
	}
	if (separated_option.size() == 1) {
		// 要素の存在さえ分かればいい場合
		return true;
	}else if (pointer->is_object() == true) {
		// そうでない場合、オブジェクトではなく値である必要がある
		return false;
	}
	// separated_option[2]に対し、型を調べて一致を検査する
	if (separated_option[2] == "*") {
		// ワイルドカード
		return true;
	}
	if (separated_option[2] == "null") {
		if (pointer->is_null()) {
			return true;
		}else {
			return false;
		}
	}
	if (separated_option[2] == "true") {
		if (pointer->is_boolean()) {
			if (*pointer == true) {
				return true;
			}
		}
		return false;
	}
	if (separated_option[2] == "false") {
		if (pointer->is_boolean() == true) {
			if (*pointer == false) {
				return true;
			}
		}
		return false;
	}
	{
		std::string tmp = is_string(separated_option[2]);
		if (tmp != "") {
			if (pointer->is_string()) {
				return compare((std::string)(*pointer), tmp, separated_option[1]);
			}
			return false;
		}
	}
	if (pointer->is_number()) {
		if (pointer->is_number_float()) {
			try {
				// nlohmann jsonでは実数は暗黙にdoubleに変換される。
				double tmp = stod(separated_option[2]);
				return compare((double)(*pointer), tmp, separated_option[1]);
			} catch (std::exception& e){
				// do nothing
			}
			return false;
		}
		if (pointer->is_number_integer()) {
			try {
				long long tmp = stoll(separated_option[2]);
				return compare((long long)(*pointer), tmp, separated_option[1]);
			} catch (std::exception& e) {
				// do nothing
			}
			return false;
		}
	}
	return true;
}

bool viewer::find(std::string option, std::ostream& ros) {
	this->list.clear();
	if (this->current->is_array()) {
		std::cerr << "You are in an array." << '\n';
	}
	std::cerr << option << '\n';
	// option "hoge/poyo=foobar"
	option = add_space(option, (std::vector<char>){'=', '<', '>', '&', '|', '^', '!'});
	// option "hoge/poyo = foobar"
	auto separated_option = separate_words(option, (std::vector<char>){' '});
	// separated_option
	// 0:"hoge/poyo"
	// 1:"="
	// 2:"foobar"
	// 3:"&"
	// 4:"huga/hugo"
	// 5:">"
	// 6:"114514"
	auto conditions = separate_conditions(separated_option);
	auto logic_array = get_logic_arrary(separated_option);

	std::vector<bool> result_array;
	int count = 0;
	for (json::iterator it = this->current->begin(); it != this->current->end(); it++) {
		for (size_t i = 0; i < conditions.size(); i++) {
			result_array.push_back(this->is_fulfill(&(*it), conditions[i]));
		}
		bool result = result_array[0];
		for (size_t i = 0; i < logic_array.size(); i++) {
			if (logic_array[i] == "&") {
				result&=result_array[i+1];
			}else if (logic_array[i] == "|") {
				result|=result_array[i+1];
			}else if (logic_array[i] == "^") {
				result^=result_array[i+1];
			}
		}
		if (result) {
			if (this->current->is_array()) {
				std::cerr << std::left << std::setw(10) << count;
				std::cerr << " " << get_datatype(&(*it));
				ros << '\n';
				count++;
				this->list.push_back(name_obj("", &(*it)));
			}else {
				std::cerr << std::left << std::setw(10) << count;
				std::cerr << std::left << std::setw(10) << get_datatype(&(*it));
				ros << it.key() << '\n';
				count++;
				this->list.push_back(name_obj(it.key(), &(*it)));
			}
		}
		result_array.clear();
		// if (this->is_fulfill(&(*it), separated_option) == true) {
		// 	std::cerr << std::left << std::setw(10) << count;
		// 	ros << it.key() << '\n';
		// 	count++;
		// 	this->list.push_back(name_obj(it.key(), &(*it)));
		// }
	}
	return true;
}

bool viewer::select(const std::string option) {
	size_t num;
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
		if (tmp.pointer->is_object() == false && tmp.pointer->is_array() == false) {
			std::cerr << "Error: " << tmp.name << " is not an object or array." << '\n';
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
		if (tmp->is_object() == true || tmp->is_array() == true) {
			this->list.clear();
			this->brc.pointer.push_back(current);
			this->current = tmp;
			this->brc.name.push_back(get_word(option, 0, (std::vector<char>){' '}));
		}else {
			std::cerr << "Error: " << get_word(option, 0, (std::vector<char>){' '}) << " is not an object or array." << '\n';
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
		ros << "{";
		for (size_t i = 0; i < this->list.size(); i++) {
			ros << "\n    \"" << this->list[i].name << "\": ";
			ros << add_tab((std::string)(this->list[i].pointer->dump(4)), 4);
			if (i != this->list.size()-1) {
				ros << ",";
			}
		}
		ros << "\n}\n";
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
	std::string option = remove_first_word(command);
	if (first == "end" || first == "\0") {
		// 終了
		return false;
	}else if (first == "list") {
		// 今の場所から見える要素を表示
		this->show_list(option, ros);
	}else if(first == "find") {
		this->find(option, ros);
	}else if (first == "select") {
		// 直近で作ったlistから選んでそこに移動
		this->select(option);
	}else if (first == "move") {
		// 直接objectを指定して移動
		this->move(option);
	}else if (first == "pwd") {
		// 現在の場所を表示
		ros << this->brc.get_pwd() << '\n';
	}else if (first == "back") {
		// 一つ前に戻る
		this->back();
	}else if (first == "dump") {
		// 現在の場所からdump
		this->dump(option, ros);
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
