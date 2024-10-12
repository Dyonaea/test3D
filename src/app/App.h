#ifndef APP_H
#define APP_H

#include "../util/util.h"
#include "shader/shader.h"
#include "../test/Test.h"
#include "./camera/Camera.h"
#include "../player/Player.h"

class App{
    private:
        static App* appInstance;

        int nbFrames = 0;
        float lastFrame = 0.0f;

        Camera* camera;
        Test* test;
        Player* player;

        void init();
        void initWindow();
        void fpsCount();
        App();
        ~App();
    public:
        GLFWwindow* window;
        Shader* shader;
        static App* getApp();
        bool isRunning();
        void render();
        void update();
        void terminate();

};


#endif