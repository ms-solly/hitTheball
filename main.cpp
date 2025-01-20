
#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define W_WIDTH 1200
#define W_HEIGHT 600

int score = 0;

typedef struct 
{
    float x, y;
    int speed_x, speed_y;
    int radius;
} Ball;

typedef struct 
{
    float x,y;
    float width, height;
    int speed;


} Paddle;

Ball ball;
Paddle player, computer;

void drawCompPaddle()
{
    DrawRectangle( computer.x, computer.y, computer.width, computer.height,WHITE);
}

void drawPaddle()
{
    DrawRectangle( player.x, player.y, player.width, player.height,WHITE);
}

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
    DrawRectangle(ball.x - ball.radius / 5, ball.y - ball.radius / 4, 40, 10, BLACK);

}
void LimitMove(Paddle *p)
{
  if ( p->y <= 0)
  {
       p->y = 5;
 }
  if (  p->y +  p->height >= GetScreenHeight())
  {
           p->y = GetScreenHeight() -   p->height - 5;
     }
}

void updateBall()
{
    // ball.x += ball.speed_x;
    // ball.y += ball.speed_y;
    ball.x += ball.speed_x * GetFrameTime() * 60;
    ball.y += ball.speed_y * GetFrameTime() * 60;

    if ( ball.y + ball.radius >= GetScreenHeight() || ball.y - ball.radius <= 0)
    {
        ball.speed_y *= -1;
    }

    if ( ball.x + ball.radius >= GetScreenWidth() || ball.x - ball.radius <= 0)
    {
        ball.speed_x *= -1;
    }
// collision check
     if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
      {
        ball.speed_x *= -1;
        score +=1;
       }

      if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
      {
          ball.speed_x *= -1;
      }

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

    LimitMove(&player);
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
    LimitMove(&computer);
}



Vector2 v_ball = {ball.x, ball.y};

int main () {

    InitAudioDevice();
    Sound fly = LoadSound("");
    SetSoundVolume(fly, 1.0f);
    SetTargetFPS(60);

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

// collision checking
     if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
      {
        PlaySound(fly);
       }
       else
       {
        StopSound(fly);
       }

      if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
      {
        PlaySound(fly);
      }
      else
      {
        StopSound(fly);
      }

        ClearBackground(BLACK);
// draw
        DrawLine(W_WIDTH/2, 0, W_WIDTH/2, W_HEIGHT, WHITE);
        drawBall();
        drawCompPaddle();
        drawPaddle();


        DrawText(TextFormat("Score: %i", score), 10, 10, 20, LIGHTGRAY);
        EndDrawing();
    }
    UnloadSound(fly);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}
