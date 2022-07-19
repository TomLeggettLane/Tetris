#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <time.h>

#define PIXEL_SIZE 20
#define COLS 10
#define ROWS 20
#define NUM_SHAPES 7
#define NUM_ROTATIONS 4
#define HIDDEN_ROWS 4
#define TOTAL_ROWS HIDDEN_ROWS+ROWS
#define STATS_ROWS 3
#define MARGIN PIXEL_SIZE / 20
#define BORDER PIXEL_SIZE / 10
#define scorePixelSize 2
#define numberBoxHeight 7
#define numberBoxWidth 5
#define textPixelSize 2
#define NUM_COLOUR_SCHEMES 5

//TODO:
	//add game over/start again screen 
	//add sounds

const short shapeRotations[7][4] = {
										 { 0b0000011001100000, 0b0000011001100000, 0b0000011001100000, 0b0000011001100000 }, //Square, 0 rotations
										 { 0b0000111100000000, 0b0010001000100010, 0b0000111100000000, 0b0010001000100010 }, //I, 2 rotations, default is horitzonal
										 { 0b0000111001000000, 0b0100110001000000, 0b0100111000000000, 0b0100011001000000 }, //T, 4 rotations, default is horizontal
										 { 0b0000111000100000, 0b0100010011000000, 0b1000111000000000, 0b0110010001000000 }, //J, 4 rotations, default is horizontal down
										 { 0b0000111010000000, 0b1100010001000000, 0b0010111000000000, 0b0100010001100000 }, //L, 4 rotations, default is horizontal down
										 { 0b0000110001100000, 0b0100110010000000, 0b0000110001100000, 0b0100110010000000 }, //Z, 2 rotations, default is Z-shape
										 { 0b0000011011000000, 0b0100011000100000, 0b0000011011000000, 0b0100011000100000 }, //S, 2 rotations, default is S-shape
										};

// x , y , width , height
SDL_Rect zero[7] = { {scorePixelSize, 0, 3 * scorePixelSize, scorePixelSize},
					 {scorePixelSize, (numberBoxHeight - 1) * scorePixelSize, 3 * scorePixelSize, scorePixelSize},
					 {0, scorePixelSize, scorePixelSize, 5 * scorePixelSize},
					 {(numberBoxWidth - 1) * scorePixelSize, scorePixelSize , scorePixelSize, 5 * scorePixelSize},
					 {3 * scorePixelSize, 2 * scorePixelSize , scorePixelSize, scorePixelSize},
				   	 {2 * scorePixelSize, 3 * scorePixelSize , scorePixelSize, scorePixelSize},
			     	 {1 * scorePixelSize, 4 * scorePixelSize , scorePixelSize, scorePixelSize}
				   };

SDL_Rect one[7] = { {0, (numberBoxHeight-1) * scorePixelSize, numberBoxWidth * scorePixelSize, scorePixelSize},
					 {2 * scorePixelSize, 0 , scorePixelSize, numberBoxHeight * scorePixelSize},
					 {scorePixelSize, scorePixelSize , scorePixelSize, scorePixelSize},
					 {0 , 2 * scorePixelSize , scorePixelSize, scorePixelSize},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};

SDL_Rect two[7] = { {0, (numberBoxHeight - 1) * scorePixelSize, numberBoxWidth * scorePixelSize, scorePixelSize},
				    {0, 5 * scorePixelSize , scorePixelSize, scorePixelSize},
					{scorePixelSize, 4 * scorePixelSize , scorePixelSize, scorePixelSize},
					{2 * scorePixelSize, 3 * scorePixelSize , 2 * scorePixelSize, scorePixelSize},
					{4 * scorePixelSize, scorePixelSize , scorePixelSize, 2 * scorePixelSize},
					{scorePixelSize, 0 , 3*scorePixelSize, scorePixelSize},
					{0, scorePixelSize , scorePixelSize, scorePixelSize}
};

