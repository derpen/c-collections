#include "sdl_fonts.h"

SDLFont SDLFontInit(char* filename, SDLTexture* s){
	SDLFont newFont;
	newFont.Texture = s;

	SDLTextureFree(s);

	newFont.Font = TTF_OpenFont(filename, 28);
	if (newFont.Font == NULL) {
		printf("Failed to load Font! TTF_Error: %s \n", TTF_GetError());
		return;
	}

	return newFont;
}

int SDLFontRenderText(char* text, SDLTexture* s, SDLFont* f){
	SDL_Color textColor = { 0, 0, 0 };

	if (strlen(text) == 0) {
		text = " ";
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(f->Font, text, textColor);
	if (textSurface == NULL) {
		printf("Unable to render Text! TTF_Error: %s \n", TTF_GetError());
		return -1;
	}

	s->Texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	if (s->Texture == NULL) {
		printf("Unable to create texture from rendered text! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	s->w = textSurface->w;
	s->h = textSurface->h;

	SDLTextureRender(s);
	SDL_FreeSurface(textSurface);

	return 0;
}

void SDLFontClose(SDLFont f) {
	//Free font
	TTF_CloseFont( f.Font );
	f.Font = NULL;
}
