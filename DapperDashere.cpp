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
    windowDimension[0] = 800;
    windowDimension[1] = 400;
    string gameName = "Dapper Dashere";
    const char* name = gameName.c_str();

    SetTargetFPS(60);
    InitWindow(windowDimension[0], windowDimension[1], name);
    
    //Acceleration due to gravity (pixels/frame)/frame
    const int gravity = 1'000;

    //Hazardus Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    //                                                                                      nebulaData.rectangle.height
    AnimData nebulaData{ { 0.0,0.0, nebula.width / 8, nebula.height / 8}, {windowDimension[0],windowDimension[1] - nebula.height / 8}, {0}, {1.0 / 16.0},{0} };
    
    AnimData neb2Data{ {0.0, 0.0, nebula.width / 8, nebula.height / 8 }, {windowDimension[0],windowDimension[1] - nebulaData.rectangle.height},{0},{1.0 / 16.0},{0} };


    AnimData nebulae[2]{ nebulae[0], neb2Data };

    int nebulaVelocity = -200;
    //NebulaHazard Animation variables


    //textures for Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{ {0.0,0.0,scarfy.width / 6,scarfy.height},{windowDimension[0] / 2 - scarfy.width / 2,windowDimension[1] - scarfyData.rectangle.height},{0},{1.0 / 12.0},{0} };

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

        //update nebula hazard position
        nebulae[0].rectangle.x += nebulaVelocity * deltaTime;

        // update the second nebula's position
        nebulae[1].postion.x += nebulaVelocity * deltaTime;


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


        nebulae[0].runningTime += deltaTime;

        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0;
            //update animation frame
            nebulae[0].rectangle.x = nebulae[0].frame * nebulae[0].rectangle.width;

            nebulae[0].frame++;
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }
        
        nebulae[1].runningTime += deltaTime;
        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;
            nebulae[1].rectangle.x = nebulae[1].frame * nebulae[1].rectangle.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        //Drawing hazardus Nebula
        DrawTextureRec(nebula, nebulae[0].rectangle, nebulae[0].postion, BLACK);

        // draw the second nebula
        DrawTextureRec(nebula, nebulae[1].rectangle, nebulae[1].postion, RED);

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
