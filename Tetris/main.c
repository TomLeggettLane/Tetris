#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <time.h>
#include "text.h"
#include "colours.h"

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
#define textPixelSize 2

typedef struct {
	int musicOn;
	int startLevel;
	int appState;
	int lastScore;
} Settings;

const short shapeRotations[7][4] = {
		{ 0b0000011001100000, 0b0000011001100000, 0b0000011001100000, 0b0000011001100000 }, //Square, 0 rotations
		{ 0b0000111100000000, 0b0010001000100010, 0b0000111100000000, 0b0010001000100010 }, //I, 2 rotations, default is horitzonal
		{ 0b0000111001000000, 0b0100110001000000, 0b0100111000000000, 0b0100011001000000 }, //T, 4 rotations, default is horizontal
		{ 0b0000111000100000, 0b0100010011000000, 0b1000111000000000, 0b0110010001000000 }, //J, 4 rotations, default is horizontal down
		{ 0b0000111010000000, 0b1100010001000000, 0b0010111000000000, 0b0100010001100000 }, //L, 4 rotations, default is horizontal down
		{ 0b0000110001100000, 0b0100110010000000, 0b0000110001100000, 0b0100110010000000 }, //Z, 2 rotations, default is Z-shape
		{ 0b0000011011000000, 0b0100011000100000, 0b0000011011000000, 0b0100011000100000 }, //S, 2 rotations, default is S-shape
	};

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

Settings* createSettings() {
	Settings* settings = malloc(sizeof(Settings));
	settings->musicOn = 1;
	settings->startLevel = 12;
	settings->appState = 0;
	settings->lastScore = 0;
	return settings;
}

void destroySettings(Settings* settings) {
	free(settings);
}

/* ~ ~ ~ ~ ~ ~ ~ ~ DRAW METHODS ~ ~ ~ ~ ~ ~ ~ ~ */

void drawString(SDL_Renderer* renderer, char charArray[], int strLength, float startXPos, float yPos, int fontSize, Colour colour) {
	double spaceBetweenChars = 1;
	if (fontSize == 2) spaceBetweenChars = 0.65;
	else if (fontSize == 1) spaceBetweenChars = 0.5;

	for (int i = 0; i < strLength; i++) {
		drawText(renderer, (startXPos + i * (spaceBetweenChars)) * PIXEL_SIZE, yPos * PIXEL_SIZE, charArray[i], fontSize, colour);
	}
}

void fillScoreArray(char* scoreArray, int score) {
	for (int i = 5; i > -1; i--) {
		scoreArray[i] = score % 10 + '0';
		score /= 10;
	}
}

void drawScore(SDL_Renderer* renderer, int score) {
	char scoreArray[6];
	fillScoreArray(scoreArray, score);
	drawString(renderer, "score", 5, 0.25, 21, 2, white);
	drawString(renderer, scoreArray, 6, 0.25, 22, 2, white);
}

void drawShape(SDL_Renderer* renderer, Tetromino currentShape, int screenX, int screenY, ColourScheme colourScheme) {
	short bitmap = currentShape.rotations[currentShape.currentRotation];

	unsigned short bitmask = 0b1000000000000000;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (bitmask & bitmap) {
				HollowCubeDesign.outerRect.x = screenX + j * PIXEL_SIZE + MARGIN;
				HollowCubeDesign.outerRect.y = screenY + i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, colourScheme.primary.r, colourScheme.primary.g, colourScheme.primary.g, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &HollowCubeDesign.outerRect);
				SDL_RenderFillRect(renderer, &HollowCubeDesign.outerRect);
				
				HollowCubeDesign.innerRect.x = screenX + j * PIXEL_SIZE + BORDER + MARGIN;
				HollowCubeDesign.innerRect.y = screenY + i * PIXEL_SIZE + BORDER + MARGIN;
				SDL_SetRenderDrawColor(renderer, colourScheme.secondary.r, colourScheme.secondary.g, colourScheme.secondary.b, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &HollowCubeDesign.innerRect);
				SDL_RenderFillRect(renderer, &HollowCubeDesign.innerRect);

				HollowCubeDesign.specularRect.x = screenX + j * PIXEL_SIZE + MARGIN;
				HollowCubeDesign.specularRect.y = screenY + i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, colourScheme.specular.r, colourScheme.specular.g, colourScheme.specular.b, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &HollowCubeDesign.specularRect);
				SDL_RenderFillRect(renderer, &HollowCubeDesign.specularRect);
			}
			bitmask = bitmask >> 1;
		}
	}
}

