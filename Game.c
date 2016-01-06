#include "Game.h"
#include "Snake.h"
#include "Sprite.h"
#include "Highscore.h"

#include <stdbool.h>
#include <stdio.h>

int mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

int game_loop(indata* data)
{
	SDL_Event e;
	bool running = true;
	int score = 0;
	char title[64];

	SDL_Window* window = data->window;
	SDL_Renderer* renderer = data->renderer;

	sprite_t* head_sprite = data->head;
	sprite_t* body_sprite = data->body;
	sprite_t* apple_sprite = data->apple;

	/* Initialize the snake */
	snake_t snake;
	init_snake(&snake, 275, 300, 750, 500, 25);
	body_t* b;

	int apple_x = 600;
	int apple_y = 100;

	int dir_queue[2] = { 0, 0 };
	int queued = 0;

	unsigned int last_time = 0, current_time;

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return 0;
			}

			if (e.type == SDL_KEYDOWN && queued < 2) {
				if (e.key.keysym.sym == SDLK_UP && snake.dir != 2)
					dir_queue[queued++] = 1;
				else if (e.key.keysym.sym == SDLK_DOWN && snake.dir != 1)
					dir_queue[queued++] = 2;
				else if (e.key.keysym.sym == SDLK_LEFT && snake.dir != 4)
					dir_queue[queued++] = 3;
				else if (e.key.keysym.sym == SDLK_RIGHT && snake.dir != 3)
					dir_queue[queued++] = 4;
				else if (e.key.keysym.sym == SDLK_ESCAPE) {
					int t = pause_screen(renderer);
					if (t == 0) {
						return 0;
					}
					else if (t == 2) {
						return 1;
					}
				}
					

			}
		}

		/* Movement update */
		current_time = SDL_GetTicks();
		if (current_time > last_time + (500 / data->speed)) {

			if (queued > 0) {
				snake.dir = dir_queue[queued - 1];
				queued--;
			}

			if (!move_forward(&snake)) {
				SDL_Delay(1000);
				running = false;
			}

			last_time = current_time;

			/* Check for apple collision */
			if (snake.body.x == apple_x && snake.body.y == apple_y) {
				add_body_segment(&snake);
				apple_x = 25 * (current_time % 30);
				apple_y = 25 * (current_time % 20);
				score += data->speed;
				sprintf(title, "Snake -- Score: %d", score);
				SDL_SetWindowTitle(window, title);
			}
		}

		SDL_RenderClear(renderer);

		/* Render apple */
		render_sprite(apple_sprite, apple_x, apple_y, renderer);

		/* Render body */
		b = snake.body.tail;
		while (b != NULL) {
			render_sprite(body_sprite, b->x, b->y, renderer);
			b = b->tail;
		}

		/* Render head */
		render_sprite(head_sprite, snake.body.x, snake.body.y, renderer);

		SDL_RenderPresent(renderer);
	}

	/* Free the snake */
	body_t* temp = NULL;
	b = snake.body.tail;
	while (b != NULL) {
		free(temp);
		temp = b;
		b = b->tail;
	}

	SDL_SetWindowTitle(window, "Snake");

	if (!new_high_score(renderer, score))
		return 0;

	return 1;
}

int speed_screen(SDL_Renderer* r, int* speed)
{
	SDL_Event e;
	bool running = true;

	char temp[24];
	
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return 0;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_RIGHT) {
					if ((*speed) < 15) (*speed)++;
				} else if (e.key.keysym.sym == SDLK_LEFT) {
					if ((*speed) > 1) (*speed)--;
				} else if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_RETURN) {
					running = false;
				}
			}
		}

		SDL_RenderClear(r);

		font_render("SET THE SPEED FOR THE GAME", 50, 140, r);
		font_render("IT WILL AFFECT YOUR SCORES", 50, 170, r);
		sprintf(temp, "<%02d>", *speed);
		font_render(temp, 325, 250, r);

		SDL_RenderPresent(r);
	}

	return 1;
}

int pause_screen(SDL_Renderer* r)
{
	SDL_Event e;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return 0;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				if (e.key.keysym.sym == SDLK_m) {
					return 2;
				}
			}
		}

		SDL_RenderClear(r);

		font_render("PAUSE", 310, 140, r);
		font_render("ESC - CONTINUE", 200, 240, r);
		font_render("M - MAIN MENU", 210, 275, r);

		SDL_RenderPresent(r);
	}

	return 1;
}

int new_high_score(SDL_Renderer* r, int score)
{
	SDL_Event e;
	bool running = true;
	bool skip = false;

	char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
	char temp[24];

	int current_input = 0;
	int current_letter = 0;
	char name[4] = "A  ";

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return 0;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_RETURN) {
					if (current_input == 2) {
						running = false;
					} else {
						current_input++;
						name[current_input] = alphabet[current_letter];
					}
				} else if (e.key.keysym.sym == SDLK_ESCAPE) {
					if (current_input == 0) {
						running = false;
						skip = true;
					}
					if (current_input > 0) current_input--;
					current_letter = 0; // Maybe should find the current letter instead
				} else if (e.key.keysym.sym == SDLK_UP) {
					current_letter = mod(current_letter - 1, 37);
					name[current_input] = alphabet[current_letter];
				} else if (e.key.keysym.sym == SDLK_DOWN) {
					current_letter = mod(current_letter + 1, 37);
					name[current_input] = alphabet[current_letter];
				}
			}
		}

		SDL_RenderClear(r);

		sprintf(temp, "SCORE: %05d", score);
		font_render(temp, 230, 140, r);

		for (int i = 0; i < 3; i++) {
			if (i == current_input) {
				font_render("^", 330 + i * 25, 225, r);
				font_render("v", 330 + i * 25, 275, r);
			}
			else {
				font_render(" ", 330 + i * 25, 225, r);
				font_render(" ", 330 + i * 25, 275, r);
			}
			sprintf(temp, "%c", name[i]);
			font_render(temp, 330 + i * 25, 250, r);
		}

		if (current_input == 0) {
			font_render("PRESS ESCAPE TO SKIP", 130, 400, r);
		}

		SDL_RenderPresent(r);
	}

	if (!skip) {
		enter_highscore(score, name);
	}

	return 1;
}

int high_score(SDL_Renderer* r)
{
	SDL_Event e;
	bool running = true;

	char list[256];
	get_highscore(list);
	int entries = 0;

	/* Count the number of entries in the list */
	for (int i = 0; i < 256; i++) {
		if (list[i] == ';')
			entries++;
	}

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return 0;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_RETURN) {
					running = false;
				}
			}
		}

		SDL_RenderClear(r);

		font_render("HIGH SCORES", 230, 50, r);

		char temp[16] = { 0 };
		int score;
		for (int i = 0; i < 10; i++) {
			if (i < entries) {
				memcpy(temp, &(list[i * 11 + i]), 11);
				font_render(temp, 230, 150 + i * 30, r);
			} else {
				font_render("      -    ", 230, 150 + i * 30, r);
			}
			
		}		

		SDL_RenderPresent(r);
	}

	return 1;
}