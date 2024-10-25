/*

This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.

------

Me, current author of this github repo, have modified it a little

*/

//Using SDL and standard IO
#include "utils/sdl_utils.h"
#include "utils/sdl_button.h"
#include "utils/sdl_fonts.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char* args[]) {

	if (SDLUtilInit() < 0) {
		printf("Failed to initialize \n");
		return -1;
	}

	//Create Texture
	SDLTexture buttonTexture = SDLTextureInit();
	SDLTexture textTexture = SDLTextureInit();
	SDLFont globalFont = SDLFontInit("res/fonts/Roboto-Regular.ttf", &textTexture);

	if (SDLTextureLoad("res/osaka2.jpeg", &buttonTexture) < 0) {
		printf("Failed to load texture \n");
		return -1;
	}

	int buttonX = 20;
	int buttonY = 20;
	SDLButton timerButton = SDLButtonInit(buttonX, buttonY, &buttonTexture);

	SDL_Event e; 
	int quit = 0;

	int MAX_INPUT_SIZE = 6;
	char inputOne[6] = "Empti";

	SDLFontRenderText(inputOne, &textTexture, &globalFont);
	SDL_StartTextInput();

	// TODO: RENDER TEXT HERE

	while (quit == 0) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;
			else if (e.type == SDL_TEXTINPUT) {
				strncat(inputOne, e.text.text, MAX_INPUT_SIZE - strlen(inputOne) - 1); /* <-- TODO: wtf is this ?? */
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					// Remove the last character
					size_t len = strlen(inputOne);
					if (len > 0) {
						inputOne[len - 1] = '\0';
					}
				}
			}

			SDLButtonHandleEvent(&timerButton, &e);
		}

		// Renderz
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		SDLButtonRender(&timerButton);
		SDLTextureRender(&textTexture);
		SDLFontRenderText(inputOne, &textTexture, &globalFont);

		SDL_RenderPresent(gRenderer);
	}

	SDL_StopTextInput();
	SDLTextureFree(&buttonTexture);
	SDLTextureFree(&textTexture);
	SDLUtilClose();

	return 0;
}
