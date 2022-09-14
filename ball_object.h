///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The BallObject class represents the ball objects used to break bricks
//  in the game.
//  This class inherits from the GameObject class.
// 
//  The BallObject class adds these additional attributes:
// 
//     * float Radius: Used to process collisions, not to render a circle)
//     * bool isHeld: Whether the ball is being held by the player paddle)
// 
//  The BallObject class adds this additional method:
// 
//     * MoveBall: Calculates new position for the ball. Called from the 
//		 Game class's UpdateGame method.
//
///////////////////////////////////////////////////////////////////////////

#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "player.h"

class BallObject : public GameObject
{

public:

	// Variable for radius
	// NOTE: Not used to draw the ball, but used in collision processing
	float Radius;
	
	// Variable for whether the paddle is holding the ball
	bool isHeld;



	bool isInPlay;



	// Default Constructor
	BallObject();

	// Constructor #2
	BallObject(unsigned int window_width, unsigned int window_height, Player& player);

	// Full Constructor
	BallObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity);

	// Method to initialize the ball object
	void InitBall(unsigned int window_width, unsigned int window_height, Player& player);

	// Method to draw the ball object
	void DrawBall(ShapeRenderer& shape_renderer, Shader& shader);

	// Method to calculate new position and return it via a vec2
	glm::vec2 MoveBall(float dt, unsigned int window_width);
};

#endif