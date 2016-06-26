#define debug false
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

const GLuint loadShaders (const std::string vertex_file_path, const std::string fragment_file_path)
{
    std::chrono::system_clock::time_point t1, t2;
    t1 = std::chrono::system_clock::now();

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

    GLint Result = GL_FALSE;
    int InfoLogLength;

    std::cout << "Compiling shader: " << vertex_file_path << std::endl;
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader (VertexShaderID);

    if (debug)
    {
        glGetShaderiv (VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv (VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> VertexShaderErrorMessage (InfoLogLength);
        glGetShaderInfoLog (VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage.at (0) );
        std::cout << VertexShaderErrorMessage.at (0) << std::endl;
    }

    std::cout << "Compiling shader: " << fragment_file_path << std::endl;
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource (FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader (FragmentShaderID);

    if (debug)
    {
        glGetShaderiv (FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv (FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> FragmentShaderErrorMessage (InfoLogLength);
        glGetShaderInfoLog (FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage.at (0) );
        std::cout << FragmentShaderErrorMessage.at (0) << std::endl;
    }

    // Link the program
    std::cout << "Linking program" << std::endl;
    GLuint ProgramID = glCreateProgram();
    glAttachShader (ProgramID, VertexShaderID);
    glAttachShader (ProgramID, FragmentShaderID);
    glLinkProgram (ProgramID);

    // Check the program
    if (debug)
    {
        glGetProgramiv (ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv (ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ProgramErrorMessage (std::max (InfoLogLength, 1) );
        glGetProgramInfoLog (ProgramID, InfoLogLength, NULL, &ProgramErrorMessage.at (0) );
        std::cout << ProgramErrorMessage.at (0) << std::endl;
    }

    glDeleteShader (VertexShaderID);
    glDeleteShader (FragmentShaderID);

    t2 = std::chrono::system_clock::now();
    std::cout << "This took: " << static_cast<std::chrono::system_clock::duration> (t2 - t1).count() << " nanoseconds" << std::endl;

    return ProgramID;
}
