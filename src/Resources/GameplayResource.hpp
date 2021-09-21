#ifndef PLAYER_RESOURCE_HPP
#define PLAYER_RESOURCE_HPP

#include "Resource.hpp"
#include "raylib.h"

struct GameplayResource : public Resource {
	Texture tileAtlas;

	GameplayResource();
	~GameplayResource();

};

#endif