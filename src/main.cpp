#include "raylib.h"
#include <stdio.h>

#define NUM_OBSTACLES 3

Rectangle OrigPlayerVar(Rectangle Player, float *velocityY, bool *onGround, float Playerx)      // Setting the player Coordinates and stats for the Round
{
    Player = { Playerx, 100, 40, 50 };// Initialising the Player Rectangle   
    *velocityY = 0;                  // Vertical velocity (+ ... the player falls, - ... flies up )
    *onGround = false;              // Checks if the player is on Ground

    return Player;
}

void Kollisionscheck(Rectangle *Player,float* velocityY,float* gravity,float* playerspeed,
                    float* jumpForce,Rectangle *oldPlayer, Rectangle obstacles[],bool* onGround){

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        if (CheckCollisionRecs(*Player, obstacles[i])) {
            if(oldPlayer->y + oldPlayer->height <= obstacles[i].y) // Upside: checks if the player is falling 
            {
                Player->y = obstacles[i].y - oldPlayer->height;     // sets the player on the obstacle
                *onGround = true;        // Now the player can jump again
                *velocityY = 0;         // That the player stops building vertical speed
            }
            else if (oldPlayer->y >= obstacles[i].y + obstacles[i].height) // Downside
            {
                Player->y = obstacles[i].y + obstacles[i].height;     // sets the player on the downside of the obstacle
                *onGround = false;       // The player shouldnt be able to jump if hes on the downside
                *velocityY = 0;          // Reset vertical speed, so the player falls
            }
            else if (oldPlayer->x < Player->x)  // Left side: checks if the player moved right
            {
                Player->x = obstacles[i].x - Player->width;     // sets the player on the Left side of the obstacle
            }
            else if (oldPlayer->x > Player->x)  // Right side: checks if the player moved left
            {
                Player->x = obstacles[i].x + obstacles[i].width;   // sets the player on the Right side of the obstacle
            }
            break;      // Only one collision at a frame
        }
        else
        {
            *onGround = false;   // if the player doesnt collide with or stand on an obstacle hes falling
        }
    }
}

Rectangle SideBarriers(Rectangle Player, const int windowWidht, const int windowHeight, float *velocityY)
{
    if(Player.x<0)       // Left side
    Player.x = 0;

if(Player.x + Player.width > windowWidht)     // Right side
    Player.x = windowWidht - Player.width;

if(Player.y < 0)       // Upside
{
    Player.y = 0;
    *velocityY = 0;
}
return Player;
}

Rectangle CatcherMarker_xy(Rectangle CatcherMarker, Rectangle Player)   // Setting the Coordinates for the Player Marker
{
    CatcherMarker.x = Player.x + Player.width / 2 - CatcherMarker.width / 2;
    CatcherMarker.y = Player.y - CatcherMarker.height;

    return CatcherMarker;
}

