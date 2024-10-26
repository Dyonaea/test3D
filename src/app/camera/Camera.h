#ifndef CAMERA_H
#define CAMERA_H

#include "../../util/util.h"
#include "../shader/shader.h"


class Camera{
    
    private:
        bool firstClick = true;

    public:
        glm::vec3 *position;
        glm::vec3 *orientation;
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        float aspect;
        int width;
        int height;
        float speed = 0.1f;
        float sensitivity = 3.0f;

        Camera(int width, int height, glm::vec3 *position, glm::vec3 *orientation);

        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader *shader, const char *uniform);
        void inputs(GLFWwindow *window);
};

#endif