#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    myGM = new GameMechs();
    myPlayer = new Player(myGM);    
    
    objPos tempPos{1, 1, 'o'};
    myGM->generateFood(tempPos);
}

void GetInput(void)
{

}

void RunLogic(void)
{    
    objPos tempPos{1, 1, 'o'};
    
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    if(myGM->getInput() == '/')
    {
        myGM->setExitTrue();
    }
    if(myGM->getInput() == '+')
    {
        myGM->incrementScore();
    }
    if(myGM->getInput() == 'L')
    {
        myGM->setLoseFlag();
        myGM->setExitTrue();
    }
    if(myGM->getInput() == 'F')
    {
        myGM->generateFood(tempPos);
    }
    myGM->clearInput();


}

void DrawScreen(void)
{
    int bX = myGM->getBoardSizeX();
    int bY = myGM->getBoardSizeY();

    char board[bY][bX];
    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos foodPos;
    myGM->getFoodPos(foodPos);

    MacUILib_clearScreen();

    for (int i = 0; i < bY; i++)
    {
        for (int j = 0; j < bX; j++)
        {
            //Drawing board
            board[i][j] = ' ';
        }
    }
    for (int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            // iterate through player list
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (i == tempBody.y && j == tempBody.x)
                {
                    board[i][j] = tempBody.symbol;
                }
            }


            //Drawing board
            if (i == 0 || j == 0 || i == myGM->getBoardSizeY() - 1 || j == myGM->getBoardSizeX() - 1)
            {
                board[i][j] = '#';
            }
            else if (i == foodPos.y && j == foodPos.x)
            {
                board[i][j] = foodPos.symbol;
            }
            MacUILib_printf("%c",board[i][j]);
        }
        MacUILib_printf("\n");        
    }
    MacUILib_printf("Score: %d", myGM->getScore());
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   
    if(myGM->getLoseFlagStatus() == true)
    {
        MacUILib_printf("LOSER");
    }
    
    delete myGM;
    delete myPlayer;
    MacUILib_uninit();
}
