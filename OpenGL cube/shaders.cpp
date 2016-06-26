#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

void shadersLog (GLuint object)
{
    if (glIsShader (object) )
    {
        GLint log_length = 0;
        glGetShaderiv (object, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> log (log_length);
        glGetShaderInfoLog (object, log_length, NULL, &log.at (0) );
        std::cout << &log.at (0) << std::endl;
    }

    else if (glIsProgram (object) )
    {
        GLint log_length = 0;
        glGetProgramiv (object, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> log (log_length);
        glGetProgramInfoLog (object, log_length, NULL, &log.at (0) );
        std::cout << &log.at (0) << std::endl;
    }

    else
        std::cerr << "printlog: Not a shader or a program" << std::endl;
}

const GLuint loadShaders (const std::string vertex_file_path, const std::string fragment_file_path)
{
    GLuint VertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream (vertex_file_path.c_str() );

    if (VertexShaderStream.is_open() )
    {
        std::string line;

        while (VertexShaderStream.good() )
        {
            getline (VertexShaderStream, line);
            VertexShaderCode += "\n" + line;
        }

        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream (fragment_file_path.c_str() );

    if (FragmentShaderStream.is_open() )
    {
        std::string line;

        while (FragmentShaderStream.good() )
        {
            getline (FragmentShaderStream, line);
            FragmentShaderCode += "\n" + line;
        }

        FragmentShaderStream.close();
    }

    GLint compileSuccess (GL_FALSE);

    std::cout << "Compiling shader: " << vertex_file_path << std::endl;
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource (VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader (VertexShaderID);
    glGetShaderiv (VertexShaderID, GL_COMPILE_STATUS, &compileSuccess);

    if (compileSuccess == GL_FALSE)
        shadersLog (VertexShaderID);

    std::cout << "Compiling shader: " << fragment_file_path << std::endl;
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource (FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader (FragmentShaderID);
    glGetShaderiv (FragmentShaderID, GL_COMPILE_STATUS, &compileSuccess);

    if (compileSuccess == GL_FALSE)
        shadersLog (FragmentShaderID);

    std::cout << "Linking program" << std::endl;
    GLuint ProgramID = glCreateProgram();
    glAttachShader (ProgramID, VertexShaderID);
    glAttachShader (ProgramID, FragmentShaderID);
    glLinkProgram (ProgramID);
    glGetProgramiv (ProgramID, GL_LINK_STATUS, &compileSuccess);

    if (compileSuccess == GL_FALSE)
        shadersLog (ProgramID);

    else
        std::cout << "Success!" << std::endl;

    glDeleteShader (VertexShaderID);
    glDeleteShader (FragmentShaderID);

    return ProgramID;
}
