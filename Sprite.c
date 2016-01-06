#include "Sprite.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Initialize a sprite from a texture */
sprite_t* init_sprite(SDL_Texture* t, int x, int y, int w, int h)
{
	sprite_t* s = malloc(sizeof(sprite_t));
	assert(s != NULL);

	s->texture = t;

	s->rectangle.x = x;
	s->rectangle.y = y;
	s->rectangle.w = w;
	s->rectangle.h = h;

	return s;
}

/* Free an initilized sprite */
void free_sprite(sprite_t* s)
{
	free(s);
}

/* Render sprite */
void render_sprite(sprite_t* sprite, int x, int y, SDL_Renderer* r)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = sprite->rectangle.w;
	dst.h = sprite->rectangle.h;

	SDL_RenderCopy(r, sprite->texture, &sprite->rectangle, &dst);
}