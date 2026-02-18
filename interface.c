#include <ncurses.h>
#include "interface.h"

Vec2 new_vec2(int x, int y){
    Vec2 new = {x, y};
    return new;
}

void draw_horizontal_border(Vec2 start_position, int location){
   char* left_corner = location == SNAKE_BORDER_TOP ? "╔" : "╚";
   char* right_corner = location == SNAKE_BORDER_TOP ? "╗" : "╝";
   int y_position = location == SNAKE_BORDER_TOP ? start_position.y : start_position.y + SNAKE_AREA_HEIGHT - 1;
   mvprintw(y_position, start_position.x, "%s", left_corner);
   mvprintw(y_position, start_position.x + SNAKE_AREA_WIDTH - 1, "%s", right_corner);
   for(int x = start_position.x + 1; x < start_position.x + SNAKE_AREA_WIDTH - 1; x++){
       mvprintw(y_position, x, "═");
   }
}

void draw_box(Vec2 screen_size, int border_color, int field_color){
    Vec2 start = {START_X(screen_size.x), START_Y(screen_size.y)};
    attron(COLOR_PAIR(border_color));
    draw_horizontal_border(start, SNAKE_BORDER_TOP);
    for(int y = start.y + 1; y < start.y + SNAKE_AREA_HEIGHT - 1; y++){
        mvprintw(y, start.x, "║");
        attroff(COLOR_PAIR(border_color));
        attron(COLOR_PAIR(field_color));
        for(int x = start.x + 1; x < start.x + SNAKE_AREA_WIDTH - 1; x++){
            mvprintw(y, x, "█");
        }
        attroff(COLOR_PAIR(field_color));
        attron(COLOR_PAIR(border_color));
        mvprintw(y, start.x + SNAKE_AREA_WIDTH - 1, "║");
    }
    draw_horizontal_border(start, SNAKE_BORDER_BOTTOM);
    attroff(COLOR_PAIR(border_color));
}
