#pragma once

// Width of the rectangle
#define SNAKE_AREA_WIDTH 50
// Height of the rectangle
#define SNAKE_AREA_HEIGHT 25

// Pass this to "int location" in draw_horizontal_border to draw border on top
#define SNAKE_BORDER_TOP 0
// Pass this to "int location" in draw_horizontal_border to draw border from below
#define SNAKE_BORDER_BOTTOM 1

// Get start point of the rectangle (x)
#define START_X(screen_width) (screen_width / 2 -  SNAKE_AREA_WIDTH / 2)
// Get start point of the rectangle (y)
#define START_Y(screen_height) (screen_height / 2 - SNAKE_AREA_HEIGHT/2)

// A 2-d vector structure
typedef struct{
    int x;
    int y;
} Vec2;

// Create a new 2-d vector
Vec2 new_vec2(int x, int y);
// Draw the game rectange
void draw_box(Vec2 screen_size, int border_color, int field_color);
// Draw a horizontal border for the rectangle, int location must be 0 (SNAKE_BORDER_TOP) or 1 (SNAKE_BORDER_BOTTOM)
void draw_horizontal_border(Vec2 start_position, int location);
