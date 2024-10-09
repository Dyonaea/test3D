#include "shader.h"

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        std::streampos fileSize = in.tellg();
        if (fileSize <= 0)
        {
            in.close();
            throw std::runtime_error("Error: Could not determine file size or file is empty.");
        }
        std::string contents(static_cast<size_t>(fileSize), '\0');
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    throw std::runtime_error("Error opening file: " + std::string(filename) + " - " + std::strerror(errno));
}

void checkShaderCompilation(GLuint shader)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "Shader Compilation Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}

void checkProgramLinking(GLuint program)
{
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::cerr << "Program Linking Error: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);
    checkProgramLinking(this->ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::use()
{
    glUseProgram(this->ID);
}

void Shader::terminate()
{
    glDeleteProgram(this->ID);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1)
    {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader!" << std::endl;
    }
    else
    {
        glUniform2fv(loc, 1, &value[0]);
    }
}

void Shader::setFloat(const std::string &name, float value) const
{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1)
    {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader!" << std::endl;
    }
    else
    {
        glUniform1f(loc, value);
    }
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1)
    {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader!" << std::endl;
    }
    else
    {
        glUniform3fv(loc, 1, &value[0]);
    }
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1)
    {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader!" << std::endl;
    }
    else
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }
}