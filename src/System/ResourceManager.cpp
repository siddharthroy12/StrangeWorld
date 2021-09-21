#include <unordered_map>
#include <memory>
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
		if (!resourceLoaded(resource->_name)) {
			_resources[resource->_name] = resource;
		}
	}

	void unloadResources() {
		for (const auto& kv : _resources) {
			_resources.erase(kv.first);
		}
	}
}