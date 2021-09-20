#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include "../Resources/Resource.hpp"

namespace ResourceManager {
	extern std::unordered_map<std::string, std::shared_ptr<Resource>>  _resources;

	extern bool resourceExist(std::string name);
}

#endif