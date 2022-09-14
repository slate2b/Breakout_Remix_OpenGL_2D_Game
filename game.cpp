///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The Game class is responsible for the following:
// 
//     * Initializing all the primary game elements
//     * Processes user input (keyboard)
//	   * Processes collisions between game elements
//     * Manages the updates for all game elements
//     * Manages rendering for all game elements
//     * Resets the game when the ball falls below the bottom of the screen
//
///////////////////////////////////////////////////////////////////////////

#include "game.h"

#include <iostream>

////////////////////////////////////////
// 
// Pointers for fundamental game objects
//
////////////////////////////////////////

Shader* shader;
ShapeRenderer* shapeRenderer;
Player* player;

///////////////
//
// Constructors
//
///////////////

Game::Game(unsigned int window_width, unsigned int window_height)
{
	this->windowWidth = window_width;
	this->windowHeight = window_height;
}

Game::~Game()
{
	delete shader;
	delete shapeRenderer;
	delete player;
}

/////////////////////
//
// Basic Game Methods
//
/////////////////////

// Method to initialize the elements which make up the game
// --------------------------------------------------------
void Game::InitGame()
{
    // Initialize ball in play timer
    // NOTE: Used to manage ball object release events
    ballInPlayTimer = 0;

	// Calling the Shader constructor for the game's shader pointer (declared at top of game.cpp file)
	shader = new Shader();

	// Tell the GPU to use this shader
	shader->Use();

	// Initialze a mat4 for the game's projection matrix
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->windowWidth),
		static_cast<float>(this->windowHeight), 0.0f, -1.0f, 1.0f);

	// Send the projection matrix to the vertex shader using the projection uniform
	glUniformMatrix4fv(glGetUniformLocation(shader->shaderId, "projection"), 1, false, glm::value_ptr(projection));

	// Calling the ShapeRenderer constructor for the game's shapeRenderer pointer (declared at top of game.cpp file)
	shapeRenderer = new ShapeRenderer(*shader);

	// Calling the Player constructor for the game's player pointer (declared at top of game.cpp file)
	player = new Player(windowWidth, windowHeight);

    // Number of ball objects available per game
    // NOTE: When all ball object have gone below the bottom of the screen, the game resets
    unsigned int numBallObjects = 5;

    // Create the number of BallObjects indicated in the numBallObjects variable
    for (unsigned int i = 0; i < numBallObjects; ++i)
    {
        // Create a ball object
        BallObject b;
        // Call the InitBall method for the new ball object
        b.InitBall(windowWidth, windowHeight, *player);
        // Add the ball object to the ballObjects std::vector container
        this->ballObjects.push_back(b);
    }

	// Creating a GameLevel object
	GameLevel levelOne; 

	// Calling the GameLevel Load method to load level data from file
	// NOTE: Sending (windowHeight / 2) so that the bricks fill the top third of the window
	levelOne.Load("level_one.lvl", windowWidth, windowHeight / 3);
	
	// Add the loaded level to the Game's levels std::vector container
	this->levels.push_back(levelOne);
	
	// Setting the initial level for the game
	this->currentLevel = 0;
}


