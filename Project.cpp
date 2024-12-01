#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Food.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
#define Board_Length 30
#define Board_Height 15


bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap
GameMechs *myGM;
Food *food;


int main(void)
{

    Initialize();

    while(!myGM -> getExitFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30, 15);
    food = new Food();
    myPlayer = new Player(myGM, food);

    for(int i = 1; i <= 5; i++)
    {
        food -> generateFood(myPlayer -> getPlayerPosList(), i);
    }

    exitFlag = false; //SEE IF I SHOULD KEEP
}

void GetInput(void)
{
   if (MacUILib_hasChar())
   {
    myGM -> setInput(MacUILib_getChar());
   }
}

void RunLogic(void)
{
    myPlayer -> updatePlayerDir();
    myPlayer -> updatePlayerSpeed();
    myPlayer -> updatePlayerSpeedDelay();
    myPlayer -> movePlayer();
    myGM -> clearInput();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();
    int x;
    int y;
    int i;
    
    //objPos playerPos = myPlayer->getPlayerPos();
    //Board Drawing
    for(y=0; y < 15;y++) //For iterating through the rows
    {
        for(x=0; x < 30;x++) //For iterating through the columns
        {
            //If on border
            if(x == 0 || x == (Board_Length - 1) || y == 0 || y == (Board_Height - 1))
            {
                MacUILib_printf("#");
                continue;
            }

            //Check for player character at coordinate
            bool myPlayerPresent = false;
            bool foodPresent = false;

            for(i = 0; i < myPlayer -> getPlayerPosList() -> getSize(); i++)
            {
                objPos myPlayerTorso = myPlayer -> getPlayerPosList() -> getElement(i);

                if (myPlayerTorso.pos -> x == x && myPlayerTorso.pos -> y == y)
                {
                    MacUILib_printf("%c", myPlayerTorso.symbol);
                    myPlayerPresent = true;
                    break;
                }
            }
            //Check if food is present at coordinate, if player character is not there
            if(!myPlayerPresent)
            {
                for(i=0; i < food -> getFoodPos() -> getSize(); i++)
                {
                    objPos currentFood = food -> getFoodPos() -> getElement(i);

                    if(currentFood.pos -> x == x && currentFood.pos -> y == y)
                    {
                        MacUILib_printf("%c", currentFood.getSymbol());
                        foodPresent = true;
                        break;
                    }
                }
            }

            //if both food and myPlayer character are no present, add empty space
            if(!myPlayerPresent && !foodPresent)
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM -> getScore());
    MacUILib_printf("Current Speed Level: %d\n", myGM -> getSpeed());
    MacUILib_printf("Instructions: Press '=' to increase speed, '-' to decrease speed.\n");
}
void LoopDelay(void)
{
    MacUILib_Delay(myGM -> getDelay()); // 0.1s default delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  

        //Player Lost
    if(myGM -> getLoseFlagStatus())
    {
        MacUILib_printf("You hit yourself.\nYou Lost!");
    } 

    //Player Won
    else if (myGM -> getScore() >= 5)
    {
        MacUILib_printf("CONGRATULATIONS YOU WON!! Your achieved a score of %d", myGM->getScore());
    } 

    //Game Ended Early
    else if(myGM -> getExitFlagStatus())
    {
        MacUILib_printf("The game ended early.\nYou scored %d that round", myGM -> getScore());
    }

    delete myPlayer;
    delete myGM;
    delete food;

    MacUILib_uninit();
}
