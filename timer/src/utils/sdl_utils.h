#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "../config.h"
#include "sdl_textures.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

int SDLUtilInit();
void SDLUtilClose();