#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../../util/util.h"
#include "texture.h"

class TextureManager{
    public:
        std::map<std::string, std::shared_ptr<Texture>> textures;
        void loadTexture(const std::string& name, const std::string& filePath, const std::string& texType);
        std::shared_ptr<Texture> getTexture(const std::string& name) const;
        void bindTexture(const std::string& name) const;
};

#endif