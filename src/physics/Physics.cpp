#include "Physics.h"

const float Physics::G  = -40.8f;
const float Physics::maxVelocity = -30.0f;

bool Physics::AABB(const glm::vec3 v1min, const glm::vec3 v1max, const glm::vec3 v2min, const glm::vec3 v2max){
    return (
        v1max.x > v2min.x &&
        v1min.x < v2max.x &&
        v1max.y > v2min.y &&
        v1min.y < v2max.y &&
        v1max.z > v2min.z &&
        v1min.z < v2max.z);
}

SIDE Physics::sideDetect(const glm::vec3 v1, const glm::vec3 v2) {
    glm::vec3 gap = v1 - v2;
    if(gap.y >= 0){
        if((gap.y - (0.9f - 0.3f) > glm::abs(gap.x) && gap.y - (0.9f - 0.3f) > glm::abs(gap.z))){
            return UP;
        }
    }
    else{
         if(gap.y + (0.9f - 0.3f) < (-glm::abs(gap.x)) && gap.y + (0.9f - 0.3f) < (-glm::abs(gap.z))){
            return DOWN;
         }
    }
    if(glm::abs(gap.x) >= glm::abs(gap.z)) {
        if(gap.x > 0) {
            return RIGHT;
        }
        return LEFT;
    }
    else {
         if(gap.z > 0) {
            return FACE;
         }
         return BACK;
    }
}

void Physics::gravity(glm::vec3 *position, glm::vec3 *velocity, float deltaTime){
    velocity->y += G * deltaTime;
    if(velocity->y < maxVelocity){
        velocity->y = maxVelocity;
    }
}

