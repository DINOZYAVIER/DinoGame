
#include <iostream>
#include "stdlib.h"
#include "math.h"
#include "cstring"
#include "Framework.h"

const int max_x = 1444;
const int max_y = 1280;
const int default_amount_of_enemies = 3;
const int default_amount_of_bullets = 3;

const int safe_margin = 150;
const int AMOUNT_OF_SPRITES = 5;
const int PLAYER_SPRITE = 0;
const int ENEMY_SPRITE = 1;
const int BULLET_SPRITE = 2;
const int BACKGROUND_SPRITE = 3;
const int CROSSHAIR_SPRITE = 4;

const int PLAYER_SPEED = 20;
int ENEMY_SPEED = rand() % 10;
const int BULLET_SPEED = 5;


class Entities {

public:
   void SpriteInit()  {
       
       spriteArray[PLAYER_SPRITE] = createSprite("../data/steve.jpeg");
       spriteArray[ENEMY_SPRITE] = createSprite("../data/creeper.png");
       spriteArray[BULLET_SPRITE] = createSprite("../data/fire_charge.png");
       spriteArray[BACKGROUND_SPRITE] = createSprite("../data/background.png");
       spriteArray[CROSSHAIR_SPRITE] = createSprite("../data/crosshair.png");


       getSpriteSize(spriteArray[PLAYER_SPRITE], spriteSize[PLAYER_SPRITE][0], spriteSize[PLAYER_SPRITE][1]);
       getSpriteSize(spriteArray[ENEMY_SPRITE], spriteSize[ENEMY_SPRITE][0], spriteSize[ENEMY_SPRITE][1]);
       getSpriteSize(spriteArray[BULLET_SPRITE], spriteSize[BULLET_SPRITE][0], spriteSize[BULLET_SPRITE][1]);
       getSpriteSize(spriteArray[BACKGROUND_SPRITE], spriteSize[BACKGROUND_SPRITE][0], spriteSize[BACKGROUND_SPRITE][1]);
       getSpriteSize(spriteArray[CROSSHAIR_SPRITE], spriteSize[CROSSHAIR_SPRITE][0], spriteSize[CROSSHAIR_SPRITE][1]);

   }

   void SpriteDestroy() {
       
        for (int i = 0; i < AMOUNT_OF_SPRITES; ++i)
            destroySprite(spriteArray[i]);

        
   }

   Entities (int enemies, int bullets, int map_x, int map_y) {
       
           enemies_quantity = enemies;
           bullets_quantity = bullets;
           mapsize_x = map_x;
           mapsize_y = map_y;

           //array of enemies' positions
           enemies_pos = new int* [enemies_quantity];
           for (int i = 0; i < enemies_quantity; ++i)
           {
               enemies_pos[i] = new int [2];
               enemies_pos[i][0] = 0;
               enemies_pos[i][1] = 0;
           }
           

           //array of bullets' positions
           bullets_pos = new float* [bullets_quantity];
           for (int i = 0; i < bullets_quantity; ++i)
           {
               bullets_pos[i] = new float [2];
               bullets_pos[i][0] = 0;
               bullets_pos[i][1] = 0;
           }

           //array of bullets' directions
           bullets_dir = new float* [bullets_quantity];
           for (int i = 0; i < bullets_quantity; ++i)
           {
               bullets_dir[i] = new float [2];
               bullets_dir[i][0] = 0;
               bullets_dir[i][1] = 0;
           }
           
           bullets_flag = new bool [bullets_quantity];
           for (int i = 0; i < bullets_quantity; ++i)
               bullets_flag[i] = false;
   }

   ~Entities() {

           for (int i = 0; i < enemies_quantity; ++i)
               delete [] enemies_pos[i];
           delete []  enemies_pos;

           for (int i = 0; i < bullets_quantity; ++i)
               delete [] bullets_pos[i];
           delete [] bullets_pos;

           for (int i = 0; i < bullets_quantity; ++i)
               delete [] bullets_dir[i];
           delete [] bullets_dir;

           delete [] bullets_flag;

   }

