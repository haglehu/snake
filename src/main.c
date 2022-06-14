#include <raylib.h>
#include <stdlib.h>
#include "config.h"
#include "Cell.h"
#include <stdio.h>

typedef enum state
{
menu,
running,
paused,
dead,
reset
} state;

typedef struct Snake
{
    Vector2 head;
    Cell* body;
} Snake;

void drawRect(int x, int y, Color core, Color border)
{
    x *= SQUARESIZE;
    y *= SQUARESIZE;

    DrawRectangle(x, y, SQUARESIZE, SQUARESIZE, border);
    DrawRectangle(x + BORDERSIZE, y + BORDERSIZE,
                  SQUARESIZE - 2*BORDERSIZE, SQUARESIZE - 2*BORDERSIZE, core);
}

bool vecEq(Vector2 v1, Vector2 v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

void generateApple(Vector2* apple, Snake sn)
{
    while (collides(*apple, sn.body) || vecEq(sn.head, *apple))
    {
        apple->x = GetRandomValue(0, SIZE/SQUARESIZE - 1);
        apple->y = GetRandomValue(0, SIZE/SQUARESIZE - 1);
    }
}

int main(void)
{
    Cell* tmp;
    unsigned long long int time = 1;
    int highScore = 0;

    Vector2 input = {1,0};
    Vector2 dir = {1,0};

    int score = 0;
    Snake snake = {{8,5}};
    state gameState = reset;
    Vector2 apple = {8,5};

    snake.body = malloc(sizeof(Cell));

    SetTargetFPS(30);
    InitWindow(SIZE, SIZE, TITLE);
    SetExitKey(KEY_ESCAPE);

    while (!WindowShouldClose())
    {
    /*
    * Calculation
    */

        switch (gameState)
        {
            /*
            ** resets variables after death
             */
            case reset:
            {
                if (score > highScore)
                {
                    highScore = score;
                }

                score = 0;

                dir.x = 1;
                dir.y = 0;

                input.x = 0;
                input.y = 0;

                snake.head.x = 8;
                snake.head.y = 5;

                //free(snake.body->next);
                //snake.body->next = NULL;

                clearList(snake.body);

                snake.body->x = 6;
                snake.body->y = 5;

                append(&snake.body, 7, 5);

                generateApple(&apple, snake);

                gameState = menu;
            } break;

            case menu:
            {
                if (IsKeyDown(PAUSE_KEY))
                {
                    gameState = running;
                }
            } break;

            case running:
            {

                time += (int) (1e3 * GetFrameTime());

                /*
                 *   Input
                 */

                switch (GetKeyPressed()) {
                    case KEY_LEFT:
                    {
                        input.x = -1;
                        input.y = 0;
                    } break;

                    case KEY_RIGHT:
                    {
                        input.x = 1;
                        input.y = 0;
                    } break;

                    case KEY_UP:
                    {
                        input.y = -1;
                        input.x = 0;
                    } break;

                    case KEY_DOWN:
                    {
                        input.y = 1;
                        input.x = 0;
                    } break;

                    case PAUSE_KEY:
                    {
                        gameState = paused;
                    } break;
                }

                if (time > SPEED)
                {
                    time -= SPEED;

                    /*
                    *    Basic Movement
                     */
                    if (dir.x * -1 != input.x && input.y * -1 != dir.y)
                    {
                        dir = input;
                    }

                    append(&snake.body, snake.head.x, snake.head.y);

                    snake.head.x += dir.x;
                    snake.head.y += dir.y;

                    /*
                    *    Collision and Apple
                    */

                    if (snake.head.x == apple.x && snake.head.y == apple.y)
                    {
                        score++;
                        generateApple(&apple, snake);
                    }
                    else
                    {
                        removeLast(snake.body);
                    }

                    if (collides(snake.head, snake.body)
                        || snake.head.x < 0
                        || snake.head.y < 0
                        || snake.head.x > SIZE/ SQUARESIZE - 1
                        ||snake.head.y > SIZE/SQUARESIZE - 1)
                    {
                        gameState = dead;
                    }
                }
            } break;

            case dead:
            {
                if(IsKeyReleased(PAUSE_KEY))
                {
                    gameState = reset;
                }
            } break;

            case paused:
            {
                if (IsKeyPressed(PAUSE_KEY))
                {
                    gameState = running;
                }
            } break;
        }


        BeginDrawing();
        ClearBackground(DARKGRAY);

        /*
         * Snake drawing Code
         */

        drawRect(apple.x, apple.y, RED, MAROON);

        tmp = snake.body;

        while (tmp != NULL)
        {
            drawRect(tmp->x, tmp->y, LIME, DARKGREEN);
            tmp = tmp->next;
        }

        drawRect(snake.head.x, snake.head.y, GREEN, LIME);

        DrawText(TextFormat("Score: %d", score), 10, 10, 30, BLACK);

        switch (gameState) {
            case running:
            {

            } break;

            case reset:
            {

            }break;

            case menu:
            {
                DrawRectangle(0, 0, SIZE, SIZE, ColorAlpha(BLACK, 0.7f));
                DrawText("SNAKE", 190, 300, 100, GRAY);
                DrawText("PRESS ENTER TO START", 120, 400, 40, GRAY);
            } break;

            case dead:
            {
                DrawRectangle(0, 0, SIZE, SIZE, ColorAlpha(BLACK, 0.7f));
                DrawText("Dead", 270, 300, 100, GRAY);
                DrawText(TextFormat("Score: %d", score), 300, 400, 40, GRAY);

                if (score > highScore)
                {
                    DrawText("NEW HIGHSCORE!", 250, 500, 40, GRAY);
                }

            } break;

            case paused:
            {
                DrawRectangle(0, 0, SIZE, SIZE, ColorAlpha(BLACK, 0.7f));
                DrawText("PAUSED", 190, 300, 100, GRAY);
                DrawText("PRESS ENTER TO CONTINUE", 120, 400, 40, GRAY);
            } break;
        }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
