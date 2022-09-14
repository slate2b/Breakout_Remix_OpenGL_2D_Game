///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The Game class is responsible for the following:
// 
//     * Initializes all the primary game elements
//     * Processes user input (keyboard)
//	   * Processes collisions between game elements
//     * Manages the updates for all game elements
//     * Manages rendering for all game elements
//     * Resets the game when the ball falls below the bottom of the screen
//
///////////////////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include "shader.h"
#include "shape_renderer.h"
#include "player.h"
#include "brick_object.h"
#include "ball_object.h"
#include "game_level.h"

#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>


// enum used for directions in collision detection
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// typedef used to hold collision information
// ------------------------------------------
//   bool: whether or not a collision
//   Direction: collision direction
//   vec2: difference between the center and closest point of impact
//   ---------------------------------------------------------------
typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

class Game
{

public:

	// Fundamental variables used for the game
	bool keys[1024];
	unsigned int windowWidth;
	unsigned int windowHeight;
	unsigned int currentLevel;

	// Timer to manage ball object release events
	unsigned int ballInPlayTimer;

	// Containers for game levels and ball objects
	std::vector<GameLevel> levels;
	std::vector<BallObject> ballObjects;

	// Constructor
	Game(unsigned int window_width, unsigned int window_height);

	// Destructor
	~Game();

	// Method to initialize the elements which make up the game
	void InitGame();

	// Game Loop Methods
	// -----------------
	// Method to process user input
	void ProcessInput(float dt);
	// Method to update the game
	void UpdateGame(float dt);
	// Method to the game
	void RenderGame();

	// Method to check and manage collisions
	void ProcessCollisions();

	// Reset methods
	// -------------
	// Method to reset the level
	void ResetLevel();
	// Method to reset the player
	void ResetPlayer();

};

#endif