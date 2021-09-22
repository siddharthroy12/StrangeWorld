#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <string>

struct Resource {
	virtual std::string _name() {return "Resource";};
	virtual ~Resource() {};
};

#endif