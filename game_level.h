///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The GameLevel class represents the levels in the game.
//  The current implementation only includes a single level, but it could
//  easily be expanded to include additional levels.  Each level is 
//  made up of a particular arrangement of different types of bricks.
// 
//  The GameLevel class is responsible for the following:
// 
//     * Loading the level from file
//     * Storing data for the bricks in the current level
//	   * Drawing the level (the bricks)
//
///////////////////////////////////////////////////////////////////////////

#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "brick_object.h"
#include "shape_renderer.h"


class GameLevel
{

public:

	// vector<BrickObject> container to store brick data for the level
	std::vector<BrickObject> bricks;

	// Default Constructor (not used)
	GameLevel() {};

	// Method to load level data from file based on tilemap concept
	// NOTE: level_width and level_height refer to the width and height of the collection of bricks to be broken
	void Load(const char* file, unsigned int level_width, unsigned int level_height);

	// Method to render the level
	void DrawLevel(ShapeRenderer& shape_renderer, Shader& shader);

private:

	// Method to initialize the level
	// NOTE: level_width and level_height refer to the width and height of the collection of bricks to be broken
	void InitLevel(std::vector<std::vector<unsigned int>> tile_data, unsigned int level_width, unsigned int level_height);
};

#endif