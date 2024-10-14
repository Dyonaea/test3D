#ifndef PHYSICS_H
#define PHYSICS_H

#include "../util/util.h"
#include "../app/App.h"



class Physics{
    private:
        static const float G;
        static const float maxVelocity;

    public:
        static bool AABB(const glm::vec3 v1min, const glm::vec3 v1max, const glm::vec3 v2min, const glm::vec3 v2max);
        
        static void gravity(glm::vec3 *position, glm::vec3 *velocity, float deltaTime);

        static SIDE sideDetect(const glm::vec3 v1, glm::vec3 v2);
};

#endif