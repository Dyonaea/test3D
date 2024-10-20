#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "../app/texture/TextureManager.h"

struct voxel{
    bool isSolid;
    int textureID;
};

class Chunk{
    public:
        const static int width = 16;
        const static int height = 16;
        const static int depth = 16;

        const glm::vec2 textureAtlasCoords[3] = {
            glm::vec2(0.0f, 0.0f),  // Dirt
            glm::vec2(0.0f, 1.0f),  // Grass
            glm::vec2(1.0f, 0.0f),  // Stone
        };
        const int ATLAS_ROWS = 1;
        const int ATLAS_COLS = 1;


        glm::vec3 position;

        voxel blocks[width][height][depth];
        std::vector<float> vertices;
        std::vector<GLuint> indices;
        GLuint triangleCount;
        GLuint indexCount;
    
        Chunk(glm::vec3 pos);
        ~Chunk();
        void init();
        void render();
        
    private:
        GLuint VAO, VBO, EBO;   
        void addMeshFace(int x, int y, int z, int textureID);
        void generateMesh();
        void updateBuffer();


};

#endif