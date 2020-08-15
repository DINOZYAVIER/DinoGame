#include <iostream>
#include "Framework.h"
#include "cstring"
#include <stdlib.h>

const int max_x = 1600;
const int max_y = 900;
const int default_amount_of_enemies = 3;
const int default_amount_of_bullets = 3;

class MyFramework : public Framework {
    public:
    
    MyFramework (int xres, int yres, int mapsize_x, int mapsize_y, int amount_of_enemies, int amount_of_bullets) :
    xres(xres), yres(yres), mapsize_x(mapsize_x), mapsize_y(mapsize_y), amount_of_enemies(amount_of_enemies), amount_of_bullets(amount_of_bullets) {}
    
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
    int mapsize_x = 0;
    int mapsize_y = 0;
    int amount_of_enemies = 0;
    int amount_of_bullets = 0;
    };
    
void paramCheck(int &xres, int &yres, int &mapsize_x, int &mapsize_y, int &amount_of_enemies, int &amount_of_bullets,
                int argc, char *argv[]);

int main(int argc, char *argv[])
{
	int xres = 1440,
        	yres = 720,
        	mapsize_x  = 800,
		mapsize_y = 800,
        	amount_of_enemies = 0,
        	amount_of_bullets = 0;

        paramCheck(xres, yres, mapsize_x, mapsize_y, amount_of_enemies, amount_of_bullets, argc, argv);
        
    	MyFramework* gameFramework = new MyFramework(xres, yres, mapsize_x, mapsize_y, amount_of_enemies, amount_of_bullets);
  
  	run(gameFramework);
	return 0;
}

void paramCheck(int &xres, int &yres, int &mapsize_x, int &mapsize_y, int &amount_of_enemies, int &amount_of_bullets,
                int argc, char *argv[])
{
	std::cout << argc << std::endl;
	for (int i = 0; i < argc; ++i)
		std::cout << argv[i] << std::endl;

	for (int i = 1; i < argc; ++i)
   	{
		if (!strcmp("-window", argv[i]))	
		{
			std::cout << "-window ";
			char str[strlen(argv[++i]) / 2];

		       	//here we obtain the x coord and convert from cstring to int
			int xpos = (int)(strchr(argv[i], 'x') - argv[i]);
           		for (int j = 0; j < xpos; ++j)
               			str[j] = argv[i][j];
			xres = atoi(str);
            
            		//here we obtain y coord and convert from cstring to int
            		for (int j = xpos + 1; argv[i][j] != '\0'; ++j)
                		str[j - xpos - 1] = argv[i][j];
            		yres = atoi(str);

			std::cout << xres << " ";
			std::cout << yres << std::endl;
    		}

		if (!strcmp("-map", argv[i]))
		{
			std::cout << "-map ";
			char str[strlen(argv[++i]) / 2];

		       	//here we obtain the x coord and convert from cstring to int
			int xpos = (int)(strchr(argv[i], 'x') - argv[i]);
           		for (int j = 0; j < xpos; ++j)
               			str[j] = argv[i][j];
			mapsize_x = atoi(str);
            
            		//here we obtain y coord and convert from cstring to int
            		for (int j = xpos + 1; argv[i][j] != '\0'; ++j)
                		str[j - xpos - 1] = argv[i][j];
            		mapsize_y = atoi(str);

			std::cout << mapsize_x << " ";
			std::cout << mapsize_y << std::endl;
		}

		if (!strcmp("-num_enemies", argv[i]))
		{
			std::cout << "-num_enemies ";
			amount_of_enemies = atoi(argv[++i]);
			std::cout << amount_of_enemies << std::endl;
		}

		if (!strcmp("-num_ammo", argv[i]))
		{
			std::cout << "-num_ammo ";
			amount_of_bullets = atoi(argv[++i]);
			std::cout << amount_of_bullets << std::endl;
		}

		
	}

	if (xres >  max_x || yres > max_y)	
	{
		xres = max_x;
		yres = max_y;
	}

	if (mapsize_x < xres || mapsize_y < yres)
	{
		mapsize_x = xres;
		mapsize_y = yres;
	}

	if (amount_of_enemies < 0 || amount_of_bullets < 0)
	{
		amount_of_enemies = default_amount_of_enemies;
		amount_of_bullets = default_amount_of_bullets;
	}	
}
