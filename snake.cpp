#include <ncurses.h>
#include <unistd.h>

const int WIDTH = 30;
const int HEIGHT = 13;
const int MAX_LEN_SNAKE = (WIDTH - 2) * (HEIGHT - 2);

bool gameRunning = true;

char map[HEIGHT][WIDTH + 1] = {
    "##############################",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "##############################"
};

char snake = 'O';
int snake_x[MAX_LEN_SNAKE] = {0};
int snake_y[MAX_LEN_SNAKE] = {0};
int snake_len = 1;

int snakeDir = 0; // 0 - UP, 1 - DOWN, 2 - RIGHT, 3 - LEFT

void drawMap() 
{
    clear();  

    for (int y = 0; y < HEIGHT; ++y) 
    {
        for (int x = 0; x < WIDTH; ++x) 
        {
            mvaddch(y, x, map[y][x]);
        }
    }
    refresh();
}

void updateSnake() 
{
    for (int i = snake_len - 1; i > 0; --i) 
    {
        snake_x[i] = snake_x[i - 1];
        snake_y[i] = snake_y[i - 1];
    }
}

void placeSnake() 
{
    for (int i = 0; i < snake_len; ++i) 
    {
        map[snake_y[i]][snake_x[i]] = snake;
    }
}

void clearSnake() 
{
    for (int i = 0; i < snake_len; ++i) 
    {
        map[snake_y[i]][snake_x[i]] = ' ';
    }
}

void snakeMovement()
{
    switch (snakeDir)
    {
        case 0: // UP
            --snake_y[0];
            break;
        case 1: // DOWN
            ++snake_y[0];
            break;
        case 2: // RIGHT
            ++snake_x[0];
            break;
        case 3: // LEFT
            --snake_x[0];
            break;
    }
}

int main() {
    initscr();  
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    timeout(100);

    snake_x[0] = WIDTH / 2;
    snake_y[0] = HEIGHT / 2;

    while (gameRunning) 
    {
        
        int ch = getch();

        switch (ch) 
        {
            case KEY_UP:
                snakeDir = 0;
                break;
            case KEY_DOWN: 
                snakeDir = 1;
                break;
            case KEY_RIGHT: 
                snakeDir = 2; 
                break;
            case KEY_LEFT: 
                snakeDir = 3; 
                break;
            case 'q':
                gameRunning = false;
                break;
        }

        clearSnake();
        updateSnake();
        snakeMovement();

        if (snake_x[0] < 1 || snake_x[0] >= WIDTH - 1 || snake_y[0] < 1 || snake_y[0] >= HEIGHT - 3)
        {
            gameRunning = false;
        }

        placeSnake();
        drawMap();

        usleep(150000);
    }

    endwin();
    return 0;
}