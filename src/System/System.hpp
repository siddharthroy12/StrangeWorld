#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <unordered_map>

#include "../Utils/Id.hpp"

template<typename T>
class System {
	private:
		std::unordered_map<Id, T*> entities;
	public:
		Id create(T* entity);
		void remove(Id id);
		T* get(Id id);

		void for_each(void (*func)(T *entity));
		~System();
};

template <typename T>
Id System<T>::create(T* entity) {
	Id id = generateId();
	entity->_id = id;
	this->entities[id] = entity;
	return id;
}

template <typename T>
void System<T>::remove(Id id) {
	delete this->entities[id];
	this->entities.erase(id);
}

template <typename T>
T* System<T>::get(Id id) {
	return this->entities[id];
}

template <typename T>
void System<T>::for_each(void (*func)(T *entity)) {
	for (const auto& kv : this->entities) {
		func(kv.second);
	}
}

template <typename T>
System<T>::~System() {
	for (const auto& kv : this->entities) {
		delete kv.second;
	}
}


#endif