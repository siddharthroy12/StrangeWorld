#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "raylib.h"

class Player : public Entity {
	private:
		Texture2D sprite;
		Vector2 position;
		Vector2 velocity;
		Vector2 hitbox;
		int speed = 90;
	public:
		Player();
		void update();
		void render();
		Vector2 getPositon();
		~Player();
};

#endif