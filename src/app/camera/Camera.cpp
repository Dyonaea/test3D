#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 *position)
{
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;


}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader *shader, const char *uniform){
   glm::mat4 view = glm::mat4(1.0f); 
   glm::mat4 projection = glm::mat4(1.0f); 

   view = glm::lookAt(*position, *position + orientation, up);
   projection = glm::perspective(glm::radians(FOVdeg), (float)(width/height), nearPlane, farPlane);

   glUniformMatrix4fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        *position += speed * orientation;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        *position += speed * -glm::normalize(glm::cross(orientation, up));
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        *position += speed * -orientation;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        *position += speed * glm::normalize(glm::cross(orientation, up));
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        *position += speed * up;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
       *position += speed * -up;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        speed = 0.04f;
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
        speed = 0.01f;
    }



    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    glfwSetCursorPos(window, width / 2, height / 2);

    float deltaX = static_cast<float>(mouseX - (width / 2));
    float deltaY = static_cast<float>(mouseY - (height / 2));

if (deltaX != 0 || deltaY != 0) {
    
    float rotX = sensitivity * deltaY / height;
    float rotY = sensitivity * deltaX / width;


    glm::vec3 right = glm::normalize(glm::cross(orientation, up));


    glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), right);

    float maxVerticalAngle = glm::radians(85.0f);
    if (glm::abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= maxVerticalAngle) {
        orientation = newOrientation;
    }

    orientation = glm::rotate(orientation, glm::radians(-rotY), up);

}
}
