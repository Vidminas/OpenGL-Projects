class ShaderFactory
{
private:
    GLuint mProgramID;
    std::vector<Shader> mShaders;

public:
    ShaderFactory();
    ~ShaderFactory();

    void addShader (GLenum shaderType, std::string filePath);
    GLuint linkProgram();
};
