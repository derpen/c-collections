/*

This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.

------

Me, current author of this github repo, have modified it a little

*/

//Using SDL and standard IO
#include "utils/sdl_utils.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char* args[]) {

	if (SDLUtilInit() < 0) {
		printf("Failed to initialize \n");
		return -1;
	}

	//Create Texture
	SDLTexture currentTexture = SDLTextureInit();

	//if (SDLUtilLoadFont("res/fonts/Roboto-Regular.ttf", &currentTexture) < 0) {
	//	printf("Failed to load font \n");
	//	return -1;
	//}

	//if (SDLUtilShowText("Timer Application", &currentTexture) < 0) {
	//	printf("Failed to show text \n");
	//	return -1;
	//}

	if (SDLTextureLoad("res/osaka2.jpeg", &currentTexture) < 0) {
		printf("Failed to load texture \n");
		return -1;
	}

	SDL_Event e; 
	int quit = 0;
	while (quit == 0) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		SDLTextureRender(&currentTexture);

		SDL_RenderPresent(gRenderer);
	}

	SDLUtilClose(&currentTexture);

	return 0;
}
