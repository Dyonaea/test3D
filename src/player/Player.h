#ifndef PLAYER_H
#define PLAYER_H

#include "../util/util.h"
#include "../app/camera/Camera.h"

class Player{
    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 2.0f);
        Camera* camera;

    public:
        Player();
        ~Player();
        void update();
        void render();


};


#endif