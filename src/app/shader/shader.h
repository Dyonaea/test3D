#ifndef SHADER_H
#define SHADER_H

#include "../../util/util.h"

std::string get_file_contents(const char* filename);
void checkProgramLinking(GLuint program);
void checkShaderCompilation(GLuint shader);

class Shader{
    public:
        GLuint ID;
        Shader(const char* vertexFile, const char* fragmentFile);
        ~Shader();
        void use();
        void terminate();
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setBool(const std::string &name, bool value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;
};


#endif