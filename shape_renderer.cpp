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

#include "shape_renderer.h"

ShapeRenderer::ShapeRenderer(Shader& shader)
{
    
    this->InitVertexData(shader);
}

ShapeRenderer::~ShapeRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}


// Method to render the shape as defined by vertex data initialized in the InitVertexData() method and the given arguments
// -----------------------------------------------------------------------------------------------------------------------
void ShapeRenderer::DrawShape(glm::vec2 position, glm::vec2 size, glm::vec3 color, Shader& shader)
{   
    // Call the Use() method to activate the shader
    shader.Use();

    // Initialze a mat4 for the model matrix
    glm::mat4 model = glm::mat4(1.0f);

    // Translate the model matrix based on the position argument
    model = glm::translate(model, glm::vec3(position, 0.0f));  
    
    // Scale the model matrix based on the size argument
    model = glm::scale(model, glm::vec3(size, 1.0f));

    // Send the model matrix to the vertex shader using the model uniform
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderId, "model"), 1, false, glm::value_ptr(model));
  
    // Send the inputColor to the fragment shader using the inputColor uniform
    glUniform3f(glGetUniformLocation(shader.shaderId, "inputColor"), color.x, color.y, color.z);

    // Activate the VAO
    glBindVertexArray(this->VAO);

    // Draw the shape
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Deactivate the VAO
    glBindVertexArray(0);
}


// Method to initialize the vertex data for shape rendering
// --------------------------------------------------------
// * Activates the VAO and VBO, configures the VAB
// -----------------------------------------------
void ShapeRenderer::InitVertexData(Shader& shader)
{
    // Variable for VBO
    unsigned int VBO;

    // Position vertices for a square
    float verticesArray[] =
    {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    // Create a Vertex Array Object (VAO) - (Container for Position, Normals, and Texture Coordinate Data)
    glGenVertexArrays(1, &this->VAO);

    // Create VBO - (Buffer for Vertex Data)
    glGenBuffers(1, &VBO);

    // Activate the Vertex data VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send the vertex data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray), verticesArray, GL_STATIC_DRAW);

    // Activate the VAO
    glBindVertexArray(this->VAO);

    // Specify the starting position of the coordinate values in the buffer
    glEnableVertexAttribArray(0);

    // Create the Vertex Attribute Pointer for the position coordinates
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