void drawBoard(SDL_Renderer* renderer, Gameboard gameboard, ColourScheme colourScheme) {
	for (int i = 0; i < gameboard.numGameRows; i++) {
		unsigned short bitmask = 0b1000000000;
		for (int j = 0; j < gameboard.numGameCols; j++) {
			if (bitmask & gameboard.cells[i + HIDDEN_ROWS]) {
				ColouredCubeDesign.outerRect.x = j * PIXEL_SIZE + MARGIN;
				ColouredCubeDesign.outerRect.y = i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, colourScheme.primary.r, colourScheme.primary.g, colourScheme.primary.g, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.outerRect);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.outerRect);

				ColouredCubeDesign.innerRect.x = j * PIXEL_SIZE + BORDER + MARGIN;
				ColouredCubeDesign.innerRect.y = i * PIXEL_SIZE + BORDER + MARGIN;
				SDL_SetRenderDrawColor(renderer, colourScheme.secondary.r, colourScheme.secondary.g, colourScheme.secondary.b, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.innerRect);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.innerRect);

				ColouredCubeDesign.innerRect2.x = j * PIXEL_SIZE + BORDER + MARGIN;
				ColouredCubeDesign.innerRect2.y = i * PIXEL_SIZE + BORDER + MARGIN;
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.innerRect2);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.innerRect2);

				ColouredCubeDesign.specularRect.x = j * PIXEL_SIZE + MARGIN;
				ColouredCubeDesign.specularRect.y = i * PIXEL_SIZE + MARGIN;
				SDL_SetRenderDrawColor(renderer, colourScheme.specular.r, colourScheme.specular.g, colourScheme.specular.b, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &ColouredCubeDesign.specularRect);
				SDL_RenderFillRect(renderer, &ColouredCubeDesign.specularRect);
			}
			bitmask = bitmask >> 1;
		}
	}
}

