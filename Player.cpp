#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();    
    if(input != 0) 
    {
        switch(input)
        {                      
            case 'w':
                if (myDir != DOWN && myDir != UP)
                {
                    myDir = UP;
                }
                break;
            case 's':
                if (myDir != DOWN && myDir != UP)
                {
                    myDir = DOWN;
                }
                break;
            case 'a':
                if (myDir != RIGHT && myDir != LEFT)
                {
                    myDir = LEFT;
                }
                break;
            case 'd':
                if (myDir != RIGHT && myDir != LEFT)
                {
                    myDir = RIGHT;
                }
                break;
                
            default:
                break;
        }
        input = 0;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
        case UP:
            playerPos.y --;
            if (playerPos.y == 0)
            {
                playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN:
            playerPos.y ++;
            if (playerPos.y == mainGameMechsRef->getBoardSizeY() - 1)
            {
                playerPos.y = 1;
            }
            break;
        case LEFT:
            playerPos.x --;
            if (playerPos.x == 0)
            {
                playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT:
            playerPos.x ++;
            if (playerPos.x == mainGameMechsRef->getBoardSizeX() - 1)
            {
                playerPos.x = 1;
            }
            break;
        default:
            break;
    }
}

