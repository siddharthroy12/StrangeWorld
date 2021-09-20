#include <unordered_map>
#include <memory>
#include "../Resources/Resource.hpp"

namespace ResourceManager {
	std::unordered_map<std::string, std::shared_ptr<Resource>>  _resources;

	bool resourceExist(std::string name) {
		if (_resources.find(name) == _resources.end()) {
			return false;
		} else {
			return true;
		}
	} 
}