SDL_Rect three[7] = { {0, scorePixelSize , scorePixelSize, scorePixelSize},
						{scorePixelSize, 0 , 3 * scorePixelSize, scorePixelSize},
						{4 * scorePixelSize, scorePixelSize , scorePixelSize, 2 * scorePixelSize},
						{scorePixelSize, 3 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
						{4 * scorePixelSize, 4 * scorePixelSize , scorePixelSize, 2 * scorePixelSize},
						{scorePixelSize, 6 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
						{0, 5 * scorePixelSize , scorePixelSize, scorePixelSize}				
};

SDL_Rect four[7] = { {3 * scorePixelSize, 0 , scorePixelSize, 7 * scorePixelSize},
{0 , 4 * scorePixelSize, 5 * scorePixelSize, scorePixelSize},
{0, 3 * scorePixelSize , scorePixelSize, scorePixelSize},
{scorePixelSize, 2 * scorePixelSize , scorePixelSize, scorePixelSize},
{2 * scorePixelSize, scorePixelSize , scorePixelSize, scorePixelSize},
{-1,-1,-1,-1},
{-1,-1,-1,-1}
};

SDL_Rect five[7] = { {0, 0, 5 * scorePixelSize, scorePixelSize},
					 {0, scorePixelSize, scorePixelSize, scorePixelSize},
					 {0, 2 * scorePixelSize, 4 * scorePixelSize, scorePixelSize},
					 {4 * scorePixelSize, 3 * scorePixelSize , scorePixelSize, 3 * scorePixelSize},
					 {scorePixelSize, 6 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
					 {0, 5 * scorePixelSize , scorePixelSize, scorePixelSize},
					{-1,-1,-1,-1}
};

SDL_Rect six[7] = { {0, scorePixelSize , scorePixelSize, 5 * scorePixelSize},
						{scorePixelSize, 0 , 3 * scorePixelSize, scorePixelSize},
						{4 * scorePixelSize, scorePixelSize , scorePixelSize, scorePixelSize},
						{0, 3 * scorePixelSize, 4 * scorePixelSize, scorePixelSize},
						{4 * scorePixelSize, 4 * scorePixelSize , scorePixelSize, 2 * scorePixelSize},
						{scorePixelSize, 6 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
						{-1,-1,-1,-1}
};

SDL_Rect seven[7] = { {0, 0, 5 * scorePixelSize, scorePixelSize},
			{4 * scorePixelSize, scorePixelSize , scorePixelSize, scorePixelSize},
	{3 * scorePixelSize, 2 * scorePixelSize , scorePixelSize, scorePixelSize},
	{2 * scorePixelSize, 3 * scorePixelSize , scorePixelSize, 4 * scorePixelSize},
		{-1,-1,-1,-1},
		{-1,-1,-1,-1},
		{-1,-1,-1,-1}
};

SDL_Rect eight[7] = { {0, scorePixelSize , scorePixelSize, 2 * scorePixelSize},
						{scorePixelSize, 0 , 3 * scorePixelSize, scorePixelSize},
						{4 * scorePixelSize, scorePixelSize , scorePixelSize, 2 * scorePixelSize},
						{scorePixelSize, 3 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
						{4 * scorePixelSize, 4 * scorePixelSize , scorePixelSize, 2 * scorePixelSize},
						{scorePixelSize, 6 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
						{0, 4 * scorePixelSize , scorePixelSize, 2*scorePixelSize}
};

SDL_Rect nine[7] = { {0, scorePixelSize , scorePixelSize, 2 * scorePixelSize},
						{scorePixelSize, 0 , 3 * scorePixelSize, scorePixelSize},
						{4 * scorePixelSize, scorePixelSize , scorePixelSize, 5 * scorePixelSize},
						{scorePixelSize, 3 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
						{scorePixelSize, 6 * scorePixelSize , 3 * scorePixelSize, scorePixelSize},
						{0, 5 * scorePixelSize , scorePixelSize, scorePixelSize},
						{-1,-1,-1,-1}
};

SDL_Rect s[7] = {
				{textPixelSize, 0, 3 * textPixelSize, textPixelSize},
				{ 4 * textPixelSize, textPixelSize, textPixelSize, textPixelSize },
				{ 0, textPixelSize, textPixelSize, 2 * textPixelSize },
				{textPixelSize, 3 * textPixelSize, 3 * textPixelSize, textPixelSize},
				{ 4 * textPixelSize, 4 * textPixelSize, textPixelSize, 2 * textPixelSize },
				{textPixelSize, 6 * textPixelSize, 3 * textPixelSize, textPixelSize},
				{0, 5 * textPixelSize, textPixelSize, textPixelSize},
};

SDL_Rect c[7] = {
				{textPixelSize, 0, 3 * textPixelSize, textPixelSize},
				{ 4 * textPixelSize, textPixelSize, textPixelSize, textPixelSize },
				{ 0, textPixelSize, textPixelSize, 5 * textPixelSize },
				{textPixelSize, 6 * textPixelSize, 3 * textPixelSize, textPixelSize},
				{4*textPixelSize, 5 * textPixelSize, textPixelSize, textPixelSize},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};

SDL_Rect o[7] = { {textPixelSize, 0, 3 * textPixelSize, textPixelSize},
					 {textPixelSize, 6 * textPixelSize, 3 * textPixelSize, textPixelSize},
					 {0, textPixelSize, textPixelSize, 5 * textPixelSize},
					 {4 * textPixelSize, textPixelSize , textPixelSize, 5 * textPixelSize},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};

SDL_Rect r[7] = {
					 {0, 0, textPixelSize, 7 * textPixelSize},
					{textPixelSize, 0, 3 * textPixelSize, textPixelSize},
					{4 * textPixelSize, textPixelSize, textPixelSize, 2 * textPixelSize},
					{0, 3 * textPixelSize, 4 * textPixelSize, textPixelSize},

					{2 * textPixelSize, 4 * textPixelSize , textPixelSize, textPixelSize},
					{3 * textPixelSize, 5 * textPixelSize , textPixelSize, textPixelSize},
					 {4 * textPixelSize, 6 * textPixelSize , textPixelSize, textPixelSize}
};

SDL_Rect e[7] = {
					{0, 0, textPixelSize, 7 * textPixelSize},
					{0, 0, 5 * textPixelSize, textPixelSize},
					{0, 3 * textPixelSize, 4 * textPixelSize, textPixelSize},
					{0, 6* textPixelSize, 5 * textPixelSize, textPixelSize},
					{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}
};

SDL_Rect l[7] = {
	{0, 0, textPixelSize, 7 * textPixelSize},
	{0, 6 * textPixelSize, 5 * textPixelSize, textPixelSize},
	{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}
};

SDL_Rect v[7] = {
	{0, 0, textPixelSize, 5 * textPixelSize},
	{4 * textPixelSize, 0, textPixelSize, 5 * textPixelSize},
	{textPixelSize, 5 * textPixelSize, textPixelSize, textPixelSize},
	{3 * textPixelSize, 5 * textPixelSize, textPixelSize, textPixelSize},
	{2 * textPixelSize, 6 * textPixelSize, textPixelSize, textPixelSize},
	{-1,-1,-1,-1},{-1,-1,-1,-1}
};

SDL_Rect* numbers[10] = { zero,one,two,three,four,five,six,seven,eight,nine };

SDL_Rect* letters[7] = { s, c, o, r, e, l, v };

typedef struct {
	SDL_Rect outerRect;
	SDL_Rect innerRect;
	SDL_Rect innerRect2;
	SDL_Rect specularRect;
	unsigned int RGBouterRect[3];
	unsigned int RGBinnerRect[3];
	unsigned int RGBspecularRect[3];
} CubeVisualDesign;

typedef struct {
	int x;
	int y;
	short* rotations;
	int currentRotation;
	int shapeType;
} Tetromino;

typedef struct {
	int* cells;
	int numTotalRows;
	int numGameRows;
	int numGameCols;
} Gameboard;

typedef struct {
	int primaryRGB[3];
	int secondaryRGB[3];
	int specularRGB[3];
} ColourScheme;

ColourScheme redScheme = {
	.primaryRGB = { 165, 42, 42 },
	.secondaryRGB = { 211, 211, 211 },
	.specularRGB = { 255, 255, 255 },
};

ColourScheme greenScheme = {
	.primaryRGB = { 42, 165, 42 },
	.secondaryRGB = { 211, 211, 211 },
	.specularRGB = { 255, 255, 255 },
};

ColourScheme blueScheme = {
	.primaryRGB = { 42, 42, 165 },
	.secondaryRGB = { 211, 211, 211 },
	.specularRGB = { 255, 255, 255 },
};

ColourScheme whiteScheme = {
	.primaryRGB = { 255, 255, 255 },
	.secondaryRGB = { 255, 255, 255 },
	.specularRGB = { 255, 255, 255 },
};

ColourScheme greyScheme = {
	.primaryRGB = { 75, 75, 75 },
	.secondaryRGB = { 75, 75, 75 },
	.specularRGB = { 75, 75, 75 },
};

CubeVisualDesign HollowCubeDesign = {
	.outerRect = { 0,0, PIXEL_SIZE - 2 * MARGIN, PIXEL_SIZE - 2 * MARGIN },
	.innerRect = { 0,0, PIXEL_SIZE - 2 * BORDER - 2 * MARGIN, PIXEL_SIZE - 2 * BORDER - 2 * MARGIN },
	.specularRect = { 0,0, BORDER, BORDER},
	.RGBinnerRect = { 211, 211, 211 },
	.RGBouterRect = {165, 42, 42},
	.RGBspecularRect = {255, 255, 255 }
};

CubeVisualDesign ColouredCubeDesign = {
	.outerRect = { 0,0, PIXEL_SIZE - 2 * MARGIN, PIXEL_SIZE - 2 * MARGIN },
	.innerRect = { 0,0, 2 * BORDER, BORDER },
	.innerRect2 = { 0,0, BORDER, 2 * BORDER },
	.specularRect = { 0,0, BORDER, BORDER},
	.RGBouterRect = {165, 42, 42},
	.RGBinnerRect = { 211, 211, 211 },
	.RGBspecularRect = {255, 255, 255 }
};

typedef struct {
	Tetromino currentShape;
	Tetromino nextShape;
	Gameboard gameboard;
	int score;
	int currentLevel;
	int tetrisRows[4];
	double timeToMove;
	int totalLinesCleared;
	int currentColourIndex;
} Game;

/* ~ ~ ~ ~ ~ ~ ~ ~ DRAW METHODS ~ ~ ~ ~ ~ ~ ~ ~ */

void drawLetter(SDL_Renderer* renderer, int screenX, int screenY, char letterToDraw) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	int letterIndex = -1;

	switch (letterToDraw) {
		case ' ': return;
		case 's': {letterIndex = 0; break;}
		case 'c': {letterIndex = 1; break;}
		case 'o': {letterIndex = 2; break;}
		case 'r': {letterIndex = 3; break;}
		case 'e': {letterIndex = 4; break;}
		case 'l': {letterIndex = 5; break;}
		case 'v': {letterIndex = 6; break;}
	}

	if (letterIndex < 0 || letterIndex > 6) return;

	//draw each rectangle defined in letter mesh
	for (int i = 0; i < 7; i++) {
		if (letters[letterIndex][i].x == -1) break;
		letters[letterIndex][i].x += (screenX + scorePixelSize);
		letters[letterIndex][i].y += (screenY + scorePixelSize);
		SDL_RenderDrawRect(renderer, &letters[letterIndex][i]);
		SDL_RenderFillRect(renderer, &letters[letterIndex][i]);
		letters[letterIndex][i].x -= (screenX + scorePixelSize);
		letters[letterIndex][i].y -= (screenY + scorePixelSize);
	}
}

void drawNumber(SDL_Renderer* renderer, int screenX, int screenY, int digitToDraw) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	//draw each rectangle defined in digit mesh
	for (int i = 0; i < 7; i++) {
		if (numbers[digitToDraw][i].x == -1) break;
		numbers[digitToDraw][i].x += (screenX + scorePixelSize);
		numbers[digitToDraw][i].y += (screenY + scorePixelSize);
		SDL_RenderDrawRect(renderer, &numbers[digitToDraw][i]);
		SDL_RenderFillRect(renderer, &numbers[digitToDraw][i]);
		numbers[digitToDraw][i].x -= (screenX + scorePixelSize);
		numbers[digitToDraw][i].y -= (screenY + scorePixelSize);
	}
}

void drawScore(SDL_Renderer* renderer, int score) {
	//char scoreTextArray[6] = { ' ', 'e', 'r', 'o', 'c', 's'};
	char scoreTextArray[6] = { 's', 'c', 'o', 'r', 'e', ' ' };

	//draw each digit in the current score (from least significant digit to most)
	for (int i = 0; i < 6; i++) {
		int digitToDraw = score % 10;
		score = score / 10;
		drawNumber(renderer, 7 + (5-i) * (13), 22 * PIXEL_SIZE, digitToDraw);
		drawLetter(renderer, 7 + (5 - i) * (13), 21 * PIXEL_SIZE, scoreTextArray[5-i]);
	}
}

void drawShape(SDL_Renderer* renderer, Tetromino currentShape, int screenX, int screenY, ColourScheme currentColour) {
	short bitmap = currentShape.rotations[currentShape.currentRotation];

	unsigned short bitmask = 0b1000000000000000;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (bitmask & bitmap) {
				HollowCubeDesign.outerRect.x = screenX + j * PIXEL_SIZE + MARGIN;
				HollowCubeDesign.outerRect.y = screenY + i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, currentColour.primaryRGB[0], currentColour.primaryRGB[1], currentColour.primaryRGB[2], SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &HollowCubeDesign.outerRect);
				SDL_RenderFillRect(renderer, &HollowCubeDesign.outerRect);
				
				HollowCubeDesign.innerRect.x = screenX + j * PIXEL_SIZE + BORDER + MARGIN;
				HollowCubeDesign.innerRect.y = screenY + i * PIXEL_SIZE + BORDER + MARGIN;
				SDL_SetRenderDrawColor(renderer, currentColour.secondaryRGB[0], currentColour.secondaryRGB[1], currentColour.secondaryRGB[2], SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &HollowCubeDesign.innerRect);
				SDL_RenderFillRect(renderer, &HollowCubeDesign.innerRect);

				HollowCubeDesign.specularRect.x = screenX + j * PIXEL_SIZE + MARGIN;
				HollowCubeDesign.specularRect.y = screenY + i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, currentColour.specularRGB[0], currentColour.specularRGB[1], currentColour.specularRGB[2], SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &HollowCubeDesign.specularRect);
				SDL_RenderFillRect(renderer, &HollowCubeDesign.specularRect);
			}
			bitmask = bitmask >> 1;
		}
	}
}

void drawBoard(SDL_Renderer* renderer, Gameboard gameboard, ColourScheme currentColour) {
	for (int i = 0; i < gameboard.numGameRows; i++) {
		unsigned short bitmask = 0b1000000000;
		for (int j = 0; j < gameboard.numGameCols; j++) {
			if (bitmask & gameboard.cells[i + HIDDEN_ROWS]) {
				ColouredCubeDesign.outerRect.x = j * PIXEL_SIZE + MARGIN;
				ColouredCubeDesign.outerRect.y = i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, currentColour.primaryRGB[0], currentColour.primaryRGB[1], currentColour.primaryRGB[2], SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.outerRect);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.outerRect);

				ColouredCubeDesign.innerRect.x = j * PIXEL_SIZE + BORDER + MARGIN;
				ColouredCubeDesign.innerRect.y = i * PIXEL_SIZE + BORDER + MARGIN;
				SDL_SetRenderDrawColor(renderer, currentColour.secondaryRGB[0], currentColour.secondaryRGB[1], currentColour.secondaryRGB[2], SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.innerRect);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.innerRect);

				ColouredCubeDesign.innerRect2.x = j * PIXEL_SIZE + BORDER + MARGIN;
				ColouredCubeDesign.innerRect2.y = i * PIXEL_SIZE + BORDER + MARGIN;
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.innerRect2);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.innerRect2);

				ColouredCubeDesign.specularRect.x = j * PIXEL_SIZE + MARGIN;
				ColouredCubeDesign.specularRect.y = i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, currentColour.specularRGB[0], currentColour.specularRGB[1], currentColour.specularRGB[2], SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.specularRect);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.specularRect);
			}
			bitmask = bitmask >> 1;
		}
	}
}

