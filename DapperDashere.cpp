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

    //Hazardus Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRectangle{ 0.0f, 0.0f, nebula.width/8, nebula.height/8};


    Vector2 nebulaPosition{width,height-nebulaRectangle.height};

    int neb2Frame{};
    const float neb2UpdateTime{ 1.0 / 16.0 };
    float neb2RunningTime = 0;

    // nebual animation variables
    Rectangle neb2Rec{ 0.0, 0.0, nebula.width / 8, nebula.height / 8 };
    Vector2 neb2Pos{ width + 300, height - nebulaRectangle.height };




    int nebulaVelocity = -200;
    //NebulaHazard Animation variables
    int nebulaAnimFrame = 0;
    const float nebulaUpdateTime = 1.0 / 12.0;
    float nebulaRunningTime = 0;

    //textures for Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRectangle;
    scarfyRectangle.width = scarfy.width / 6;
    scarfyRectangle.height = scarfy.height;
    scarfyRectangle.x = 0;
    scarfyRectangle.y = 0;

    Vector2 scarfyPosition;
    scarfyPosition.x = width / 2 - scarfy.width / 2;
    scarfyPosition.y = height - scarfyRectangle.height;

    //animation frame
    int animFrame = 0;
    const float updateTimeAnimation = 1.0 / 12.0;
    float runngingTime = 0;


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
        if (scarfyPosition.y >= (height - scarfyRectangle.height))
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

        //update nebula hazard position
        nebulaRectangle.x += nebulaVelocity * deltaTime;

        // update the second nebula's position
        neb2Pos.x += nebulaVelocity * deltaTime;


        //update player position
        scarfyPosition.y += velocity * deltaTime;
        runngingTime += deltaTime;
        if (!inAir)
        {
            if (runngingTime >= updateTimeAnimation)
            {
                runngingTime = 0;
                //update animation frame
                scarfyRectangle.x = animFrame * scarfyRectangle.width;

                animFrame++;
                if (animFrame > 5)
                {
                    animFrame = 0;
                }
            }
        }


        nebulaRunningTime += deltaTime;

        if (nebulaRunningTime >= runngingTime)
        {
            runngingTime = 0;
            //update animation frame
            nebulaRectangle.x = nebulaAnimFrame * nebulaRectangle.width;

            nebulaAnimFrame++;
            if (nebulaAnimFrame > 7)
            {
                nebulaAnimFrame = 0;
            }
        }

        neb2RunningTime += deltaTime;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
        }



        //Drawing hazardus Nebula
        DrawTextureRec(nebula, nebulaRectangle, nebulaPosition, WHITE);

        // draw the second nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);



        //Draiwing scarfy
        DrawTextureRec(scarfy, scarfyRectangle, scarfyPosition, WHITE);

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
