#include <unordered_map>
#include <memory>
#include "../Resources/Resource.hpp"

namespace ResourceManager {

	std::unordered_map<std::string, std::shared_ptr<Resource>>  _resources;

	bool loadResource(std::string name, std::shared_ptr<Resource> resource) {
		if (!resourceLoaded(name)) {
			_resources[name] = resource;
		}
	}

	bool resourceLoaded(std::string name) {
		if (_resources.find(name) == _resources.end()) {
			return false;
		} else {
			return true;
		}
	} 
}