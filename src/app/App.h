#ifndef APP_H
#define APP_H

#include "../util/util.h"
#include "shader/shader.h"
#include "../world/Bloc.h"
#include "./camera/Camera.h"
#include "../player/Player.h"
#include "../physics/Physics.h"
#include "../world/World.h"


class App{
    private:
        static App* appInstance;
        std::vector<Bloc*> blocs;

        int nbFrames = 0;
        float lastFrame = 0.0f;
        Player* player;
        World* world;

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