// Method to process user input
// ----------------------------
void Game::ProcessInput(float dt)
{
	// Setting variable for playerVelocity
	float playerVelocity = 500.0f * dt;

	// If the user presses the A key...
	if (this->keys[GLFW_KEY_A])
	{
		// As long as the player isn't already up against the left side of the screen...
		if (player->Position.x >= 0.0f)
		{
			// Move the player to the left
			player->Position.x -= playerVelocity;

            // Loop through the all the ball_objects 
            for (BallObject& ball_object : this->ballObjects)
            {
                // If ball object is NOT destroyed...
                if (!ball_object.isDestroyed)
                {
                    // If the player paddle is holding the ball...
                    if (ball_object.isHeld)
                    {
                        // Make sure the ball stays with the player paddle
                        ball_object.Position.x -= playerVelocity;
                    }
                }
            }
		}
	}

	// If the user presses the D key...
	if (this->keys[GLFW_KEY_D])
	{
		// As long as the player isn't already up against the right side of the screen...
		if (player->Position.x <= this->windowWidth - player->Size.x)
		{
			// Move the player to the right
			player->Position.x += playerVelocity;

            // Loop through all the ball objects
            for (BallObject& ball_object : this->ballObjects)
            {
                // If ball object is NOT destroyed...
                if (!ball_object.isDestroyed)
                {
                    // If the player paddle is holding the ball...
                    if (ball_object.isHeld)
                    {
                        // Make sure the ball stays with the player paddle
                        ball_object.Position.x += playerVelocity;
                    }
                }
            }
    	}
	}

    // If the user presses the Space key...
    if (this->keys[GLFW_KEY_SPACE])
    {
        
        // Check the ball in play timer to help manage ball release events
        if (ballInPlayTimer >= 240)
        {
            // Variable to track whether paddle is holding a ball object
            bool isHolding = false;

            // ----------------------
            // Release a ball object?
            // ----------------------
            
            // Loop through all the ball objects
            for (BallObject& ball_object : this->ballObjects)
            {
                // If ball object is NOT destroyed...
                if (!ball_object.isDestroyed)
                {
                    // If ball object is held...
                    if (ball_object.isHeld)
                    {
                        // Update isHeld to false to release the ball object
                        ball_object.isHeld = false;

                        // Update the ball object's position so it releases from the proper location on the screen
                        glm::vec2 ballPos = player->Position + glm::vec2((player->Size.x / 2.0f) - (ball_object.Size.x / 2.0f), -ball_object.Size.y);
                        ball_object.Position = ballPos;

                        // Reset ballInPlayTimer
                        ballInPlayTimer = 0;

                        // Stop processing input for this frame
                        return;
                    }
                }
            }

            // -------------------------------------------------------------------
            // Prepare a ball object to be released (put the ball object in play)?
            // -------------------------------------------------------------------
            
            // If paddle is not already holding a ball object...
            if (!isHolding)
            {
                // Loop through all the ball objects
                for (BallObject& ball_object : this->ballObjects)
                {
                    // If ball object is not in play and not destroyed
                    if (!ball_object.isInPlay && !ball_object.isDestroyed)
                    {
                        // Place ball object in play
                        ball_object.isInPlay = true;

                        // Update the ball object to isHeld
                        ball_object.isHeld = true;

                        // Update the position of the ball object so it appears correctly on the player paddle
                        glm::vec2 ballPos = player->Position + glm::vec2((player->Size.x / 2.0f) - (ball_object.Size.x / 2.0f), -ball_object.Size.y);
                        ball_object.Position = ballPos;

                        // Reset ballInPlayTimer
                        ballInPlayTimer = 0;

                        // Stop processing input for this frame
                        return;
                    }
                }
            }
        }
    }
}


// Method to update the non-player game elements
// ---------------------------------------------
void Game::UpdateGame(float dt)
{
    // Increment the ball in play timer
    ballInPlayTimer += 1;

    // Managing large timer values to avoid potential overflow issues
    if (ballInPlayTimer > 1000)
    {
        ballInPlayTimer = 240;
    }

    // Loop through all the ball objects
    for (BallObject& ball_object : this->ballObjects)
    {
        // If the ball object is in play, is NOT held, and is NOT destroyed...
        if (ball_object.isInPlay && !ball_object.isHeld && !ball_object.isDestroyed)
        {
            // Move the ball
            ball_object.MoveBall(dt, this->windowWidth);
        }
    }

    // Check for collisions
    this->ProcessCollisions();

    // Loop through all the ball objects
    for (BallObject& ball_object : this->ballObjects)
    {
        // If the ball object has passed below the bottom of the screen...
        if (ball_object.Position.y >= this->windowHeight)
        {
            // Update the isDestroyed variable for that ball object to true
            ball_object.isDestroyed = true;
        }
    }

    // Variable to track the number of ball objects which have been destroyed
    //    Variable gets reset to zero each frame because calculations are performed each frame
    unsigned int numBallObjectsDestroyed = 0;

    // Loop through all the ball objects
    for (BallObject& ball_object : this->ballObjects)
    {
        // If a ball object has been destroyed...
        if (ball_object.isDestroyed) {

            // Increment the numBallObjectsDestroyed variable
            numBallObjectsDestroyed += 1;
        }
    }

    // If all five ball objects have been destroyed...
    if (numBallObjectsDestroyed >= 5)
    {
        // Call the ResetLevel method to reset the level
        this->ResetLevel();
        // Call the ResetPlayer method to reset the player paddle and ball
        this->ResetPlayer();
    }
}


// Method to render the game
// -------------------------
void Game::RenderGame()
{
    // Draw (the bricks for) the current level
    this->levels[this->currentLevel].DrawLevel(*shapeRenderer, *shader);

    // Draw the player
    player->DrawPlayer(*shapeRenderer, *shader);

    // Loop through all the ball objects
    for (BallObject& ball_object : this->ballObjects)
    {
        // If the ball object is in play and is NOT destroyed
        if (ball_object.isInPlay && !ball_object.isDestroyed)
        {
            // Draw the ball object
            ball_object.DrawBall(*shapeRenderer, *shader);
        }
    }
}


