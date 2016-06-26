class GLEngine
{
private:
    bool glfwInitSuccess;
    GLFWwindow* mWindow;
    ShaderFactory mShaders;
    GLuint mProgramID, mVertexArrayID;
    GLuint mVertexBuffer, mColourBuffer;

public:
    GLEngine();
    ~GLEngine();
    static void errorCallback (int error, const char* description);
    virtual void initialise (std::string vertexFilePath, std::string fragmentFilePath);

    const bool windowShouldClose() const;
    const bool keyPressed (int key) const;
    void swapBuffers();
    void pollEvents();
    void waitEvents();

    const GLuint getProgramID() const;
};
