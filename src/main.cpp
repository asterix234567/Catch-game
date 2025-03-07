#include <raylib.h>
#define GRAVITY 400
#define NUM_OBSTACLES 3

int main() 
{ 
    const int windowLenght = 800;         // Lenght of the Mainwindow
    const int windowWidht = 600;          // Widht of the Mainwindow

    int playerspeed = 4;

    InitWindow(windowLenght, windowWidht, "Catch_Game");

    Rectangle playerRec = { 400, 300, 50, 50 };        // Initialising the Player Rectangle   

    
    /*Image playerimage = 
    LoadImage("C:\Users\helene\Documents\checkouts\Catch-game\\textures\\player_test.png"); // Loading the player image
    
    // !!!Speicherort muss aktuell noch bei jedem gerät veröndert werden!!!

    ImageColorReplace(&playerimage, WHITE, (Color){ 0, 0, 0, 0 }); // Weiß wird transparent
   
    // In eine Textur umwandeln
    Texture2D playertexture = LoadTextureFromImage(playerimage);
    UnloadImage(playerimage); // Originalbild freigeben
*/
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
            playerRec.x += playerspeed;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            playerRec.x -= playerspeed;
        }
        else if(IsKeyDown(KEY_UP))
        {
            playerRec.y -= playerspeed;
        }
        else if(IsKeyDown(KEY_DOWN))
        {
            playerRec.y += playerspeed;
        }
        
        for (int i = 0; i < NUM_OBSTACLES; i++) {
            if (CheckCollisionRecs(playerRec, obstacles[i])) {
                // Zurücksetzen der Bewegung, falls Kollision
                playerRec.x -= playerspeed * (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
                playerRec.y -= playerspeed * (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP));
            }
        }
    
        if(playerRec.x<0)
            playerRec.x+=4;

        if(playerRec.x + playerRec.width > windowLenght)
        playerRec.x-=4;

        if(playerRec.y<0)
            playerRec.y+=4;
                
            
        BeginDrawing();
        ClearBackground(BLUE);

        /*// 5. Textur mit transparenter Darstellung anstatt des Rechtecks zeichnen
        DrawTexturePro(playertexture, 
            (Rectangle){ 0, 0, playertexture.width, playertexture.height }, // Quellbereich
            playerRec, // Zielbereich mit Position und Größe wie Rechteck
            (Vector2){ 0, 0 }, // Kein Offset
            0.0f, // Keine Rotation
            WHITE); // Standardfarbe
        */
        DrawRectangleRec(playerRec, PURPLE);

        for (int i = 0; i < NUM_OBSTACLES; i++) {
            DrawRectangleRec(obstacles[i], PINK);
        }

        EndDrawing();
    }

    //UnloadTexture(playertexture);
    CloseWindow();
    return 0;
}
