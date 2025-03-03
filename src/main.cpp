#include <raylib.h>


int main() 
{
    int ballx = 400;                // X-Coordinate of the Ball
    int bally = 400;                // Y-Coordinate of the Ball
    int item_place_timer = 0;       // Timer to place a new item
    int item_placed = 0;            // How many items are currently placed


    InitWindow(800, 800, "First raylib project");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        if(IsKeyDown(KEY_RIGHT))
        {
            ballx += 3;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            ballx -= 3;
        }
        else if(IsKeyDown(KEY_UP))
        {
            bally -= 3;
        }
        else if(IsKeyDown(KEY_DOWN))
        {
            bally += 3;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawCircle(ballx, bally, 50, BLUE );

        DrawRectangle(0, 750, 800, 50, GREEN);
        DrawRectangle(150, 450, 150, 50, GRAY);
        DrawRectangle(500, 450, 150, 50, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}