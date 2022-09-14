///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The ShapeRenderer class provides an interface between the game, the
//  shaders, and the GPU in order to properly render the game elements to
//  the screen.  
// 
//  In the spirit of the Atari 2600, this class uses basic primitives
//  without the use of textures.
// 
//  The ShapeRenderer class is responsible for the following:
// 
//     * Initializing vertex data for the objects to be rendered
// 
//			* Using vertices for a simple square primitive for all 
//			  objects rendered in this game
//	  
//     * Activates the VAO
//	   * Activates the VBO
//     * Configures the VAB
//	   * Model transformations for the rendered game objects
//	   * Sending game data to the shaders via uniforms
//	   * Drawing the rendered game object via glDrawArrays(GL_TRIANGLES)
//
///////////////////////////////////////////////////////////////////////////

#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H

#include <iostream>

#include "shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ShapeRenderer
{

public:

	// Constructor
	ShapeRenderer(Shader& shader);

	// Destructor
	~ShapeRenderer();

	// Method to render the shape as defined by parameters and vertex data initialized in the InitVertexData() method
	void DrawShape(glm::vec2 position, glm::vec2 size, glm::vec3 color, Shader& shader);

private:

	unsigned int VAO;

	// Method to initialize the vertex data for shape rendering
	void InitVertexData(Shader& shader);

};

#endif