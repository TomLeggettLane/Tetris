#pragma once

#define NUM_COLOUR_SCHEMES 5

typedef struct {
	int r;
	int g;
	int b;
} Colour;

Colour white = { 255,255,255 };

Colour black = { 0,0,0 };

typedef struct {
	Colour primary;
	Colour secondary;
	Colour specular;
} ColourScheme;

ColourScheme redScheme = {
	.primary = { 165, 42, 42 },
	.secondary = { 211, 211, 211 },
	.specular = { 255, 255, 255 },
};

ColourScheme greenScheme = {
	.primary = { 42, 165, 42 },
	.secondary = { 211, 211, 211 },
	.specular = { 255, 255, 255 },
};

ColourScheme blueScheme = {
	.primary = { 42, 42, 165 },
	.secondary = { 211, 211, 211 },
	.specular = { 255, 255, 255 },
};

ColourScheme whiteScheme = {
	.primary = { 255, 255, 255 },
	.secondary = { 255, 255, 255 },
	.specular = { 255, 255, 255 },
};

ColourScheme greyScheme = {
	.primary = { 75, 75, 75 },
	.secondary = { 75, 75, 75 },
	.specular = { 75, 75, 75 },
};

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
};
