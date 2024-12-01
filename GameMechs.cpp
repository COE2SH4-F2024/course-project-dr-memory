#include "GameMechs.h"
#include "Food.h"

GameMechs::GameMechs()
{
    input = 0;
    loseFlag = false;
    exitFlag = false;
    score = 0;
    delay = 100000;
    speed = 3;
    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    loseFlag = false;
    exitFlag = false;
    score = 0;
    delay = 100000;
    speed = 3;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //Nothing
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}
    
char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore(int input)
{
    score = score + input;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}


void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
int GameMechs::getSpeed() const
{
    return speed;
}

int GameMechs::getDelay() const
{
    return delay;
}

void GameMechs::setSpeed(int newSpeed)
{
    speed = newSpeed;
}

void GameMechs::setDelay(int newDelay)
{
    delay = newDelay;
}