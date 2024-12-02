#include "objPos.h"

objPos::objPos() //Constructor
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym) //sets positions at specific points with a specific symbol
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}


//Destructor
objPos::~objPos()
{
    delete pos;
}

//Copy Constructor
objPos::objPos(const objPos &other) 
{
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;
}

//Copy assignment
objPos &objPos::operator=(const objPos &other)
{
    if(this != &other)
    {
        //clean up
        delete pos;

        //memory allocation and copy data
        pos = new Pos;
        pos->x = other.pos->x;
        pos->y = other.pos->y;
        symbol = other.symbol;
    }
    return *this;
}



void objPos::setObjPos(objPos o) // Sets the position and symbol to match another objPos object.
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym) // Sets the position and symbol using individual parameters.
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const // Returns a new objPos object with the same position and symbol as the current object.
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}


char objPos::getSymbol() const // Returns the symbol of the current object.
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const // Checks if the position of the current object matches the position of a reference objPos object.
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const // Returns the symbol of the current object if its position matches the position of a reference objPos object.
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
