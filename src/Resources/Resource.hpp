#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <string>

struct Resource {
	std::string _name;
	virtual ~Resource() {};
};

#endif