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

#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public GameObject
{

public:


	// Constructor
	Player(unsigned int window_width, unsigned int window_height);

	// Full Constructor
	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity);

	// Destructor
	~Player();

	// Method to initialize player object
	void InitPlayer(unsigned int window_width, unsigned int window_height);

	// Method to draw the player
	void DrawPlayer(ShapeRenderer& shape_renderer, Shader& shader);

};

#endif