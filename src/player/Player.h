#ifndef PLAYER_H
#define PLAYER_H

#include "../util/util.h"
#include "../app/camera/Camera.h"
#include "../physics/Movable.h"
#include "../world/Bloc.h"
#include "../world/Chunk.h"
#include "../world/BlocType.h"

class Player: public Movable{
    private:
        Camera* camera;
        float currentTime;
        float lastTime;
        BlocType blocktype;

    public:
        glm::vec3 posMin = glm::vec3(-0.2f, -1.8f, -0.2f);
        glm::vec3 posMax = glm::vec3(0.2f, 0.0f, 0.2f);
        glm::vec3 posMid = glm::vec3(0.0f, -0.9f, 0.0f);
        Player();
        ~Player();
        void update(std::unordered_map<glm::ivec3, Chunk*, ChunkCoordHash> loadedChunk);
        void render();
        void movement();

        void handAction(std::unordered_map<glm::ivec3, Chunk*, ChunkCoordHash> loadedChunk);
        void collisions(std::unordered_map<glm::ivec3, Chunk*, ChunkCoordHash> loadedChunk);
};


#endif