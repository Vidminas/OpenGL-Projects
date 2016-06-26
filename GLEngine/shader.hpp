class Shader
{
private:
    GLuint mShaderID;
    std::string mShaderCode, mFilePath;

public:
    Shader (GLenum shaderType, std::string filePath);

    bool read();
    void compile();
    const GLuint getID() const;
};
