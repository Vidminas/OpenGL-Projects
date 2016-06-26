#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "shader.hpp"
#include "shaderFactory.hpp"

ShaderFactory::ShaderFactory()
{
    //nothing
}

ShaderFactory::~ShaderFactory()
{
    for (unsigned short index (0); index < mShaders.size(); index++)
    {
        glDetachShader (mProgramID, mShaders.at (index).getID() );
        glDeleteShader (mShaders.at (index).getID() );
    }

    mShaders.clear();

    glDeleteProgram (mProgramID);
}

void ShaderFactory::addShader (GLenum shaderType, std::string filePath)
{
    mShaders.push_back (Shader (shaderType, filePath) );
    mShaders.back().read();
    mShaders.back().compile();
}

GLuint ShaderFactory::linkProgram()
{
    mProgramID = glCreateProgram();

    for (unsigned short index (0); index < mShaders.size(); index++)
        glAttachShader (mProgramID, mShaders.at (index).getID() );

    glLinkProgram (mProgramID);

    // Check the program
    GLint result = GL_FALSE;
    int infoLogLength;
    glGetProgramiv (mProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv (mProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        std::vector<char> programErrorMessage (infoLogLength + 1);
        glGetProgramInfoLog (mProgramID, infoLogLength, NULL, &programErrorMessage[0]);
        std::cerr << &programErrorMessage[0] << std::endl;
    }

    return mProgramID;
}
