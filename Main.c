#include "SDL.h"
#include "SDL_image.h"
#include "SDL_net.h"

#include "Snake.h"
#include "Game.h"
#include "Sprite.h"
#include "Font.h"
#include "xmath.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define VERSION_MAJOR 1
#define VERSION_MINOR 2

#define MENU_N 4

/* Main function */
int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	/* Initilize SDL and SDL_image */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init: %s", SDL_GetError());
		return 1;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("IMG_Init: %s\n", IMG_GetError());
	}

	/* Create the window */
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 25 * 30, 25 * 20, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	/* Create the renderer */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	/* Initilize SDL_net */
	if (SDLNet_Init() == -1) {
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	/* Set up the sprites */
	SDL_Texture* sprite_sheet = IMG_LoadTexture(renderer, "res/sprites.png");

	sprite_t* head_sprite = init_sprite(sprite_sheet, 50, 0, 25, 25);
	sprite_t* body_sprite = init_sprite(sprite_sheet, 25, 0, 25, 25);
	sprite_t* apple_sprite = init_sprite(sprite_sheet, 0, 0, 25, 25);

	/* Set up the icon */
	SDL_Surface* surface = SDL_LoadBMP("res/apple.bmp");
	SDL_SetWindowIcon(window, surface);

	/* Initialize the font system */
	font_init(sprite_sheet);

	/* Main loop */
	int speed = 5;		/* Variable for the speed setting */
	int game_mode = 0;	/* Variable for game mode: 0 = classic
												   1 = bordeless
												   2 = adventure */

	indata data;
	data.window = window;
	data.renderer = renderer;
	data.head = head_sprite;
	data.body = body_sprite;
	data.apple = apple_sprite;
	data.speed = speed;
	data.game_mode = game_mode;

	SDL_Event e;
	bool exit = false;
	int current_selection = 0;

	char* menu[MENU_N];
	menu[0] = calloc(24, sizeof(char));
	menu[1] = calloc(24, sizeof(char));
	menu[2] = calloc(24, sizeof(char));
	menu[3] = calloc(24, sizeof(char));
	sprintf(menu[0], "PLAY");
	sprintf(menu[1], "OPTIONS");
	sprintf(menu[2], "HIGH SCORES");
	sprintf(menu[3], "EXIT");

	char temp[24];

	while (!exit) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				exit = true;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_UP)
					current_selection = mod(current_selection - 1, MENU_N);
				else if (e.key.keysym.sym == SDLK_DOWN)
					current_selection = mod(current_selection + 1, MENU_N);
				else if (e.key.keysym.sym == SDLK_ESCAPE)
					exit = true;
				else if (e.key.keysym.sym == SDLK_RETURN) {
					if (current_selection == 0)
						if (!game_loop(&data))
							exit = true;
					if (current_selection == 1)
						if (!options_screen(renderer, &(data.speed), &(data.game_mode)))
							exit = true;
					if (current_selection == 2)
						if (!high_score(renderer, data.game_mode))
							exit = true;
					if (current_selection == 3)
						exit = true;
				}
					
			}
		}

		SDL_RenderClear(renderer);

		/* Render logo */
		render_sprite(body_sprite, 1 * 25, 8 * 25, renderer);	/* S */
		render_sprite(body_sprite, 2 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 3 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 4 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 5 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 5 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 5 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 4 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 3 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 2 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 2 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 2 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 3 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 4 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 5 * 25, 4 * 25, renderer);

		render_sprite(body_sprite, 6 * 25, 8 * 25, renderer); /* N */
		render_sprite(body_sprite, 7 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 7 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 7 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 7 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 8 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 9 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 9 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 10 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 10 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 10 * 25, 8 * 25, renderer);

		render_sprite(body_sprite, 11 * 25, 8 * 25, renderer); /* A */
		render_sprite(body_sprite, 12 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 12 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 12 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 12 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 12 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 13 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 14 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 13 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 14 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 14 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 14 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 14 * 25, 8 * 25, renderer);

		render_sprite(body_sprite, 15 * 25, 8 * 25, renderer); /* K */
		render_sprite(body_sprite, 16 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 16 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 16 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 16 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 16 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 17 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 18 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 18 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 18 * 25, 8 * 25, renderer);

		render_sprite(body_sprite, 19 * 25, 8 * 25, renderer); /* E */
		render_sprite(body_sprite, 20 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 20 * 25, 7 * 25, renderer);
		render_sprite(body_sprite, 20 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 20 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 20 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 21 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 22 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 23 * 25, 4 * 25, renderer);
		render_sprite(body_sprite, 23 * 25, 5 * 25, renderer);
		render_sprite(body_sprite, 23 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 22 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 21 * 25, 6 * 25, renderer);
		render_sprite(body_sprite, 21 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 22 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 23 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 24 * 25, 8 * 25, renderer);
		render_sprite(body_sprite, 25 * 25, 8 * 25, renderer);

		render_sprite(head_sprite, 26 * 25, 8 * 25, renderer);
		render_sprite(apple_sprite, 28 * 25, 8 * 25, renderer);

		/* Render menu */
		for (int i = 0; i < MENU_N; i++) {
			if (i == current_selection) {
				sprintf(temp, "<%s>", menu[i]);
			}
			else {
				sprintf(temp, " %s ", menu[i]);
			}
			font_render(temp, 50, 340 + i * 30, renderer);
		}

		/* Render version number */
		char version[10] = { 0 };
		sprintf(version, "VER %d,%d", VERSION_MAJOR, VERSION_MINOR);
		font_render(version, 570, 470, renderer);

		SDL_RenderPresent(renderer);
	}


	/* Free the sprites */
	free_sprite(head_sprite);
	free_sprite(body_sprite);
	free_sprite(apple_sprite);
	font_quit();

	/* Destroy and exit */
	SDLNet_Quit();
	IMG_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}