void drawLevel(SDL_Renderer* renderer, int currentLevel) {
	char levelTextArray[3] = { 'l','v','l' };

	for (int i = 0; i <= 5; i++) {
		if (i < 2) {
			int digitToDraw = currentLevel % 10;
			drawNumber(renderer, 7 + (5 - i) * (13), 23.75 * PIXEL_SIZE, digitToDraw);
			currentLevel = currentLevel / 10;
		} else if (i > 2) {
			drawLetter(renderer, 7 + (5 - i) * (13), 23.75 * PIXEL_SIZE, levelTextArray[i-3]);
		}
	}
}

void drawStats(SDL_Renderer* renderer) {
	//stats width = 4.75 (5.25 -> 10), height = 4.5 (20.5 --> 25)

	SDL_Rect verticalWallSection;
	verticalWallSection.w = 0.5 * PIXEL_SIZE;
	verticalWallSection.h = (STATS_ROWS + 2) * PIXEL_SIZE;
	verticalWallSection.x = 4.75 * PIXEL_SIZE;
	verticalWallSection.y = (ROWS + 0.5)*PIXEL_SIZE;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &verticalWallSection);
	SDL_RenderFillRect(renderer, &verticalWallSection);

	SDL_Rect wallSection;
	wallSection.w = COLS * PIXEL_SIZE;
	wallSection.h = 0.45 * PIXEL_SIZE;
	wallSection.x = 0;
	wallSection.y = (ROWS+0.05)*PIXEL_SIZE;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &wallSection);
	SDL_RenderFillRect(renderer, &wallSection);

	return;
}

