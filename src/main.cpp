#include <raylib.h>
#define GRAVITY 400
#define NUM_OBSTACLES 3

void Kollisionscheck(Rectangle Player,float velocityY,float gravity,
                    float playerspeed,float jumpForce, bool ,Rectangle oldPlayer, Rectangle obstacles[]){
    // Kollisionscheck

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        if (CheckCollisionRecs(Player, obstacles[i])) {
            if(oldPlayer + oldPlayer.height <= obstacles[i].y) // Upside: checks if the player is falling 
            {
                Player.y = obstacles[i].y - oldPlayer1.height;     // sets the player on the obstacle
                onGround = true;        // Now the player can jump again
                velocityY = 0;          // That the player stops building vertical speed
            }
            else if (oldPlayer >= obstacles[i].y + obstacles[i].height) // Downside
            {
                Player1.y = obstacles[i].y + obstacles[i].height;     // sets the player on the downside of the obstacle
                onGround1 = false;       // The player shouldnt be able to jump if hes on the downside
                velocityY1 = 0;          // Reset vertical speed, so the player falls
            }
            else if (oldPlayerRec.x < Player1.x)  // Left side: checks if the player moved right
            {
                Player1.x = obstacles[i].x - Player1.width;     // sets the player on the Left side of the obstacle
            }
            else if (oldPlayer1.x > Player1.x)  // Right side: checks if the player moved left
            {
                Player1.x = obstacles[i].x + obstacles[i].width;   // sets the player on the Right side of the obstacle
            }
            break;      // Only one collision at a frame
        }
        else
        {
            onGround = false;   // if the player doesnt collide with or stand on an obstacle hes falling
        }
    }
}


int main() 
{ 
    const int windowWidht = 878;         // Lenght of the Mainwindow
    const int windowHeight = 500;          // Widht of the Mainwindow

    InitWindow(windowWidht, windowHeight, "Catch_Game");        // Initialaising the Game Window

    Texture2D background = LoadTexture("textures\\Background1.png");  // Loading Background Image

    Rectangle Player1 = { 150, 100, 50, 50 };        // Initialising the Player Rectangle   

    float velocityY1 = 0;            // Vertical velocity (+ ... the player falls, - ... flies up )
    float gravity = 800;           // Gravitation (Pixel per s^2)
    float playerspeed = 400;       // Movementspeed (Pixel per s)
    float jumpForce1 = -700;      // Jump force: is applied at the beginning of the jump to VerticalY and slowly 
    bool onGround1 = false;      // Checks if the player is on Ground
                                //player speed und gravity sind konstant bei beide spieler
    Rectangle Player2 = { 150, 100, 50, 50 };        // Initialising the Player Rectangle   

    float velocityY2 = 0;        // Vertical velocity (+ ... the player falls, - ... flies up )
           // Gravitation (Pixel per s^2)
    float jumpForce2 = -700;     // Jump force: is applied at the beginning of the jump to VerticalY and slowly 
    bool onGround2 = false;      // Checks if the player is on Ground
    Image playerimage1 = LoadImage("textures\\player_test.png"); // Loading the player image
    Image playerimage2 = LoadImage("textures\\player_test.png");    ImageColorReplace(&playerimage2, WHITE, (Color){ 0, 0, 0, 0 }); // Weiß wird transparent
   
    // In eine Textur umwandeln
    Texture2D playertexture = LoadTextureFromImage(playerimage1);
    UnloadImage(playerimage1); // Originalbild freigeben
    Texture2D playertexture = LoadTextureFromImage(playerimage2);
    UnloadImage(playerimage2); // Originalbild freigeben
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
        Rectangle oldPlayer1=Player1;
        Rectangle oldPlayer2 =Player2;     // saves the last postion of the player

        // Horizontal Movement with Arrow-Keys

        if(IsKeyDown(KEY_RIGHT))
        {
            Player1.x += playerspeed * dt;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            Player1.x -= playerspeed * dt;
        }

        // Gravitational Pull
        velocityY1 += gravity * dt;
        Player1.y += velocityY1 * dt;
        
        if(IsKeyDown(KEY_D))
        {
            Player2.x += playerspeed * dt;
        }
        else if(IsKeyDown(KEY_A))
        {
            Player2.x -= playerspeed * dt;
        }

        // Gravitational Pull2
        velocityY2 += gravity * dt;
        Player2.y += velocityY2 * dt;

            // Kollisionscheck

        Kollisionscheck(Player1,velocityY1, gravity, playerspeed,jumpForce1,onGround1,obstacles);
        Kollisionscheck(Player2,velocityY2, gravity, playerspeed,jumpForce2,onGround2,obstacles )

        // Jumping

        if (IsKeyPressed(KEY_UP) && onGround1) {
            velocityY1 = jumpForce1;
            onGround1 = false;
        }
       
        // Side barriers

        if(Player1.x<0)       // Left side
            Player1.x = 0;

        if(Player1.x + Player1.width > windowWidht)     // Right side
            Player1.x = windowWidht - Player1.width;

        if(Player1.y < 0)       // Upside
        {
            Player1.y = 0;
            velocityY = 0;
        }
        // Drawing the Frame

        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);

        // 5. Player texture
        DrawTexturePro(playertexture, 
            (Rectangle){ 0, 0, playertexture.width, playertexture.height }, 
            Player1, // Zielbereich mit Position und Größe wie Rechteck
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