#ifndef GAMEPLAY_RESOURCE_HPP
#define GAMEPLAY_RESOURCE_HPP

#include "Resource.hpp"
#include "raylib.h"
#include <thread>

struct GameplayResource : public Resource {
	Texture2D tileAtlas;
	Texture2D player;
	std::string _name();
	GameplayResource();
	~GameplayResource();
};

#endif