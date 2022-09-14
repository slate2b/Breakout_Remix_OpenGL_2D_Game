///////////////////////////////////////////////////////////////////////////
//
//  BREAKOUT REMIX 
//  --------------
//  by slate2b
//
//  The Shader class handles the shaders used for the game.
// 
//  In the spirit of the Atari 2600, this class uses basic primitives
//  without the use of textures or any post-processing effects.
// 
//  The Shader class is responsible for the following:
// 
//     * Storing vertex and fragment shader source code
//	   * Creating the vertex shader
//     * Compiling the vertex shader
//	   * Creating the fragment shader
//     * Compiling the fragment shader
//	   * Creating the shader program 
//     * Compiling the shader program
//     * Linking the vertex and fragment shaders to the shader program
//	   * Activating the shader program to be used in the game
//
///////////////////////////////////////////////////////////////////////////

#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{

public:

	// Variable to store the ID for the Shader Program
	unsigned int shaderId;

	// Constructor
	Shader();

	// Destructor
	~Shader();

	// Method which activates the current shader
	Shader& Use();

	// Method to initialize the shader program for the game
	unsigned int InitShader();

};




#endif