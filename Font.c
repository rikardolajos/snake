#include "Font.h"

#include <string.h>

/* Initialize the funt system */
void font_init(SDL_Texture* sprite_sheet)
{
	/* Set up letters and digits */
	symbols[0].letter = '0';
	symbols[0].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT5 | SEGMENT6;
	symbols[1].letter = '1';
	symbols[1].segments = SEGMENT2 | SEGMENT3;
	symbols[2].letter = '2';
	symbols[2].segments = SEGMENT1 | SEGMENT2 | SEGMENT4 | SEGMENT5 | SEGMENT7 | SEGMENT9;
	symbols[3].letter = '3';
	symbols[3].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT7 | SEGMENT9;
	symbols[4].letter = '4';
	symbols[4].segments = SEGMENT2 | SEGMENT3 | SEGMENT6 | SEGMENT7 | SEGMENT9;
	symbols[5].letter = '5';
	symbols[5].segments = SEGMENT1 | SEGMENT3 | SEGMENT4 | SEGMENT6 | SEGMENT7 | SEGMENT9;
	symbols[6].letter = '6';
	symbols[6].segments = SEGMENT1 | SEGMENT3 | SEGMENT4 | SEGMENT5 | SEGMENT6 | SEGMENT7 | SEGMENT9;
	symbols[7].letter = '7';
	symbols[7].segments = SEGMENT1 | SEGMENT12 | SEGMENT14;
	symbols[8].letter = '8';
	symbols[8].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT5 | SEGMENT6 | SEGMENT7 | SEGMENT9;
	symbols[9].letter = '9';
	symbols[9].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT6 | SEGMENT7 | SEGMENT9;

	symbols[10].letter = ' ';
	symbols[10].segments = SEGMENT0;

	symbols[11].letter = 'A';
	symbols[11].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT5 | SEGMENT6 | SEGMENT7 | SEGMENT9;
	symbols[12].letter = 'B';
	symbols[12].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT8 | SEGMENT9 | SEGMENT10;
	symbols[13].letter = 'C';
	symbols[13].segments = SEGMENT1 | SEGMENT4 | SEGMENT5 | SEGMENT6;
	symbols[14].letter = 'D';
	symbols[14].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT8 | SEGMENT10;
	symbols[15].letter = 'E';
	symbols[15].segments = SEGMENT1 | SEGMENT4 | SEGMENT5 | SEGMENT6 | SEGMENT7;
	symbols[16].letter = 'F';
	symbols[16].segments = SEGMENT1 | SEGMENT5 | SEGMENT6 | SEGMENT7;
	symbols[17].letter = 'G';
	symbols[17].segments = SEGMENT1 | SEGMENT3 | SEGMENT4 | SEGMENT5 | SEGMENT6 | SEGMENT9;
	symbols[18].letter = 'H';
	symbols[18].segments = SEGMENT2 | SEGMENT3 | SEGMENT5 | SEGMENT6 | SEGMENT7 | SEGMENT9;
	symbols[19].letter = 'I';
	symbols[19].segments = SEGMENT1 | SEGMENT4 | SEGMENT8 | SEGMENT10;
	symbols[20].letter = 'J';
	symbols[20].segments = SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT5;
	symbols[21].letter = 'K';
	symbols[21].segments = SEGMENT5 | SEGMENT6 | SEGMENT7 | SEGMENT12 | SEGMENT13;
	symbols[22].letter = 'L';
	symbols[22].segments = SEGMENT4 | SEGMENT5 | SEGMENT6;
	symbols[23].letter = 'M';
	symbols[23].segments = SEGMENT2 | SEGMENT3 | SEGMENT5 | SEGMENT6 | SEGMENT11 | SEGMENT12;
	symbols[24].letter = 'N';
	symbols[24].segments = SEGMENT2 | SEGMENT3 | SEGMENT5 | SEGMENT6 | SEGMENT11 | SEGMENT13;
	symbols[25].letter = 'O';
	symbols[25].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT5 |SEGMENT6;
	symbols[26].letter = 'P';
	symbols[26].segments = SEGMENT1 | SEGMENT2 | SEGMENT5 | SEGMENT6 | SEGMENT7 | SEGMENT9;
	symbols[27].letter = 'Q';
	symbols[27].segments = SEGMENT1 | SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT5 | SEGMENT6 | SEGMENT13;
	symbols[28].letter = 'R';
	symbols[28].segments = SEGMENT1 | SEGMENT2 | SEGMENT5 | SEGMENT6 | SEGMENT7 | SEGMENT9 | SEGMENT13;
	symbols[29].letter = 'S';
	symbols[29].segments = SEGMENT1 | SEGMENT4 | SEGMENT11 | SEGMENT13;
	symbols[30].letter = 'T';
	symbols[30].segments = SEGMENT1 | SEGMENT8 | SEGMENT10;
	symbols[31].letter = 'U';
	symbols[31].segments = SEGMENT2 | SEGMENT3 | SEGMENT4 | SEGMENT5 | SEGMENT6;
	symbols[32].letter = 'V';
	symbols[32].segments = SEGMENT5 | SEGMENT6 | SEGMENT12 | SEGMENT14;
	symbols[33].letter = 'W';
	symbols[33].segments = SEGMENT2 | SEGMENT3 | SEGMENT5 | SEGMENT6 | SEGMENT13 | SEGMENT14;
	symbols[34].letter = 'X';
	symbols[34].segments = SEGMENT11 | SEGMENT12 | SEGMENT13 | SEGMENT14;
	symbols[35].letter = 'Y';
	symbols[35].segments = SEGMENT10 | SEGMENT11 | SEGMENT12;
	symbols[36].letter = 'Z';
	symbols[36].segments = SEGMENT1 | SEGMENT4 | SEGMENT12 | SEGMENT14;

	symbols[37].letter = '<';
	symbols[37].segments = SEGMENT12 | SEGMENT13;
	symbols[38].letter = '>';
	symbols[38].segments = SEGMENT11 | SEGMENT14;
	symbols[39].letter = '^';
	symbols[39].segments = SEGMENT13 | SEGMENT14;
	symbols[40].letter = 'v';
	symbols[40].segments = SEGMENT11 | SEGMENT12;
	symbols[41].letter = ':';
	symbols[41].segments = SEGMENT8 | SEGMENT10;
	symbols[42].letter = '-';
	symbols[42].segments = SEGMENT7 | SEGMENT9;
	symbols[43].letter = ',';
	symbols[43].segments = SEGMENT14;


	/* Set up the sprites for the segments */
	segments[0] = init_sprite(sprite_sheet, 100, 0, 25, 25);
	segments[1] = init_sprite(sprite_sheet, 125, 0, 25, 25);
	segments[2] = init_sprite(sprite_sheet, 150, 0, 25, 25);
	segments[3] = init_sprite(sprite_sheet, 175, 0, 25, 25);
	segments[4] = init_sprite(sprite_sheet, 200, 0, 25, 25);
	segments[5] = init_sprite(sprite_sheet, 225, 0, 25, 25);
	segments[6] = init_sprite(sprite_sheet, 250, 0, 25, 25);
	segments[7] = init_sprite(sprite_sheet, 275, 0, 25, 25);
	segments[8] = init_sprite(sprite_sheet, 75, 25, 25, 25);
	segments[9] = init_sprite(sprite_sheet, 100, 25, 25, 25);
	segments[10] = init_sprite(sprite_sheet, 125, 25, 25, 25);
	segments[11] = init_sprite(sprite_sheet, 150, 25, 25, 25);
	segments[12] = init_sprite(sprite_sheet, 175, 25, 25, 25);
	segments[13] = init_sprite(sprite_sheet, 200, 25, 25, 25);
	segments[14] = init_sprite(sprite_sheet, 75, 0, 25, 25);
}