void drawCurrentShape(SDL_Renderer* renderer, Tetromino currentShape, ColourScheme currentColour) {
	int screenX = currentShape.x * PIXEL_SIZE;
	int screenY = currentShape.y * PIXEL_SIZE;
	drawShape(renderer, currentShape, screenX, screenY, currentColour);
}

void drawNextShape(SDL_Renderer* renderer, Tetromino nextShape, ColourScheme currentColour) {
	int previewXpos = 123;
	int previewYpos = 415;

	//Centers nextShape in the 'preview next shape' box;
	if (nextShape.shapeType == 0) {
		previewXpos -= PIXEL_SIZE / 2;
	}
	else if (nextShape.shapeType == 1) {
		previewXpos -= PIXEL_SIZE / 2;
		previewYpos += PIXEL_SIZE / 2;
	}

	drawShape(renderer, nextShape, previewXpos, previewYpos, currentColour);
}

void animateAndClearTetrisRows(SDL_Renderer* renderer, int tetrisRows[]) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect rect;
	rect.w = PIXEL_SIZE;
	rect.h = PIXEL_SIZE;
	int numTetrisRows = 0;

	for (int i = 0; i < 4; i++) {
		if (tetrisRows[i] == -1) break;
		numTetrisRows++;
	}

	if (!numTetrisRows) return;

	for (int j = 0; j < COLS / 2; j++) {
		for (int i = 0; i < numTetrisRows; i++) {
			rect.x = (4 - j) * PIXEL_SIZE;
			rect.y = tetrisRows[i] * PIXEL_SIZE;

			SDL_RenderDrawRect(renderer, &rect);
			SDL_RenderFillRect(renderer, &rect);

			rect.x = (5 + j) * PIXEL_SIZE;
			SDL_RenderDrawRect(renderer, &rect);
			SDL_RenderFillRect(renderer, &rect);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(35);
	}

	resetTetrisRows(tetrisRows);
}

