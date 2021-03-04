#ifndef VIEWER_HPP_INCLUDED
#define VIEWER_HPP_INCLUDED

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class branch {
public:
	branch() {}
	int size() const {
		return pointer.size();
	}
	std::vector<json*> pointer;
	std::vector<std::string> name;
	std::string get_pwd() const;
};

class name_obj {
public:
	name_obj(std::string nm, json* p):name(nm), pointer(p){}
	std::string name;
	json* pointer;
};

class viewer {
private:
	json data;
	json* current;
	branch brc;
	std::vector<name_obj> list;
	bool show_list(const std::string option, std::ostream& ros);
	bool is_fulfill(json* pointer, const std::vector<std::string> separatad_option) const;
	bool find(std::string option, std::ostream& ros);
	bool select(const std::string option);
	bool move(const std::string option);
	bool back();
	bool dump(const std::string option, std::ostream& ros);
	bool file_output(const std::string option);
public:
	viewer(json src) {
		data = src;
		current = &data;
	}
	bool manip(const std::string command, std::ostream& ros);
	std::string current_pos() const;
};

#endif /* end of include guard: VIEWER_HPP_INCLUDED */
