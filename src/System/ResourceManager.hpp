#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <memory>
#include "../Resources/Resource.hpp"

namespace ResourceManager {
	bool loadResource(std::string name, std::shared_ptr<Resource> resource);
	bool resourceLoaded(std::string name);
}

#endif