   void PositionFill(int xres, int yres) {

           SpriteInit();

           //player's position
           player_pos[0][0] = (xres - spriteSize[PLAYER_SPRITE][0]) / 2;
           player_pos[0][1] = (yres - spriteSize[PLAYER_SPRITE][1]) / 2;

           dx = 0;
           dy = 0;

           xlimit = (mapsize_x - xres) / 2;
           ylimit = (mapsize_y - yres) / 2;

           //here we fill enemies' position
           for (int i = 0; i < enemies_quantity; ++i)
           {
               do {

                   enemies_pos[i][0] = rand() % (mapsize_x - spriteSize[ENEMY_SPRITE][0]);
                   enemies_pos[i][1] = rand() % (mapsize_y - spriteSize[ENEMY_SPRITE][1]);

                   if ((!isOccupied(enemies_pos[i][0], enemies_pos[i][1], i, i)  && ((enemies_pos[i][0] < player_pos[0][0] && enemies_pos[i][0] < player_pos[0][0] - safe_margin)
                               || (enemies_pos[i][0] > player_pos[0][0] && enemies_pos[i][0] > player_pos[0][0] + safe_margin)
                           || (enemies_pos[i][1] < player_pos[0][1] && enemies_pos[i][1] < player_pos[0][1] - safe_margin)
                           || (enemies_pos[i][1] > player_pos[0][1] && enemies_pos[i][1] > player_pos[0][1] + safe_margin))))
                       break;
                   else
                       continue;
           } while (1);
           }
   }

   void DisplayEntities()
   {
       drawSprite (spriteArray[PLAYER_SPRITE], player_pos[0][0], player_pos[0][1]);
       for (int i = 0; i < enemies_quantity; ++i)
           drawSprite(spriteArray[ENEMY_SPRITE], enemies_pos[i][0], enemies_pos[i][1]);
   }

   void makeBackground() {

       for (int i = 0; i < mapsize_x; i += spriteSize[BACKGROUND_SPRITE][0])
           for (int j = 0; j < mapsize_y; j += spriteSize[BACKGROUND_SPRITE][1])
               drawSprite(spriteArray[BACKGROUND_SPRITE], i, j);
   }

   void displayCrosshair() {
       
       drawSprite(spriteArray[CROSSHAIR_SPRITE], crosshair_pos[0][0] - spriteSize[CROSSHAIR_SPRITE][0] / 2, crosshair_pos[0][1] - spriteSize[CROSSHAIR_SPRITE][1] / 2);
   }

   void displayBullets() {
       for (int i = 0; i < bullet_count; ++i)
       {
           if (bullets_flag[i])
               drawSprite(spriteArray[BULLET_SPRITE], (int)bullets_pos[i][0], (int)bullets_pos[i][1]);
       }
   }

   void playerShoot() {
       
       if (bullet_count == bullets_quantity)
           bullet_count = 0;

       bullets_flag[bullet_count] = true;

       bullets_pos[bullet_count][0] = (float) player_pos[0][0];
       bullets_pos[bullet_count][1] = (float) player_pos[0][1];
       bullets_dir[bullet_count][0] = (float) (crosshair_pos[0][0] - bullets_pos[bullet_count][0]);
       bullets_dir[bullet_count][1] = (float) (crosshair_pos[0][1] - bullets_pos[bullet_count][1]);

       float length = sqrtf(bullets_dir[bullet_count][0] * bullets_dir[bullet_count][0] + bullets_dir[bullet_count][1] * bullets_dir[bullet_count][1]);
       bullets_dir[bullet_count][0] /= length;
       bullets_dir[bullet_count][1] /= length;

       ++bullet_count;

   }

   void bulletMove() {
       
       for (int i = 0; i < bullets_quantity; ++i)
       {
           if (bullets_flag[i])
           {
               bullets_pos[i][0] = bullets_pos[i][0] + bullets_dir[i][0] * BULLET_SPEED;
               bullets_pos[i][1] = bullets_pos[i][1] + bullets_dir[i][1] * BULLET_SPEED;
               if (bullets_pos[i][0] < 0 || bullets_pos[i][0] > mapsize_x || bullets_pos[i][1] < 0 || bullets_pos[i][1] > mapsize_y)
               {

                   bullets_flag[i] = false;
               }
           }
       }
   }

