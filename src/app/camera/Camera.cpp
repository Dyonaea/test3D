#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 *position, glm::vec3 *orientation)
{
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
    Camera::orientation = orientation;
    aspect = (float)width/(float)height;

}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader *shader, const char *uniform){
   glm::mat4 view = glm::mat4(1.0f); 
   glm::mat4 projection = glm::mat4(1.0f); 

   view = glm::lookAt(*position, *position + *orientation, up);
   projection = glm::perspective(glm::radians(FOVdeg), aspect, nearPlane, farPlane);

   glUniformMatrix4fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow *window){
    
    // if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    //     *position += speed * -glm::normalize(glm::cross(*orientation, up));
    // }
    // if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    //     *position += speed * -*orientation;
    // }
    // if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    //     *position += speed * glm::normalize(glm::cross(*orientation, up));
    // }
    // if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
    //     *position += speed * up;
    // }
    // if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
    //    *position += speed * -up;
    // }
    // if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
    //     speed = 0.04f;
    // }
    // else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
    //     speed = 0.01f;
    // }



if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	if (firstClick)
	{
		glfwSetCursorPos(window, (width / 2), (height / 2));
		firstClick = false;
	}
	
	double mouseX;
	double mouseY;
	
	glfwGetCursorPos(window, &mouseX, &mouseY);
	
	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

	glm::vec3 newOrientation = glm::rotate(*orientation, glm::radians(-rotX), glm::normalize(glm::cross(*orientation, up)));

	if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		*orientation = newOrientation;
	}

	*orientation = glm::rotate(*orientation, glm::radians(-rotY), up);

	glfwSetCursorPos(window, (width / 2), (height / 2));
}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		firstClick = true;
	}
}

