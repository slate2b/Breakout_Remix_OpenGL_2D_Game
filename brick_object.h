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

#ifndef BRICKOBJECT_H
#define BRICKOBJECT_H

#include "game_object.h"

class BrickObject : public GameObject
{

public:

	// Constructor
	BrickObject(unsigned int window_width, unsigned int window_height);

	// Full Constructor
	BrickObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, bool is_destroyed);

	// Destructor
	~BrickObject();

	// Method to initialize brick object
	void InitBrick(unsigned int window_width, unsigned int window_height);

	// Method to draw the brick
	void DrawBrick(ShapeRenderer& shape_renderer, Shader& shader);

};

#endif