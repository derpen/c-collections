#pragma once

#include <SDL.h>
#include <stdio.h>
#include "../config.h"

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gImage;

int util_SDLInit();
int util_SDLLoadMedia(char *filename);
void util_SDLClose();