#include "./Player.h"
#include "../app/App.h"

Player::Player(){
    camera = new Camera(1000, 1000, &position, &orientation);
}

Player::~Player(){
    delete camera;
}

void Player::render(){
    camera->inputs(App::getApp()->window);
    camera->Matrix(70.0f, 0.1f, 100.0f, App::getApp()->shader, "camMatrix");
}

void Player::update(std::vector<Test*> blocs){
    stop();
    currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    Physics::gravity(&position, &velocity, deltaTime);
    movement(deltaTime);
    for (auto &bloc : blocs){
        if(Physics::AABB( posMin+ position, posMax+ position, bloc->posMin+ bloc->position, bloc->posMax+ bloc->position)){
            handleCollision(Physics::sideDetect(position + posMid, bloc->position + bloc->posMid));

        }
    }
    position += velocity * deltaTime;
}

void Player::movement(float deltaTime){
    if(glfwGetKey(App::getApp()->window, GLFW_KEY_SPACE) == GLFW_PRESS){
        jump();
    }
    if(glfwGetKey(App::getApp()->window, GLFW_KEY_W) == GLFW_PRESS){
        moveForward();
    }
    if(glfwGetKey(App::getApp()->window, GLFW_KEY_S) == GLFW_PRESS){
        moveBackward();
    }
    if(glfwGetKey(App::getApp()->window, GLFW_KEY_D) == GLFW_PRESS){
        moveLeft();
    }
    if(glfwGetKey(App::getApp()->window, GLFW_KEY_A) == GLFW_PRESS){
        moveRight();
    }
    
}
