#ifndef CHUNK_H
#define CHUNK_H

#include "../util/util.h"
#include "../app/texture/TextureManager.h"
#include "BlocType.h"

struct voxel{
    BLOC_ID blockID;
};

class Chunk{
    public:
        const static int width = 32;
        const static int height = 128;
        const static int depth = 32;

        bool firstGen = false;

        BlocType blocType;

        const glm::vec2 textureAtlasCoords[4] = {
            glm::vec2(0.0f, 0.0f),  // Dirt
            glm::vec2(0.0f, 1.0f),  // Grass
            glm::vec2(0.0f, 2.0f),  // Stone
            glm::vec2(0.0f, 3.0f),  // Stone
        };
        const int ATLAS_ROWS = 1;
        const int ATLAS_COLS = 4;
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
        bool destroyBlock(glm::ivec3 pos);
        
    private:

        const float faceV[2][6][13] = 
        {
        {
            // LEFT
            { 0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,     0.6f },
            // RIGHT    
            { 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,     0.6f },
            // UP   
            { 1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f,     1.0f },
            // DOWN 
            { 1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,     0.4f },
            // FACE 
            { 0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,     0.8f },
            // BACK 
            { 1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,     0.8f },
        },
        {
            //
            {0.1464f, 1.0f, 0.8536f, 0.1464f, 0.0f, 0.8536f, 0.8536f, 0.0f, 0.1464f, 0.8536f, 1.0f, 0.1464f,   1.0f},

            {0.1464f, 1.0f, 0.1464f, 0.1464f, 0.0f, 0.1464f, 0.8536f, 0.0f, 0.8536f, 0.8536f, 1.0f, 0.8536f,   1.0f},

            {0.8536f, 1.0f, 0.1464f, 0.8536f, 0.0f, 0.1464f, 0.1464f, 0.0f, 0.8536f, 0.1464f, 1.0f, 0.8536f,   1.0f},

            {0.8536f, 1.0f, 0.8536f, 0.8536f, 0.0f, 0.8536f, 0.1464f, 0.0f, 0.1464f, 0.1464f, 1.0f, 0.1464f,   1.0f}
        }
        };

        GLuint VAO, VBO, EBO;   
        void addMeshFace(int x, int y, int z, int textureID, SIDE f, MODEL m);
        void generateMesh();
        void updateBuffer();
        


};

#endif