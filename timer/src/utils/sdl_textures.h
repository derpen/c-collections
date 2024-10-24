#pragma once

#include <SDL_image.h>

typedef struct {
	SDL_Texture* Texture;
	int w;
	int h;
} SDLTexture;

SDLTexture SDLTextureInit();
int SDLTextureLoad(char* filename, SDLTexture* s);

void _SDLTextureRender(SDLTexture* s, SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip);
void SDLTextureRender(SDLTexture* s);
//newButton.rect = (SDL_Rect){ posX, posY, s->w, s->h};
//newButton.angle = 0.0;
//newButton.position = (SDL_Point){ posX, posY };
//newButton.flip = SDL_FLIP_NONE;


void SDLTextureFree(SDLTexture* s);