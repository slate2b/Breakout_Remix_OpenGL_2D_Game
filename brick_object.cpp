///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The BrickObject class represents the brick objects in the game.
//  This class inherits from the GameObject class.
// 
///////////////////////////////////////////////////////////////////////////

#include "brick_object.h"

BrickObject::BrickObject(unsigned int window_width, unsigned int window_height)
	: GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
{
	// Setting initial size, position, and color in the InitBrick method
	this->InitBrick(window_width, window_height);

}

BrickObject::BrickObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, bool is_destroyed)
	: GameObject(pos, size, color, velocity, is_destroyed)
{
}

BrickObject::~BrickObject()
{
	GameObject::~GameObject();
}

// Method to initizlize the brick object
void BrickObject::InitBrick(unsigned int window_width, unsigned int window_height)
{
	// Setting the brick's initial color
	glm::vec3 brickColor = glm::vec3(0.2f, 0.6f, 0.2f);
	this->Color = brickColor;

	// Setting the brick's initial size based on window size
	glm::vec2 brickSize = glm::vec2((window_width / 10.0f), window_height / 36.0f);
	this->Size = brickSize;

	// Setting the brick's initial position based on window size
	glm::vec2 brickPos = glm::vec2((window_width / 2.0f) - (this->Size.x / 2.0f), 0.0f);
	this->Position = brickPos;
}

// Method to draw the brick
void BrickObject::DrawBrick(ShapeRenderer& shape_renderer, Shader& shader)
{
	// Calling the GameObject class's Draw method
	this->DrawObject(shape_renderer, shader);
}
