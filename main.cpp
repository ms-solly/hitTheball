// nice job go ahead and and implement more features 

#include <stdio.h>
#include <raylib.h>

#define W_WIDTH 1200
#define W_HEIGHT 600

int score = 0;

struct Ball
{
    float x, y;
    int speed_x, speed_y;
    int radius;
} ball;

void drawBall()
{
    DrawCircle(ball.x, ball.y, ball.radius,WHITE);

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

Vector2 v_ball = {ball.x, ball.y};

int main () {

    InitWindow(W_WIDTH,W_HEIGHT,"pong version");

    ball.radius     = 20;
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
        
        DrawText(TextFormat("Score: %i", score), 10, 10, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
