#include "Food.h"

Food::Food()
{
    foodStorage = new objPosArrayList();
}

Food::~Food()
{
    delete foodStorage;
}

void Food::generateFood(const objPosArrayList *blockOff, int foodSpecial)
{
    int randomX, randomY, i;
    bool validPos = false;
    char foodSymbol;
    bool occupied[Board_Length][Board_Height];

    srand(time(NULL));

    while(!validPos)
    {
        validPos = true;

        for(i = 0; i < Board_Length; i++)
        {
            for(int j = 0; j < Board_Height; j++)
            {
                occupied[i][j] = 0;
            }
        }

        for(i = 0; i < blockOff -> getSize(); i++)
        {
            objPos player = blockOff -> getElement(i);

            occupied[player.pos -> x][player.pos -> y] = 1;
        }

        for(i = 0; i < foodStorage -> getSize(); i++)
        {
            objPos food = foodStorage -> getElement(i);
            occupied[food.pos -> x][food.pos -> y] = 1;
        }

        randomX = (rand() % (Board_Length - 2)) + 1;
        randomY = (rand() % (Board_Height - 2)) + 1;

        if(occupied[randomX][randomY] == 1)
        {
            validPos = false;
        }

        else
        {
            switch(foodSpecial)
            {
                case 1:
                case 2:
                case 3:
                    foodSymbol = 'N';
                    break;
                case 4:
                    foodSymbol = 'M';
                    break;
                case 5:
                    foodSymbol = 'A';
                    break;
            }
            objPos foodPos = objPos(randomX, randomY, foodSymbol);
            foodStorage -> insertHead(foodPos);
        }
    }
}

objPosArrayList* Food::getFoodPos() const
{
    return foodStorage;
}