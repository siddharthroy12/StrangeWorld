#include "../Entities/Entity.hpp"

#include <unordered_map>
#include "../Utils/Id.hpp"
#include <memory>

namespace EntitySystem {
	std::unordered_map<Id, std::shared_ptr<Entity>> _entities;

	Id create(std::shared_ptr<Entity> entity) {
		Id id = generateId();
		entity->_id = id;
		_entities[id] = entity;
		return id;
	}

	void remove(Id id) {
		_entities.erase(id);
	}

	void unloadEntities() {
		_entities.clear();
	}
}