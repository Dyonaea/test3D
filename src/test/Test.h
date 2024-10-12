#ifndef TEST_H
#define TEST_H

#include "../util/util.h"
#include "../app/buffer/Buffer.h"

class Test{

    private:


        // unsigned int VBO, VAO;
//         float vertices[180] = {
//         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  5.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  5.0f, 5.0f,
//         0.5f,  0.5f, -0.5f,  5.0f, 5.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f, 5.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  5.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  5.0f, 5.0f,
//         0.5f,  0.5f,  0.5f,  5.0f, 5.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f, 5.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

//         -0.5f,  0.5f,  0.5f,  5.0f, 0.0f,
//         -0.5f,  0.5f, -0.5f,  5.0f, 5.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 5.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 5.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f,  0.5f,  0.5f,  5.0f, 0.0f,

//         0.5f,  0.5f,  0.5f,  5.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  5.0f, 5.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 5.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 5.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  5.0f, 0.0f,

//         -0.5f, -0.5f, -0.5f,  0.0f, 5.0f,
//         0.5f, -0.5f, -0.5f,  5.0f, 5.0f,
//         0.5f, -0.5f,  0.5f,  5.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  5.0f, 0.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, 5.0f,

//         -0.5f,  0.5f, -0.5f,  0.0f, 5.0f,
//         0.5f,  0.5f, -0.5f,  5.0f, 5.0f,
//         0.5f,  0.5f,  0.5f,  5.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  5.0f, 0.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f, 5.0f
// };

float vertices[5 * 4 * 6] = {
    // Positions         // Texture Coords
    // Back 
    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  
    1.0f, 0.0f, 0.0f,  5.0f, 0.0f,  
    1.0f, 1.0f, 0.0f,  5.0f, 5.0f,  
    0.0f, 1.0f, 0.0f,  0.0f, 5.0f,  

    // Front 
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 
    1.0f, 0.0f, 1.0f,  5.0f, 0.0f, 
    1.0f, 1.0f, 1.0f,  5.0f, 5.0f, 
    0.0f, 1.0f, 1.0f,  0.0f, 5.0f, 

    // Left face
    0.0f, 0.0f, 1.0f,  5.0f, 0.0f, 
    0.0f, 1.0f, 1.0f,  5.0f, 5.0f, 
    0.0f, 1.0f, 0.0f,  0.0f, 5.0f, 
    0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 

    // Right 
    1.0f, 0.0f, 1.0f,  5.0f, 0.0f, 
    1.0f, 1.0f, 1.0f,  5.0f, 5.0f, 
    1.0f, 1.0f, 0.0f,  0.0f, 5.0f, 
    1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 

    // Bottom 
    0.0f, 0.0f, 0.0f,  0.0f, 5.0f,
    1.0f, 0.0f, 0.0f,  5.0f, 5.0f,
    1.0f, 0.0f, 1.0f,  5.0f, 0.0f,
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

    // Top 
    0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
    1.0f, 1.0f, 0.0f,  5.0f, 5.0f,
    1.0f, 1.0f, 1.0f,  5.0f, 0.0f,
    0.0f, 1.0f, 1.0f,  0.0f, 0.0f 
};

    unsigned int indices[2*3*6] = {
    // Back face
    0, 1, 2,  
    2, 3, 0,  

    // Front face
    4, 5, 6,  
    6, 7, 4,  

    // Left face
    8, 9, 10,  
    10, 11, 8,  

    // Right face
    12, 13, 14,  
    14, 15, 12,  

    // Bottom face
    16, 17, 18,  
    18, 19, 16,  

    // Top face
    20, 21, 22,  
    22, 23, 20
};
        VAO* vao;
        VBO* vbo;
        EBO* ebo;
        glm::vec2 pos;

        void init();

    public:
        glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 posMin = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 posMax = glm::vec3(1.0f, 1.0f, 1.0f);
        unsigned int texture;
        Test();
        ~Test();
        void render();
        void update();
};

#endif