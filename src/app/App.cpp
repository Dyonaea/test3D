#include "App.h"

App* App::appInstance = nullptr;

App* App::getApp(){
    if (appInstance == nullptr) {
        appInstance = new App();
    }
    return appInstance;
}


void App::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->window = glfwCreateWindow(1000, 1000, "hello x)", NULL, NULL);
    if(this->window == NULL){
        std::cout<<"problem occured during window creation" << std::endl;
        this->terminate();
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
    std::cerr << "Failed to initialize GLAD!" << std::endl;
    this->terminate();
    exit(EXIT_FAILURE);
    }
    glViewport(0, 0, 1000, 1000);
}


void App::init(){
    initWindow();
    shader = new Shader("./src/app/shader/default.vert", "./src/app/shader/default.frag");
    test = new Test();
    
    camera = new Camera(1000, 1000, glm::vec3(0.0f, 0.0f, 2.0f));
}

void App::fpsCount(){
    float currentFrame = static_cast<float>(glfwGetTime());
    nbFrames++;
    if(currentFrame - lastFrame >= 1.0f){
        std::stringstream ss;
        ss << "x) -FPS: " << std::to_string(nbFrames); 
        glfwSetWindowTitle(window, ss.str().c_str());
        nbFrames = 0;
        lastFrame += 1.0f;
    }
}

void App::update(){
    fpsCount();
    glfwPollEvents();
}
void App::render(){

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   

    shader->use();
    camera->inputs(window);
    camera->Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

    test->render();
    glfwSwapBuffers(window);
}

App::App(){
    init();
    std::cout<<"ahh"<<std::endl;
}

App::~App(){
    terminate();
    delete test;
    delete camera;
}

void App::terminate(){
    shader->terminate(); 
    if (appInstance != nullptr) {
        delete appInstance;
        appInstance = nullptr;
    }
    glfwDestroyWindow(window);
    glfwTerminate();  
}


bool App::isRunning(){
    return !glfwWindowShouldClose(window);
}