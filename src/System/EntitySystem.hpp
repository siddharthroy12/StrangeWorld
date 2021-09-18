#ifndef ENTITY_SYSTEM_HPP
#define ENTITY_SYSTEM_HPP

#include <unordered_map>

#include "../Utils/Id.hpp"

template<typename T>
class EntitySystem {
	private:
		std::unordered_map<Id, T*> entities;
	public:
		Id create(T* entity);
		void remove(Id id);
		T* get(Id id);

		void for_each(void (*func)(T *entity));
		~EntitySystem();
};

template <typename T>
Id EntitySystem<T>::create(T* entity) {
	Id id = generateId();
	entity->_id = id;
	this->entities[id] = entity;
	return id;
}

template <typename T>
void EntitySystem<T>::remove(Id id) {
	delete this->entities[id];
	this->entities.erase(id);
}

template <typename T>
T* EntitySystem<T>::get(Id id) {
	return this->entities[id];
}

template <typename T>
void EntitySystem<T>::for_each(void (*func)(T *entity)) {
	for (const auto& kv : this->entities) {
		func(kv.second);
	}
}

template <typename T>
EntitySystem<T>::~EntitySystem() {
	for (const auto& kv : this->entities) {
		delete kv.second;
	}
}


#endif