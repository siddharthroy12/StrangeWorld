#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <map>
#include <iostream>

#include "../Utils/Id.hpp"

template<typename T>
class System {
	private:
		std::map<Id, T*> entities;
	public:
		void insert();
		void remove(Id id);
		T* get(Id id);

		void for_each(void (*func)(T *entity));
};

template <typename T>
void System<T>::insert() {
	Id id = generateId();
	this->entities[id] = new T(id);
}

template <typename T>
void System<T>::remove(Id id) {
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


#endif