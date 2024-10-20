#include "Chunk.h"


Chunk::Chunk(glm::vec3 pos) {
    position.x = pos.x * width;
    position.y = pos.y * height;
    position.z = pos.z * depth;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    init();
}

Chunk::~Chunk(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Chunk::init(){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < depth; k++){
                blocks[i][j][k] = {true, 0};
            }
        }
    }
    generateMesh();
    updateBuffer();
}


void Chunk::generateMesh(){
    vertices.clear();
    indices.clear();
    triangleCount = 0;
    indexCount = 0;
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            for(int z = 0; z < depth; z++){
                addMeshFace(x, y, z, blocks[x][y][z].textureID);
            }
        }
    }
}

void Chunk::addMeshFace(int x, int y, int z, int textureID){
    glm::vec2 texCoords = textureAtlasCoords[textureID];

    glm::vec2 texSize(1.0f/ATLAS_COLS, 1.0f/ATLAS_ROWS);
    glm::vec2 topLeft = texCoords * texSize;
    glm::vec2 botRight = topLeft + texSize;

    float topFace[] = {
            // Position                     // Texture Coords
        x,        y + 1.0f, z,        topLeft.x, topLeft.y,
        x + 1.0f, y + 1.0f, z,        botRight.x, topLeft.y, 
        x + 1.0f, y + 1.0f, z + 1.0f, botRight.x, botRight.y, 
        x,        y + 1.0f, z + 1.0f, topLeft.x, botRight.y    
    };
    vertices.insert(vertices.end(), std::begin(topFace), std::end(topFace));
    GLuint topIndices[] = { indexCount, indexCount + 1, indexCount + 2, indexCount, indexCount + 2, indexCount + 3 };
    indices.insert(indices.end(), std::begin(topIndices), std::end(topIndices));
    indexCount +=4;
    triangleCount +=2;
}

void Chunk::updateBuffer(){
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));  
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

}

void Chunk::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
