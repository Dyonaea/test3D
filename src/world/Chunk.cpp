#include "Chunk.h"


Chunk::Chunk(glm::ivec3 pos) {
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
                blocks[i][j][k] = {false, 0};
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
        for(int z = 0; z < depth; z++){
            float e = 
                1.0f * noise.GetNoise(1.0f * (x + position.x), 1.0f * (z + position.z)) +
                0.5f * noise.GetNoise(2.0f * (x + position.x), 2.0f * (z + position.z)) +
                0.25f * noise.GetNoise(4.0f * (x + position.x), 4.0f * (z + position.z));

                e = (e + 1.75f) / (2*1.75); 
            for(int y = 0; y < pow(e, 3) * (float)height; y++){
                voxel block = {true, 2};
                blocks[x][y][z] = block;
            }
        }
    }


    for(int x = 0; x < width; x++){
        for(int z = 0; z < depth; z++){
            for(int y = 0; y < height; y++){
                voxel& block = blocks[x][y][z];

                if (block.isSolid) {
                    // Add top face
                     if (y == height - 1 || !blocks[x][y + 1][z].isSolid) {
                        addMeshFace(x, y, z, block.textureID, UP);
                    }
                    // Add bottom face
                    if (y == 0 || !blocks[x][y - 1][z].isSolid) {
                        addMeshFace(x, y, z, block.textureID, DOWN);
                    }
                    // Add front face
                    if (z == depth - 1 || !blocks[x][y][z + 1].isSolid) {
                        addMeshFace(x, y, z, block.textureID, FACE);
                    }
                    // Add back face
                    if (z == 0 || !blocks[x][y][z - 1].isSolid) {
                        addMeshFace(x, y, z, block.textureID, BACK);
                    }
                    // Add left face
                    if (x == 0 || !blocks[x - 1][y][z].isSolid) {
                        addMeshFace(x, y, z, block.textureID, LEFT);
                    }
                    // Add right face
                    if (x == width - 1 || !blocks[x + 1][y][z].isSolid) {
                        addMeshFace(x, y, z, block.textureID, RIGHT);
                    }
                }
            }
        }
    }
}

void Chunk::addMeshFace(int x, int y, int z, int textureID, SIDE f){
    glm::vec2 texCoords = textureAtlasCoords[textureID];

    glm::vec2 texSize(1.0f/ATLAS_COLS, 1.0f/ATLAS_ROWS);
    glm::vec2 topLeft = texCoords * texSize;
    glm::vec2 botRight = topLeft + texSize;

    float Face[] = {
            // Position                                                                             // Texture Coords       //Shading Values
        x + position.x + faceV[f][0], y + position.y + faceV[f][1],  z + position.z + faceV[f][2],  topLeft.x, topLeft.y, faceV[f][12],
        x + position.x + faceV[f][3], y + position.y + faceV[f][4],  z + position.z + faceV[f][5],  botRight.x, topLeft.y, faceV[f][12], 
        x + position.x + faceV[f][6], y + position.y + faceV[f][7],  z + position.z + faceV[f][8],  botRight.x, botRight.y, faceV[f][12], 
        x + position.x + faceV[f][9], y + position.y + faceV[f][10], z + position.z + faceV[f][11], topLeft.x, botRight.y, faceV[f][12]    
    };
    vertices.insert(vertices.end(), std::begin(Face), std::end(Face));
    GLuint topIndices[] = { indexCount, indexCount + 1, indexCount + 2, indexCount, indexCount + 2, indexCount + 3 };
    indices.insert(indices.end(), std::begin(topIndices), std::end(topIndices));
    indexCount +=4;  
    triangleCount +=2;
}

void Chunk::updateBuffer(){
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);  
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));  
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

}

void Chunk::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
