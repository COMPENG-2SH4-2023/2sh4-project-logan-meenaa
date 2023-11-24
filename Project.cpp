#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    char board[10][20];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            //Drawing board
            board[i][j] = ' ';
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            //Drawimg board
            if (i == 0 || j == 0 || i == 9 || j == 19)
            {
                board[i][j] = '#';
            }
            MacUILib_printf("%c",board[i][j]);
        }
        MacUILib_printf("\n"); 
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
