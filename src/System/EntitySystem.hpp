#ifndef ENTITY_SYSTEM_INSTANCE_HPP
#define ENTITY_SYSTEM_INSTANCE_HPP

#include "../Entities/Entity.hpp"

#include <unordered_map>
#include "../Utils/Id.hpp"
#include <memory>

namespace EntitySystem {
	extern std::unordered_map<Id, std::shared_ptr<Entity>> _entities;
	extern int X;
	Id create(std::shared_ptr<Entity> entity);
	void remove(Id id);
	void for_each(void (*func)(std::shared_ptr<Entity> entity));
	void unloadEntities();
}

#endif