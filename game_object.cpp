///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The GameObject class is the base class for the interactable objects in
//  the game: 
// 
//		* The player paddle
//		* The ball
//		* The bricks
//
///////////////////////////////////////////////////////////////////////////

#include "game_object.h"

GameObject::GameObject()
{
	Position.x = 0.0f;
	Position.y = 0.0f;
	Size.x = 1.0f;
	Size.y = 1.0f;
	Color.x = 1.0f;
	Color.y = 1.0f;
	Color.z = 1.0f;
	Velocity.x = 0.0f;
	Velocity.y = 0.0f;
	isBreakable = true;
	isDestroyed = false;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
{
	Position = pos;
	Size = size;
	Color = color;
	Velocity = velocity;
	isBreakable = true;
	isDestroyed = false;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, bool is_destroyed)
{
	Position = pos;
	Size = size;
	Color = color;
	Velocity = velocity;
	isBreakable = true;
	isDestroyed = is_destroyed;
}

GameObject::~GameObject()
{

}

// Method to draw a game object (virtual)
void GameObject::DrawObject(ShapeRenderer& shape_renderer, Shader& shader)
{
	shape_renderer.DrawShape(this->Position, this->Size, this->Color, shader);
}