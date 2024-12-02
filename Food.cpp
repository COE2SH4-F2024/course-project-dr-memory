#include "Food.h"

Food::Food() //constructor 
{
    foodStorage = new objPosArrayList();
}

Food::~Food() //destructor
{
    delete foodStorage; 
}

// Generates food at a valid position on the board while avoiding blockOff areas.
void Food::generateFood(const objPosArrayList *blockOff, int foodSpecial)
{
    int randomX, randomY, i; //randomX/randomY hold random x-y values to print Food items
    bool validPos = false;   // Flag to check if the generated position is valid.
    char foodSymbol;
    bool occupied[Board_Length][Board_Height]; // Tracks occupied positions on the board.

    srand(time(NULL));

    // Loop until a valid food position is generated.
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

        // Mark all blockOff positions as occupied.
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

        // Generate a random position within the board boundaries
        randomX = (rand() % (Board_Length - 2)) + 1;
        randomY = (rand() % (Board_Height - 2)) + 1;

        if(occupied[randomX][randomY] == 1)
        {
            validPos = false;
        }

        else
        {
            // Assign a symbol to the food based on the foodSpecial value.
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

            // Add the new food position to the head of the foodStorage list.
            foodStorage -> insertHead(foodPos);
        }
    }
}

objPosArrayList* Food::getFoodPos() const // Returns the pointer to the foodStorage list.
{
    return foodStorage;
}