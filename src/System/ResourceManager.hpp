#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include "../Resources/Resource.hpp"

namespace ResourceManager {
	bool resourceExist(std::string name);
}

#endif