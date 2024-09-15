#include <iostream>
#include <unistd.h>

const int WIDTH = 30;
const int HEIGHT = 13;
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT - 2);

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

int snake_dir = UP;

bool gameRunning = true;

char map[] =
"##############################\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"#                            #\n"
"##############################\n";

char snake = 'O';

int snake_x[MAX_LEN_SNAKE] = {0};
int snake_y[MAX_LEN_SNAKE] = {0};
int snake_len = 1;

void cleanScreen()
{
    std::cout << "\033[2J\033[H";
}

int main()
{
    snake_x[0] = WIDTH / 2;
    snake_y[0] = HEIGHT / 2;

    while (gameRunning)
    {
        cleanScreen();

        for (int i = 0; i < snake_len; ++i)
        {
            map[snake_y[i] * WIDTH + snake_x[i]] = snake;
        }
        std::cout << map << std::endl;
        usleep(200000);
    }

    return 0;
}