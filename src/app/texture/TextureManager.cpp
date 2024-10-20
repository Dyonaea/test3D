#include "TextureManager.h"

void TextureManager::loadTexture(const std::string& name, const std::string& filePath, const std::string& texType){
    if(textures.find(name) == textures.end()){
        textures[name] = std::make_shared<Texture>(filePath, texType);
    }
}

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name)const{
    auto it = textures.find(name);
    if(it != textures.end()){
        return it->second;
    } else{
        std::cerr << "Texture " << name << " not found" << std::endl;
        return nullptr;
    }
}

void TextureManager::bindTexture(const std::string& name) const{
    auto texture = getTexture(name);
    if(texture){
        texture->bind();
    }
}