#ifndef MOVABLE_H
#define MOVABLE_H

#include "../util/util.h"

class Movable{
    public:
        float speed = 3.0;
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void jump();    
        void stop();
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);    
        glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        
};


#endif