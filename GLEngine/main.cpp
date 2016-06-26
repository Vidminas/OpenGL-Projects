#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "shaderFactory.hpp"
#include "GLEngine.hpp"
#include "geometry2D.hpp"

int main()
{
    std::array <Point, 8> points =
    {
        {
        Point(),
        Point(1,  1, 0, 0.6, 0.4, 0.2),
        Point(0,  3, 0, 0,   1,   0),
        Point(1,  2, 0, 0,   0,   1),
        Point(0,  5, 0),
        Point(2,  4, 0),
        Point(-1, 5, 0),
        Point(2,  2, 0)
}
    };

    GLEngine engine;
    engine.initialise("VertexShader.glsl", "FragmentShader.glsl");
    GLuint programID = engine.getProgramID();

    std::vector <GLfloat> vertexBufferData, colorBufferData;

    for (const auto & i: points)
    {
        vertexBufferData.push_back(i.getX());
        vertexBufferData.push_back(i.getY());
        vertexBufferData.push_back(i.getZ());
        colorBufferData.push_back(i.getR());
        colorBufferData.push_back(i.getG());
        colorBufferData.push_back(i.getB());
    }

    glPointSize(10.f);

    // Get a handle for our "MVP" uniform
    GLuint uniformMatrixID = glGetUniformLocation(programID, "MVP");

    // Projection matrix : 45° Field of View, 16:9 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projection = glm::perspective(glm::radians(45.f), 16.f / 9.f, 0.1f, 100.f);

    // Camera matrix
    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 0, -5), // Camera is at (0,0,-5), in World Space
        glm::vec3(0, 0, 0),  // and looks at the origin
        glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
        );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 model = glm::mat4(1.f);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof( GLfloat ), &vertexBufferData.front(), GL_STATIC_DRAW);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colorBufferData.size() * sizeof( GLfloat ), &colorBufferData.front(), GL_STATIC_DRAW);

    // Check if the ESC key was pressed or the window was closed
    // while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose (window) )
    while (!engine.keyPressed(GLFW_KEY_ESCAPE) && !engine.windowShouldClose())
    {
        /*
         * std::cout << view[0][0] << ", " << view[0][1] << ", " << view[0][2] << ", " << view[0][3] << std::endl;
         * std::cout << view[1][0] << ", " << view[1][1] << ", " << view[1][2] << ", " << view[1][3] << std::endl;
         * std::cout << view[2][0] << ", " << view[2][1] << ", " << view[2][2] << ", " << view[2][3] << std::endl;
         * std::cout << view[3][0] << ", " << view[3][1] << ", " << view[3][2] << ", " << view[3][3] << std::endl
         *        << std::endl << std::endl << std::endl;
         */

        if (engine.keyPressed(GLFW_KEY_W))
            view[3][1] -= 0.1;

        else if (engine.keyPressed(GLFW_KEY_S))
            view[3][1] += 0.1;

        if (engine.keyPressed(GLFW_KEY_A))
            view[3][0] += 0.1;

        else if (engine.keyPressed(GLFW_KEY_D))
            view[3][0] -= 0.1;

        if (engine.keyPressed(GLFW_KEY_Q))
            view[3][2] -= 0.5;

        else if (engine.keyPressed(GLFW_KEY_E))
            view[3][2] += 0.5;

        glm::mat4 mvp = projection * view * model;

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(uniformMatrixID, 1, GL_FALSE, &mvp[0][0]);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,                // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,               // stride
            (void *)0    // array buffer offset
            );

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(
            1,                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,               // stride
            (void *)0    // array buffer offset
            );

        glDrawArrays(GL_POINTS, 0, vertexBufferData.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        engine.swapBuffers();
        engine.waitEvents();
    }

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);

    return 0;
}