void draw(SDL_Renderer* renderer, Game* game, ColourScheme currentColour) {
	Gameboard gameboard = game->gameboard;
	Tetromino currentShape = game->currentShape;
	Tetromino nextShape = game->nextShape;
	int score = game->score;
	int currentLevel = game->currentLevel;

	drawStats(renderer);
	drawBoard(renderer, gameboard, currentColour);
	drawCurrentShape(renderer, currentShape, currentColour);
	drawNextShape(renderer, nextShape, currentColour);
	drawScore(renderer, score);
	drawLevel(renderer, currentLevel);
	SDL_RenderPresent(renderer);
}

void clear(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

/* ~ ~ ~ ~ ~ ~ ~ ~ UPDATE METHODS ~ ~ ~ ~ ~ ~ ~ ~ */

void setNextShape(Tetromino* nextShape) {
	int previousShapeType = nextShape->shapeType;
	int newShapeType;
	do {
		newShapeType = rand() % NUM_SHAPES;
	} while (newShapeType == previousShapeType);

	nextShape->shapeType = newShapeType;
	nextShape->currentRotation = 0;
	nextShape->rotations = shapeRotations[nextShape->shapeType];
	nextShape->x = 3;
	nextShape->y = 0;
}

void updateCurrentShape(Tetromino* currentShape, Tetromino* nextShape) {
	currentShape->x = 3;
	currentShape->y = 0;
	currentShape->currentRotation = nextShape->currentRotation;
	currentShape->shapeType = nextShape->shapeType;
	currentShape->rotations = nextShape->rotations;
}

void initNewShape(Tetromino* currentShape, Tetromino* nextShape) {
	int currentShapeInitialized = (currentShape->shapeType >= 0);
	//if neither shape initialized yet
	if (!currentShapeInitialized) {
		setNextShape(nextShape);
	}

	updateCurrentShape(currentShape, nextShape);
	setNextShape(nextShape);

	//increases currentShape.y until tetromino is at the top of the board, because some meshes have empty first&second rows
	unsigned short bitmask = 0b1111000000000000;

	while ((currentShape->rotations[currentShape->currentRotation] & bitmask) == 0) {
		currentShape->y--;
		bitmask = bitmask >> 4;
	}
	return;
}

void initGameboard(Gameboard* gameboard, int rows, int cols) {
	int* cells = malloc(sizeof(int) * (rows + HIDDEN_ROWS));

	gameboard->cells = cells;
	gameboard->numGameRows = rows;
	gameboard->numGameCols = cols;
	gameboard->numTotalRows = gameboard->numGameRows + HIDDEN_ROWS;

	for (int i = 0; i < gameboard->numTotalRows; i++) {
		gameboard->cells[i] = 0;
	}
	return;
}

Game* createGame(int numRows, int numCols) {
	Game* game = malloc(sizeof(Game));

	game->currentShape.shapeType = -1;    //initialize to -1 (no tetromino type defined yet)
	game->nextShape.shapeType = -1; 
	initNewShape(&game->currentShape, &game->nextShape);
	initGameboard(&game->gameboard, numRows, numCols);
	game->timeToMove = 0;

	game->score = 0;
	game->currentLevel = 1;
	game->totalLinesCleared = 0;
	game->currentColourIndex = 4;

	for (int i = 0; i < sizeof(*game->tetrisRows); i++) {
		game->tetrisRows[i] = -1;
	}
	    //updates elements to the row numbers if a row is full (ie tetris scored) otherwise -1

	return game;
}

void destroyGame(Game* game) {
	free(game);
}

void DeinitGameboard(Gameboard* gameboard) {
	free(gameboard->cells);
}

void updateTetrisRowsAndGameboard(Gameboard* gameboard, int tetrisRows[]) {
	int rows_index = 0;
	int tempGameboard[TOTAL_ROWS];
	int temp_ptr = TOTAL_ROWS - 1;

	//add all full rows to tetrisRows, else add to tempGameboard
	for (int i = temp_ptr; i >= HIDDEN_ROWS; i--) {
		if (gameboard->cells[i] == 0b1111111111) {
			tetrisRows[rows_index++] = i-HIDDEN_ROWS;
		}
		else {
			tempGameboard[temp_ptr--] = gameboard->cells[i];
		}
	}

	if (!rows_index) return; //no tetris rows found --> (no change in gameboard) 

	//update the new state of the gameboard with full rows removed
	for (int i = TOTAL_ROWS - 1; i > -1; i--) {
		if (i > temp_ptr) {
			gameboard->cells[i] = tempGameboard[i];
		}
		else {
			gameboard->cells[i] = 0;
		}
	}
}

void copyShapeToBoard(Tetromino* currentShape, Gameboard* gameboard) {
	short currentRotation = currentShape->rotations[currentShape->currentRotation];
	int x = currentShape->x;
	int y = currentShape->y;

	unsigned short bitmask16 = 0b1000000000000000;
	unsigned short bitmask10 = 0b1000000000;

	//copies the shape to the gameboard
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (currentRotation & bitmask16) {
				if ((y + i) < gameboard->numGameRows && (x + j) < gameboard->numGameCols) {
					short val = gameboard->cells[HIDDEN_ROWS + y + i] | (bitmask10 >> (x + j));
					gameboard->cells[HIDDEN_ROWS + y + i] = val;
				}
			}
			bitmask16 = bitmask16 >> 1;
		}
	}

	return;
}

