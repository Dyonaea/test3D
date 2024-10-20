#include "World.h"

World::World(){
    init();
    texManager.loadTexture( "grass", "res/dirt.png", "specular");
}

World::~World(){
    for(auto &bloc: blocs){
        delete bloc;
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
    chunk = new Chunk(glm::vec3(0.0f, 0.0f, 0.0f));



}

void World::render(){
    
    texManager.bindTexture("grass");
    player->render();
    chunk->render();

    // for(auto &bloc : blocs){
    //     bloc->render();
    // }

}

void World::update(){
    player->update(blocs);
}