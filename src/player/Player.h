#ifndef PLAYER_H
#define PLAYER_H

#include "../util/util.h"
#include "../app/camera/Camera.h"

class Player{
    private:
        Camera* camera;
        // float currentTime;
        // float lastTime;


    public:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 2.0f);
        glm::vec3 posMin = glm::vec3(-0.2f, -1.8f, -0.2f);
        glm::vec3 posMax = glm::vec3(0.2f, 0.0f, 0.2f);
        Player();
        ~Player();
        void update();
        void render();


};


#endif