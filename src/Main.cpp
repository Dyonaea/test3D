#include  "./app/app.h"

int main(){
    while(App::getApp()->isRunning()){
      
        App::getApp()->update();
        App::getApp()->render();
    }
    return EXIT_SUCCESS;
}