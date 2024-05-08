#include <stdio.h>
#include <string.h>
#include "../include/raylib.h"

#define gridSize 10 
#define SIZE 10 
#define gridWidth 800/SIZE
#define gridHeight 800/SIZE

const int screenWidth = 800;
const int screenHeight = 450;

void drawGrid()
{
    //row 
    for(int i = 0 ; i < screenHeight ; i += gridSize)
    {
        Vector2 startPos = {0,i};
        Vector2 endPos = {screenWidth,i};
        DrawLineV(startPos,endPos,LIGHTGRAY);
    }

    //col 
    for(int i = 0 ; i < screenWidth ; i += gridSize)
    {
        Vector2 startPos = {i,0};
        Vector2 endPos = {i,screenHeight};
        DrawLineV(startPos,endPos,LIGHTGRAY);
    }
}

int main()
{


    InitWindow(screenWidth, screenHeight, "GameOfLife");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    int fps = 60;
    int tick = 0;
    int tickRate = 5;

    int grid[gridHeight][gridWidth] = {0}; 

    int xDir[4] = {1,0,-1,0};
    int yDir[4] = {0,1,0,-1};

    Vector2 selectPos = {SIZE,SIZE};
    Vector2 selectSize = {SIZE,SIZE}; 

    Color selectColor = BLUE;

    bool canRun = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        int key = GetKeyPressed();
        switch(key)
        {
            case KEY_A:
                {
                    if(selectPos.x - SIZE >= 0)
                    {
                        selectPos.x -= SIZE;
                    }
                } break;
            case KEY_D:
                {
                    if(selectPos.x + SIZE <= screenWidth)
                    {
                        selectPos.x += SIZE;
                    }
                } break;
            case KEY_W:
                {
                    if(selectPos.y - SIZE >= 0)
                    {
                        selectPos.y -= SIZE;
                    }
                } break;
            case KEY_S:
                {
                    if(selectPos.y + SIZE <= screenHeight)
                    {
                        selectPos.y += SIZE;
                    }
                } break;
            case KEY_ENTER:
                {
                    grid[(int)selectPos.y/SIZE][(int)selectPos.x/SIZE] = 1;
                }break;
            case KEY_P:
                {
                    canRun = true;
                }break;
        }

        if((tick == fps/tickRate) && canRun)
        {
            int backGrid[gridHeight][gridWidth] = {0}; 

            memcpy(backGrid,grid,sizeof(int)*gridHeight*gridWidth);

            for(int i = 1 ; i < gridHeight ; i++) 
            {
                for(int j = 1 ; j < gridWidth - 1 ; j++)
                {
                    int alive= 0;
                    for(int k = 0 ; k < 4 ; k++)
                    {
                        int dy = i + yDir[k];
                        int dx = j + xDir[k];

                        if(backGrid[dy][dx])
                        {
                            alive++;
                        }
                    } 
                    if(backGrid[i-1][j-1])alive++; 
                    if(backGrid[i-1][j+1])alive++; 
                    if(backGrid[i+1][j-1])alive++; 
                    if(backGrid[i+1][j+1])alive++; 
                    if(backGrid[i][j])
                    {
                        if(alive > 3 || alive < 2)
                        {
                            grid[i][j] = 0;
                        }
                    }
                    else
                    {
                        if(alive == 3)
                        {
                            grid[i][j] = 1;
                        }
                    }
                }
            }
            tick = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        drawGrid();
        if(!canRun)
        {
            DrawRectangleV(selectPos,selectSize,selectColor);
        }

        //draw 

        for(int i = 0 ; i < gridHeight ; i++)
        {
            for(int j = 0 ; j < gridWidth ; j++)
            {
                if(grid[i][j])
                {
                    Vector2 pos = {j * gridSize,i * gridSize};
                    Vector2 size = {gridSize,gridSize};
                    DrawRectangleV(pos,size,WHITE);
                }
            }
        }
        tick++;
        if(tick >= fps)tick = 0;
        EndDrawing();
        //----------------------------------------------------------------------------------

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context

    //--------------------------------------------------------------------------------------



    return 0;

}
