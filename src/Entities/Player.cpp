#include "Player.hpp"
#include "../Utils/Assets.hpp"

Player::Player() {
	this->type = "Player";

	this->sprite = LoadTexture(ASSETS_PATH"player.png");
	position.x = 10;
	position.y = 10;
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
}

void Player::update() {
	if (IsKeyDown(KEY_RIGHT)) {
		this->position.x += this->speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_LEFT)) {
		this->position.x -= this->speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_UP)) {
		this->position.y -= this->speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_DOWN)) {
		this->position.y += this->speed * GetFrameTime();
	}
}

Vector2 Player::getPositon() {
	return this->position;
}

Player::~Player() {
	UnloadTexture(this->sprite);
}