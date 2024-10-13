#include "./Movable.h"

void Movable::stop(){
    velocity.x = 0.0f;
    velocity.z = 0.0f;
}

void Movable::jump(){
    velocity.y = 5.0f;
}

void Movable::moveForward(){
    glm::vec3 flat_orientation = glm::normalize(glm::vec3(orientation.x, 0.0f, orientation.z));
    velocity.x += speed * flat_orientation.x;
    velocity.z += speed * flat_orientation.z;
    std::cout<<"ox:"<<orientation.x<<std::endl;
    std::cout<<"oz:"<<orientation.z<<std::endl;
}

void Movable::moveBackward(){
    glm::vec3 flat_orientation = glm::normalize(glm::vec3(orientation.x, 0.0f, orientation.z));
    velocity.x += speed * -flat_orientation.x;
    velocity.z += speed * -flat_orientation.z;
    std::cout<<"ox:"<<orientation.x<<std::endl;
    std::cout<<"oz:"<<orientation.z<<std::endl;
}

void Movable::moveLeft(){
    glm::vec3 flat_orientation = glm::normalize(glm::vec3(orientation.x, 0.0f, orientation.z));
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 left = glm::normalize(glm::cross(up, flat_orientation));
    velocity.x += -speed * left.x; 
    velocity.z += -speed * left.z; 
}


void Movable::moveRight(){
    glm::vec3 flat_orientation = glm::normalize(glm::vec3(orientation.x, 0.0f, orientation.z));
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 left = glm::normalize(glm::cross(up, flat_orientation));
    velocity.x += speed * left.x; 
    velocity.z += speed * left.z; 
}