#pragma once
#define numberBoxHeight 7
#define numberBoxWidth 5
#include "colours.h"
#ifndef PIXEL_SIZE 20
#endif

SDL_Rect zero[7] = { {1, 0, 3, 1},
					 {1, (numberBoxHeight - 1), 3,1},
					 {0, 1, 1, 5},
					 {(numberBoxWidth - 1), 1 , 1, 5},
					 {3, 2, 1, 1},
					 {2, 3, 1, 1},
					 {1, 4, 1, 1}
};
SDL_Rect one[7] = { {0, (numberBoxHeight - 1), numberBoxWidth, 1},
					 {2, 0 , 1, numberBoxHeight},
					 {1, 1 , 1, 1},
					 {0 , 2 , 1, 1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};
SDL_Rect two[7] = { {0, (numberBoxHeight - 1), numberBoxWidth, 1},
					{0, 5 , 1, 1},
					{1, 4 , 1, 1},
					{2, 3 , 2, 1},
					{4, 1 , 1, 2},
					{1, 0 , 3, 1},
					{0, 1 , 1, 1}
};
SDL_Rect three[7] = { {0, 1 , 1, 1},
						{1, 0 , 3, 1},
						{4, 1 , 1, 2},
						{1, 3 , 3, 1},
						{4, 4 , 1, 2},
						{1, 6, 3, 1},
						{0, 5, 1, 1}
};
SDL_Rect four[7] = { {3, 0 , 1, 7},
					{0 , 4, 5, 1},
					{0, 3 , 1, 1},
					{1, 2 , 1, 1},
					{2, 1 , 1, 1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};
SDL_Rect five[7] = { {0, 0, 5, 1},
					 {0, 1, 1, 1},
					 {0, 2, 4, 1},
					 {4, 3 , 1, 3},
					 {1, 6 , 3, 1},
					 {0, 5 , 1, 1},
					{-1,-1,-1,-1}
};
SDL_Rect six[7] = { {0, 1 , 1, 5},
						{1, 0 , 3, 1},
						{4, 1 , 1, 1},
						{0, 3, 4, 1},
						{4, 4 , 1, 2},
						{1, 6 , 3, 1},
						{-1,-1,-1,-1}
};
SDL_Rect seven[7] = { {0, 0, 5, 1},
						{4, 1 , 1, 1},
					{3, 2 , 1, 1},
					{2, 3 , 1, 4},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};
SDL_Rect eight[7] = { {0, 1 , 1, 2},
						{1, 0 , 3, 1},
						{4, 1 , 1, 2},
						{1, 3 , 3, 1},
						{4, 4 , 1, 2},
						{1, 6 , 3, 1},
						{0, 4 , 1, 2}
};
SDL_Rect nine[7] = { {0, 1 , 1, 2},
						{1, 0 , 3, 1},
						{4, 1 , 1, 5},
						{1, 3 , 3, 1},
						{1, 6 , 3, 1},
						{0, 5 , 1, 1},
						{-1,-1,-1,-1}
};

SDL_Rect a[7] = { { 2, 0, 1, 1 },
				{ 1, 1, 3, 1 },
				{ 0, 2, 1, 5 },
				{ 4, 2, 1, 5 },
				{ 1, 4, 3, 1 },
				{ -1,-1,-1,-1 },
				{ -1,-1,-1,-1 } };
SDL_Rect b[7] = { { 0, 0, 1, 7 },
				{ 0, 0, 4, 1 },
				{ 4, 1, 1, 2 },
				{ 0, 3, 4, 1 },
				{ 4, 4, 1, 2 },
				{ 0,6,4,1 },
				{ -1,-1,-1,-1 } };
SDL_Rect c[7] = {
				{1, 0, 3, 1},
				{ 4, 1, 1, 1 },
				{ 0, 1, 1, 5 },
				{1, 6, 3, 1},
				{4, 5, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect d[7] = {
				{0, 0, 1, 7},
				{ 0, 0, 3, 1 },
				{ 0, 6, 3, 1 },
				{3, 1, 1, 1},
				{3, 5, 1, 1},
				{4,2,1,3},
				{-1,-1,-1,-1}
};
SDL_Rect e[7] = {
					{0, 0, 1, 7},
					{0, 0, 5, 1},
					{0, 3, 4, 1},
					{0, 6, 5, 1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};
SDL_Rect f[7] = {
					{0, 0, 5, 1},
					{0, 0, 1, 7},
					{0, 3, 4, 1},
					{-1, -1, -1, -1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};
SDL_Rect g[7] = {
				{1, 0, 3, 1},
				{4, 1, 1, 1},
				{0, 1, 1, 5},
				{1, 6, 3, 1},
				{4, 4, 1, 2},
				{2, 3, 2, 1},
				{-1,-1,-1,-1}
};
SDL_Rect h[7] = {
				{0, 0, 1, 7},
				{0, 3, 4, 1},
				{4, 0, 1, 7},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect i[7] = {
				{2, 0, 1, 7},
				{0, 0, 5, 1},
				{0, 6, 5, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect l[7] = {
				{0, 0, 1, 7},
				{0, 6, 5, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect m[7] = {
				{0, 0, 1, 7},
				{4, 0, 1, 7},
				{1, 1, 1, 1},
				{3, 1, 1, 1},
				{2, 2, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect n[7] = {
				{0, 0, 1, 7},
				{4, 0, 1, 7},
				{1, 2, 1, 1},
				{2, 3, 1, 1},
				{3, 4, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect o[7] = { {1, 0, 3, 1},
					 {1, 6, 3, 1},
					 {0, 1, 1, 5},
					 {4, 1 , 1, 5},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1},
					{-1,-1,-1,-1}
};
SDL_Rect p[7] = {
				{0, 0, 1, 7},
				{0, 0, 4, 1},
				{4, 1, 1, 2},
				{0, 3, 4, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect r[7] = {
					 {0, 0, 1, 7},
					{1, 0, 3, 1},
					{4, 1, 1, 2},
					{0, 3, 4, 1},
					{2, 4 , 1, 1},
					{3, 5 , 1, 1},
					{4, 6 , 1, 1}
};
SDL_Rect s[7] = {
				{1, 0, 3, 1},
				{ 4, 1, 1, 1 },
				{ 0, 1, 1, 2 },
				{1, 3, 3, 1},
				{ 4, 4, 1, 2 },
				{1, 6, 3, 1},
				{0, 5, 1, 1},
};
SDL_Rect t[7] = {
				{0, 0, 5, 1},
				{2, 0, 1, 7},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect u[7] = {
				{0, 0, 1, 6},
				{4, 0, 1, 6},
				{1, 6, 3, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect v[7] = {
				{0, 0, 1, 5},
				{4, 0, 1, 5},
				{1, 5, 1, 1},
				{3, 5, 1, 1},
				{2, 6, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect w[7] = {
				{0, 0, 1, 7},
				{4, 0, 1, 7},
				{1, 5, 1, 1},
				{3, 5, 1, 1},
				{2, 4, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect y[7] = {
				{0, 0, 1, 2},
				{4, 0, 1, 2},
				{1, 2, 1, 1},
				{3, 2, 1, 1},
				{2, 3, 1, 4},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect heart[7] = {
				{1, 1, 1, 1},
				{3, 1, 1, 1},
				{0, 2, 5, 3},
				{1, 5, 3, 1},
				{2, 6, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect slash[7] = {
				{0, 5, 1, 2},
				{1, 4, 1, 2},
				{2, 3, 1, 2},
				{3, 2, 1, 2},
				{4, 1, 1, 2},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect leftArrow[7] = {
				{3, 0, 1, 7},
				{2, 1, 1, 5},
				{1, 2, 1, 3},
				{0, 3, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect rightArrow[7] = {
				{0, 0, 1, 7},
				{1, 1, 1, 5},
				{2, 2, 1, 3},
				{3, 3, 1, 1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1},
				{-1,-1,-1,-1}
};
SDL_Rect* text[40] = { zero,one,two,three,four,five,six,seven,eight,nine, 
			a,b,c,d,e,f,g,h,i,NULL,NULL,l,m,n,o,p,NULL,r,s,t,u,v,w,NULL,y, NULL, heart, slash, leftArrow, rightArrow };

void setFontSize(int fontSize, int charToDraw) {
	for (int i = 0; i < 7; i++) {
		if (text[charToDraw][i].x == -1) return;
		text[charToDraw][i].x *= fontSize;
		text[charToDraw][i].y *= fontSize;
		text[charToDraw][i].w *= fontSize;
		text[charToDraw][i].h *= fontSize;
	}
}

void unSetFontSize(int currentFontSize, int charToDraw) {
	for (int i = 0; i < 7; i++) {
		if (text[charToDraw][i].x == -1) return;
		text[charToDraw][i].x /= currentFontSize;
		text[charToDraw][i].y /= currentFontSize;
		text[charToDraw][i].w /= currentFontSize;
		text[charToDraw][i].h /= currentFontSize;
	}
}

void drawText(SDL_Renderer* renderer, int screenX, int screenY, char charToDraw, int fontSize, Colour c) {
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);

	if (charToDraw == ' ') return;
	
	int index = -1;
	if (48 <= charToDraw && charToDraw <= 57) index = (int)charToDraw - 48;
	else if (97 <= charToDraw && charToDraw <= 122) index = (int)charToDraw - 87;
	else {
		switch (charToDraw) {
			case 38: { index = 36; break; } 
			case 47: { index = 37; break; }
			case 60: { index = 38; break; }
			case 62: { index = 39; break; }
		}
	}

	if (index < 0 || index > 39) {
		printf("Text Index Out of Bounds\n");
		return;
	}
	//draw each rectangle defined in digit mesh
	for (int i = 0; i < 7; i++) {
		if (text[index][i].x == -1) return;
		setFontSize(fontSize, index);
		text[index][i].x += (screenX + fontSize);
		text[index][i].y += (screenY + fontSize);

		SDL_RenderDrawRect(renderer, &text[index][i]);
		SDL_RenderFillRect(renderer, &text[index][i]);

		text[index][i].x -= (screenX + fontSize);
		text[index][i].y -= (screenY + fontSize);
		unSetFontSize(fontSize, index);
	}
}


