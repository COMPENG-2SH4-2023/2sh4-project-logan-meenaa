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
    
}

void GetInput(void)
{

}

void RunLogic(void)
{
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
    myGM->clearInput();
}

void DrawScreen(void)
{
    int bX = myGM->getBoardSizeX();
    int bY = myGM->getBoardSizeY();
    objPos currPos;
    myPlayer->getPlayerPos(currPos);

    char board[bY][bX];

    MacUILib_clearScreen();

    for (int i = 0; i < bY; i++)
    {
        for (int j = 0; j < bX; j++)
        {
            //Drawing board
            board[i][j] = ' ';
        }
    }

    for (int i = 0; i < bY; i++)
    {
        for (int j = 0; j < bX; j++)
        {
            //Drawing board
            if (i == 0 || j == 0 || i == bY - 1 || j == bX - 1)
            {
                board[i][j] = '#';
            }
            if (i == currPos.y && j == currPos.x)
            {
                board[i][j] = currPos.symbol;
            }
 
            MacUILib_printf("%c",board[i][j]);
        }
        MacUILib_printf("\n");        
    }
    MacUILib_printf("%d", myGM->getScore());

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
    MacUILib_uninit();
}