void drawLevel(SDL_Renderer* renderer, int currentLevel) {
	char levelArray[2] = { currentLevel / 10 + '0',currentLevel % 10 + '0'};
	drawString(renderer, "lvl", 3, 0.25, 23.75, 2, white);
	drawString(renderer, levelArray, 2, 2.9, 23.75, 2, white);
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

void drawCurrentShape(SDL_Renderer* renderer, Tetromino currentShape, ColourScheme colourScheme) {
	int screenX = currentShape.x * PIXEL_SIZE;
	int screenY = currentShape.y * PIXEL_SIZE;
	drawShape(renderer, currentShape, screenX, screenY, colourScheme);
}

void drawNextShape(SDL_Renderer* renderer, Tetromino nextShape, ColourScheme colourScheme) {
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

	drawShape(renderer, nextShape, previewXpos, previewYpos, colourScheme);
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

void draw(SDL_Renderer* renderer, Game* game, ColourScheme colourScheme) {
	Gameboard gameboard = game->gameboard;
	Tetromino currentShape = game->currentShape;
	Tetromino nextShape = game->nextShape;
	int score = game->score;
	int currentLevel = game->currentLevel;

	drawStats(renderer);
	drawBoard(renderer, gameboard, colourScheme);
	drawCurrentShape(renderer, currentShape, colourScheme);
	drawNextShape(renderer, nextShape, colourScheme);
	drawScore(renderer, score);
	drawLevel(renderer, currentLevel);
	SDL_RenderPresent(renderer);
}

void clear(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void gameOverAnimation(SDL_Renderer* renderer) {
	for (int k = 0; k < 12; k++) {
		clear(renderer);
		drawString(renderer, "game", 4, 3, k, 3, white);
		drawString(renderer, "over", 4, 3, 24 - k, 3, white);
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}
	SDL_Delay(1000);
}

void scoreAnimation(SDL_Renderer* renderer, char scoreArray[]) {
	for (int k = 0; k <= 10; k++) {
		clear(renderer);
		drawString(renderer, "score", 5, - 2.5 + k / 2.0, 11, 3, white);
		drawString(renderer, scoreArray, 6, 7 - k / 2.0, 13, 3, white);
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}
	SDL_Delay(1000);
}

void exitLoop(SDL_Renderer* renderer, char scoreArray[], Settings* settings) {
	int flashOn = 1;
	clock_t lastUpdate = clock();
	while (settings->appState == 3) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				settings->appState = -1;
				return;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
				settings->appState = 0;
				return;
			}
		}

		clock_t now = clock();
		if ((double)(now - lastUpdate) / CLOCKS_PER_SEC >= 0.7) {
			clear(renderer);

			if (flashOn) {
				drawString(renderer, "enter", 5, 3.75, 22.5, 1, white);
				flashOn = 0;
			} else {
				flashOn = 1;
			}

			drawString(renderer, "score", 5, 2.5, 11, 3, white);
			drawString(renderer, scoreArray, 6, 2, 13, 3, white);
			drawString(renderer, "press", 5, 3.75, 21.5, 1, white);
			drawString(renderer, "to continue", 11, 2.25, 23.5, 1, white);
			lastUpdate = now;
			SDL_RenderPresent(renderer);
		}
		SDL_Delay(100);
	}
}

