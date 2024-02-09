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
    
    //Acceleration due to gravity (pixels/frame)/frame
    const int gravity = 1'000;

    //textures
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRectangle;
    scarfyRectangle.width = scarfy.width / 6;
    scarfyRectangle.height = scarfy.height;
    scarfyRectangle.x = 0;
    scarfyRectangle.y = 0;

    Vector2 scarfyPosition;
    scarfyPosition.x = width / 2 - scarfy.width / 2;
    scarfyPosition.y = height - scarfyRectangle.height;

    //Jump velocity (pixels/sec)
    const int jumpVelocity = -600;
    bool inAir = false;

    int velocity = 0;

   
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
       
        //rectangle on the ground
        if (scarfyPosition.y >= (height - scarfyRectangle.height))
        {
             velocity = 0;
             inAir = false;
        }
        else
        {
            //Apply gravity
            velocity += gravity;
            inAir = true;
        }

        //Jump Check
        if (IsKeyPressed(KEY_SPACE) && !inAir)
        {
            velocity += jumpVelocity;
            
        }

        //update position
        scarfyPosition.y += velocity;

        DrawTextureRec(scarfy, scarfyRectangle, scarfyPosition, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
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
