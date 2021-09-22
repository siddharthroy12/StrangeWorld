#include <unordered_map>
#include <memory>
#include <iostream>
#include "../Resources/Resource.hpp"

namespace ResourceManager {
	std::unordered_map<std::string, std::shared_ptr<Resource>>  _resources;

	bool resourceLoaded(std::string name) {
		if (_resources.find(name) == _resources.end()) {
			return false;
		} else {
			return true;
		}
	}

	std::shared_ptr<Resource> getResource(std::string name) {
		return _resources[name];
	}

	void loadResource(std::shared_ptr<Resource> resource) {
		std::cout << "LoadResource: " << resource->_name() << std::endl;
		if (!resourceLoaded(resource->_name())) {
			_resources[resource->_name()] = resource;
		}
	}

	void unloadResources() {
		std::cout << "unloading" << std::endl;
		_resources.clear();
	}
}