/////////////////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
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
//  -------------------------------------------------------------------------------------
// 
//  This Source.cpp file is responsible for the following:
// 
//     * Configures the glfw window
//     * Creates the glfw window
//     * Creates and initializes the Game object
//     * Runs the primary Game Loop
//     * Manages primary callback methods
//
/////////////////////////////////////////////////////////////////////////////////////


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"

#include <iostream>


// Constants for the screen
const char* const WINDOW_TITLE = "Breakout Remix - slate2b";
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Declaring and Initializing the GLFW window 
GLFWwindow* gameWindow = nullptr;

// Call game constructor to create the game object
Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

// Forward Method Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
bool InitializeWindow(int argc, char* argv[], GLFWwindow** window);


//-------------------//
//                   //
//  The Main Method  //
//                   //
//-------------------//

int main(int argc, char* argv[])
{

    // Call the InitializeWindow method defined below the main method
    if (!InitializeWindow(argc, argv, &gameWindow))
    {
        return -1;
    }

    // Call the Game::InitGame method to initialize the game
    game.InitGame();

    // Create and initialize Delta Time Variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    //-----------------//
    //                 //
    //  The Game Loop  //
    //                 //
    //-----------------//

    while (!glfwWindowShouldClose(gameWindow))
    {
        // Calculate Delta Time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // Set the color for glClear
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Process User Input
        // ------------------
        game.ProcessInput(deltaTime);

        // Update the Game
        // ---------------
        game.UpdateGame(deltaTime);

        // Render the Frame
        // ----------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set the clear color
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the background
        game.RenderGame();  // Call the game's render method to render all drawable game elements

        // Swap the front and back buffers to update displayed image for current frame
        glfwSwapBuffers(gameWindow);
    }

    // Close the GLFW window
    glfwTerminate();

	// End the program
	return 0;
}


// Callback Method for handling window resize activity
// ---------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// Callback Method for handling keyboard activity
// ----------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // If the user presses the Escape Key, set glfwWindowShouldClose to true
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // Check standard keys
    if (key >= 0 && key < 1024)
    {
        // If the user presses a key... 
        if (action == GLFW_PRESS)
        {
            // Set the corresponding boolean in the game.keys array to true
            game.keys[key] = true;
        }
        // If the user releases a key...
        else if (action == GLFW_RELEASE)
        {
            // Set the corresponding boolean in the game.keys array to false
            game.keys[key] = false;
        }
    }
}


// Method which initializes the GLFW window
// ----------------------------------------
bool InitializeWindow(int argc, char* argv[], GLFWwindow** window)
{
    // Initialize GLFW to manage window functions
    if (!glfwInit())
    {
        std::cout << "Error: GLFW Initialization" << std::endl;
        glfwTerminate();
        return false;
    }

    // Configure the GLFW window
    // -------------------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    // Create the GLFW window
    *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

    // Check to make sure the window was created
    if (*window == nullptr)
    {
        std::cout << "Error: Window Creation" << std::endl;
        glfwTerminate();
        return false;
    }

    // Set current context for OpenGL to the window we just created
    glfwMakeContextCurrent(*window);

    // Initialize GLAD to manage function pointers for OpenGL 
    // ------------------------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Error: GLAD Initialization" << std::endl;
        return -1;
    }

    // Set GLFW callback functions
    glfwSetKeyCallback(*window, key_callback);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

    // Configure the coordinates for the render window
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    return true;
}