void updateScore(int* score, int tetrisRows[4], int *totalLinesCleared) {
	int tetrisCount = 0;
	for (int i = 0; i < 4; i++) {
		if (tetrisRows[i] >= 0) {
			tetrisCount++;
			(*totalLinesCleared)++;
			/*tetrisRows[i] = -1;*/
		}
	}


	switch (tetrisCount) {
	case 1: {*score += 40; break;}
	case 2: {*score += 100; break;}
	case 3: {*score += 300; break;}
	case 4: {*score += 1200; break;}
	}
}

void updateColourIndex(int* colourIndex) {
	int newIndex = *colourIndex;
	while (newIndex == *colourIndex) {
		newIndex = rand() % NUM_COLOUR_SCHEMES;
	}
	*colourIndex = newIndex;
}

void updateLevel(int* currentLevel, int totalLinesCleared, int* colourIndex) {
	if (totalLinesCleared > (*currentLevel-1) * (5 + *currentLevel / 2)) {
		(*currentLevel)++;
		updateColourIndex(colourIndex);
	}
}

int updateTimeToMove(int* timeToMove, int currentLevel, double timeElapsed) {
	*timeToMove -= timeElapsed;

	if (*timeToMove > 0) {
		return 1;
	}

	*timeToMove += 30 * exp(-currentLevel / 8.0);
	return 0;
}

