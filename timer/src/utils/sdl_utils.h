#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "../config.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gImage;

extern SDL_Texture* _texture;
extern int _imgWidth;
extern int _imgHeight;

extern TTF_Font* gFont;

int util_SDLInit();
int util_SDLLoadTexture(char *filename);
int util_SDLLoadFont(char* filename);
void util_SDLFree();
void util_SDLRender();
void util_SDLClose();