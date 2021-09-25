#ifndef ID_HPP
#define ID_HPP

#include <string>
#include "Random.hpp"

typedef int Id;

static Id generateId() {
	static int prevId = -1;

	prevId++;
	return prevId;
}

static bool idMatch(Id id1, Id id2) {

	return id1 == id2;
}

#endif