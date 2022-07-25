#define NUM_COLOUR_SCHEMES 5

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