// DapperDashere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"raylib.h"
#include"string"
#include <vector>

using namespace std;
int main()
{
    const int width = 800;
    const int height = 400;
    string gameName = "Dapper Dashere";
    const char* name = gameName.c_str();

    SetTargetFPS(60);
    InitWindow(width, height, name);

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
       

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }
        posY += velocity;

        DrawRectangle(width / 2, velocity, widthRectangle, heightRectangle, BLACK);

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
