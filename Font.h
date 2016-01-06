#ifndef FONT_H
#define FONT_H

#include "SDL.h"
#include "Sprite.h"

#define SEGMENT0  (0)
#define SEGMENT1  (1 << 0)
#define SEGMENT2  (1 << 1)
#define SEGMENT3  (1 << 2)
#define SEGMENT4  (1 << 3)
#define SEGMENT5  (1 << 4)
#define SEGMENT6  (1 << 5)
#define SEGMENT7  (1 << 6)
#define SEGMENT8  (1 << 7)
#define SEGMENT9  (1 << 8)
#define SEGMENT10 (1 << 9)
#define SEGMENT11 (1 << 10)
#define SEGMENT12 (1 << 11)
#define SEGMENT13 (1 << 12)
#define SEGMENT14 (1 << 13)

#define N_SYMBOLS (45)
#define N_SEGMENTS (15)

typedef struct symbol_t symbol_t;
struct symbol_t {
	unsigned int segments;
	char letter;
};

static sprite_t* segments[N_SEGMENTS];
static symbol_t symbols[N_SYMBOLS];

void font_init(SDL_Texture* sprite_sheet);
void font_quit();
void font_render(char* string, int x, int y, SDL_Renderer* r);


#endif