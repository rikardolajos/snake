#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"

typedef struct sprite_t sprite_t;
struct sprite_t {
	SDL_Texture* texture;
	SDL_Rect rectangle;
};

/* Initialize a sprite from a texture */
sprite_t* init_sprite(SDL_Texture* t, int x, int y, int w, int h);

/* Free an initilized sprite */
void free_sprite(sprite_t* s);

/* Render sprite */
void render_sprite(sprite_t* sprite, int x, int y, SDL_Renderer* r);

#endif