// Method to reset the current level
// NOTE: Current implementation is a single level, but could be expanded to include additional levels
// --------------------------------------------------------------------------------------------------
void Game::ResetLevel()
{
	// If the currentLevel is the first level in the levels std::vector
    if (this->currentLevel == 0)
    {
        // Call the Load method to load the first level (Resets the level)
        this->levels[0].Load("level_one.lvl", windowWidth, windowHeight / 3);

        // Clear the ballObjects std::vector container
        this->ballObjects.clear();

        // Create new ball objects and refill the ballObjects std::vector container
        // ------------------------------------------------------------------------
        // Number of ball objects available per game
        // NOTE: When all ball object have gone below the bottom of the screen, the game resets
        unsigned int numBallObjects = 5;

        // Create the number of BallObjects indicated in the numBallObjects variable
        for (unsigned int i = 0; i < numBallObjects; ++i)
        {
            // Create a ball object
            BallObject b;
            // Call the InitBall method for the new ball object
            b.InitBall(windowWidth, windowHeight, *player);
            // Add the ball object to the ballObjects std::vector container
            this->ballObjects.push_back(b);
        }
    }
}


// Method to reset the player paddle and the ball
// ----------------------------------------------
void Game::ResetPlayer()
{
	// Reset the player to its initial state
	player->InitPlayer(windowWidth, windowHeight);

    // Loop through all the ball objects
    for (BallObject& ball_object : this->ballObjects)
    {
        // Call the InitBall method to reset ball object to its original state
        ball_object.InitBall(windowWidth, windowHeight, *player);
    }
}


/////////////////////////////////////
// 
// Collision detection and management
// 
/////////////////////////////////////


// Variables for collisions
bool DetectBoxCollision(GameObject& one, GameObject& two);
Collision DetectCircleCollision(BallObject& one, GameObject& two);
Direction VectorDirection(glm::vec2 closest);


// Primary method used to detect and manage collisions
// ---------------------------------------------------
void Game::ProcessCollisions()
{
    // Check collisions between ball and bricks
    // ----------------------------------------

    // Check each ball object
    for (BallObject& ball_object : this->ballObjects)
    {
        // If the current ball is in play and is not destroyed...
        if (ball_object.isInPlay && !ball_object.isDestroyed)
        {
            // Check each brick object
            for (BrickObject& brick_object : this->levels[this->currentLevel].bricks)
            {
                // If the current brick is not destroyed...
                if (!brick_object.isDestroyed)
                {
                    // Create a Collision variable to hold the collision information
                    // Then calling the CheckCollision method which returns a Collision object
                    Collision collision = DetectCircleCollision(ball_object, brick_object);

                    // If the ball collided with the current brick...
                    if (std::get<0>(collision))
                    {
                        // Destroy the brick
                        brick_object.isDestroyed = true;

                        // Calculate the new position and velocity for the ball
                        // ----------------------------------------------------

                        // Creating a Direction variable to hold the collision direction
                        Direction direction = std::get<1>(collision);

                        // Creating a vec2 variable to hold difference vector for the collision
                        glm::vec2 diff_vector = std::get<2>(collision);

                        // If a horizontal collision...
                        if (direction == LEFT || direction == RIGHT)
                        {
                            // Reverse the horizontal velocity
                            ball_object.Velocity.x = -ball_object.Velocity.x;

                            // Creating a variable to track how far into the brick the ball penetrated
                            float penetration = (ball_object.Radius) - std::abs(diff_vector.x);

                            // If the ball was traveling left...
                            if (direction == LEFT)
                            {
                                // Shift the ball to where the right edge of the brick was
                                ball_object.Position.x += penetration;
                            }
                            // If the ball was traveling right...
                            else
                            {
                                // Shift the ball to where the left edge of the brick was
                                ball_object.Position.x -= penetration;
                            }
                        }
                        // If a vertical collision...
                        else
                        {
                            // Reverse the vertical velocity
                            ball_object.Velocity.y = -ball_object.Velocity.y;

                            // Creating a variable to track how far into the brick the ball penetrated
                            float penetration = (ball_object.Radius) - std::abs(diff_vector.y);

                            // If the ball was traveling up...
                            if (direction == UP)
                            {
                                // Shift the ball to where the bottom edge of the brick was
                                ball_object.Position.y += penetration;
                            }
                            // If the ball was traveling down...
                            else
                            {
                                // Shift the ball to where the top edge of the brick was
                                ball_object.Position.y -= penetration;
                            }
                        }
                    }
                }
            }
        }
    }

    // Check collisions between ball and player paddle
    // NOTE: Only checks collisions for ball objects that are not held
    // ---------------------------------------------------------------

    // Check each ball object
    for (BallObject& ball_object : this->ballObjects)
    {
        // If the current ball is in play and is not destroyed...
        if (ball_object.isInPlay && !ball_object.isDestroyed)
        {
            // Collision variable to hold the result of the collision
            Collision result = DetectCircleCollision(ball_object, *player);
            
            // If the player paddle is not holding the ball and collision is true
            if (!ball_object.isHeld && std::get<0>(result))
            {
                // Variables used to determine difference between point of impact and the center of the paddle
                float paddleCenter = player->Position.x + player->Size.x / 2.0f;
                float diffDistance = (ball_object.Position.x + ball_object.Radius) - paddleCenter;
                float diffPercentage = diffDistance / (player->Size.x / 2.0f);

                // Variables used to determine amount of change in velocity
                float initialBallVelocityX = 100.0f;
                float strength = 2.0f;
                glm::vec2 oldVelocity = ball_object.Velocity;

                // Update the ball's velocity based on the point of impact on the paddle and the amount of change
                ball_object.Velocity.x = initialBallVelocityX * diffPercentage * strength;

                // Normalize the vector to keep new speed consistent across both x and y axes
                ball_object.Velocity = glm::normalize(ball_object.Velocity) * glm::length(oldVelocity);

                // Adjust vertical velocity to compensate for sticky paddle effect
                ball_object.Velocity.y = -1.0f * abs(ball_object.Velocity.y);
            }
        }
    }
}


