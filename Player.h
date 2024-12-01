#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* foodRef);
        ~Player();

        objPosArrayList* getPlayerPosList() const;
       
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here
        void updatePlayerSpeed();
        void updatePlayerSpeedDelay();
        void foodEating(const objPos &NewHead);
        void selfCollisionCheck(const objPos &NewHead);
        void myPlayerMovement(const objPos &NewHead);

    private:
        objPosArrayList* playerPosList; // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* food;
};

#endif 