void gameOverScreen(SDL_Renderer* renderer, Settings* settings) {
	char scoreChars[6];
	fillScoreArray(scoreChars, settings->lastScore);
	gameOverAnimation(renderer);
	scoreAnimation(renderer, scoreChars);
	exitLoop(renderer, scoreChars, settings);
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

Game* createGame(int numRows, int numCols, int startLevel) {
	Game* game = malloc(sizeof(Game));

	game->currentShape.shapeType = -1;    //initialize to -1 (no tetromino type defined yet)
	game->nextShape.shapeType = -1; 
	initNewShape(&game->currentShape, &game->nextShape);
	initGameboard(&game->gameboard, numRows, numCols);
	game->timeToMove = 0;

	game->score = 0;
	game->currentLevel = startLevel;
	game->totalLinesCleared = 0;
	game->currentColourIndex = 0;

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

	SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, COLS * PIXEL_SIZE, (ROWS + STATS_ROWS + 2) * PIXEL_SIZE, 0);
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

void drawCredits(SDL_Renderer* renderer) {
	drawString(renderer, "game & music", 12, 2, 22, 1, white);
	drawString(renderer, "by", 2, 4.5, 23, 1, white);
	drawString(renderer, "tom leggett", 11, 2.25, 24, 1, white);
}

void drawTitle(SDL_Renderer* renderer) {
	int xPos = 2;
	int yPos = 1;
	drawString(renderer, "tetris", 6, xPos, yPos, 3, white);
}

void drawPressEnterToStart(SDL_Renderer* renderer) {
	double xPos = 5 - 11 / 4.0;
	double yPos = 12;
	drawString(renderer, "press enter", 11, xPos, yPos, 1, white);
}

void fillLevelCharArray(char level[], int startLevel) {
	if (level < 10) {
		level[0] = startLevel % 10 + '0';
		level[1] = ' ';
	} else {
		level[0] = startLevel / 10 + '0';
		level[1] = startLevel % 10 + '0';
	}
}

void fillMusicCharArray(char musicSetting[], int musicOn) {
	if (musicOn) {
		musicSetting[0] = 'o';
		musicSetting[1] = 'n';
		musicSetting[2] = ' ';
	} else {
		musicSetting[0] = 'o';
		musicSetting[1] = 'f';
		musicSetting[2] = 'f';
	}
}

void drawAllSettings(SDL_Renderer* renderer, Settings* settings, int focus) {
	char levelSetting[2];
	char musicSetting[3];
	fillLevelCharArray(levelSetting, settings->startLevel);
	fillMusicCharArray(musicSetting, settings->musicOn);

	drawString(renderer, "music", 5, 2.5, 9, 1, white);
	drawString(renderer, "settings", 8, 3, 6, 1, white);
	drawString(renderer, "level", 5, 2.5, 8, 1, white);
	drawString(renderer, musicSetting, 3, 6, 9, 1, white);
	drawString(renderer, levelSetting, 2, 6, 8, 1, white);
	
	SDL_Rect levelSettingRect = { 6 * PIXEL_SIZE, 8 * PIXEL_SIZE, 2 * 0.45 * PIXEL_SIZE, 0.5 * PIXEL_SIZE };
	SDL_Rect musicSettingRect = { 6 * PIXEL_SIZE, 9 * PIXEL_SIZE, 2 * 0.45 * PIXEL_SIZE, 0.5 * PIXEL_SIZE };

	if (focus == 0) {
		SDL_RenderDrawRect(renderer, &levelSettingRect);
		SDL_RenderFillRect(renderer, &levelSettingRect);
		drawString(renderer, levelSetting, 2, 6, 8, 1, black);
	}
	else {
		if (!settings->musicOn) {
			musicSettingRect.w += 0.5*PIXEL_SIZE;
		} 
		SDL_RenderDrawRect(renderer, &musicSettingRect);
		SDL_RenderFillRect(renderer, &musicSettingRect);
		drawString(renderer, musicSetting, 3, 6, 9, 1, black);
	}

}

void drawAllControls(SDL_Renderer* renderer) {
	drawString(renderer, "controls", 8, 3, 13, 1, white);
	drawString(renderer, "move      a / d", 15, 1.25, 15, 1, white);
	drawString(renderer, "rotate    < / >", 15, 1.25, 16, 1, white);
	drawString(renderer, "drop      space", 15, 1.25, 17, 1, white);
	drawString(renderer, "pause     esc", 13, 1.25, 18, 1, white);
}

void drawSettingsMenu(SDL_Renderer* renderer, Settings* settings) {
	int flashOn = 1;
	clock_t lastUpdate = clock();
	int focus = 0;

	while (settings->appState == 1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				settings->appState = -1;
				return;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_RETURN: { settings->appState = 2; return; }
					case SDLK_RIGHT: {
						if (focus == 1) {
							settings->musicOn = !settings->musicOn;
						} else {
							if (settings->startLevel < 15) settings->startLevel++;
						}
						break;
					}
					case SDLK_LEFT: {
						if (focus == 1) {
							settings->musicOn = !settings->musicOn;
						}
						else {
							if (settings->startLevel > 1) settings->startLevel--;
						}
						break;
					}
					case SDLK_UP: {if (focus == 1) focus--; break;}
					case SDLK_DOWN: {if (focus == 0) focus++; break;}
				}
			}
		}
		clock_t now = clock();
		if ((double)(now - lastUpdate) / CLOCKS_PER_SEC >= 0.7) {
			flashOn = !flashOn;
			lastUpdate = now;
		}

		clear(renderer);
		drawTitle(renderer);
		drawAllSettings(renderer, settings, focus);
		drawAllControls(renderer);

		drawString(renderer, "press", 5, 2.25, 22.5, 1, white);
		drawString(renderer, "to start", 8, 3, 23.5, 1, white);
		if (flashOn) {
			drawString(renderer, "enter", 5, 5.25, 22.5, 1, white);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}
}