// Method to perform collision detection when a ball collides with a box: Returns Collosion object
// aka: AABB - Circle collision
// -----------------------------------------------------------------------------------------------
Collision DetectCircleCollision(BallObject& one, GameObject& two) 
{
    // Variable to hold the center point of the circle shape (BallObject)
    glm::vec2 center(one.Position + one.Radius);

    // Calculate values for the box shape (GameObject: Brick or Player Paddle)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);

    // ----------------------------------------------------------------------------------------
    // Using the point of impact on the surface of the box-shaped object in order to 
    // determine the new movement vector and direction the BallObject will travel after impact.
    // The goal is to determine which surface of the box-shaped GameObject should exert the 
    // influence over the ball's change in direction after impact.
    // ----------------------------------------------------------------------------------------

    // Calculate the vector between center of BallObject and the center of the box-shaped GameObject
    //    This represents which part of the box-shaped game object the ball collided with
    glm::vec2 impactPoint = center - aabb_center;
    // Clamp the impact point vector
    glm::vec2 clamped = glm::clamp(impactPoint, -aabb_half_extents, aabb_half_extents);
    // Calculate the point of the box-shaped GameObject closest to the BallObject by adding the clamped impact point vector to the center
    glm::vec2 closest = aabb_center + clamped;
    // Calculate the final point of impact by calculating the difference between
    //    the center of the BallObject and the closest point on the box-shaped GameObject
    impactPoint = closest - center;

    // If the length of the impact vector is less than the radius of the BallObject...
    if (glm::length(impactPoint) < one.Radius)
    {
        // Return collision true, call the VectorDirection method to calculate Direction then return it, and also return the difference vector
        return std::make_tuple(true, VectorDirection(impactPoint), impactPoint);
    }
    // If the length of the difference vector is equal to or more than the radius of the BallObject...
    else
        // Return collision false, Direction UP, and difference vector of zero
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}


// Method to calculate a compass direction based on the point of impact
//    The goal is to determine which surface of the box-shaped GameObject should exert the primary
//    influence over the ball's change in direction after impact
// -----------------------------------------------------------------------------------------------
Direction VectorDirection(glm::vec2 impact_point)
{
    // Creating vec2s for the four compass directions
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// Up
        glm::vec2(1.0f, 0.0f),	// Right
        glm::vec2(0.0f, -1.0f),	// Down
        glm::vec2(-1.0f, 0.0f)	// Left
    };

    // Variables used in calculations below to identify the compass direction which most closely matches the impact point vector
    // -------------------------------------------------------------------------------------------------------------------------
    // Variable to store the highest dot product so far. Initializing to zero.
    float highestValue = 0.0f;
    // Variable to store the compass direction which most closely matches the impact point. Initializing to -1.
    unsigned int bestMatch = -1;

    // Loop through the four compass directions
    for (unsigned int i = 0; i < 4; i++)
    {
        // Normalize the impact point vector argument, then calculate the dot product between the normalized vector and the compass direction
        float dotProduct = glm::dot(glm::normalize(impact_point), compass[i]);

        // If the dot product is greater than the highest value calculated so far...
        if (dotProduct > highestValue)
        {
            // Assign the value of highestValue with the dot product calculated through this iteration of the loop
            highestValue = dotProduct;
            // Assign the value of bestMatch with the compass direction from this iteration of the loop
            bestMatch = i;
        }
    }

    // After comparing all the compass directions to the impact point vector, return the closest compass direction
    return (Direction)bestMatch;
}