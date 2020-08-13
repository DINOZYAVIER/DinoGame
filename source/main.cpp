#include "Framework.h"
#include "cstring"
#include <stdlib.h>

class MyFramework : public Framework {
    public:
    
    MyFramework (int xres, int yres, int mapsize, int amount_of_enemies, int amount_of_bullets) :
    xres(xres), yres(yres), mapsize(mapsize), amount_of_enemies(amount_of_enemies), amount_of_bullets(amount_of_bullets) {}
    
        virtual void PreInit(int& width, int& height, bool& fullscreen)
        {
            width = xres;
            height = yres;
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
    
private:
    int xres = 0;
    int yres = 0;
    int mapsize = 0;
    int amount_of_enemies = 0;
    int amount_of_bullets = 0;
    };
    
bool paramCheck(int &xres, int &yres, int &mapsize, int &amount_of_enemies, int &amount_of_bullets,
                int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int xres = 1440,
        yres = 720,
        mapsize  = 800,
        amount_of_enemies = 0,
        amount_of_bullets = 0;
        
    paramCheck(xres, yres, mapsize, amount_of_enemies, amount_of_bullets, argc, argv);
        
        
    MyFramework* gameFramework = new MyFramework(xres, yres, mapsize, amount_of_enemies, amount_of_bullets);
        
    run(gameFramework);
    return 0;
}

bool paramCheck(int &xres, int &yres, int &mapsize, int &amount_of_enemies, int &amount_of_bullets,
                int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-window"))
        {
            char str[strlen(argv[i+1]) / 2];
            
            //here we obtain the x coord and convert from cstring to int
            int j = 0;
            for ( ; argv[i][j] != 'x'; ++j)
                str[j] = argv[i][j];
            j++;
            xres = atoi(str);
            
            //here we clean str var from previous coord in case x and y have different places
            for (int k = 0; k < strlen(argv[i+1]) / 2; ++k)
                str[k] = '\0';
            
            //here we obtain y coord and convert from cstring to int
            for (int k = 0; argv[i][j] != '\0'; ++j)
                str[k] = argv[i][j];
            yres = atoi(str);
        }
    }
    
    if(1440 < xres || 1600 < yres || mapsize > xres || mapsize > yres || 0 > mapsize || 0 > amount_of_bullets)
        return true;
    else
        return false;
}
