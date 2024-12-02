#include "GameMechs.h"
#include "Food.h"

GameMechs::GameMechs() //constructor 
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

GameMechs::GameMechs(int boardX, int boardY) //constructs the game board with the provided x and y values
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

GameMechs::~GameMechs()
{
    //Nothing
}

bool GameMechs::getLoseFlagStatus() const //returns the loseFlag value 
{
    return loseFlag;
}

bool GameMechs::getExitFlagStatus() const //returns the exitFlag value 
{
    return exitFlag;
}
    
char GameMechs::getInput() const //returns the input provided to the game 
{
    return input;
}

int GameMechs::getScore() const //returns the score of the player 
{
    return score;
}

void GameMechs::incrementScore(int input) //increments the score of the game (by adding the input)
{
    score = score + input;
}

int GameMechs::getBoardSizeX() const //returns the board size of the game on the x-axis 
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const //returns the board size of the game on the y-axis 
{
    return boardSizeY;
}

void GameMechs::setExitTrue() //sets the exitFlag value to true 
{
    exitFlag = true;
}

void GameMechs::setLoseFlag() //sets the loseFlag value to true 
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input) //sets the input of the game 
{
    input = this_input;
}


void GameMechs::clearInput() //clears any input given to the game (to zero)
{
    input = 0;
}


int GameMechs::getSpeed() const //returns the speed of the game 
{
    return speed;
}

int GameMechs::getDelay() const //returns the delay constant of the game 
{
    return delay;
}

void GameMechs::setSpeed(int newSpeed) //sets a specific speed of the game 
{
    speed = newSpeed;
}

void GameMechs::setDelay(int newDelay) //sets the delay constant for the Game
{
    delay = newDelay;
}