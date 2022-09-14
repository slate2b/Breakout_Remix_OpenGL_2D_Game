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

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shape_renderer.h"

class GameObject
{

public:

	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec2 Velocity;
	glm::vec3 Color;
	bool isBreakable;
	bool isDestroyed;

	// Default Constructor
	GameObject();
	
	// Constructor # 2 
	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity);

	// Constructor # 3 (for bricks)
	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, bool is_destroyed);

	// Destructor
	~GameObject();

	// Method to draw a game object (virtual)
	virtual void DrawObject(ShapeRenderer& shape_renderer, Shader& shader);

};







#endif