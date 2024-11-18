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
                blocks[i][j][k] = {AIR};
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
    std::cout<<indices.size()<<std::endl;
    if(!firstGen){
        for(int x = 0; x < width; x++){
            for(int z = 0; z < depth; z++){
                float e = 
                    1.0f * noise.GetNoise(0.5f * (x + position.x), 0.5f * (z + position.z)) +
                    0.2f * noise.GetNoise(2.0f * (x + position.x), 2.0f * (z + position.z)) +
                    0.1f * noise.GetNoise(4.0f * (x + position.x), 4.0f * (z + position.z));

                    e = (e + 1.3f) / (2*1.3); 
                for(int y = 0; y < pow(e, 3) * (float)height +1; y++){
                    voxel block = {GRASS};
                    blocks[x][y][z] = block;
                }
            }
        }
        firstGen = true;
    }
    // std::cout<<"test"<<std::endl;
    for(int x = 0; x < width; x++){
        for(int z = 0; z < depth; z++){
            for(int y = 0; y < height; y++){
                voxel& b = blocks[x][y][z];

                if (blocType.vtRegistry[b.blockID].isSolid) {
                    voxelType block = blocType.vtRegistry[b.blockID];
                    // Add left face
                    if (x == 0 ||!blocType.vtRegistry[blocks[x-1][y][z].blockID].isSolid) {
                        addMeshFace(x, y, z, block.textures[0], LEFT, block.blocModel);
                    }
                    // Add right face
                    if (x == width - 1 || !blocType.vtRegistry[blocks[x+1][y][z].blockID].isSolid) {
                        addMeshFace(x, y, z, block.textures[1], RIGHT, block.blocModel);
                    }
                    // Add top face
                     if (y == height - 1 ||  !blocType.vtRegistry[blocks[x][y + 1][z].blockID].isSolid) {
                        addMeshFace(x, y, z, block.textures[2], UP, block.blocModel);
                    }
                    // Add bottom face
                    if (y == 0 || !blocType.vtRegistry[blocks[x][y-1][z].blockID].isSolid) {
                        addMeshFace(x, y, z, block.textures[3], DOWN, block.blocModel);
                    }
                    // Add front face
                    if (z == depth - 1 || !blocType.vtRegistry[blocks[x][y][z+1].blockID].isSolid) {
                        addMeshFace(x, y, z, block.textures[4], FACE, block.blocModel);
                    }
                    // Add back face
                    if (z == 0 || !blocType.vtRegistry[blocks[x][y][z-1].blockID].isSolid) {
                        addMeshFace(x, y, z, block.textures[5], BACK, block.blocModel);
                    }
                }
            }
        }
    }
}

void Chunk::addMeshFace(int x, int y, int z, int textureID, SIDE f, MODEL m){
    glm::vec2 texCoords = textureAtlasCoords[textureID];

    glm::vec2 texSize(1.0f/ATLAS_ROWS, 1.0f/ATLAS_COLS);
    glm::vec2 topLeft = texCoords * texSize;
    glm::vec2 botRight = topLeft + texSize;

    float Face[6*4] = {
            // Position                                                                             // Texture Coords       //Shading Values
        x + position.x + faceV[m][f][0], y + position.y + faceV[m][f][1],  z + position.z + faceV[m][f][2], topLeft.y, botRight.x , faceV[m][f][12],
        x + position.x + faceV[m][f][3], y + position.y + faceV[m][f][4],  z + position.z + faceV[m][f][5], topLeft.y, topLeft.x , faceV[m][f][12], 
        x + position.x + faceV[m][f][6], y + position.y + faceV[m][f][7],  z + position.z + faceV[m][f][8],  botRight.y, topLeft.x, faceV[m][f][12], 
        x + position.x + faceV[m][f][9], y + position.y + faceV[m][f][10], z + position.z + faceV[m][f][11], botRight.y, botRight.x, faceV[m][f][12]    
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

bool Chunk::destroyBlock(glm::ivec3 pos){
    // std::cout<<position.x << "  " << position.z <<"  "<<pos.x<<" "<<pos.y<< " "<<pos.z<<std::endl;
    if (!blocType.vtRegistry[blocks[pos.x][pos.y][pos.z].blockID].isSolid){
        //std::cout<<vertices.size()<<std::endl;
        blocks[pos.x][pos.y][pos.z] = {GRASS};
        generateMesh();
        updateBuffer();
        return true;
    }
    return false;
}