#include "Framework.h"
class MyFramework : public Framework {
    public:
    
        virtual void PreInit(int& width, int& height, bool& fullscreen)
        {
            width = 320;
            height = 200;
            fullscreen = false;
        }
    
        virtual bool Init() {
            //createSprite("/Users/dinozyavier/Desktop/DinoGame/DinoGame/data");
            return true;
        }
    
        virtual void Close() {
    
        }
    
        virtual bool Tick() {
            drawTestBackground();
            drawSprite(createSprite("/Users/dinozyavier/Desktop/DinoGame/DinoGame/data/avatar.jpg"), 0, 0);
            return false;
        }
    
        virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
    
        }
    
        virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
    
        }
    
        virtual void onKeyPressed(FRKey k) {
        }
    
        virtual void onKeyReleased(FRKey k) {
        }
    };
    
    int main(int argc, char *argv[])
    {
        run(new MyFramework);
        return 0;
    }
