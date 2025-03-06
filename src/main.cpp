#include <raylib.h>
#define GRAVITY 400
#define NUM_OBSTACLES 3

int main() 
{ 
    const int windowLenght = 800;         // Lenght of the Mainwindow
    const int windowWidht = 600;          // Widht of the Mainwindow

    int playerspeed = 3;    

    InitWindow(windowLenght, windowWidht, "Catch_Game");

    Rectangle player = { 400, 300, 50, 50 };        // Initialising the Player Rectangle   

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
            player.x += playerspeed;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            player.x -= playerspeed;
        }
        else if(IsKeyDown(KEY_UP))
        {
            player.y -= playerspeed;
        }
        else if(IsKeyDown(KEY_DOWN))
        {
            player.y += playerspeed;
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

        DrawRectangleRec(player, PURPLE);

        for (int i = 0; i < NUM_OBSTACLES; i++) {
            DrawRectangleRec(obstacles[i], GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}