   void playerMove (FRKey k) {

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

   void enemyMove() {
       
       for (int i = 0; i < enemies_quantity; ++i)
       {

           if ((player_pos[0][0] > enemies_pos[i][0]) && !isOccupied(enemies_pos[i][0] + 1, enemies_pos[i][1], enemies_quantity, i))
               ++enemies_pos[i][0];
           
           if ((player_pos[0][0] < enemies_pos[i][0]) && !isOccupied(enemies_pos[i][0] - 1, enemies_pos[i][1], enemies_quantity, i))
               --enemies_pos[i][0];

           if ((player_pos[0][1] > enemies_pos[i][1]) && !isOccupied(enemies_pos[i][0], enemies_pos[i][1] + 1, enemies_quantity, i))
               ++enemies_pos[i][1];

           if ((player_pos[0][1] < enemies_pos[i][1]) && !isOccupied(enemies_pos[i][0], enemies_pos[i][1] - 1, enemies_quantity, i))
               --enemies_pos[i][1];

       }
   }

   bool isOccupied(int x, int y, int num, int limit) {
       
       for (int i = 0; i < num; ++i)
       {

           if (((( x >= enemies_pos[i][0] && x <= (enemies_pos[i][0] + spriteSize[ENEMY_SPRITE][0]))
                   || (x + spriteSize[ENEMY_SPRITE][0] >= enemies_pos[i][0] && (x <= enemies_pos[i][0])))
               && ((y >= enemies_pos[i][1] && y <= (enemies_pos[i][1] + spriteSize[ENEMY_SPRITE][1]))
                   || (y + spriteSize[ENEMY_SPRITE][1] >= enemies_pos[i][1] && y <= enemies_pos[i][1]))) && i != limit)
           {
               return true;
           }
       }

       return false;
   }

   bool isDead() {
       
       for (int i = 0; i < enemies_quantity; ++i)
       {

           if (((( player_pos[0][0] >= enemies_pos[i][0] && player_pos[0][0] <= (enemies_pos[i][0] + spriteSize[ENEMY_SPRITE][0]))
                   || (player_pos[0][0]  + spriteSize[ENEMY_SPRITE][0] >= enemies_pos[i][0] && (player_pos[0][0] <= enemies_pos[i][0])))
               && ((player_pos[0][1] >= enemies_pos[i][1] && player_pos[0][1] <= (enemies_pos[i][1] + spriteSize[ENEMY_SPRITE][1]))
                   || (player_pos[0][1] + spriteSize[ENEMY_SPRITE][1] >= enemies_pos[i][1] && player_pos[0][1] <= enemies_pos[i][1]))))
           {
               std::cout << "you died" << std::endl;
               return true;
           }
       }

       return false;
   }

   void isShot() {
       
       for (int i = 0; i < bullets_quantity; ++i)
       {
           if (!bullets_flag[i])
               continue;
           for (int j = 0; j < enemies_quantity; ++j)
           {
               if (((( bullets_pos[i][0] >= enemies_pos[j][0] && bullets_pos[i][0] <= (enemies_pos[j][0] + spriteSize[ENEMY_SPRITE][0]))
                   || (bullets_pos[i][0]  + spriteSize[BULLET_SPRITE][0] >= enemies_pos[j][0]
                       && (bullets_pos[i][0] + spriteSize[BULLET_SPRITE][0]  <= enemies_pos[j][0] + spriteSize[ENEMY_SPRITE][0] )))
               && ((bullets_pos[i][1] >= enemies_pos[j][1] && bullets_pos[i][1] <= (enemies_pos[j][1] + spriteSize[ENEMY_SPRITE][1]))
                   || (bullets_pos[i][1] + spriteSize[BULLET_SPRITE][1] >= enemies_pos[j][1]
                       && bullets_pos[i][1] + spriteSize[BULLET_SPRITE][1] <= enemies_pos[j][1] + spriteSize[ENEMY_SPRITE][1]))))
               {
                   bullets_flag[i] = false;
                   do {

                       enemies_pos[j][0] = rand() % (mapsize_x - spriteSize[ENEMY_SPRITE][0]);
                       enemies_pos[j][1] = rand() % (mapsize_y - spriteSize[ENEMY_SPRITE][1]);

                       if ((!isOccupied(enemies_pos[j][0], enemies_pos[j][1], enemies_quantity, j)
                                       && ((enemies_pos[j][0] < player_pos[0][0]
                                   && enemies_pos[j][0] < player_pos[0][0] - safe_margin)
                           || (enemies_pos[j][0] > player_pos[0][0] && enemies_pos[j][0] > player_pos[0][0] + safe_margin)
                       || (enemies_pos[j][1] < player_pos[0][1] && enemies_pos[j][1] < player_pos[0][1] - safe_margin)
                       || (enemies_pos[j][1] > player_pos[0][1] && enemies_pos[j][1] > player_pos[0][1] + safe_margin))))
                           break;
                       else
                           continue;
                   } while (1);
               }

           }
       }
   }

    int* getCrosshairSpriteSize() { return spriteSize[CROSSHAIR_SPRITE]; }

    void setCrosshairPos(int x, int y, int xrelative, int yrelative) {
        
        crosshair_pos[0][0] = x;
        crosshair_pos[0][1] = y;
        crosshair_pos[1][0] = xrelative;
        crosshair_pos[1][1] = yrelative;
   }

private:
    //here I try to implement data oriented design (structure of arrays instead of array of structures)
    int player_pos[1][2];
    int crosshair_pos[2][2];
    int **enemies_pos;
    float **bullets_pos;
    float **bullets_dir;
    bool *bullets_flag;
    int bullet_count = 0;
    Sprite* spriteArray[AMOUNT_OF_SPRITES];
    int spriteSize[AMOUNT_OF_SPRITES][2];
    int mapsize_x;
    int mapsize_y;
    int dx;
    int dy;
    int xlimit;
    int ylimit;
    int enemies_quantity;
    int bullets_quantity;
    bool moveFlag[4];
};

class MyFramework : public Framework {

public:

