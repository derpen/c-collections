#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "../config.h"
#include "sdl_textures.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

int SDLUtilInit();
int SDLUtilLoadFont(char* filename, SDLTexture* s);
int SDLUtilShowText(char* text, SDLTexture* s); /* TODO: Might wanna move this one into its own font handler soon */
void SDLUtilClose(SDLTexture* s);