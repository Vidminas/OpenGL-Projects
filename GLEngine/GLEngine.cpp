#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "shaderFactory.hpp"
#include "GLEngine.hpp"

GLEngine::GLEngine()
{
    //nothing
}

GLEngine::~GLEngine()
{
    if (mWindow)
    {
        glDeleteVertexArrays (1, &mVertexArrayID);

        glfwDestroyWindow (mWindow);
        std::cout << "window destroyed" << std::endl;
    }

    if (glfwInitSuccess)
    {
        glfwTerminate();
        std::cout << "glfw terminated" << std::endl;
    }
}

void GLEngine::errorCallback (int error, const char* description)
{
    std::cerr << description << std::endl;
}

void GLEngine::initialise (std::string vertexFilePath, std::string fragmentFilePath)
{
    glfwInitSuccess = glfwInit();

    if (!glfwInitSuccess)
        std::cerr << "Could not initialise GLFW" << std::endl;

    else
    {
        glfwSetErrorCallback (errorCallback);

        glfwWindowHint (GLFW_SAMPLES, 4);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        mWindow = glfwCreateWindow (640, 480, "GL Engine", NULL, NULL);

        if (!mWindow)
            std::cerr << "Could not create GLFW window" << std::endl;

        else
        {
            glfwMakeContextCurrent (mWindow);

            // Initialize GLEW
            glewExperimental = true; // Needed for core profile

            if (glewInit() != GLEW_OK)
                std::cerr << "Failed to initialize GLEW" << std::endl;

            else
            {
                // Ensure we can capture the escape key being pressed below
                glfwSetInputMode (mWindow, GLFW_STICKY_KEYS, GL_TRUE);

                // Black background
                glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

                // Enable depth test
                glEnable (GL_DEPTH_TEST);
                // Accept fragment if it closer to the camera than the former one
                glDepthFunc (GL_LESS);

                mShaders.addShader (GL_VERTEX_SHADER, vertexFilePath);
                mShaders.addShader (GL_FRAGMENT_SHADER, fragmentFilePath);
                mProgramID = mShaders.linkProgram();

                glGenVertexArrays (1, &mVertexArrayID);
                glBindVertexArray (mVertexArrayID);
            }
        }
    }
}

const bool GLEngine::windowShouldClose() const
{
    return glfwWindowShouldClose (mWindow);
}

const bool GLEngine::keyPressed (int key) const
{
    return (glfwGetKey (mWindow, key) == GLFW_PRESS);
}

void GLEngine::swapBuffers()
{
    glfwSwapBuffers (mWindow);
}

void GLEngine::pollEvents()
{
    glfwPollEvents();
}

void GLEngine::waitEvents()
{
    glfwWaitEvents();
}

const GLuint GLEngine::getProgramID() const
{
    return mProgramID;
}
