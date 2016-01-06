#ifndef GAME_H
#define GAME_H

#include "Sprite.h"
#include "SDL.h"

typedef struct indata indata;
struct indata {
	SDL_Window* window;
	SDL_Renderer* renderer;
	sprite_t* head;
	sprite_t* body;
	sprite_t* apple;
	int speed;
};

/* These functions returns 0 for SDL_QUIT */

/* The main game loop */
int game_loop(void* data);

/* Screen for changing the speed */
int speed_screen(SDL_Renderer* r, int* speed);

/* The pause screen presented when pressing ESC 
   It returns 2 for RETURN TO MENU request */
int pause_screen(SDL_Renderer* r);

/* The screen presented after each game */
int new_high_score(SDL_Renderer* r, int score);

/* Screen for showing the scores stored at the server */
int high_score(SDL_Renderer* r);

#endif