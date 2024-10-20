#include "Bloc.h"
#include "../app/App.h"


Bloc::Bloc(glm::vec3 position, TextureManager *textureManager)
:position(position), texManager(textureManager)
{
    init();
}

Bloc::~Bloc(){
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    delete vao;
    delete ebo;
    delete vbo;
}

void Bloc::init(){
    vao = new VAO();
    vao->Bind();
    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices, sizeof(indices));
    vao->LinkVBO(*vbo);
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
   

    
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // int width, height, nrChannels;
    // stbi_set_flip_vertically_on_load(true);   

    // unsigned char *data = stbi_load("./res/grassBlock.png", &width, &height, &nrChannels, 0); 
    // if (data)
    // {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else
    // {
    //     std::cout << "Failed to load texture" << std::endl;
    // }
    // stbi_image_free(data);

    // glEnable(GL_DEPTH_TEST); 
}

void Bloc::render(){
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture);
    texManager->bindTexture("grass");
    glUniform1i(glGetUniformLocation(App::getApp()->shader->ID, "texture"), 0);
    App::getApp()->shader->setVec3("position", position);
    
    glBindVertexArray(vao->ID);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void Bloc::update(){

}