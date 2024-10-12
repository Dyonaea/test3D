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



static double lastMouseX = width / 2;
static double lastMouseY = height / 2;

// Get the current cursor position
double mouseX, mouseY;
glfwGetCursorPos(window, &mouseX, &mouseY);

// Calculate the mouse movement
float deltaX = static_cast<float>(mouseX - lastMouseX);
float deltaY = static_cast<float>(mouseY - lastMouseY);

// Update the last mouse position for the next frame
lastMouseX = mouseX;
lastMouseY = mouseY;

// Sensitivity can be adjusted based on your preferences
float rotX = sensitivity * deltaY / height; // Vertical rotation
float rotY = sensitivity * deltaX / width;  // Horizontal rotation

if (deltaX != 0 || deltaY != 0) {
    // Compute the right vector based on the current orientation
    glm::vec3 right = glm::normalize(glm::cross(orientation, up));

    // Rotate around the right vector for vertical movement
    glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), right);

    // Limit vertical rotation
    float maxVerticalAngle = glm::radians(85.0f);
    float angle = glm::angle(newOrientation, up);
    if (angle <= maxVerticalAngle || angle >= (3.14159f - maxVerticalAngle)) {
        orientation = newOrientation;
    }

    // Rotate around the up vector for horizontal movement
    orientation = glm::rotate(orientation, glm::radians(-rotY), up);
}

// Reset the cursor to the center after processing movement
glfwSetCursorPos(window, width / 2, height / 2);

}

