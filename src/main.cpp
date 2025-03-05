#include <raylib.h>
#define GRAVITY 400
#define NUM_OBSTACLES 3

int main() 
{ 

    const int windowLenght = 800;         // Lenght of the Mainwindow
    const int windowWidht = 600;          // Widht of the Mainwindow

    int ballx = windowLenght / 2;                // X-Coordinate of the Ball
    int bally = windowWidht / 2;                // Y-Coordinate of the Ball

    int playerspeed = 3;    

    InitWindow(windowLenght, windowWidht, "Catch_Game");

    Rectangle player = { 100, 100, 50, 50 };        // Initialising the Player Rectangle   

    // Initialising the Obstacles    

    Rectangle obstacles[NUM_OBSTACLES] = {
        { 0, windowWidht - 50, windowLenght, 50 },  // GROUND
        { 150, 250, 150, 50 },   // Platform 1
        { 500, 250, 150, 50 }    // Platform 2
    };

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        if(IsKeyDown(KEY_RIGHT))
        {
            ballx += playerspeed;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            ballx -= playerspeed;
        }
        else if(IsKeyDown(KEY_UP))
        {
            bally -= playerspeed;
        }
        else if(IsKeyDown(KEY_DOWN))
        {
            bally += playerspeed;
        }
        
        for (int i = 0; i < NUM_OBSTACLES; i++) {
            if (CheckCollisionRecs(player, obstacles[i])) {
                // Zurücksetzen der Bewegung, falls Kollision
                player.x -= playerspeed * (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
                player.y -= playerspeed * (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP));
            }
        }
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleRec(player, RED);

        for (int i = 0; i < NUM_OBSTACLES; i++) {
            DrawRectangleRec(obstacles[i], GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}