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

	newFont.position = (SDL_Point){ 0, 0 };

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

	//// Render, lots of parameter
	//SDL_Rect* clip = NULL;
	//SDL_Rect* renderQuad = NULL;
	//double angle = 0.0;
	//SDL_Point center = f->position;
	//SDL_RendererFlip flip = SDL_FLIP_NONE;
	//_SDLTextureRender(s, clip, renderQuad, angle, &center, flip);

	SDLTextureRender(s);

	SDL_FreeSurface(textSurface);

	return 0;
}

void SDLFontSetPos(int x, int y, SDLFont* f) {
	f->position.x = x;
	f->position.y = y;
}

void SDLFontFree(SDLFont* f) {
	//Free font
	TTF_CloseFont( f->Font );
	f->Font = NULL;
}
