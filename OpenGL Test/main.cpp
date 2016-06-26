#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaders.hpp"

int main()
{
    if (!glfwInit() )
        std::cerr << "Failed to initialize GLFW" << std::endl;

    else
    {
        glfwWindowHint (GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.4
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

        // Open a window and create its OpenGL context
        GLFWwindow* window; // (In the accompanying source code, this variable is global)
        window = glfwCreateWindow (1024, 768, "Test", NULL, NULL);

        if (window == NULL)
        {
            std::cerr << "Failed to open GLFW window." << std::endl;
            glfwTerminate();
        }

        else
        {
            glfwMakeContextCurrent (window); // Initialize GLEW
            glewExperimental = true; // Needed in core profile

            if (glewInit() != GLEW_OK)
            {
                std::cerr << "Failed to initialize GLEW" << std::endl;
                glfwTerminate();
            }

            else
            {
                GLuint VertexArrayID; // The vertex array object - VAO
                glGenVertexArrays (1, &VertexArrayID);
                glBindVertexArray (VertexArrayID);

                const GLuint programID (loadShaders ("VertexShader.glsl", "FragmentShader.glsl") );

                // An array of 3 vectors which represents 3 vertices
                static const GLfloat g_vertex_buffer_data[] =
                {-1.0f, -1.0f, 0.0f,
                  1.0f, -1.0f, 0.0f,
                  0.0f,  1.0f, 0.0f};

                GLuint vertexbuffer; // This will identify our vertex buffer
                glGenBuffers (1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
                glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer); // The following commands will talk about our 'vertexbuffer' buffer
                glBufferData (GL_ARRAY_BUFFER, sizeof (g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); // Give our vertices to OpenGL.
                glfwSetInputMode (window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key being pressed below
                glClearColor (0.0f, 0.0f, 0.4f, 0.0f); // Clear the screen with a bluish colour

                // Check if the ESC key was pressed or the window was closed
                while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose (window) )
                {
                    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    glUseProgram (programID); // Use our shader
                    glEnableVertexAttribArray (0); // 1st attribute buffer : vertices
                    glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer);

                    glVertexAttribPointer (
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

                    // Draw the triangle !
                    glDrawArrays (GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
                    glDisableVertexAttribArray (0);

                    glfwSwapBuffers (window);
                    glfwPollEvents();
                }

                glfwTerminate();
            }
        }
    }
    return 0;
}
