#include <iostream>
#include "Framework.h"
#include "cstring"
#include <stdlib.h>

const int max_x = 1444;
const int max_y = 1280;
const int default_amount_of_enemies = 3;
const int default_amount_of_bullets = 3;
const int safe_margin = 150;

const int AMOUNT_OF_SPRITES = 4;
const int PLAYER_SPRITE = 0;
const int ENEMY_SPRITE = 1;
const int BULLET_SPRITE = 2;
const int BACKGROUND_SPRITE = 3;

const int PLAYER_SPEED = 20;

class MyFramework : public Framework {

public:
	class Entities {
	
	public:
		void SpriteInit()
		{
			spriteArray[PLAYER_SPRITE] = createSprite("/Users/dinozyavier/Desktop/godplease/data/steve.jpeg");
			spriteArray[ENEMY_SPRITE] = createSprite("/Users/dinozyavier/Desktop/godplease/data/creeper.png");
			spriteArray[BULLET_SPRITE] = createSprite("/Users/dinozyavier/Desktop/godplease/data/fire_charge.png");
			spriteArray[BACKGROUND_SPRITE] = createSprite("/Users/dinozyavier/Desktop/godplease/data/background.png");


			getSpriteSize(spriteArray[PLAYER_SPRITE], spriteSize[PLAYER_SPRITE][0], spriteSize[PLAYER_SPRITE][1]);
			getSpriteSize(spriteArray[ENEMY_SPRITE], spriteSize[ENEMY_SPRITE][0], spriteSize[ENEMY_SPRITE][1]);
			getSpriteSize(spriteArray[BULLET_SPRITE], spriteSize[BULLET_SPRITE][0], spriteSize[BULLET_SPRITE][1]);
			getSpriteSize(spriteArray[BACKGROUND_SPRITE], spriteSize[BACKGROUND_SPRITE][0], spriteSize[BACKGROUND_SPRITE][1]);

		}

		Entities (MyFramework& fr) 
		{			
			enemies_quantity = fr.amount_of_enemies;
			bullets_quantity = fr.amount_of_bullets;

			//array of enemies' positions
			enemies_pos = new int* [fr.amount_of_enemies];
			for (int i = 0; i < fr.amount_of_enemies; ++i)
				enemies_pos[i] = new int [2];
			
			//array of bullets' positions
			bullets_pos = new int* [fr.amount_of_bullets];
			for (int i = 0; i < fr.amount_of_bullets; ++i)
				enemies_pos[i] = new int [2];
		}

		~Entities() {

		//	for (int i = 0; i < enemies_quantity; ++i)
		//		delete [] enemies_pos[i];
		//	delete enemies_pos;

		//	for (int i = 0; i < bullets_quantity; ++i)
		//		delete [] bullets_pos[i];
		//	delete bullets_pos;

		}
		void PositionFill(MyFramework& fr)
		{

			SpriteInit();
	
			//player's position
			player_pos[0][0] = (fr.xres - spriteSize[PLAYER_SPRITE][0]) / 2;
			player_pos[0][1] = (fr.yres - spriteSize[PLAYER_SPRITE][1]) / 2;

			dx = 0;
			dy = 0;

			xlimit = (fr.mapsize_x - fr.xres) / 2;
			ylimit = (fr.mapsize_y - fr.yres) / 2;

			//here we fill enemies' position
			for (int i = 0; i < fr.amount_of_enemies; ++i)
			{
				do {

					enemies_pos[i][0] = rand() % (fr.mapsize_x - spriteSize[ENEMY_SPRITE][0]);
					enemies_pos[i][1] = rand() % (fr.mapsize_y - spriteSize[ENEMY_SPRITE][1]);

					if ((enemies_pos[i][0] < player_pos[0][0] && enemies_pos[i][0] < player_pos[0][0] - safe_margin)
						       	|| (enemies_pos[i][0] > player_pos[0][0] && enemies_pos[i][0] > player_pos[0][0] + safe_margin)
							|| (enemies_pos[i][1] < player_pos[0][1] && enemies_pos[i][1] < player_pos[0][1] - safe_margin)
							|| (enemies_pos[i][1] > player_pos[0][1] && enemies_pos[i][1] > player_pos[0][1] + safe_margin))
						break;
					else
						continue;
				} while (1);
			}
		}


