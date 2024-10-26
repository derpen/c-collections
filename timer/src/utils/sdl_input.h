#pragma once
#define MAX_INPUT_SIZE 3

#include <SDL.h>
#include <stdbool.h>
#include "sdl_fonts.h"

typedef struct {
	SDLFont* font;
	SDL_Point position;
	char inputText[MAX_INPUT_SIZE];
	bool isTyping;
} SDLInputText;

//SDLInputText SDLInputInit(char* text, SDLFont* f);
SDLInputText SDLInputInit(char* text);
void SDLInputToggle(SDLInputText t);
void SDLInputRender(SDLInputText t);
void SDLInputHandleEvent(SDLInputText t, SDL_Event e);