#pragma once

#include <SDL_ttf.h>
#include "sdl_utils.h"
#include "sdl_textures.h"

typedef struct {
	SDLTexture* Texture;
	TTF_Font* Font;
	SDL_Point position;
} SDLFont;

SDLFont SDLFontInit(char* filename, SDLTexture* s);
int SDLFontRenderText(char* text, SDLTexture* s, SDLFont* f); 
void SDLFontSetPos(int x, int y, SDLFont* f);
void SDLFontFree(SDLFont* f);

