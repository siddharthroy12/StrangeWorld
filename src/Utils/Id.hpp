#ifndef ID_HPP
#define ID_HPP

#include <string>

#include "Random.hpp"

#define ID_SIZE 16

typedef std::string Id;


static Id generateId() {
	char letters[] = {
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};
	Id result;

	for (int i = 0; i < ID_SIZE; i++) {
		result.push_back(letters[randRange(0, 62)]);
	}

	return result;
}

static bool idMatch(Id id1, Id id2) {
	bool result = true;

	for (int i = 0; i < ID_SIZE; i++) {
		if (id1[i] != id2[i]) {
			result = false;
		}
	}

	return result;
}

#endif