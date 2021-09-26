#include "Player.hpp"
#include "../Utils/Assets.hpp"
#include "raymath.h"
#include "../Sizes/TileSize.hpp"
#include "../World/World.hpp"

Player::Player() {
	this->type = "Player";

	this->sprite = LoadTexture(ASSETS_PATH"player.png");
	position.x = 10;
	position.y = BLOCK_TILE_SIZE * 850;

	velocity.x = 0;
	velocity.y = 0;

	this->hitbox = (Rectangle) {
		.x = position.x - (sprite.width/2),
		.y = position.y - (sprite.height/2),
		.width = (float)sprite.width,
		.height = (float)sprite.height
	};
}

void Player::render() {
	DrawTexturePro(
		this->sprite,
		(Rectangle) {
			0.0f,
			0.0f,
			(float)this->sprite.width,
			(float)this->sprite.height
		},
		(Rectangle) {
			this->position.x,
			this->position.y,
			(float)this->sprite.width,
			(float)this->sprite.height
		},
		(Vector2){ (float)sprite.width/2, (float)sprite.height/2 },
		0.0f,
		WHITE
	);

	DrawRectangleLinesEx(hitbox, 1, BLACK);
}

void Player::update() {
	if (IsKeyDown(KEY_RIGHT)) {
		this->velocity.x = this->speed;
	}

	if (IsKeyDown(KEY_LEFT)) {
		this->velocity.x = -this->speed;
	}

	if (IsKeyDown(KEY_UP)) {
		this->velocity.y = -this->speed;
	}

	if (IsKeyDown(KEY_DOWN)) {
		this->velocity.y = this->speed;
	}

	position = World::moveAndCollide(position, velocity, hitbox);

	hitbox.x = position.x - (sprite.width/2);
	hitbox.y = position.y - (sprite.height/2);

	velocity.x = Lerp(velocity.x, 0.0f, 0.1);
	velocity.y = Lerp(velocity.y, 0.0f, 0.1);
}

Vector2 Player::getPositon() {
	return this->position;
}

Player::~Player() {
	UnloadTexture(this->sprite);
}