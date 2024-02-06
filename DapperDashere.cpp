// DapperDashere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"raylib.h"
#include"string"
#include <vector>

using namespace std;
int main()
{
    const int width = 512;
    const int height = 380;
    string gameName = "Dapper Dashere";
    const char* name = gameName.c_str();

    SetTargetFPS(60);
    InitWindow(width, height, name);
    
    //Acceleration due to gravity (pixels/frame)/frame
    const int gravity = 1;
    const int jumpVelocity = -22;

    int positionPlayerY = 0;
    int positionPlayerX = 0;
    //int velocity = 10;

    int widthRectangle = 50;
    int heightRectangle = 80;
    int posY = (height - heightRectangle);
    int velocity = 0;
   
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
       
        //rectangle on the ground
        if (posY >= (height - heightRectangle))
        {
             velocity = 0;
        }
        else
        {
            //Apply gravity
            velocity += gravity;
        }

        //Jump Check
        if (IsKeyPressed(KEY_SPACE))
        {
            velocity += jumpVelocity;
        }

        //update position
        posY += velocity;

        DrawRectangle(width / 2, posY, widthRectangle, heightRectangle, BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
