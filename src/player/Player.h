#ifndef PLAYER_H
#define PLAYER_H

#include "../util/util.h"
#include "../app/camera/Camera.h"
#include "../physics/Movable.h"
#include "../test/Test.h"

class Player: public Movable{
    private:
        Camera* camera;
        float currentTime;
        float lastTime;


    public:
        glm::vec3 posMin = glm::vec3(-0.2f, -1.8f, -0.2f);
        glm::vec3 posMax = glm::vec3(0.2f, 0.0f, 0.2f);
        glm::vec3 posMid = glm::vec3(0.0f, -0.9f, 0.0f);
        Player();
        ~Player();
        void update(std::vector<Test*> blocs);
        void render();
        void movement(float deltaTime);

};


#endif