#include <raylib.h>
#define GRAVITY 400
#define NUM_OBSTACLES 3

int main() 
{ 
    const int windowWidht = 878;         // Lenght of the Mainwindow
    const int windowHeight = 500;          // Widht of the Mainwindow

    InitWindow(windowWidht, windowHeight, "Catch_Game");        // Initialaising the Game Window

    Texture2D background = LoadTexture("textures\\Background1.png");  // Loading Background Image

    Rectangle playerRec = { 150, 100, 50, 50 };        // Initialising the Player Rectangle   

    float velocityY = 0;        // Vertical velocity (+ ... the player falls, - ... flies up )
    float gravity = 800;        // Gravitation (Pixel per s^2)
    float playerspeed = 400;    // Movementspeed (Pixel per s)
    float jumpForce = -700;     // Jump force: is applied at the beginning of the jump to VerticalY and slowly 
    bool onGround = false;      // Checks if the player is on Ground

    Image playerimage = LoadImage("textures\\player_test.png"); // Loading the player image

    ImageColorReplace(&playerimage, WHITE, (Color){ 0, 0, 0, 0 }); // Weiß wird transparent
   
    // In eine Textur umwandeln
    Texture2D playertexture = LoadTextureFromImage(playerimage);
    UnloadImage(playerimage); // Originalbild freigeben

    // Initialising the Obstacles    

    Rectangle obstacles[NUM_OBSTACLES] = {
        { 0, windowHeight - 95, windowWidht, 95 },  // GROUND
        { 150, 300, 150, 20 },   // Platform 1
        { 500, 300, 150, 20 }    // Platform 2
    };

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
    float dt = GetFrameTime(); // Time since the last frame (Multiply with every speed)

        Rectangle oldPlayerRec = playerRec;     // saves the last postion of the player

        // Horizontal Movement with Arrow-Keys

        if(IsKeyDown(KEY_RIGHT))
        {
            playerRec.x += playerspeed * dt;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            playerRec.x -= playerspeed * dt;
        }

        // Gravitational Pull
        velocityY += gravity * dt;
        playerRec.y += velocityY * dt;

        // Kollisionscheck

        for (int i = 0; i < NUM_OBSTACLES; i++) {
            if (CheckCollisionRecs(playerRec, obstacles[i])) {
                if(oldPlayerRec.y + oldPlayerRec.height <= obstacles[i].y) // Upside: checks if the player is falling 
                {
                    playerRec.y = obstacles[i].y - oldPlayerRec.height;     // sets the player on the obstacle
                    onGround = true;        // Now the player can jump again
                    velocityY = 0;          // That the player stops building vertical speed
                }
                else if (oldPlayerRec.y >= obstacles[i].y + obstacles[i].height) // Downside
                {
                    playerRec.y = obstacles[i].y + obstacles[i].height;     // sets the player on the downside of the obstacle
                    onGround = false;       // The player shouldnt be able to jump if hes on the downside
                    velocityY = 0;          // Reset vertical speed, so the player falls
                }
                else if (oldPlayerRec.x < playerRec.x)  // Left side: checks if the player moved right
                {
                    playerRec.x = obstacles[i].x - playerRec.width;     // sets the player on the Left side of the obstacle
                }
                else if (oldPlayerRec.x > playerRec.x)  // Right side: checks if the player moved left
                {
                    playerRec.x = obstacles[i].x + obstacles[i].width;   // sets the player on the Right side of the obstacle
                }
                break;      // Only one collision at a frame
            }
            else
            {
                onGround = false;   // if the player doesnt collide with or stand on an obstacle hes falling
            }
        }

        // Jumping

        if (IsKeyPressed(KEY_UP) && onGround) {
            velocityY = jumpForce;
            onGround = false;
        }
       
        // Side barriers

        if(playerRec.x<0)       // Left side
            playerRec.x = 0;

        if(playerRec.x + playerRec.width > windowWidht)     // Right side
            playerRec.x = windowWidht - playerRec.width;

        if(playerRec.y < 0)       // Upside
        {
            playerRec.y = 0;
            velocityY = 0;
        }
        // Drawing the Frame

        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);

        // 5. Player texture
        DrawTexturePro(playertexture, 
            (Rectangle){ 0, 0, playertexture.width, playertexture.height }, 
            playerRec, // Zielbereich mit Position und Größe wie Rechteck
            (Vector2){ 0, 0 }, // Kein Offset
            0.0f, // Keine Rotation
            WHITE); // Standardfarbe
        
        //DrawRectangleRec(playerRec, PURPLE);        // Player Rectangle

        // Obstacles
        for (int i = 1; i < NUM_OBSTACLES; i++) {
            DrawRectangleRec(obstacles[i], PINK);
        }

        EndDrawing();
    }

    UnloadTexture(playertexture);
    UnloadTexture(background);
    CloseWindow();
    return 0;
}