#ifndef MOVABLE_H
#define MOVABLE_H

#include "../util/util.h"

class Movable{
    public:
        float speed = 20.0f;
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void moveDown();
        void jump();    
        void stop();
        void handleCollision(SIDE side);
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);    
        glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        
};


#endif