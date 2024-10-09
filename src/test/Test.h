#ifndef TEST_H
#define TEST_H

#include "../util/util.h"
#include "../app/buffer/Buffer.h"

class Test{

    private:

    glm::vec3 position = glm::vec3(0.0, 1.0, 0.0);

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

    float vertices[5*4*6] = {
    // Positions         // Texture Coords
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Vertex 0
     0.5f, -0.5f, -0.5f,  5.0f, 0.0f,  // Vertex 1
     0.5f,  0.5f, -0.5f,  5.0f, 5.0f,  // Vertex 2
    -0.5f,  0.5f, -0.5f,  0.0f, 5.0f,  // Vertex 3

    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Vertex 4
     0.5f, -0.5f,  0.5f,  5.0f, 0.0f,  // Vertex 5
     0.5f,  0.5f,  0.5f,  5.0f, 5.0f,  // Vertex 6
    -0.5f,  0.5f,  0.5f,  0.0f, 5.0f,  // Vertex 7

    // Left face
    -0.5f, -0.5f,  0.5f,  5.0f, 0.0f,  // Vertex 8
    -0.5f,  0.5f,  0.5f,  5.0f, 5.0f,  // Vertex 9
    -0.5f,  0.5f, -0.5f,  0.0f, 5.0f,  // Vertex 10
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Vertex 11

    // Right face
     0.5f, -0.5f,  0.5f,  5.0f, 0.0f,  // Vertex 12
     0.5f,  0.5f,  0.5f,  5.0f, 5.0f,  // Vertex 13
     0.5f,  0.5f, -0.5f,  0.0f, 5.0f,  // Vertex 14
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Vertex 15

    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 5.0f,  // Vertex 16
     0.5f, -0.5f, -0.5f,  5.0f, 5.0f,  // Vertex 17
     0.5f, -0.5f,  0.5f,  5.0f, 0.0f,  // Vertex 18
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Vertex 19

    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 5.0f,  // Vertex 20
     0.5f,  0.5f, -0.5f,  5.0f, 5.0f,  // Vertex 21
     0.5f,  0.5f,  0.5f,  5.0f, 0.0f,  // Vertex 22
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f   // Vertex 23
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
        unsigned int texture;
        Test();
        ~Test();
        void render();
        void update();
};

#endif