#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "../app/texture/TextureManager.h"

struct voxel{
    bool isSolid;
    int textureID;
};

struct ChunkCoordHash{
    std::size_t operator()(const glm::ivec3 coord) const{
        return std::hash<int>()(coord.x) ^ std::hash<int>()(coord.y) << 1 ^ std::hash<int>()(coord.z) << 2;
    }
};


class Chunk{
    public:
        const static int width = 32;
        const static int height = 128;
        const static int depth = 32;

        const glm::vec2 textureAtlasCoords[3] = {
            glm::vec2(0.0f, 0.0f),  // Dirt
            glm::vec2(0.0f, 1.0f),  // Grass
            glm::vec2(1.0f, 0.0f),  // Stone
        };
        const int ATLAS_ROWS = 1;
        const int ATLAS_COLS = 2;
        const int SEED = 1;
        FastNoiseLite noise;


        glm::vec3 position;

        voxel blocks[width][height][depth];
        std::vector<float> vertices;
        std::vector<GLuint> indices;
        GLuint triangleCount;
        GLuint indexCount;
    
        Chunk(glm::ivec3 pos);
        ~Chunk();
        void init();
        void render();
        
    private:

        const float faceV[6][13] = {
        // LEFT
        { 0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 0.6f },
        // RIGHT
        { 1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 0.6f },
        // UP
        { 0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f, 1.0f },
        // DOWN
        { 0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, 0.4f },
        // FACE
        { 0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f, 0.8f },
        // BACK
        { 0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.8f },
        };

        float shading_values[6][4] = {
            0.6, 0.6, 0.6, 0.6,
            0.6, 0.6, 0.6, 0.6,
            1.0, 1.0, 1.0, 1.0,
            0.4, 0.4, 0.4, 0.4,
            0.8, 0.8, 0.8, 0.8,
	        0.8, 0.8, 0.8, 0.8,
        };

        GLuint VAO, VBO, EBO;   
        void addMeshFace(int x, int y, int z, int textureID, SIDE f);
        void generateMesh();
        void updateBuffer();


};

#endif