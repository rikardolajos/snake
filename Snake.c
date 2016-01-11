#include "Snake.h"

#include "xmath.h"

#include <stdlib.h>


void init_snake(snake_t* s, int x, int y, int field_width, int field_height, int tile_size, int game_mode)
{
	body_t* b;

	s->body.x = x;
	s->body.y = y;
	s->dir = 4;
	s->field_width = field_width;
	s->field_height = field_height;
	s->tile_size = tile_size;
	s->game_mode = game_mode;

	/* First body segement */
	b = malloc(sizeof(body_t));
	b->x = s->body.x - s->tile_size;
	b->y = s->body.y;
	s->body.tail = b;

	/* Second body segement */
	b = malloc(sizeof(body_t));
	b->x = s->body.tail->x - s->tile_size;
	b->y = s->body.tail->y;
	b->tail = NULL;
	s->body.tail->tail = b;
}

void set_direction(snake_t* s, int dir)
{
	s->dir = dir;
}

static bool check_collision(snake_t* s)
{
	bool alive = true;
	body_t* temp = s->body.tail;

	if (s->body.x < 0 || s->body.x == s->field_width)
		alive = false;

	if (s->body.y < 0 || s->body.y == s->field_height)
		alive = false;

	while (temp != NULL) {
		if (s->body.x == temp->x && s->body.y == temp->y)
			alive = false;
		temp = temp->tail;
	}

	return alive;
}

bool move_forward(snake_t* s)
{
	body_t* prev = NULL;
	body_t* temp = s->body.tail;

	while (temp->tail != NULL) {
		prev = temp;
		temp = temp->tail;
	}

	prev->tail = NULL;

	temp->tail = s->body.tail;
	s->body.tail = temp;
	temp->x = s->body.x;
	temp->y = s->body.y;

	/* Classic movement */
	if (s->game_mode == 0) {
		if (s->dir == 1) {
			s->body.y -= s->tile_size;
		}
		else if (s->dir == 2) {
			s->body.y += s->tile_size;
		}
		else if (s->dir == 3) {
			s->body.x -= s->tile_size;
		}
		else if (s->dir == 4) {
			s->body.x += s->tile_size;
		}
	}
	/* Borderless movement */
	else {
		if (s->dir == 1) {
			s->body.y = mod(s->body.y - s->tile_size, s->field_height);
		}
		else if (s->dir == 2) {
			s->body.y = mod(s->body.y + s->tile_size, s->field_height);
		}
		else if (s->dir == 3) {
			s->body.x = mod(s->body.x - s->tile_size, s->field_width);
		}
		else if (s->dir == 4) {
			s->body.x = mod(s->body.x + s->tile_size, s->field_width);
		}
	}
	

	return check_collision(s);
}

void add_body_segment(snake_t* s)
{
	body_t* b = malloc(sizeof(body_t));

	body_t* temp = s->body.tail;
	while (temp->tail != NULL)
		temp = temp->tail;

	b->x = temp->x;
	b->y = temp->y;
	b->tail = NULL;
	temp->tail = b;
}