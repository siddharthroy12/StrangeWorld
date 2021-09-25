#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Utils/Id.hpp"
#include <iostream>

class Entity {
	protected:
		std::string type;
	public:
		virtual void update() {}
		virtual void render() {}
		virtual ~Entity() {}
		std::string getType() {
			return type;
		}
		Id _id;
		
};

#endif