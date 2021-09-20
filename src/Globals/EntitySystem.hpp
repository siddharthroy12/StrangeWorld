#ifndef ENTITY_SYSTEM_INSTANCE_HPP
#define ENTITY_SYSTEM_INSTANCE_HPP

#include "../Entities/Entity.hpp"
#include <unordered_map>
#include <memory>

namespace EntitySystem {
	extern std::unordered_map<Id, std::shared_ptr<Entity>> _entities;
	extern Id create(std::shared_ptr<Entity> entity);
	extern void remove(Id id);
	void for_each(void (*func)(std::shared_ptr<Entity> entity));
}

#endif