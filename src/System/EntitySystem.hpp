#ifndef ENTITY_SYSTEM_INSTANCE_HPP
#define ENTITY_SYSTEM_INSTANCE_HPP

#include "../Entities/Entity.hpp"
#include <unordered_map>
#include <memory>

namespace EntitySystem {
	Id create(std::shared_ptr<Entity> entity);
	void remove(Id id);
	void for_each(void (*func)(std::shared_ptr<Entity> entity));
}

#endif