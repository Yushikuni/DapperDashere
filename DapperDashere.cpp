// DapperDashere.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include"raylib.h"
#include"string"
#include <vector>

using namespace std;

struct AnimData
{
    Rectangle rectangle;
    Vector2 postion;
    int frame;
    float updateTime;
    float runningTime;
};


int main()
{
    int windowDimension[2];
    windowDimension[0] = 1024;
    windowDimension[1] = 760;
    string gameName = "Dapper Dashere";
    const char* name = gameName.c_str();

    SetTargetFPS(60);
    InitWindow(windowDimension[0], windowDimension[1], name);
    
    //Acceleration due to gravity (pixels/frame)/frame
    const int gravity = 1'000;

    //Hazardus Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    AnimData nebulae[10];


    for (int i = 0; i < 3; i++)
    {
        nebulae[i].rectangle.x = 0.0;
        nebulae[i].rectangle.y = 0.0;
        nebulae[i].rectangle.width = nebula.width / 8;
        nebulae[i].rectangle.height = nebula.height / 8;
        nebulae[i].postion.y = windowDimension[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].postion.x = windowDimension[0] + (i * 300);
    }


    int nebulaVelocity = -200;
    //NebulaHazard Animation variables


    //textures for Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{ {0.0,0.0,scarfy.width / 6,scarfy.height},{windowDimension[1] / 2 - scarfy.width / 2,windowDimension[1] - scarfyData.rectangle.height},{0},{1.0 / 12.0},{0} };

    //Jump velocity (pixels/sec)
    const int jumpVelocity = -600;
    bool inAir = false;
    float velocity = 0.0f;
 
    while (!WindowShouldClose())
    {
        //Making a delta time (time since last frame)
        const float deltaTime = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(WHITE);
       
        //rectangle on the ground
        if (scarfyData.postion.y >= (windowDimension[1] - scarfyData.rectangle.height))
        {
             velocity = 0;
             inAir = false;
        }
        else
        {
            //Apply gravity
            velocity += gravity * deltaTime;
            inAir = true;
        }

        //Jump Check
        if (IsKeyPressed(KEY_SPACE) && !inAir)
        {
            velocity += jumpVelocity;
        }


        //update player position
        scarfyData.postion.y += velocity * deltaTime;
        scarfyData.runningTime += deltaTime;
        if (!inAir)
        {
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0;
                //update animation frame
                scarfyData.rectangle.x = scarfyData.frame* scarfyData.rectangle.width;

                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        for (int i = 0; i < size(nebulae); ++i)
        {
            nebulae[i].runningTime += deltaTime;

            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0;
                //update animation frame
                nebulae[i].rectangle.x = nebulae[i].frame * nebulae[i].rectangle.width;

                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
        }

        for (int i = 0; i < size(nebulae); ++i)
        {
            DrawTextureRec(nebula, nebulae[i].rectangle, nebulae[i].postion, WHITE);
        }

        //Draiwing scarfy
        DrawTextureRec(scarfy, scarfyData.rectangle, scarfyData.postion, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
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