/* Free the sprites for the font */
void font_quit() {
	for (int i = 0; i < N_SEGMENTS; i++) {
		free_sprite(segments[i]);
	}
}

/* Render string at given position */
void font_render(char* string, int x, int y, SDL_Renderer* r)
{
	SDL_Rect dst;
	int i, j, k;

	/* Parse the string and render one letter at a time */
	for (i = 0; i < strlen(string); i++) {
		/* Find the letter in symbols */
		for (j = 0; j < N_SYMBOLS; j++) {
			if (symbols[j].letter == string[i])
				break;
		}

		/* Render background */
		dst.x = x + 25 * i;
		dst.y = y;
		dst.w = segments[14]->rectangle.w;
		dst.h = segments[14]->rectangle.h;
		SDL_RenderCopy(r, segments[14]->texture, &segments[14]->rectangle, &dst);

		/* Render all segments for symbol j at letter i*/
		for (k = 0; k < N_SEGMENTS; k++) {
			if (symbols[j].segments & (1 << k)) {
				dst.x = x + 25 * i;
				dst.y = y;
				dst.w = segments[k]->rectangle.w;
				dst.h = segments[k]->rectangle.h;

				SDL_RenderCopy(r, segments[k]->texture, &segments[k]->rectangle, &dst);
			}
		}
		
	}
}