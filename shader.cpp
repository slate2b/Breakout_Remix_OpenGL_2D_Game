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

#include "shader.h"

Shader::Shader()
{
    shaderId = InitShader();
}

Shader::~Shader()
{
	glDeleteProgram(shaderId);
}

// Method which activates the current shader
Shader& Shader::Use()
{
	glUseProgram(shaderId);
	return *this;
}

// Method to initialize the shader program for the game
unsigned int Shader::InitShader()
{
    // Vertex Shader Program Source Code (GLSL)
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec2 vertexPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * model * vec4(vertexPos.x, vertexPos.y, 0.0, 1.0);\n"
        "}\n\0";

    // Fragment Shader Program Source Code (GLSL)
    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "uniform vec3 inputColor;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(inputColor, 1.0);\n"
        "}\n\0";

    // Error-checking variables for shader compilation errors
    int success;
    char infoLog[512];

    // The Vertex Shader
    // -----------------
    // Create the Vertex Shader
    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    // Retrieve the source code for the Vertex Shader
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
    // Compile the Vertex Shader
    glCompileShader(vertexShaderId);
    // Check for compilation errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // The Fragment Shader
    // -------------------
    // Create the Fragment Shader
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    // Retrieve the source code for the Fragment Shader
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    // Compile the Fragment Shader
    glCompileShader(fragmentShaderId);
    // Check for compilation errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // The Shader Program
    // ------------------
    // Create the Shader Program
    unsigned int programId = glCreateProgram();
    // Attach the Compiled Vertex Shader to the Shader Program
    glAttachShader(programId, vertexShaderId);
    // Attach the Compiled Fragment Shader to the Shader Program
    glAttachShader(programId, fragmentShaderId);
    // Check for compilation errors
    glGetShaderiv(programId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link the Shader Program
    glLinkProgram(programId);

    // Delete the vertex and fragment shaders. Since they're linked we don't need them anymore.
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}
