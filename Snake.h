#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

typedef struct body_t body_t;
struct body_t {
	int		x;
	int		y;
	body_t* tail;
};

typedef struct snake_t snake_t;
struct snake_t {
	body_t	body;
	int		dir;	/* 1 = up, 2 = down, 3 = left, 4 = right */
	int		field_width;
	int		field_height;
	int		tile_size;
	int		game_mode;
};

void init_snake(snake_t* s, int x, int y, int field_width, int field_height, int tile_size, int game_mode);
void set_direction(snake_t* s, int dir);
static bool check_collision(snake_t* s);
bool move_forward(snake_t* s);
void add_body_segment(snake_t* s);

#endif