# breakout_remix_opengl_2d_game

# BREAKOUT REMIX 
--------------
by slate2b

//  The goal of this project is to create a minimalist version of the classic 
//  Atari 2600 game "Breakout" without relying on libraries like SDL or SFML...
//  with a slight twist.  
// 
//  In this remix version, the player can place up to five balls in play at once 
//  by pressing the Spacebar.  When all the balls have dropped below the bottom
//  of the screen, the game resets.  
// 
//  The design and code for this project, especially the collision detection,
//  were inspired and influenced by the framework outlined in the 2D Game section
//  of the Learn OpenGL site found at: https://learnopengl.com/
// 
//  This project utilzes the following concepts / approaches / tools:
// 
//     * Shader programs written in GLSL to send data to GPU
//     * OpenGL coding via GLAD, GLFW, and GLM
//     * Complex game logic to handle collision processing
//     * Custom classes designed to modularize specialized functionality
//     * Inheritance through a GameObject parent class and multiple child classes
//     * Create custom files based on tilemap concept
//     * Read data from file to build game levels
//     * High Scalability due to ease of designing and adding additional levels
//     * Funcational data access between multiple classes and files
//     * Complex conditional logic
//     * Multi-dimensional data structures
//     * Extensive utilization of loops (for, foreach, and while)
// 
//  -------------------------------------------------------------
// 
//  Index of Key Functions:
// 
//     * Shader source code:                shader.cpp 
//     * Creating, compiling, 
//         linking, activating shaders:     shader.cpp
//     * Initializing Vertex Data:          shape_renderer.cpp
//     * Activating the VAO and VBO:        shape_renderer.cpp
//     * Configure the VAB:                 shape_renderer.cpp
//     * Model transformations:             shape_renderer.cpp
//     * Drawing the game objects:          shape_renderer.cpp
//     * Configures and creates window:     Source.cpp
//     * Creates and initializes game:      Source.cpp
//     * Runs the primary Game Loop:        Source.cpp
//     * Initializing game elements:        game.cpp
//     * Processes user input:              game.cpp
//	   * Processes collisions:              game.cpp
//     * Manages the game updates:          game.cpp
//     * Manages rendering game elements:   game.cpp
//     * Loading the level from file:       game_level.cpp
//     * Storing level/brick data:          game_level.cpp
//	   * Manages level/brick data:          game_level.cpp
//     * Manages level/brick rendering:     game_level.cpp
// 
//  ------------------------------------------------------
// 
//  Game Controls:
// 
//     * Move the player paddle left with the A key
//     * Move the player paddle right with the D key
//     * If there are still ball objects available, place a ball on the paddle 
//       by pressing the Spacebar
//     * If there is a ball on the paddle, hit the ball toward the bricks
//       by pressing the Spacebar
//     * When all 5 balls have been released, the Spacebar no longer affects the game
//
/////////////////////////////////////////////////////////////////////////////////////////
