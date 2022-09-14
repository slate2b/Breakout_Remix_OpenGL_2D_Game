///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The Player class represents the player paddle object in the game.
//  This class inherits from the GameObject class.
// 
///////////////////////////////////////////////////////////////////////////

#include "player.h"

Player::Player(unsigned int window_width, unsigned int window_height)
	: GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
{
	// Setting initial size, position, and color in the InitPlayer method
	// NOTE: Velocity managed in the game.cpp ProcessInput method in current implementation
	this->InitPlayer(window_width, window_height);
}

Player::Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
	: GameObject(pos, size, color, velocity)
{
}

Player::~Player()
{
	GameObject::~GameObject();

}

// Method to initizlize the player object
void Player::InitPlayer(unsigned int window_width, unsigned int window_height)
{
	// Setting the player's initial color
	glm::vec3 playerColor = glm::vec3(0.7f, 0.7f, 0.4f);
	this->Color = playerColor;

	// Setting the player's initial size based on window size
	glm::vec2 playerSize = glm::vec2((window_width / 8.0f), window_height / 36.0f);
	this->Size = playerSize;

	// Setting the player's initial position based on window size
	glm::vec2 playerPos = glm::vec2((window_width / 2.0f) - (this->Size.x / 2.0f), window_height - this->Size.y);
	this->Position = playerPos;
}

// Method to draw the player
void Player::DrawPlayer(ShapeRenderer& shape_renderer, Shader& shader)
{
	// Calling the GameObject class's Draw method
	this->DrawObject(shape_renderer, shader);
}