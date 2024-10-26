#ifndef WORLD_H
#define WORLD_H

#include "../util/util.h"
#include "../player/Player.h"
#include "../app/texture/TextureManager.h"
#include "../world/Chunk.h"


class World{
    public:
        TextureManager texManager;
        std::unordered_map<glm::ivec3, Chunk*, ChunkCoordHash> loadedChunk;
        int renderDistance = 5;

        World();
        ~World();
        void init();
        void render();
        void update();
        void chunkGenerationUpdate();

    private:
        Player* player;
        std::vector<Bloc*> blocs;
        Chunk* chunk;


};



#endif