// DapperDashere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
    //                                                                                      nebulaData.rectangle.height
    AnimData nebulaData{ { 0.0,0.0, nebula.width / 8, nebula.height / 8}, {width,height - nebula.height / 8}, {0}, {1.0 / 16.0},{0} };
    
    AnimData neb2Data{ {0.0, 0.0, nebula.width / 8, nebula.height / 8 }, {width,height - nebulaData.rectangle.height},{0},{1.0 / 16.0},{0} };

    int neb2Frame{};
    const float neb2UpdateTime{ 1.0 / 16.0 };
    float neb2RunningTime = 0;

    // nebual animation variables
   /* Rectangle neb2Rec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 neb2Pos{ width + 300, height - nebulaRectangle.height };*/




    int nebulaVelocity = -200;
    //NebulaHazard Animation variables
    int nebulaAnimFrame = 0;
    const float nebulaUpdateTime = 1.0 / 12.0;
    float nebulaRunningTime = 0;

    //textures for Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rectangle.width = scarfy.width / 6;
    scarfyData.rectangle.height = scarfy.height;
    scarfyData.rectangle.x = 0;
    scarfyData.rectangle.y = 0;

    scarfyData.postion.x = width / 2 - scarfy.width / 2;
    scarfyData.postion.y = height - scarfyData.rectangle.height;

    scarfyData.runningTime = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.frame = 0;



    //Jump velocity (pixels/sec)
    const int jumpVelocity = -600;
    bool inAir = false;

    float velocity = 0.0f;

    float runngingTime = 1.0 / 12.0;
    
   
    while (!WindowShouldClose())
    {
        //Making a delta time (time since last frame)
        const float deltaTime = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(WHITE);
       
        //rectangle on the ground
        if (scarfyData.postion.y >= (height - scarfyData.rectangle.height))
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
        nebulaData.rectangle.x += nebulaVelocity * deltaTime;

        // update the second nebula's position
        neb2Data.postion.x += nebulaVelocity * deltaTime;


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


        nebulaData.runningTime += deltaTime;

        if (nebulaRunningTime >= runngingTime)
        {
            runngingTime = 0;
            //update animation frame
            nebulaData.rectangle.x = nebulaAnimFrame * nebulaData.rectangle.width;

            nebulaAnimFrame++;
            if (nebulaAnimFrame > 7)
            {
                nebulaAnimFrame = 0;
            }
        }
        
        neb2Data.runningTime += deltaTime;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rectangle.x = neb2Frame * neb2Data.rectangle.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }



        //Drawing hazardus Nebula
        DrawTextureRec(nebula, nebulaData.rectangle, nebulaData.postion, BLACK);

        // draw the second nebula
        DrawTextureRec(nebula, neb2Data.rectangle, neb2Data.postion, RED);



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
