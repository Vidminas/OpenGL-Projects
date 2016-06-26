#define GLEW_STATIC
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <chrono>
#include "shaders.hpp"
#include "FPS.hpp"

int main()
{
    if (!glfwInit() )
        std::cerr << "Failed to initialize GLFW" << std::endl;

    else
    {
        glfwWindowHint (GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window;
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

                const GLfloat cube_vertices[] = {
                // front
                -1.0, -1.0,  1.0,
                 1.0, -1.0,  1.0,
                 1.0,  1.0,  1.0,
                -1.0,  1.0,  1.0,
                // back
                -1.0, -1.0, -1.0,
                 1.0, -1.0, -1.0,
                 1.0,  1.0, -1.0,
                -1.0,  1.0, -1.0};

                const GLfloat cube_colors[] = {
                // front colors
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0,
                1.0, 1.0, 1.0,
                // back colors
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0,
                1.0, 1.0, 1.0};

                const GLushort cube_elements[] = {
                0, 1, 2, // front
                2, 3, 0,
                3, 2, 6, // top
                6, 7, 3,
                7, 6, 5, // back
                5, 4, 7,
                4, 5, 1, // bottom
                1, 0, 4,
                4, 0, 3, // left
                3, 7, 4,
                1, 5, 6, // right
                6, 2, 1};

                const GLint attribute_coords (glGetAttribLocation (programID, "coords") );
                if (attribute_coords == -1)
                    std::cerr << "Could not bind attribute coords"  << std::endl;

                const GLint attribute_colors (glGetAttribLocation (programID, "colors") );
                if (attribute_colors == -1)
                    std::cerr << "Could not bind attribute colors" << std::endl;

                const GLint uniform_mvp (glGetUniformLocation (programID, "MVP") );
                if (uniform_mvp == -1)
                    std::cerr << "Could not bind uniform MVP" << std::endl;

                glm::mat4 model = glm::translate (glm::mat4 (1.0f), glm::vec3 (0.0, 0.0, -4.0) );
                glm::mat4 view = glm::lookAt (glm::vec3 (4.0, 3.0, 2.0), glm::vec3 (0.0, 0.0, -4.0), glm::vec3 (0.0, 1.0, 0.0) );
                glm::mat4 projection = glm::perspective (45.0f, 1.0f * 1024 / 768, 0.1f, 10.0f);

                GLuint vertexbuffer; // This will identify our vertex buffer
                glGenBuffers (1, &vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
                glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer); // The following commands will talk about our 'vertexbuffer' buffer
                glBufferData (GL_ARRAY_BUFFER, sizeof (cube_vertices), cube_vertices, GL_STATIC_DRAW); // Give our vertices to OpenGL.

                GLuint colorbuffer;
                glGenBuffers (1, &colorbuffer);
                glBindBuffer (GL_ARRAY_BUFFER, colorbuffer);
                glBufferData (GL_ARRAY_BUFFER, sizeof (cube_colors), cube_colors, GL_STATIC_DRAW);

                GLuint elementbuffer;
                glGenBuffers (1, &elementbuffer);
                glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
                glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (cube_elements), cube_elements, GL_STATIC_DRAW);
                glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

                glfwSetInputMode (window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key being pressed below

                glEnable (GL_DEPTH_TEST); // Enable depth test
                glDepthFunc (GL_LESS); // Accept fragment if it closer to the camera than the former one

                glEnable (GL_BLEND); // Enable alpha
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                float angle (0);
                FrameCap limiter (60);
                std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
                t1 = std::chrono::high_resolution_clock::now();
                t2 = t1;

                // Check if the ESC key was pressed or the window was closed
                while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose (window) )
                {
                    t2 = std::chrono::high_resolution_clock::now();
                    angle = (t2 - t1).count() / 1e9f;
                    glm::mat4 animation = glm::rotate (glm::mat4 (1.0f), angle, glm::vec3 (0.0f, 1.0f, 0.0f) );
                    glm::mat4 mvp = projection * view * model * animation;
                    glUseProgram (programID);
                    glUniformMatrix4fv (uniform_mvp, 1, GL_FALSE, glm::value_ptr (mvp) );

                    glClearColor (1.0f, 1.0f, 1.0f, 1.0f); // Clear the screen with a white colour
                    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    glUseProgram (programID); // Use our shader

                    // 1st attribute buffer : vertices
                    glEnableVertexAttribArray (attribute_coords);
                    glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer);
                    glVertexAttribPointer (
                    attribute_coords,   // attribute
                    3,                  // size (x, y, z for coords and R, G, B for colors)
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    0                   // array buffer offset
                    );

                    // 2nd attribute buffer : colors
                    glEnableVertexAttribArray (attribute_colors);
                    glBindBuffer (GL_ARRAY_BUFFER, colorbuffer);
                    glVertexAttribPointer (
                    attribute_colors,
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    0);

                    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
                    int size;
                    glGetBufferParameteriv (GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
                    glDrawElements (GL_TRIANGLES, size / sizeof (GLushort), GL_UNSIGNED_SHORT, 0);

                    glDisableVertexAttribArray (attribute_coords);
                    glDisableVertexAttribArray (attribute_colors);

                    glfwSwapBuffers (window);
                    glfwPollEvents();
                    limiter.limit();
                }

                glDeleteProgram (programID);
                glDeleteBuffers (1, &vertexbuffer);
                glDeleteBuffers (1, &colorbuffer);
                glfwDestroyWindow (window);
                glfwTerminate();
            }
        }
    }
    return 0;
}
