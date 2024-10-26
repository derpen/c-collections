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
#include "utils/sdl_input.h"
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
	SDLInputText hour = SDLInputInit("00");
	SDLInputText min = SDLInputInit("05");
	SDLInputText sec = SDLInputInit("00");

	if (SDLTextureLoad("res/osaka2.jpeg", &buttonTexture) < 0) {
		printf("Failed to load texture \n");
		return -1;
	}

	SDLButton timerButton = SDLButtonInit(20, 20, &buttonTexture);
	SDLButton hourInput = SDLButtonInit(50, 50, &buttonTexture);
	SDLButton minuteInput = SDLButtonInit(80, 80, &buttonTexture);
	SDLButton secondInput = SDLButtonInit(100, 100, &buttonTexture);

	SDL_Event e; 
	short quit = 0;

	SDLFontRenderText(hour.inputText, &textTexture, &globalFont);
	SDLFontRenderText(min.inputText, &textTexture, &globalFont);
	SDLFontRenderText(sec.inputText, &textTexture, &globalFont);
	SDL_StartTextInput();

	// the toggle for timer
	short is_timer_counting = 0;

	while (quit == 0) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;

			short osakaButton = SDLButtonHandleEvent(&timerButton, &e);
			if (osakaButton > 0) {
				is_timer_counting = !is_timer_counting;
				//printf("Sata andaagii!! \n");
				printf("timer status: %d \n", is_timer_counting);
			}
		}

		// Renderz
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		SDLButtonRender(&timerButton);
		SDLButtonRender(&hourInput);
		SDLButtonRender(&minuteInput);
		SDLButtonRender(&secondInput);
		SDLTextureRender(&textTexture);
		SDLFontRenderText(hour.inputText, &textTexture, &globalFont);
		SDLFontRenderText(min.inputText, &textTexture, &globalFont);
		SDLFontRenderText(sec.inputText, &textTexture, &globalFont);

		SDL_RenderPresent(gRenderer);
	}

	SDL_StopTextInput();
	SDLFontFree(&globalFont);
	SDLTextureFree(&timerButton.texture);
	SDLTextureFree(&buttonTexture);
	SDLTextureFree(&textTexture);
	SDLUtilClose();

	return 0;
}