		void DisplayEntities(MyFramework& fr)
		{
			drawSprite (spriteArray[PLAYER_SPRITE], player_pos[0][0], player_pos[0][1]);
			for (int i = 0; i < fr.amount_of_enemies; ++i)
				drawSprite(spriteArray[ENEMY_SPRITE], enemies_pos[i][0], enemies_pos[i][1]);
		}

		void makeBackground(MyFramework& fr) {

			for (int i = 0; i < fr.mapsize_x; i += spriteSize[BACKGROUND_SPRITE][0])
				for (int j = 0; j < fr.mapsize_y; j += spriteSize[BACKGROUND_SPRITE][1])
					drawSprite(spriteArray[BACKGROUND_SPRITE], i, j);
		}

		void playerMove (MyFramework& fr, FRKey k) {

			switch(k)
			{
				case FRKey::LEFT:

					if (dx > -xlimit)
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][0] += PLAYER_SPEED;
				
						dx -= PLAYER_SPEED;
					}
					else
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][0] -= xlimit + dx;
						dx = -xlimit;
					}	
					break;

				case FRKey::RIGHT:

					if (dx < xlimit)
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][0] -= PLAYER_SPEED;
				
						dx += PLAYER_SPEED;
					}
					else
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][0] += dx - xlimit;
						dx = xlimit;
					}
					break;

				case FRKey::DOWN:

					if (dy < ylimit)
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][1] -= PLAYER_SPEED;
				
						dy += PLAYER_SPEED;
					}
					else
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][1] -= dy - ylimit;
						dy = ylimit;
					}
					break;

				case FRKey::UP:
					if (dy > -ylimit)
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][1] += PLAYER_SPEED;
				
						dy -= PLAYER_SPEED;
					}
					else
					{
						for (int i = 0; i < enemies_quantity; ++i)
							enemies_pos[i][1] += ylimit + dy;
						dy = -ylimit;
					}
					break;

				default:
					break;
			}


		}
	private:
		//here I try to implement data oriented design (structure of arrays instead of array of structures) 
		int player_pos[1][2];
		int **enemies_pos;
		int **bullets_pos;
		Sprite* spriteArray[AMOUNT_OF_SPRITES];
		int spriteSize[AMOUNT_OF_SPRITES][2];
		int dx;
		int dy;
		int xlimit;
		int ylimit;
		int enemies_quantity;
		int bullets_quantity;
		bool moveFlag[4];
	};

    void ParamCheck (int argc, char *argv[]);

    MyFramework (int argc, char *argv[])
    {
	ParamCheck(argc, argv);

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

	ent = new Entities(*this);
    }


    
        virtual void PreInit(int& width, int& height, bool& fullscreen) {
		
        	width = xres;
        	height = yres;
        	fullscreen = false;
        }
    
        virtual bool Init() {

		ent->PositionFill(*this);
            	return true;
        }
    
        virtual void Close() {
		//delete ent; 
        }
    
        virtual bool Tick() {
		ent->makeBackground(*this);
		ent->DisplayEntities(*this);
            	return ShouldStop;
        }
    
        virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

        }
    
        virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
    
        }
    
        virtual void onKeyPressed(FRKey k) {

		ent->playerMove(*this, k);
			
	}
    
        virtual void onKeyReleased(FRKey k) {
	}




	int get_xres() { return xres; }

	int get_yres() { return xres; }

	int get_mapsize_x() { return mapsize_x; }

	int get_mapsize_y() { return mapsize_y; }

	int get_amount_of_enemies() { return amount_of_enemies; }

	int get_amount_of_bullets() { return amount_of_bullets; }
    
private:
    int xres = 800;
    int yres = 600;
    int mapsize_x = 0;
    int mapsize_y = 0;
    int amount_of_enemies = 0;
    int amount_of_bullets = 0;
    Entities *ent;
    bool ShouldStop = false;
};
    

int main(int argc, char *argv[])
{
    	MyFramework* gameFramework = new MyFramework(argc, argv);
  
  	run(gameFramework);
	return 0;
}

void MyFramework::ParamCheck(int argc, char *argv[])
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


}
