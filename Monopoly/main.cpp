#include "sgg\graphics.h"
#include "defines.h"
#include <string>
#include "game.h"
void update(float ms)
{
    Game* mygame = Game::getInstance();//pairnei to idio game pou arxikopoiisame ekatw
    mygame->update();
}

// The window content drawing function.
void draw()//ti na sxediasei
{
    Game* mygame = Game::getInstance();
    mygame->draw();
}

int main()
{
    graphics::createWindow(WINDOWS_WIDTH,WINDOWS_HEIGHT,"Monopoly");//arxikopoiw opoiodipote entity meta apo auti tin sunartisi
    Game* game = Game::getInstance();

   
    graphics::playMusic(std::string(ASSET_PATH) + "LoadingScreen.mp3", 0.1f, true);//arxizei me autin tin mousiki arxika kai meta allazei
    graphics::setCanvasSize(CANVAS_WIDTH,CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::setUpdateFunction(update);
    graphics::setDrawFunction(draw);
    graphics::startMessageLoop();//ola prin apo aut
    Game::releaseInstance();
    graphics::destroyWindow();
   return 0;
}