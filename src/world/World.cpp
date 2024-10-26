#include "World.h"

World::World(){
    renderDistance = 10;
    init();
    texManager.loadTexture( "grass", "res/dirt.png", "specular");
}

World::~World(){
    for(auto &bloc: blocs){
        delete bloc;
    }
    for(auto &pair: loadedChunk){
        delete pair.second;
    }
    delete player;
}

void World::init(){
    player = new Player();
    // for(int i = 0; i < 20; i++){
    //     for (int j = 0; j < 20; j++){
    //         blocs.push_back(new Bloc(glm::vec3(i, 0.0f, j), &texManager));
    //     }
    // }
    // blocs.push_back(new Bloc(glm::vec3(-1.0f, 0.0f, -1.0f), &texManager));
    //  blocs.push_back(new Bloc(glm::vec3(1.0f, 0.0f, 0.0f)));
    //  blocs.push_back(new Bloc(glm::vec3(0.0f, 0.0f, 1.0f)));
    //  blocs.push_back(new Bloc(glm::vec3(1.0f, 0.0f, 1.0f)));
    // chunk = new Chunk(glm::vec3(0.0f, 0.0f, 0.0f));



}

void World::chunkGenerationUpdate(){
    int playerX = player->position.x/Chunk::width;
    int playerZ = player->position.z/Chunk::depth;
    glm::vec3 playerPos(playerX, 0, playerZ);
    for(int x = -renderDistance + player->position.x/Chunk::width; x < renderDistance + player->position.x/Chunk::width; x++){
        for (int z = - renderDistance + player->position.z/Chunk::depth; z < renderDistance + player->position.z/Chunk::depth; z++){
            glm::vec3 chunkCoord(x, 0, z);
            if (glm::distance(chunkCoord, playerPos) < renderDistance) {
            if(loadedChunk.find(glm::ivec3(chunkCoord)) == loadedChunk.end()){
                loadedChunk[glm::ivec3(chunkCoord)] = new Chunk(glm::vec3(x, 0, z));
            }
            }
        }
    }
    for (auto it = loadedChunk.begin(); it != loadedChunk.end(); ) {
        if (glm::distance(glm::vec3(it->second->position.x / Chunk::width, 0, it->second->position.z / Chunk::depth), playerPos) >= renderDistance) {
                delete it->second;
                it = loadedChunk.erase(it);
        } else {
            ++it;
        }
    }
}

void World::render(){
    texManager.bindTexture("grass");
    player->render();
    // chunk->render();
    for(auto &pair: loadedChunk){
        pair.second->render();
    }
    // for(auto &bloc : blocs){
    //     bloc->render();
    // }

}

void World::update(){
    chunkGenerationUpdate();
    player->update(blocs);
}