#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "shader.hpp"

Shader::Shader (GLenum shaderType, std::string filePath)
    : mShaderCode ("")
    , mFilePath (filePath)
{
    mShaderID = glCreateShader (shaderType);
}

bool Shader::read()
{
    std::ifstream shaderFile (mFilePath, std::ios::in);

    if (shaderFile.is_open() )
    {
        std::string line;

        while (shaderFile.good() && getline (shaderFile, line) )
            mShaderCode.append (line + '\n');

        shaderFile.close();
        return true;
    }

    else
    {
        std::cerr << "Could not open " << mFilePath << ". Check directories." << std::endl;
        return false;
    }
}

void Shader::compile()
{
    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile Shader
    std::cout << "Compiling shader: " << mFilePath << std::endl;
    char const* sourcePointer = mShaderCode.c_str();
    glShaderSource (mShaderID, 1, &sourcePointer, NULL);
    glCompileShader (mShaderID);

    // Check Shader
    glGetShaderiv (mShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv (mShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        std::vector<char> shaderErrorMessage (infoLogLength + 1);
        glGetShaderInfoLog (mShaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        std::cerr << &shaderErrorMessage[0] << std::endl;
    }
}

const GLuint Shader::getID() const
{
    return mShaderID;
}
