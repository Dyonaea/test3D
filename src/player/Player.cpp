#include "./Player.h"
#include "../app/App.h"

Player::Player(){
    camera = new Camera(1000, 1000, &position, &orientation);
    position.y = 40;
}

Player::~Player(){
    delete camera;
}

void Player::render(){
    camera->inputs(App::getApp()->window);
    camera->Matrix(80.0f, 0.1f, 1000.0f, App::getApp()->shader, "camMatrix");
}

void Player::update(std::unordered_map<glm::ivec3, Chunk*, ChunkCoordHash> loadedChunk){

    stop();
    velocity.y = 0;
    currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Physics::gravity(&position, &velocity, deltaTime);
    movement();
    handAction(loadedChunk);
    // collisions(loadedChunk);
    position += velocity * deltaTime;

}

void Player::movement(){
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
    if(glfwGetKey(App::getApp()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        moveDown();
    }
    
}

void Player::handAction(std::unordered_map<glm::ivec3, Chunk*, ChunkCoordHash> loadedChunk){
    glm::ivec3 chunkKey(std::floor(position.x / Chunk::width), 
                    std::floor(position.y / Chunk::height), 
                    std::floor(position.z / Chunk::depth));
    if (glfwGetMouseButton(App::getApp()->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && loadedChunk.find(chunkKey) != loadedChunk.end()) {
        // std::cout << "try to destroy block" << std::endl;
        //std::cout<<glm::abs((int)position.x % Chunk::width)<<"  "<< glm::abs((int)position.y % Chunk::height)<<"  "<<glm::abs((int)position.z % Chunk::depth)<<std::endl;
        loadedChunk[chunkKey]->destroyBlock(glm::ivec3(
                                            std::floor(position.x - chunkKey.x*Chunk::width),
                                            std::floor(position.y - chunkKey.y*Chunk::height),
                                            std::floor(position.z - chunkKey.z*Chunk::depth)));
    }
}

void Player::collisions(std::unordered_map<glm::ivec3, Chunk*, ChunkCoordHash> loadedChunk){
    int roundx = std::floor(position.x);
    int roundy = std::floor(position.y);
    int roundz = std::floor(position.z);
    for (int x = roundx-1; x <= roundx+1; x++){
        for (int y = roundy-2; y <= roundy+1; y++){
            if (y < 0){
                break;
            }
            for (int z = roundz-1; z <= roundz+1; z++){
                if (blocktype.vtRegistry[World::getBlocAt(glm::vec3(x, y, z), loadedChunk).blockID].isSolid){
                    if (Physics::AABB(posMin+ position, posMax+ position, glm::vec3(x, y, z), glm::vec3(x+1, y+1, z+1))){
                        handleCollision(Physics::sideDetect(position + posMid, glm::vec3(x+0.5f, y+0.5f, z+0.5f)));
                    }
                }
            }
        }
    }
}
