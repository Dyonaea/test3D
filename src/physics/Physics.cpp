#include "Physics.h"

const float Physics::G  = -9.8f;
const float Physics::maxVelocity = -10.0f;

bool Physics::AABB(const glm::vec3 v1min, const glm::vec3 v1max, const glm::vec3 v2min, const glm::vec3 v2max){
    return (
        v1max.x > v2min.x &&
        v1min.x < v2max.x &&
        v1max.y > v2min.y &&
        v1min.y < v2max.y &&
        v1max.z > v2min.z &&
        v1min.z < v2max.z);
}

void Physics::gravity(glm::vec3 *position, glm::vec3 *velocity, float deltaTime){
    velocity->y += G * deltaTime;
    if(velocity->y < maxVelocity){
        velocity->y = maxVelocity;
    }
    if(position->y <= 1.8f){
        position->y = 1.8f;
        velocity->y = 0;
    }
}

