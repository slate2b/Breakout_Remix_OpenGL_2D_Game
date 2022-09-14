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

#include "ball_object.h"

BallObject::BallObject()
	: GameObject() {}

BallObject::BallObject(unsigned int window_width, unsigned int window_height, Player& player)
    : GameObject(glm::vec2(1.0f), glm::vec2(1.0f), glm::vec3(1.0f), glm::vec2(1.0f))
{
    // Setting initial size, position, and color in the InitBall method
    this->InitBall(window_width, window_height, player);
}

BallObject::BallObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity)
	: GameObject(position, size, glm::vec3(0.6f, 0.2f, 0.1f), velocity) {}


// Method to initialize the ball object
void BallObject::InitBall(unsigned int window_width, unsigned int window_height, Player& player)
{
    // Setting the ball's initial color
    glm::vec3 ballColor = glm::vec3(0.7f, 0.7f, 0.4f);
    this->Color = ballColor;

    // Setting the ball's initial size based on window size
    glm::vec2 ballSize = glm::vec2((window_width / 48.0f), window_height / 36.0f);
    this->Size = ballSize;

    // Setting the ball's initial position based on window size
    glm::vec2 ballPos = player.Position + glm::vec2((player.Size.x / 2.0f) - (ballSize.x / 2.0f), -ballSize.y);
    this->Position = ballPos;

    // Setting the ball's initial xy velocity
    glm::vec2 ballVelocity = glm::vec2(100.0f, -350.0f);
    this->Velocity = ballVelocity;

    // Setting the isHeld bool to true (player paddle is holding the ball)
    this->isHeld = false;




    // Setting the isInPlay bool to false 
    this->isInPlay = false;




    // Setting the radius based on ballSize 
    this->Radius = (ballSize.x / 2.0f);  // using ballSize.x is arbitrary. ballSize.y would have worked just as well.
}

// Method to draw the ball object
void BallObject::DrawBall(ShapeRenderer& shape_renderer, Shader& shader)
{
    // Calling the GameObject class's Draw method
    this->DrawObject(shape_renderer, shader);
}

// Method to calculate new position and return it via a vec2
glm::vec2 BallObject::MoveBall(float dt, unsigned int window_width)
{
    // If the ball is:
    //    In play &&
    //    NOT currently being held by the player paddle &&
    //    NOT destroyed...
    if (this->isInPlay && !this->isHeld && !this->isDestroyed)
    {
        // Move the ball based on the ball's current xy velocity
        this->Position += this->Velocity * dt;

        // Check if the updated position places the ball outside the window bounds.
        //   If it would be out of bounds, reverse the velocity and place the ball in bounds.
        //   --------------------------------------------------------------------------------
        // If past the left side of the screen...
        if (this->Position.x <= 0.0f)
        {
            // Reverse the x velocity of the ball
            this->Velocity.x = -this->Velocity.x;
            // Update the x position of the ball to the left side of the screen
            this->Position.x = 0.0f;
        }
        // If past the right side of the screen...
        else if (this->Position.x + this->Size.x >= window_width)
        {
            // Reverse the x velocity of the ball
            this->Velocity.x = -this->Velocity.x;
            // Update the x position of the ball to the right side of the screen
            this->Position.x = window_width - this->Size.x;
        }
        // If past the top of the screen...
        if (this->Position.y <= 0.0f)
        {
            // Reverse the y velocity of the ball
            this->Velocity.y = -this->Velocity.y;
            // Update the y position of the ball to the top of the screen
            this->Position.y = 0.0f;
        }
    }

    // Return the ball's updated position
    return this->Position;
}
