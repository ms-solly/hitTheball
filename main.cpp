// nice job go ahead and and implement more features 

#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define W_WIDTH 1200
#define W_HEIGHT 600

int score = 0;

struct Ball
{
    float x, y;
    int speed_x, speed_y;
    int radius;
} ball;

struct Paddle
{
    float x,y;
    float width, height;
    int speed;

    // keep player limited space (shouldnt go outside window)
    void LimitMove()
    {
        if ( y <= 0)
        {
             y = 5;
        }
        if ( y + height >= GetScreenHeight())
        {
             y = GetScreenHeight() -  height - 5;
        }
    }
} player, computer;

void Vmouth();
void initialMouth();
void updateMouth();

void drawBall()
{
    // DrawCircle(ball.x, ball.y, ball.radius,WHITE);
    DrawCircle(ball.x, ball.y, ball.radius,WHITE);

    
    float amplitude = 5; // Amplitude of the wave (height of the wave)
    float frequency = 8; // Frequency of the wave (tightness of the wave)

    for (float y = -ball.radius; y <= ball.radius; y += 1.0f) {
        for (float x = -sqrtf(ball.radius * ball.radius - y * y); x <= sqrtf(ball.radius * ball.radius - y * y); x += 1.0f) {
            // Calculate the wave's displacement at this x-coordinate
            float waveY = amplitude * sinf(x / frequency);

            if (y > waveY) { // Below the wave
                DrawPixel(ball.x + x, ball.y + y, DARKGRAY);
            }
        }
    }


    for (float x = -ball.radius; x <= ball.radius; x += 1.0f) {
        // Calculate the wave's displacement along the y-axis
        float waveY = amplitude * sinf(x / frequency);

        // Ensure the wave stays within the circle's boundary
        float maxY = sqrtf(ball.radius * ball.radius - x * x); // Top and bottom boundary of the circle

        if (fabsf(waveY) <= maxY) { // Ensure the wave point is inside the circle
            DrawPixel(ball.x + x, ball.y + waveY, WHITE); // Draw the wave pixel
        }
    }


    // eyes
    DrawCircleV(Vector2{ball.x+ ball.radius/2 - 5,ball.y - ball.radius/2},5,BLACK);
    DrawCircleV(Vector2{ball.x- ball.radius/2 + 5,ball.y - ball.radius/2},5,BLACK);

    // ears 


    // mouth

}

void Vmouth()
{
    float vWidth = 40;
    float vHeight = 20;

    // Left point of the V (starting at the rectangle position)
    Vector2 vLeft = {ball.x - ball.radius / 5, ball.y - ball.radius / 4};
    
    // Right point of the V (ending at the rectangle position)
    Vector2 vRight = {ball.x - ball.radius / 5 + vWidth, ball.y - ball.radius / 4};

    // Top point of the V (moving upwards)
    Vector2 vTop = {ball.x, ball.y - ball.radius / 4 - vHeight};

    // Draw lines to form the V shape
    DrawLine(vLeft.x, vLeft.y, vTop.x, vTop.y, BLACK); // Left side of V
    DrawLine(vRight.x, vRight.y, vTop.x, vTop.y, BLACK); // Right side of V
}

void initialMouth()
{
    DrawRectangle(ball.x - ball.radius / 5, ball.y - ball.radius / 4, 40, 10, BLACK);
}

void updateBall()
{
    ball.x += ball.speed_x;
    ball.y += ball.speed_y;

    if ( ball.y + ball.radius >= GetScreenHeight() || ball.y - ball.radius <= 0)
    {
        ball.speed_y *= -1;
    }

    if ( ball.x + ball.radius >= GetScreenWidth() || ball.x - ball.radius <= 0)
    {
        ball.speed_x *= -1;
    }

}



void drawPaddle()
{
    DrawRectangle( player.x, player.y, player.width, player.height,WHITE);
}
void updatePlayer()
{
    if (IsKeyDown(KEY_UP))
    {
        player.y = player.y - player.speed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        player.y = player.y + player.speed;
    }

    player.LimitMove();
}


void drawCompPaddle()
{
    DrawRectangle( computer.x, computer.y, computer.width, computer.height,WHITE);
}

void updateComp(int ball_y)
{
    if (computer.y + computer.height/2 > ball_y)
    {
        computer.y = computer.y - computer.speed;
    }
    if (computer.y + computer.height/2 <= ball_y)
    {
        computer.y = computer.y + computer.speed;
    }

    computer.LimitMove();
}
void updateMouth()
{
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}) ||
        CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
    {
        Vmouth(); 
    }
    else
    {
        initialMouth(); 
    }
}


Vector2 v_ball = {ball.x, ball.y};

int main () {

    InitWindow(W_WIDTH,W_HEIGHT,"pong version");

    ball.radius     = 100;
    ball.x          = W_WIDTH/2;
    ball.y          = W_HEIGHT/2;
    ball.speed_x    = 1;
    ball.speed_y    = 1;

    player.width    = 25;
    player.height   = 125;
    player.x        = W_WIDTH - player.width - 10;
    player.y        = W_HEIGHT/2 - player.height/2;
    player.speed    = 6;

    computer.height = 120;
    computer.width  = 25;
    computer.x      = 10;
    computer.y      = W_HEIGHT/2 - computer.height/2;
    computer.speed  = 6;

    while(!WindowShouldClose())
    {
        BeginDrawing();
// update
        updateBall();
        updatePlayer();
        updateComp(ball.y);
        updateMouth();

// collision checking
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
            score +=1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
        {
            ball.speed_x *= -1;
        }
        

        ClearBackground(BLACK);
// draw
        DrawLine(W_WIDTH/2, 0, W_WIDTH/2, W_HEIGHT, WHITE);
        drawBall();
        drawCompPaddle();
        drawPaddle();
        bool playerCollide= CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}) || CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height});
        playerCollide? Vmouth(): initialMouth();

        DrawText(TextFormat("Score: %i", score), 10, 10, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
