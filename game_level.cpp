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

#include "game_level.h"

#include <fstream>
#include <sstream>


// Method to load level data from file based on tilemap concept
// NOTE: level_width and level_height refer to the width and height of the collection of bricks to be broken
void GameLevel::Load(const char* file, unsigned int level_width, unsigned int level_height)
{
    // Using int values (tileType) to determine the color of the bricks
    // ----------------------------------------------------------------
    // 0 = Empty Space (No Brick)
    // 1 = Red
    // 2 = Orange
    // 3 = Orange-Brown
    // 4 = Yellow
    // 5 = Green
    // 6 = Blue
    // ---------------------------------

	// Clear any pre-existing level data
	this->bricks.clear();

    // Variables used to load level data
    // ---------------------------------
    // Creating variable to hold the code which differentiates the different tiles
    unsigned int tileType;
    // Creating a GameLevel object
    GameLevel level;
    // Creating a string to hold a single line of data
    std::string line;
    // Creating a ifstream to read data from file
    std::ifstream fstream(file);
    // Creating a 2D std::vector to hold the data from the file
    std::vector<std::vector<unsigned int>> tileData;

    // Load data from file
    if (fstream)
    {
        // While there are still lines to read in the file
        while (std::getline(fstream, line))
        {
            // Creating a istringstream to read data from the current line of the file
            std::istringstream sstream(line);
            // Creating a std::vector to hold a single row of tile data
            std::vector<unsigned int> row;

            // While there is still tile data to read in the current line
            while (sstream >> tileType)
            {
                // Add the tileType to the current row vector
                row.push_back(tileType);
            }

            // Add the data for the row we just read to the tileData 2D vector 
            tileData.push_back(row);
        }

        // Once finished, as long as the tileData 2D vector is not empty, 
        // call the InitLevel method based on the loaded tileData
        if (tileData.size() > 0)
            this->InitLevel(tileData, level_width, level_height);
    }

}

// Method to render the bricks in the level
void GameLevel::DrawLevel(ShapeRenderer& shape_renderer, Shader& shader)
{
    // Loop through all the bricks (tiles) in the bricks std::vector container
    for (BrickObject& tile : this->bricks)
    {
        // If the brick is NOT destroyed
        if (!tile.isDestroyed)
        {
            // Draw it
            tile.DrawBrick(shape_renderer, shader);
        }
    }
}

// Method to initialize the level by populating the bricks std::vector container which holds all bricks data for the level
// NOTE: level_width and level_height refer to the width and height of the collection of bricks to be broken
void GameLevel::InitLevel(std::vector<std::vector<unsigned int>> tile_data, unsigned int level_width, unsigned int level_height) 
{
    // Variables for initializing the level
    unsigned int height = tile_data.size();    // Number of rows from the tile data 2D vector
    unsigned int width = tile_data[0].size();  // Number of columns from the tile data 2D vector
    float tile_height = level_height / height; // Tile height is determined by level_height and the number of rows
    float tile_width = level_width / static_cast<float>(width); // tile width is determined by level_width and the number of columns


    // Loop through each row		
    for (unsigned int y = 0; y < height; ++y)
    {
        // Loop through each cell within the row
        for (unsigned int x = 0; x < width; ++x)
        {
            // Variables for the individual bricks 
            glm::vec3 color = glm::vec3(1.0f);   // Initializing to white, but changing below
            glm::vec2 pos(tile_width * x, tile_height * y); // Assigning the position per tile data
            glm::vec2 size(tile_width, tile_height); // Assigning the size based on calculated tile dimensions
            glm::vec2 velocity(0.0f, 0.0f);  // Assigning zero velocity. No moving bricks in the current implementation
            bool is_destroyed = false;  // Initializing to false, but changing below for tile type zero
            
            // Check the tile type for the current cell
            // ----------------------------------------

            // Using destroyed bricks as empty spaces (tileType = 0)
            if (tile_data[y][x] == 0)
            {
                // Setting isDestroyed to true
                //   Using isDestroyed so game will not render or calculate collision for the brick
                //   making it essentially an empty space
                is_destroyed = true; 

                // Calling the BrickObject constructor with isDestroyed set to true,
                //   then adding the brick to the bricks std::vector container
                this->bricks.push_back(BrickObject(pos, size, color, velocity, is_destroyed));
            }
            // For all other bricks, the only differentiator is the color
            else
            {
                // Set is_destroyed to false so we can render and calculate collision for the brick
                is_destroyed = false;

                // Assign the brick's color based on the tile type
                // -----------------------------------------------
                if (tile_data[y][x] == 1)
                    color = glm::vec3(0.7f, 0.3f, 0.2f);
                else if (tile_data[y][x] == 2)
                    color = glm::vec3(0.8f, 0.4f, 0.2f);
                else if (tile_data[y][x] == 3)
                    color = glm::vec3(0.7f, 0.5f, 0.2f);
                else if (tile_data[y][x] == 4)
                    color = glm::vec3(0.7f, 0.7f, 0.2f);
                else if (tile_data[y][x] == 5)
                    color = glm::vec3(0.2f, 0.7f, 0.2f);
                else if (tile_data[y][x] == 6)
                    color = glm::vec3(0.2f, 0.3f, 0.7f);

                // Calling the BrickObject constructor with isDestroyed set to false,
                //   then adding the brick to the bricks std::vector container
                this->bricks.push_back(BrickObject(pos, size, color, velocity, is_destroyed));
            }
        }
    }
}