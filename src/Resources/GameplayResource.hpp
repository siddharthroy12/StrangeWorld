#ifndef GAMEPLAY_RESOURCE_HPP
#define GAMEPLAY_RESOURCE_HPP

#include "Resource.hpp"
#include "raylib.h"

struct GameplayResource : public Resource {
	Texture tileAtlas;
	std::string _name();
	GameplayResource();
	~GameplayResource();
};

#endif