#ifndef TEXTURE_H
#define TEXTURE_H
#include "../../util/util.h"

class Texture{
    public:
    GLuint ID;
    std::string type;
    std::string path;

    Texture(const std::string filePath, const std::string texType);
    void bind();
    
};

#endif