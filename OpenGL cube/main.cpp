#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLuint loadShaders (std::string vertexFilePath,  std::string fragmentFilePath)
{
    // Create the shaders
    GLuint vertexShaderID = glCreateShader (GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader (GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderFile (vertexFilePath, std::ios::in);
    
    if (vertexShaderFile.is_open() )
    {
        std::string line;
        
        while (vertexShaderFile.good() && getline (vertexShaderFile, line) )
            vertexShaderCode.append (line+'\n');

        vertexShaderFile.close();
    }
    
    else
    {
        std::cerr << "Could not open " << vertexFilePath << ". Is the file or this executable in the wrong directory?" << std::endl;
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderFile (fragmentFilePath, std::ios::in);
    
    if (fragmentShaderFile.is_open() )
    {
        std::string line;
        
        while (fragmentShaderFile.good() && getline (fragmentShaderFile, line) )
            fragmentShaderCode.append (line+'\n');

        fragmentShaderFile.close();
    }
    
    else
    {
        std::cerr << "Could not open " << fragmentFilePath << ". Is the file or this executable in the wrong directory?" << std::endl;
        return 0;
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    std::cout << "Compiling shader: " << vertexFilePath << std::endl;
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource (vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader (vertexShaderID);

    // Check Vertex Shader
    glGetShaderiv (vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv (vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    if (infoLogLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage (infoLogLength+1);
        glGetShaderInfoLog (vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        std::cerr << &vertexShaderErrorMessage[0] << std::endl;
    }

    // Compile Fragment Shader
    std::cout << "Compiling shader: " << fragmentFilePath << std::endl;
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource (fragmentShaderID, 1, &fragmentSourcePointer , NULL);
    glCompileShader (fragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv (fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv (fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    if (infoLogLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage (infoLogLength+1);
        glGetShaderInfoLog (fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        std::cerr << &fragmentShaderErrorMessage[0] << std::endl;
    }

    // Link the program
    std::cout << "Linking program" << std::endl;
    GLuint programID = glCreateProgram();
    glAttachShader (programID, vertexShaderID);
    glAttachShader (programID, fragmentShaderID);
    glLinkProgram (programID);

    // Check the program
    glGetProgramiv (programID, GL_LINK_STATUS, &result);
    glGetProgramiv (programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    if (infoLogLength > 0)
    {
        std::vector<char> programErrorMessage (infoLogLength+1);
        glGetProgramInfoLog (programID, infoLogLength, NULL, &programErrorMessage[0]);
        std::cerr << &programErrorMessage[0] << std::endl;
    }

    glDetachShader (programID, vertexShaderID);
    glDetachShader (programID, fragmentShaderID);
    
    glDeleteShader (vertexShaderID);
    glDeleteShader (fragmentShaderID);

    return programID;
}

void errorCallback (int error, const char* description)
{
    std::cerr << description << std::endl;
}

int main()
{
    if (!glfwInit() )
        std::cerr << "Could not initialise GLFW";

    else
    {
        glfwSetErrorCallback (errorCallback);
        
        glfwWindowHint (GLFW_SAMPLES, 4);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWwindow* window = glfwCreateWindow (640, 480, "Spinning cube", NULL, NULL);

        if (!window)
            std::cerr << "Could not create GLFW window";
        
        else
        {
            glfwMakeContextCurrent (window);
            
            // Initialize GLEW
            glewExperimental = true; // Needed for core profile
            
            if (glewInit() != GLEW_OK)
                std::cerr << "Failed to initialize GLEW" << std::endl;
                
            else
            {
                // Ensure we can capture the escape key being pressed below
                glfwSetInputMode (window, GLFW_STICKY_KEYS, GL_TRUE);

                // Dark blue background
                glClearColor (0.0f, 0.0f, 0.4f, 0.0f);

                // Enable depth test
                glEnable (GL_DEPTH_TEST);
                // Accept fragment if it closer to the camera than the former one
                glDepthFunc (GL_LESS);
                
                GLuint vertexArrayID;
                glGenVertexArrays (1, &vertexArrayID);
                glBindVertexArray (vertexArrayID);

                // Create and compile our GLSL program from the shaders
                GLuint programID = loadShaders ("VertexShader.glsl", "FragmentShader.glsl");
                
                // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
                // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
                static const GLfloat vertexBufferData[] = { 
                    -1.0f,-1.0f,-1.0f,
                    -1.0f,-1.0f, 1.0f,
                    -1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f,-1.0f,
                    -1.0f,-1.0f,-1.0f,
                    -1.0f, 1.0f,-1.0f,
                     1.0f,-1.0f, 1.0f,
                    -1.0f,-1.0f,-1.0f,
                     1.0f,-1.0f,-1.0f,
                     1.0f, 1.0f,-1.0f,
                     1.0f,-1.0f,-1.0f,
                    -1.0f,-1.0f,-1.0f,
                    -1.0f,-1.0f,-1.0f,
                    -1.0f, 1.0f, 1.0f,
                    -1.0f, 1.0f,-1.0f,
                     1.0f,-1.0f, 1.0f,
                    -1.0f,-1.0f, 1.0f,
                    -1.0f,-1.0f,-1.0f,
                    -1.0f, 1.0f, 1.0f,
                    -1.0f,-1.0f, 1.0f,
                     1.0f,-1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f,
                     1.0f,-1.0f,-1.0f,
                     1.0f, 1.0f,-1.0f,
                     1.0f,-1.0f,-1.0f,
                     1.0f, 1.0f, 1.0f,
                     1.0f,-1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f,-1.0f,
                    -1.0f, 1.0f,-1.0f,
                     1.0f, 1.0f, 1.0f,
                    -1.0f, 1.0f,-1.0f,
                    -1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f,
                    -1.0f, 1.0f, 1.0f,
                     1.0f,-1.0f, 1.0f
                };

                // One color for each vertex. They were generated randomly.
                static const GLfloat colorBufferData[] = { 
                    0.583f,  0.771f,  0.014f,
                    0.609f,  0.115f,  0.436f,
                    0.327f,  0.483f,  0.844f,
                    0.822f,  0.569f,  0.201f,
                    0.435f,  0.602f,  0.223f,
                    0.310f,  0.747f,  0.185f,
                    0.597f,  0.770f,  0.761f,
                    0.559f,  0.436f,  0.730f,
                    0.359f,  0.583f,  0.152f,
                    0.483f,  0.596f,  0.789f,
                    0.559f,  0.861f,  0.639f,
                    0.195f,  0.548f,  0.859f,
                    0.014f,  0.184f,  0.576f,
                    0.771f,  0.328f,  0.970f,
                    0.406f,  0.615f,  0.116f,
                    0.676f,  0.977f,  0.133f,
                    0.971f,  0.572f,  0.833f,
                    0.140f,  0.616f,  0.489f,
                    0.997f,  0.513f,  0.064f,
                    0.945f,  0.719f,  0.592f,
                    0.543f,  0.021f,  0.978f,
                    0.279f,  0.317f,  0.505f,
                    0.167f,  0.620f,  0.077f,
                    0.347f,  0.857f,  0.137f,
                    0.055f,  0.953f,  0.042f,
                    0.714f,  0.505f,  0.345f,
                    0.783f,  0.290f,  0.734f,
                    0.722f,  0.645f,  0.174f,
                    0.302f,  0.455f,  0.848f,
                    0.225f,  0.587f,  0.040f,
                    0.517f,  0.713f,  0.338f,
                    0.053f,  0.959f,  0.120f,
                    0.393f,  0.621f,  0.362f,
                    0.673f,  0.211f,  0.457f,
                    0.820f,  0.883f,  0.371f,
                    0.982f,  0.099f,  0.879f
                };

                // Get a handle for our "MVP" uniform
                GLuint uniformMatrixID = glGetUniformLocation (programID, "MVP");

                // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
                glm::mat4 projection = glm::perspective (glm::radians (45.f), 4.f / 3.f, 0.1f, 100.f);
                // Camera matrix
                glm::mat4 view = glm::lookAt (
                                            glm::vec3 (4,3,-3), // Camera is at (4,3,-3), in World Space
                                            glm::vec3 (0,0,0), // and looks at the origin
                                            glm::vec3 (0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                            );
                // Model matrix : an identity matrix (model will be at the origin)
                glm::mat4 model = glm::mat4 (1.f);
                
                GLuint vertexBuffer;
                glGenBuffers (1, &vertexBuffer);
                glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
                glBufferData (GL_ARRAY_BUFFER, sizeof (vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

                GLuint colorBuffer;
                glGenBuffers (1, &colorBuffer);
                glBindBuffer (GL_ARRAY_BUFFER, colorBuffer);
                glBufferData (GL_ARRAY_BUFFER, sizeof (colorBufferData), colorBufferData, GL_STATIC_DRAW);
                
                float angle = glm::radians (0.f);
                std::chrono::time_point<std::chrono::steady_clock> t1, t2;
                t1 = t2 = std::chrono::steady_clock::now();

                // Check if the ESC key was pressed or the window was closed
                while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose (window) )
                {
                    t2 = std::chrono::steady_clock::now();
                    angle = (t2 - t1).count() / 1e9f;
                    
                    glm::mat4 animation = glm::rotate (glm::mat4 (1.f), angle, glm::vec3 (0.f, 1.f, 0.f) );
                    
                    // Our ModelViewProjectionAnimation matrix : multiplication of our 4 matrices
                    // Remember, matrix multiplication is the other way around
                    glm::mat4 mvpa = projection * view * model * animation;
                    
                    // Clear the screen
                    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    // Use our shader
                    glUseProgram (programID);

                    // Send our transformation to the currently bound shader, 
                    // in the "MVP" uniform
                    glUniformMatrix4fv (uniformMatrixID, 1, GL_FALSE, &mvpa[0][0]);

                    // 1st attribute buffer : vertices
                    glEnableVertexAttribArray (0);
                    glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
                    glVertexAttribPointer (
                        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                        3,                  // size
                        GL_FLOAT,   // type
                        GL_FALSE,   // normalized?
                        0,                  // stride
                        (void*)0        // array buffer offset
                    );

                    // 2nd attribute buffer : colors
                    glEnableVertexAttribArray (1);
                    glBindBuffer (GL_ARRAY_BUFFER, colorBuffer);
                    glVertexAttribPointer (
                        1,                  // attribute. No particular reason for 1, but must match the layout in the shader.
                        3,                  // size
                        GL_FLOAT,   // type
                        GL_FALSE,   // normalized?
                        0,                  // stride
                        (void*)0        // array buffer offset
                    );

                    // Draw the triangle !
                    glDrawArrays (GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

                    glDisableVertexAttribArray (0);
                    glDisableVertexAttribArray (1);

                    // Swap buffers
                    glfwSwapBuffers (window);
                    glfwPollEvents();
                }
                
                // Cleanup VBO and shader
                glDeleteBuffers (1, &vertexBuffer);
                glDeleteBuffers (1, &colorBuffer);
                glDeleteProgram (programID);
                glDeleteVertexArrays (1, &vertexArrayID);
            }
            glfwDestroyWindow (window);
        }
        glfwTerminate();
    }

    return 0;
}
