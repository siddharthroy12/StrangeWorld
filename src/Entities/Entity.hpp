#ifndef ENETIY_HPP
#define ENTIT_HPP

#include "../Utils/Id.hpp"

class Entity {
	public:
		void update();
		Entity(Id id) : id(id) {}
		Id id;
	private:
		
};

#endif