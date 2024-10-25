#pragma once

#include <SDL.h>
#include "sdl_textures.h"
#include <stdio.h>

typedef struct {
	SDLTexture* texture;
	SDL_Rect rect;
	double angle;
	SDL_Point position;
	SDL_RendererFlip flip;

} SDLButton;

SDLButton SDLButtonInit(int posX, int posY, SDLTexture* s);
void SDLButtonHandleEvent(SDLButton* b, SDL_Event* e);
void SDLButtonRender(SDLButton* b);
