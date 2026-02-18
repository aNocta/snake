#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"
#include "interface.h"

Snake* new_snake(){
    Vec2* nodes = malloc(sizeof(Vec2) * 3);
    Snake* new_snake = malloc(sizeof(Snake));
    new_snake->nodes = nodes;
    new_snake->size = 3;
    new_snake->direction = RIGHT;
    new_snake->reset = 0;
    return new_snake;
}

void push_to_snake(Snake* snake, Vec2 position){
    snake->size++;
    snake->nodes = realloc(snake->nodes, sizeof(Vec2) * snake->size);
    snake->nodes[snake->size - 1] = position;
}

void eat_an_apple(Snake* snake){
    Vec2 new_node_pos;
    switch (snake->direction) {
        case UP:
            new_node_pos.x = snake->nodes[snake->size - 1].x;
            new_node_pos.y = snake->nodes[snake->size - 1].y + 1;
            break;
        case DOWN:
            new_node_pos.x = snake->nodes[snake->size - 1].x;
            new_node_pos.y = snake->nodes[snake->size - 1].y - 1;
            break;
        case LEFT:
            new_node_pos.x = snake->nodes[snake->size - 1].x + 1;
            new_node_pos.y = snake->nodes[snake->size - 1].y;
            break;
        case RIGHT:
            new_node_pos.x = snake->nodes[snake->size - 1].x - 1;
            new_node_pos.y = snake->nodes[snake->size - 1].y;
            break;
    }
    push_to_snake(snake, new_node_pos);
}

int move_snake(Snake* snake, Vec2 apple_position){
    int points = 0;
    if(snake->direction == LEFT || snake->direction == RIGHT){
        snake->nodes[0].x += snake->direction == RIGHT ? 1 : -1;
        snake->nodes[0].x = CHECK_HORIZONTAL_BORDERS(snake->nodes[0].x);
    }else{
        snake->nodes[0].y += snake->direction == DOWN ? 1 : -1;
        snake->nodes[0].y = CHECK_VERTICAL_BORDERS(snake->nodes[0].y);
    }
    Vec2 prev = snake->nodes[0];
    for(size_t i = 1; i < snake->size; i++){
        Vec2 temp = snake->nodes[i];
        snake->nodes[i].x = prev.x;
        snake->nodes[i].y = prev.y;
        prev = temp;
        if(i > 1 && snake->nodes[i].x == snake->nodes[0].x && snake->nodes[i].y == snake->nodes[0].y){
            snake->reset = i;
            return 0;
        }
    }



    if(snake->nodes[0].x == apple_position.x && snake->nodes[0].y == apple_position.y){
        eat_an_apple(snake);
        points++;
    }
    return points;
}

void free_snake(Snake* snake){
    free(snake->nodes);
    free(snake);
}

void draw_snake(Snake* snake, Vec2 screen_size, int color){
    Vec2 start = {START_X(screen_size.x), START_Y(screen_size.y)};
    attron(COLOR_PAIR(color));
    for(int y = start.y + 1; y < start.y + SNAKE_AREA_HEIGHT - 1; y++){
        for(int x = start.x + 1; x < start.x + SNAKE_AREA_WIDTH - 1; x++){
           for(int n = 0; n < snake->size; n++){
               if(snake->nodes[n].x == x - start.x - 1 && snake->nodes[n].y == y - start.y - 1){
                   mvprintw(y, x, "█");
                   //mvprintw(y, x, "%d", n);
               }
           }
        }
    }
    attroff(COLOR_PAIR(color));
}

int reset_snake(Snake* snake){
    int score;
    snake->size = snake->reset;
    score = snake->reset - 3;
    snake->nodes = realloc(snake->nodes, sizeof(Vec2) * snake->size);
    snake->reset = 0;
    clear();
    return score;
}

void draw_apple(Vec2 position, Vec2 screen_size, int color){
    Vec2 start = {START_X(screen_size.x), START_Y(screen_size.y)};
    attron(COLOR_PAIR(color));
    mvprintw(start.y + 1 + position.y, start.x + 1 + position.x, "█");
    attroff(COLOR_PAIR(color));
}