void displayTitleScreen(SDL_Renderer* renderer, Settings* settings) {
	int flashOn = 1;
	clock_t lastUpdate = clock();
	while (settings->appState == 0) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				settings->appState = -1;
				return;
			} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
				settings->appState = 1;
				return;
			}
		}
		clock_t now = clock();
		if ((double)(now - lastUpdate) / CLOCKS_PER_SEC >= 0.7) {
			flashOn = !flashOn;
			lastUpdate = now;
		}

		clear(renderer);
		if (flashOn) {
			drawPressEnterToStart(renderer);
		}
		drawTitle(renderer);
		drawCredits(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}
}

void displaySettingsMenu(SDL_Renderer* renderer, Settings* settings) {
	clear(renderer);
	drawSettingsMenu(renderer, settings);
	SDL_RenderPresent(renderer);
	SDL_Delay(50);
}

void gameLoop(SDL_Renderer* renderer, ColourScheme colours[], Settings* settings) {
	Game* game = createGame(ROWS, COLS, settings->startLevel);
	clock_t lastUpdate = clock();

	while (settings->appState == 2) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
				settings->appState = -1;
				DeinitGameboard(&game->gameboard);
				destroyGame(game);
				return;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_a: { if (isValidMove(&game->currentShape, &game->gameboard, 'L')) game->currentShape.x--; break;}
				case SDLK_d: { if (isValidMove(&game->currentShape, &game->gameboard, 'R'))  game->currentShape.x++; break;}
				case SDLK_s: { if (isValidMove(&game->currentShape, &game->gameboard, 'D'))  game->currentShape.y++; break;}
				case SDLK_SPACE: { while (isValidMove(&game->currentShape, &game->gameboard, 'D'))  game->currentShape.y++; break;}
				case SDLK_RIGHT: { if (isValidMove(&game->currentShape, &game->gameboard, 'C')) {
					game->currentShape.currentRotation = ((game->currentShape.currentRotation + 1) % NUM_ROTATIONS + NUM_ROTATIONS) % NUM_ROTATIONS;
					break;
					}
				}
				case SDLK_LEFT: { if (isValidMove(&game->currentShape, &game->gameboard, 'A')) {
					game->currentShape.currentRotation = ((game->currentShape.currentRotation - 1) % NUM_ROTATIONS + NUM_ROTATIONS) % NUM_ROTATIONS;
					break;
					}
				}
				}
			}
		}

		clock_t currentTime = clock();

		if (!update(game, (double)(currentTime - lastUpdate) / CLOCKS_PER_SEC)) {
			//end-game conditions met
			settings->lastScore = game->score;
			settings->appState = 3;
			DeinitGameboard(&game->gameboard);
			destroyGame(game);
			SDL_Delay(500);
			return;
		}
		if (game->tetrisRows[0] != -1) {
			animateAndClearTetrisRows(renderer, game->tetrisRows);
		}
		lastUpdate = currentTime;
		clear(renderer);
		draw(renderer, game, colours[game->currentColourIndex]);
		SDL_Delay(20);
	}
}

/* ~ ~ ~ ~ ~ ~ ~ ~ MAIN METHOD ~ ~ ~ ~ ~ ~ ~ ~ */

int main(int argc, char* args[]) {
	ColourScheme* colours = createColoursArray(NUM_COLOUR_SCHEMES, redScheme, greenScheme, blueScheme, whiteScheme, greyScheme);
	SDL_Renderer* renderer = initGraphicsAndGetRenderer();
	Settings* settings = createSettings();
	
    // app state 0 -> titleScreen, 1 -> settingsMenu,   2 -> playingGame,  3 -> gameOverScreen, -1 -> exit 

	while (settings->appState > -1) {
		switch (settings->appState) {
			case 0: { displayTitleScreen(renderer, settings); break; }
			case 1: { displaySettingsMenu(renderer, settings); break; }
			case 2: { srand(time(NULL)); gameLoop(renderer, colours, settings); break; }
			case 3: { gameOverScreen(renderer, settings); break; }
		}
	}

	printf("\n\n\n~~~~~~~ G A M E   O V E R ~~~~~~~\n\n\n");
	SDL_DestroyRenderer(renderer);
	destroyColoursArray(colours);
	destroySettings(settings);
	SDL_Quit();
	return 1;
}