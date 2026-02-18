#pragma once

#include "interface.h"

// Move top
#define UP 0
// Move down
#define DOWN 1
// Move to the left
#define LEFT 2
// Move to the right
#define RIGHT 3

// Checking whether the head goes beyond the horizontal borders
#define CHECK_HORIZONTAL_BORDERS(position) (position >= SNAKE_AREA_WIDTH - 2 ? 0 : (position < 0 ? SNAKE_AREA_WIDTH - 3 : position))
// Checking whether the head goes beyond the vertical borders
#define CHECK_VERTICAL_BORDERS(position) (position >= SNAKE_AREA_HEIGHT - 2 ? 0 : (position < 0 ? SNAKE_AREA_HEIGHT - 3 : position))

// Snake structure
typedef struct {
    // Direction of movement
    int direction;
    // Parts of the snake, zero is the head
    Vec2* nodes;
    // Number of parts
    int size;
    int reset;
} Snake;

// Snake object creation
Snake* new_snake();
// Add new node to snake
void push_to_snake(Snake* snake, Vec2 position);
// push_to_snake depending on the direction
void eat_an_apple(Snake* snake);
// Move the snake
int move_snake(Snake* snake, Vec2 apple_position);
// Free all nodes and the snake itself
void free_snake(Snake* snake);
// Draw the snake
void draw_snake(Snake* snake, Vec2 screen_size, int color);
// Decrease game score and shorten the tail
int reset_snake(Snake* snake);
// Draw an apple
void draw_apple(Vec2 position, Vec2 screen_size, int color);
