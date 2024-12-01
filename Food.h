#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "time.h"
#include "stdlib.h"

#define Board_Length 30
#define Board_Height 15

class Food
{
    private:
        char foodSymbol;
        objPosArrayList *foodStorage;
        
    public:
        Food();
        ~Food();

        void generateFood(const objPosArrayList *blockOff, int foodSpecial);
        objPosArrayList* getFoodPos() const;
};

#endif