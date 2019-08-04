#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define END 27
#define WIDTH 120
#define HEIGHT 30
#define PANEL_X 2
#define PANEL_Y 2
#define SPEED_X3 1
#define SPEED_X2 10
#define SPEED_X1 100
#define SPEED_DEBUG 500

typedef struct{
    int x;
    int y;
    int dir;
    char look;
}partOfSnake;

typedef struct{
    int x;
    int y;
    int safe;
    float time;
    char look;
}food;

typedef struct{
    int x;
    int y;
    int dir;
    int enabled;
}bend;

food f;
int bendCount = 0;
bend bArray[100];
COORD coord = {0, 0};

void go_to_xy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void game_board(){
    int x, y;
    for(x=PANEL_X; x<WIDTH; x++){
        go_to_xy(x, PANEL_Y);
        printf("*");
        go_to_xy(x, HEIGHT);
        printf("*");
    }
    for(y=PANEL_Y; y<HEIGHT; y++){
        go_to_xy(PANEL_X, y);
        printf("*");
        go_to_xy(WIDTH, y);
        printf("*");
    }
}

void draw_snake(partOfSnake array[], int length){
    int i, j;
    for(i=0; i<=length; i++){
        for(j=0; j<bendCount; j++){
            if(array[i].x == bArray[j].x && array[i].y == bArray[j].y){
                if(bArray[j].enabled){
                    array[i].dir = bArray[j].dir;
                }
                if(i == length){
                    bArray[j].enabled = 0;
                }
            }
        }
        if(array[i].dir == RIGHT){
            array[i].x = array[i].x + 1;
        }
        if(array[i].dir == LEFT){
            array[i].x = array[i].x - 1;
        }
        if(array[i].dir == DOWN){
            array[i].y = array[i].y + 1;
        }
        if(array[i].dir == UP){
            array[i].y = array[i].y - 1;
        }
        go_to_xy(array[i].x, array[i].y);
        printf("%c", array[i].look);
    }
}

void generate_food(int x, int y, float time, int s){
    f.x = x;
    f.y = y;
    f.time = time;
    if(s == 1){
        f.safe = 1;
        f.look = 'f';
    }else {
        f.safe = 0;
        f.look = 'p';
    }
    go_to_xy(f.x, f.y);
    printf("%c", f.look);
}

int game_over(partOfSnake array[], int length){
    int i;
    if(array[0].x >= WIDTH || array[0].y >= HEIGHT || array[0].x <= PANEL_X || array[0].y <= PANEL_Y)
        return 1;
    for(i=1; i<=length; i++){
        if(array[0].x == array[i].x && array[0].y == array[i].y)
            return 1;
    }
    return 0;
}

int main() {

    int i, x = 15, y = 10, snakeLength = 5;

    partOfSnake array[100];
    array[0].x = x;
    array[0].y = y;
    array[0].dir = RIGHT;
    array[0].look = '>';

    for(i=1; i<=snakeLength; i++){
        array[i].x = --x;
        array[i].y = y;
        array[i].dir = RIGHT;
        array[i].look = '+';
    }

    int foodX = rand() % (WIDTH - 1) + 2;
    int foodY = rand() % (HEIGHT - 1) + 2;
    float foodTime = rand() % (15) + 5;
    int foodS = rand() % 2;
    time_t startTime = time(NULL);

    while(!game_over(array, snakeLength)){
        game_board();
        generate_food(foodX, foodY, foodTime, foodS);
        draw_snake(array, snakeLength);

        if(time(NULL) - startTime > f.time){
            foodX = rand() % (WIDTH - 1) + 2;
            foodY = rand() % (HEIGHT - 1) + 2;
            foodTime = rand() % (15) + 5;
            foodS = rand() % 2;
            startTime = time(NULL);
        }

        if(array[0].x == f.x && array[0].y == f.y){
            if(f.safe == 0){
                break;
            }
            foodX = rand() % (WIDTH - 1) + 2;
            foodY = rand() % (HEIGHT - 1) + 2;
            foodTime = rand() % (15) + 5;
            foodS = rand() % 2;
            snakeLength++;
            if(array[snakeLength - 1].dir == LEFT){
                array[snakeLength].x = array[snakeLength - 1].x + 1;
                array[snakeLength].y = array[snakeLength - 1].y;
                array[snakeLength].dir = array[snakeLength - 1].dir;
                array[snakeLength].look = '!';
            }
            if(array[snakeLength - 1].dir == RIGHT){
                array[snakeLength].x = array[snakeLength - 1].x - 1;
                array[snakeLength].y = array[snakeLength - 1].y;
                array[snakeLength].dir = array[snakeLength - 1].dir;
                array[snakeLength].look = '!';
            }
            if(array[snakeLength - 1].dir == UP){
                array[snakeLength].x = array[snakeLength - 1].x;
                array[snakeLength].y = array[snakeLength - 1].y - 1;
                array[snakeLength].dir = array[snakeLength - 1].dir;
                array[snakeLength].look = '!';
            }
            if(array[snakeLength - 1].dir == DOWN){
                array[snakeLength].x = array[snakeLength - 1].x;
                array[snakeLength].y = array[snakeLength - 1].y + 1;
                array[snakeLength].dir = array[snakeLength - 1].dir;
                array[snakeLength].look = '!';
            }
        }

        if(kbhit()){
            int ch = getch();
            if(ch == END)
                break;
            if(ch == RIGHT){
                if(array[0].dir != LEFT){
                    bArray[bendCount].x = array[0].x;
                    bArray[bendCount].y = array[0].y;
                    bArray[bendCount].dir = RIGHT;
                    bArray[bendCount].enabled = 1;
                    bendCount++;
                    array[0].look = '>';
                }
            }
            if(ch == LEFT){
                if(array[0].dir != RIGHT){
                    bArray[bendCount].x = array[0].x;
                    bArray[bendCount].y = array[0].y;
                    bArray[bendCount].dir = LEFT;
                    bArray[bendCount].enabled = 1;
                    bendCount++;
                    array[0].look = '<';
                }
            }
            if(ch == UP){
                if(array[0].dir != DOWN){
                    bArray[bendCount].x = array[0].x;
                    bArray[bendCount].y = array[0].y;
                    bArray[bendCount].dir = UP;
                    bArray[bendCount].enabled = 1;
                    bendCount++;
                    array[0].look = '^';
                }
            }
            if(ch == DOWN){
                if(array[0].dir != UP){
                    bArray[bendCount].x = array[0].x;
                    bArray[bendCount].y = array[0].y;
                    bArray[bendCount].dir = DOWN;
                    bArray[bendCount].enabled = 1;
                    bendCount++;
                    array[0].look = 'v';
                }
            }
        }

        Sleep(SPEED_X2);
        system("CLS");
    }

}
