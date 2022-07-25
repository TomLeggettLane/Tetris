#define numberBoxHeight 7
#define numberBoxWidth 5

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
SDL_Rect e[7] = {
					{0, 0, 1, 7},
					{0, 0, 5, 1},
					{0, 3, 4, 1},
					{0, 6, 5, 1},
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

SDL_Rect* text[37] = { zero,one,two,three,four,five,six,seven,eight,nine, 
			a,b,c,NULL,e,NULL,g,NULL,i,NULL,NULL,l,m,n,o,p,NULL,r,s,t,u,v,NULL,NULL,y, NULL, heart };

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

void drawText(SDL_Renderer* renderer, int screenX, int screenY, char charToDraw, int fontSize) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	if (charToDraw == ' ') return;
	
	int index = -1;
	if (48 <= charToDraw && charToDraw <= 57) index = (int)charToDraw - 48;
	else if (97 <= charToDraw && charToDraw <= 122) index = (int)charToDraw - 87;
	else if (38 == charToDraw) index = 36;
	if (index < 0 || index > 37) {
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

