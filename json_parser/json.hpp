#ifndef JSON_HPP_INCLUDED
#define JSON_HPP_INCLUDED

#include <vector>
#include <string>

namespace voidhoge {



class json {
private:
	static enum data_type {
		object,
		array,
		integer,
		floating,
		boolean,
		str,
		null
	};
	std::string name;
	std::vector<json> elements;
public:
	json ();
	json (std::string name);
	void dump(int tab, int space);
};

}

#endif