int isValidMove(Tetromino *currentShape, Gameboard* gameboard, char moveType) {
	int x = currentShape->x;
	int y = currentShape->y;
	short currentRotation = currentShape->rotations[currentShape->currentRotation];

	switch (moveType) {
		case 'D': y++; break;
		case 'R': x++; break;
		case 'L': x--; break;
		case 'U': y--; break;
		case 'C': currentRotation = currentShape->rotations[((currentShape->currentRotation + 1) % NUM_ROTATIONS + NUM_ROTATIONS) % NUM_ROTATIONS];
			break;
		case 'A': currentRotation = currentShape->rotations[((currentShape->currentRotation - 1) % NUM_ROTATIONS + NUM_ROTATIONS) % NUM_ROTATIONS];
			break;
	}

	unsigned short bitmask16 = 0b1000000000000000;
	unsigned short bitmask10 = 0b1000000000;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (currentRotation & bitmask16) {
				//checks that the bounding box around the tetromino is within our board's bounds
				if ((x + j) < 0 || (x + j) >= gameboard->numGameCols || (y + i) < (-HIDDEN_ROWS) || (y + i) >= gameboard->numGameRows) {
					return 0;
				}
				////checks that the tetromino is not overlapping with tetromino's already on the board.
				if (gameboard->cells[HIDDEN_ROWS + y + i] & (bitmask10 >> (x + j))) {
					return 0;
				}
			}
			bitmask16 = bitmask16 >> 1;
		}

	}
	return 1;
}

int update(Game* game, double timeElapsed) {
	Tetromino* currentShape = &game->currentShape;
	Tetromino* nextShape = &game->nextShape;
	Gameboard* gameboard = &game->gameboard;
	int* tetrisRows = game->tetrisRows;
	int* score = &game->score;
	int* currentLevel = &game->currentLevel;
	int* totalLinesCleared = &game->totalLinesCleared;
	int* currentColourIndex = &game->currentColourIndex;

	if (updateTimeToMove(&game->timeToMove, *currentLevel, timeElapsed)) {
		return 1;
	}

	if (isValidMove(currentShape, gameboard, 'D')) {
		currentShape->y++;
		return 1;
	}

	//if the shape is at top of the board we move the shape up and check if a hidden row is > 0 (endgame)
	if (currentShape->y <= 0 && isValidMove(currentShape, gameboard, 'U')) {
		currentShape->y--;
	}

	copyShapeToBoard(currentShape, gameboard);
	updateTetrisRowsAndGameboard(gameboard, tetrisRows);
	updateScore(score, tetrisRows, totalLinesCleared);
	updateLevel(currentLevel, *totalLinesCleared, currentColourIndex);
	initNewShape(currentShape, nextShape);
	return checkEndGame(*gameboard);
}

