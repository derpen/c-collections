#pragma once

#include <SDL_ttf.h>
#include "sdl_utils.h"
#include "sdl_textures.h"

typedef struct {
	SDLTexture* Texture;
	TTF_Font* Font;
} SDLFont;

SDLFont SDLFontInit(char* filename, SDLTexture* s);
int SDLFontRenderText(char* text, SDLTexture* s, SDLFont* f); 
void SDLFontClose(SDLFont f);
