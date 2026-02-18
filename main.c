#include <complex.h>
#include <locale.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "interface.h"
#include "snake.h"


uint score = 0;
int main(){
    setlocale(LC_ALL, "");
    Vec2 screen_size;
    Vec2 apple_position = {(rand() % (SNAKE_AREA_WIDTH - 2)) + 1, (rand() % (SNAKE_AREA_HEIGHT - 2)) + 1};
    uint temp_score = 0;
    Snake* snake = new_snake();
    snake->nodes[0] = new_vec2(2, 1);
    snake->nodes[1] = new_vec2(1, 1);
    snake->nodes[2] = new_vec2(1, 0);
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_GREEN);
    init_pair(4, COLOR_RED, COLOR_GREEN);
    keypad(stdscr, 1);
    timeout(0);
    getmaxyx(stdscr, screen_size.y, screen_size.x);
    while(1){
        score += move_snake(snake, apple_position);
        if(snake->reset){
            score = reset_snake(snake);
        }
        if(temp_score != score){
            apple_position.x = (rand() % (SNAKE_AREA_WIDTH - 3)) + 1;
            apple_position.y = (rand() % (SNAKE_AREA_HEIGHT - 3)) + 1;
            temp_score = score;
        }
        int c = getch();
        if(c == KEY_UP && snake->direction != DOWN)
            snake->direction = UP;
        if(c == KEY_DOWN && snake->direction != UP)
            snake->direction = DOWN;
        if(c == KEY_LEFT && snake->direction != RIGHT)
            snake->direction = LEFT;
        if(c == KEY_RIGHT && snake->direction != LEFT)
            snake->direction = RIGHT;
        if(c == 'q')
            break;
        mvprintw(START_Y(screen_size.y) - 1, screen_size.x / 2 - 5, "Snake game");
        mvprintw(START_Y(screen_size.y) - 1, START_X(screen_size.x), "Score: %d", score);
        draw_box(screen_size, 1, 2);
        draw_apple(apple_position, screen_size, 4);
        draw_snake(snake, screen_size, 3);
        mvprintw(screen_size.y - 1, screen_size.x - 1, "q");
        refresh();
        usleep(150000);
    }
    endwin();
    free_snake(snake);
    return 0;
}
