#include "./Player.h"
#include "../app/App.h"

Player::Player(){
    camera = new Camera(1000, 1000, &position);
}

Player::~Player(){
    delete camera;
}

void Player::render(){
    camera->inputs(App::getApp()->window);
    camera->Matrix(45.0f, 0.1f, 100.0f, App::getApp()->shader, "camMatrix");
}

void Player::update(){
    
}