#ifndef ENETIY_HPP
#define ENTITY_HPP

#include "../Utils/Id.hpp"
#include <iostream>

class Entity {
	public:
		virtual void update() {};
		virtual void render() {};
		Id _id;
		
};

#endif