int main() 
{ 
    const int windowWidht = 878;         // Lenght of the Mainwindow
    const int windowHeight = 500;          // Widht of the Mainwindow

    InitWindow(windowWidht, windowHeight, "Catch_Game");        // Initialaising the Game Window

    int catcher = 1;        // determins who is the catcher( 0=Player1 , 1=Player2)
    int catchStreak = 0;  // number of Colliding player frames

    double timeLimit = 31;       // Maximal time (+1 for the start screen)
    double timePassed = timeLimit;       // Sum of the passed time since the round start 
    char timePrint[10];         // string for Printing the timer
    int timerSize = 40;         // Size for the printed timer 

    char roundCount = '1';         
    char roundPrint[16] = "0 - ROUND 1 - 0"; 
    int roundPrintSize = 60;     

    float gravity = 1600;           // Gravitation (Pixel per s^2)
    float playerspeed = 550;       // Movementspeed (Pixel per s)
    float jumpForce = -850;      // Jump force: is applied at the beginning of the jump to VerticalY and slowly 

    Rectangle Player1;   
    float velocityY1;           
    bool onGround1;
    float origPlayer1x = 150;
    Player1 = OrigPlayerVar(Player1, &velocityY1, &onGround1, origPlayer1x);     
    int Player1points = '0';

    Rectangle Player2;
    float velocityY2; 
    bool onGround2;
    float origPlayer2x = 550;
    Player2 = OrigPlayerVar(Player1, &velocityY2, &onGround2, origPlayer2x);
    int Player2points = '0';

    Rectangle CatcherMarker = { 0, 0, Player1.width / 2, (Player1.height * 2) / 3};    // Stays above the Catchers head

    Texture2D background = LoadTexture("textures\\Background.png");  // Loading Background Image
    Texture2D playertexture1 = LoadTexture("textures\\player1.png");
    //Texture2D playertexture2 = LoadTextureFromImage(playerimage2);

    // Initialising the Obstacles   
    Rectangle obstacles[NUM_OBSTACLES] = {
        { 0, windowHeight - 95, windowWidht, 95 },  // GROUND
        { 150, 300, 150, 20 },   // Platform 1
        { 500, 300, 150, 20 }    // Platform 2
    };

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime(); // Time in s since the last frame (Multiply with every speed)
        
        if(timePassed == 31)        // Printing Start screen
        {
            int roundPrintWidth = MeasureText(roundPrint, roundPrintSize);         // saving the text widht into a variable
            
            while(!IsKeyPressed(KEY_SPACE))
            {
                BeginDrawing();
                
                ClearBackground(RED);
                DrawText(roundPrint, (windowWidht - roundPrintWidth) / 2, (windowHeight - roundPrintSize) / 2, roundPrintSize, BLACK);  
                EndDrawing();
            }
            timePassed -= 1;
        }
        else if(timePassed <= 0.00)     // Resets the timer and Player variables if the round is over
        {
            Player1 = OrigPlayerVar(Player1, &velocityY1, &onGround1, origPlayer1x);
            Player2 = OrigPlayerVar(Player2, &velocityY2, &onGround2, origPlayer2x);
            
            timePassed = timeLimit;

            roundCount++;       // Next Round + 1
            roundPrint[10] = roundCount;    // Transform into ASCII (2 = 50)

            if(catcher==0)
                Player2points++;
            else
                Player1points++;

            roundPrint[0] = Player1points;
            roundPrint[14] = Player2points;
            
        }
        else
            timePassed -= dt;       // Reducing the passed time from the sumTime

        if(Player1points == '3')
        {
            while (1)
            { 
                BeginDrawing();
                ClearBackground(BLUE);
                EndDrawing();
            }
        }
        else if(Player2points == '3') 
        {
            while (1)
            { 
                BeginDrawing();
                ClearBackground(YELLOW);
                EndDrawing();
            }
        }
        Rectangle oldPlayer1 = Player1;
        Rectangle oldPlayer2 = Player2;     // saves the last postion of the player

        // Horizontal Movement with Arrow-Keys

        if(IsKeyDown(KEY_D))
        {
            Player1.x += playerspeed * dt;
        }
        else if(IsKeyDown(KEY_A))
        {
            Player1.x -= playerspeed * dt;
        }

        // Gravitational Pull
        velocityY1 += gravity * dt;
        Player1.y += velocityY1 * dt;
        
        if(IsKeyDown(KEY_RIGHT))
        {
            Player2.x += playerspeed * dt;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            Player2.x -= playerspeed * dt;
        }

        // Gravitational Pull2
        velocityY2 += gravity * dt;
        Player2.y += velocityY2 * dt;

        // Kollisionscheck

        Kollisionscheck(&Player1,&velocityY1, &gravity, &playerspeed,&jumpForce,&oldPlayer1,obstacles,&onGround1);
        Kollisionscheck(&Player2,&velocityY2, &gravity, &playerspeed,&jumpForce,&oldPlayer2,obstacles,&onGround2);
 
        // Jumping

        if (IsKeyPressed(KEY_W) && onGround1) {
            velocityY1 = jumpForce;
            onGround1 = false;
        }
        if (IsKeyPressed(KEY_UP) && onGround2) {
            velocityY2 = jumpForce;
            onGround2 = false;
        }

        // Side barriers

        Player1 = SideBarriers(Player1, windowWidht, windowHeight, &velocityY1);
        Player2 = SideBarriers(Player2, windowWidht, windowHeight, &velocityY2);

        // Checking if the players collide and setting the catchers
        
        if (CheckCollisionRecs(Player1, Player2))
        {
            if(catchStreak == 0)
            {
                if(catcher == 0)
                catcher = 1;
                else
                catcher = 0;

                catchStreak++;
            }
        }
        else 
            catchStreak = 0;

        // Setting the Coordinates of the CatcherMarker based on who is the Catcher
        if(catcher == 0)
            CatcherMarker = CatcherMarker_xy(CatcherMarker, Player1);
        else 
            CatcherMarker = CatcherMarker_xy(CatcherMarker, Player2);

       // Drawing the Frame
        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);

        // 5. Player texture
        DrawTexturePro(playertexture1, (Rectangle){ 0, 0, playertexture1.width, playertexture1.height }, 
            Player1, // Zielbereich mit Position und Größe wie Rechteck
            (Vector2){ 0, 0 }, // Kein Offset
            0.0f, // Keine Rotation
            WHITE); // Standardfarbe
        
            /*// 5. Player texture
        DrawTexturePro(playertexture2, (Rectangle){ 0, 0, playertexture2.width, playertexture2.height }, 
        Player2, // Zielbereich mit Position und Größe wie Rechteck
        (Vector2){ 0, 0 }, // Kein Offset
        0.0f, // Keine Rotation
        WHITE); // Standardfarbe
        */
       
        // Player Rectangles
        //DrawRectangleRec(Player1, BLUE);        
        DrawRectangleRec(Player2, YELLOW);

        // Obstacles
        for (int i = 1; i < NUM_OBSTACLES; i++) {
            DrawRectangleRec(obstacles[i], DARKBLUE);
        }
        
        DrawRectangleRec(CatcherMarker, RED);

        sprintf(timePrint, "%0.0f", timePassed);        // Converting the time into a string
        int textWidth = MeasureText(timePrint, timerSize);         // saving the text widht into a variable
        DrawText(timePrint, (windowWidht - textWidth) / 2, 0, timerSize, BLACK);    

        EndDrawing();
    }

    UnloadTexture(playertexture1);
    //UnloadTexture(playertexture2):
    UnloadTexture(background);
    CloseWindow();
    return 0;
}