    MyFramework (int argc, char *argv[]) {
        
        ParamCheck(argc, argv);
    }

    ~MyFramework() {
        
        ent->SpriteDestroy();
        delete ent;
    }

    void PreInit(int& width, int& height, bool& fullscreen) {
            
                width = xres;
                height = yres;
                fullscreen = false;
    }

    bool Init() {

        showCursor(false);
        ent->PositionFill(get_xres(), get_yres());
                return true;
    }

    void Close() {
        
    }

    bool Tick() {

        ent->makeBackground();
        if(!(getTickCount() % ENEMY_SPEED))
            ent->enemyMove();
        ent->bulletMove();
        ent->isShot();
        ent->DisplayEntities();
        ent->displayBullets();
        ent->displayCrosshair();
        ShouldStop = ent->isDead();
                return ShouldStop;
        }

    void onMouseMove(int x, int y, int xrelative, int yrelative) {

        ent->setCrosshairPos(x, y, xrelative, yrelative);
    }

    void onMouseButtonClick(FRMouseButton button, bool isReleased) {

        if (button == FRMouseButton::LEFT && isReleased)
            ent->playerShoot();
    }

    void onKeyPressed(FRKey k) {

        ent->playerMove(k);
    }

    void onKeyReleased(FRKey k) {

    }

    int get_xres() { return xres; }

    int get_yres() { return xres; }

    bool getShouldStop() { return ShouldStop; }

    void ParamCheck(int argc, char *argv[])
    {
        int enemies = 0,
            bullets = 0,
            map_x = 0,
            map_y = 0;

        for (int i = 1; i < argc; ++i)
        {
            if (!strcmp("-window", argv[i]))
            {
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
                }

            if (!strcmp("-map", argv[i]))
            {
                char str[strlen(argv[++i]) / 2];

                    //here we obtain the x coord and convert from cstring to int
                int xpos = (int)(strchr(argv[i], 'x') - argv[i]);
                    for (int j = 0; j < xpos; ++j)
                            str[j] = argv[i][j];
                map_x = atoi(str);
                
                        //here we obtain y coord and convert from cstring to int
                        for (int j = xpos + 1; argv[i][j] != '\0'; ++j)
                            str[j - xpos - 1] = argv[i][j];
                        map_y = atoi(str);
            }

            if (!strcmp("-num_enemies", argv[i]))
            {
                enemies = atoi(argv[++i]);
            }

            if (!strcmp("-num_ammo", argv[i]))
            {
                bullets = atoi(argv[++i]);
            }
        }

        if (xres >  max_x)
            xres = max_x;
        if (yres > max_y)
            yres = max_y;
        

        if (map_x < xres)
            map_x = xres;
        if (map_y < yres)
            map_y = yres;


        if (enemies < 0)
            enemies = default_amount_of_enemies;
        if (bullets < 0)
            bullets = default_amount_of_bullets;
        

        ent = new Entities(enemies, bullets, map_x, map_y);
    }

private:
    int xres = 800;
    int yres = 600;
    Entities *ent;
    bool ShouldStop = false;
};

int main(int argc, char *argv[])
{
    MyFramework* gameFramework = new MyFramework(argc, argv);
    do {
          run(gameFramework);

    } while (gameFramework->getShouldStop());
    delete gameFramework;

    return 0;
}





    





