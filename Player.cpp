#include "Player.h"
#include "objPosArrayList.h"


Player::Player(GameMechs* thisGMRef, Food *foodRef)
{   
    // Initializes references to GameMechs and Food
    mainGameMechsRef = thisGMRef;
    myDir = STOP; //sets deafult direction
    food = foodRef;

    
    int BoardSizeX = mainGameMechsRef -> getBoardSizeX(); 
    int BoardSizeY = mainGameMechsRef -> getBoardSizeY(); 
    
    playerPosList = new objPosArrayList();
    playerPosList -> insertHead(objPos(BoardSizeX/2, BoardSizeY/2, '*')); // Place snake's head in the center of the board
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPosList() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

// Updates the direction of the player based on input
void Player::updatePlayerDir()
{
        // PPA3 input processing logic  
        char input = mainGameMechsRef -> getInput();
        if(input != 0)
        {

            switch(input)
            {
                case 27: //Exit key
                    mainGameMechsRef -> setExitTrue();
                    break;

                case 'W':
                case 'w': //Move up
                    if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
                    {
                        myDir = UP;
                    }
                    break;

                case 'S':
                case 's': //Move Down
                    if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
                    {
                        myDir = DOWN;
                    }
                    break;

                case 'A':
                case 'a': //Move left
                    if(myDir == UP || myDir == DOWN || myDir == STOP)
                    {
                        myDir = LEFT;
                    }
                    break;
            
                case 'D':
                case 'd'://Move right
                    if(myDir == UP || myDir == DOWN || myDir == STOP)
                    {
                        myDir = RIGHT;
                    }
                    break;

                default:
                    break;    
            
            }   
        }     
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos NewHead = playerPosList -> getHeadElement(); //current head position
    
    // Update the head position based on direction
    switch(myDir)
    {
        case STOP:
            return;

        case RIGHT:
            NewHead.pos -> x = NewHead.pos -> x + 1;
            if(NewHead.pos -> x == mainGameMechsRef -> getBoardSizeX() - 1)
            {
                NewHead.pos -> x = 1;// Wrap around
            }
            break;

        case LEFT:
            NewHead.pos -> x = NewHead.pos -> x - 1;
            if(NewHead.pos -> x ==0)
            {
                NewHead.pos -> x = mainGameMechsRef -> getBoardSizeX() - 2;// Wrap around
            }
            break;

        case UP:
            NewHead.pos -> y = NewHead.pos -> y - 1;
            if(NewHead.pos -> y == 0)
            {
                NewHead.pos -> y = mainGameMechsRef -> getBoardSizeY() - 2;// Wrap around
            }
            break;

        case DOWN:
            NewHead.pos -> y = NewHead.pos -> y + 1;
            if(NewHead.pos -> y==mainGameMechsRef -> getBoardSizeY() - 1)
            {
                NewHead.pos -> y = 1;// Wrap around
            }
            break;
        
        default:
            break;
    }

    //Movement and Collision handling
    foodEating(NewHead);
    selfCollisionCheck(NewHead);
    myPlayerMovement(NewHead);
}


// Updates the player's speed based on input
void Player::updatePlayerSpeed()
{
    //Speed Input
    char input = mainGameMechsRef -> getInput();
    int speed = mainGameMechsRef -> getSpeed();

    //Speed Adjustments
    if(input != 0)
    {
        switch (input)
        {
        case '=':
            if(speed < 5)
            {
                speed++;
            }
            break;

        case '-':
            if(speed > 1)
            {
                speed--;
            }
            break;
        
        default:
            break;
        }
    }
    mainGameMechsRef -> setSpeed(speed);
}

void Player::updatePlayerSpeedDelay()
{
    //Speed and Delay Inputs
    int speed = mainGameMechsRef -> getSpeed();
    int delay = mainGameMechsRef -> getDelay();

    //Changing Delay
    switch(speed)
    {
        case 1:
            delay = 500000;
            break;
        
        case 2:
            delay = 250000;
            break;
        
        case 3:
            delay = 125000;
            break;
        
        case 4:
            delay = 62500;
            break;
        
        case 5:
            delay = 10000;
            break;

        default:
            delay = 100000;
            break;
    }
    mainGameMechsRef -> setDelay(delay);
}

// Checks if the player has eaten food and handles score and new food generation
void Player::foodEating(const objPos &NewHead)
{
    int i;
    int j;
    int k;

    for(i = 0; i < food -> getFoodPos() -> getSize(); i++)
    {
        if(NewHead.pos -> x == food -> getFoodPos() -> getElement(i).pos -> x 
        && NewHead.pos -> y == food -> getFoodPos() -> getElement(i).pos -> y)
            {
                //Generation of New Food
                int foodGen = rand() % (5) + 1;
                char foodSpecial = food -> getFoodPos() -> getElement(i).getSymbol();

                
                if(foodSpecial == 'M') //Increase score by 15
                {
                    mainGameMechsRef -> incrementScore(15);
                }

                else if(foodSpecial == 'A') //Increases Score by 45 and length by 5
                {
                    mainGameMechsRef -> incrementScore(45);
                    playerPosList -> insertTails(5);
                }

                //Normal food
                else
                {
                    mainGameMechsRef -> incrementScore(1);
                    playerPosList -> insertTails(1);
                }
                food -> getFoodPos() -> removeElement(i);

                //M Food Generation
                if(foodGen == 3)
                {
                    food -> generateFood(playerPosList, 3);
                }

                //A Food Generation
                else if(foodGen == 4)
                {
                    food -> generateFood(playerPosList, 4);
                }

                //Normal Apple Generation
                else
                {
                    food -> generateFood(playerPosList, 1);
                }
                
            }
    }
}

//Regular Movement
void Player::myPlayerMovement(const objPos &NewHead)
{
    int i;

    for(i = 0; i < food -> getFoodPos() -> getSize(); i++)
    {
        if(NewHead.pos -> x == food -> getFoodPos() -> getElement(i).pos -> x
        && NewHead.pos -> y == food -> getFoodPos() -> getElement(i).pos -> y)
        {
            return;
        }
    }

    playerPosList -> insertHead(NewHead);
    playerPosList -> removeTail();
}

//Check for Character Collision
void Player::selfCollisionCheck(const objPos &NewHead)
{
    int i;

    for(i = 0; i < playerPosList -> getSize(); i++)
    {
        objPos bodyPart = playerPosList -> getElement(i);

        if(NewHead.pos -> x == bodyPart.pos -> x && NewHead.pos -> y == bodyPart.pos -> y)//checks for each body part
        {
            mainGameMechsRef -> setLoseFlag();
            mainGameMechsRef -> setExitTrue();
        }
    }
}