int checkEndGame(Gameboard gameboard) {
	for (int i = 0; i < HIDDEN_ROWS; i++) {
		if (gameboard.cells[i]) {
			return 0;
		}
	}
	return 1;
}

int resetTetrisRows(int tetrisRows[]) {
	for (int i = 0; i < 4; i++) {
		tetrisRows[i] = -1;
	}
}

SDL_Renderer* initGraphicsAndGetRenderer() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		printf("SDL initialization unsuccessful: %s\n", SDL_GetError());
		return 0;
	}

	SDL_Window* window = SDL_CreateWindow("Tetris In C ~ Tom Leggett", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, COLS * PIXEL_SIZE, (ROWS + STATS_ROWS + 2) * PIXEL_SIZE, 0);
	if (!window) {
		printf("Error Creating Window: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Error Initializing Renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}

	SDL_Surface* screen = SDL_GetWindowSurface(window);
	if (!screen) {
		printf("Error creating surface\n");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}

	return renderer;
}

ColourScheme* createColoursArray(int size, ColourScheme redScheme, ColourScheme greenScheme, ColourScheme blueScheme, ColourScheme whiteScheme, ColourScheme greyScheme) {
	ColourScheme* colours = malloc(sizeof(ColourScheme) * size);

	colours[0] = redScheme;
	colours[1] = greenScheme;
	colours[2] = blueScheme;
	colours[3] = whiteScheme;
	colours[4] = greyScheme;
	return colours;
}

void destroyColoursArray(ColourScheme* colours) {
	free(colours);
}

/* ~ ~ ~ ~ ~ ~ ~ ~ MAIN METHOD ~ ~ ~ ~ ~ ~ ~ ~ */

int main(int argc, char* args[]) {
	ColourScheme* colours = createColoursArray(NUM_COLOUR_SCHEMES, redScheme, greenScheme, blueScheme, whiteScheme, greyScheme);
	Game* game = createGame(ROWS, COLS);
	SDL_Renderer* renderer = initGraphicsAndGetRenderer();
	srand(time(NULL));		//sets new seed for random number generator;

	int playing = 1;
	clock_t lastUpdate = clock();

	while (playing) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				playing = 0;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: {playing = 0; break;}
					case SDLK_a: { if(isValidMove(&game->currentShape, &game->gameboard, 'L')) game->currentShape.x--; break;}
					case SDLK_d: { if (isValidMove(&game->currentShape, &game->gameboard, 'R'))  game->currentShape.x++; break;}
					case SDLK_s: { if (isValidMove(&game->currentShape, &game->gameboard, 'D'))  game->currentShape.y++; break;}
					case SDLK_SPACE: { while(isValidMove(&game->currentShape, &game->gameboard, 'D'))  game->currentShape.y++; break;}
					case SDLK_RIGHT: { if (isValidMove(&game->currentShape, &game->gameboard, 'C')) {
						game->currentShape.currentRotation = (( game->currentShape.currentRotation + 1) % NUM_ROTATIONS + NUM_ROTATIONS) % NUM_ROTATIONS;
						break;}
					}
					case SDLK_LEFT: { if (isValidMove(&game->currentShape, &game->gameboard, 'A')) {
						game->currentShape.currentRotation = ((game->currentShape.currentRotation - 1) % NUM_ROTATIONS + NUM_ROTATIONS) % NUM_ROTATIONS;
						break;}
					}
				}
			}
		}

		clock_t currentTime = clock();
		
		if (!update(game, (double)(currentTime - lastUpdate) / CLOCKS_PER_SEC)) {
			//end-game conditions met
			break;
		}
		if (game->tetrisRows[0] != -1) {
			animateAndClearTetrisRows(renderer, game->tetrisRows);
		}
		lastUpdate = currentTime;
		clear(renderer);  
		draw(renderer, game, colours[game->currentColourIndex]);
		SDL_Delay(20);
	}
	printf("\n\n\n~~~~~~~ G A M E   O V E R ~~~~~~~\n\n\n");
	SDL_DestroyRenderer(renderer);
	DeinitGameboard(&game->gameboard);
	destroyGame(game);
	destroyColoursArray(colours);
	SDL_Quit();
	return 1;
}