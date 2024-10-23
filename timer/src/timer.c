/*

This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.

------

Me, current author of this github repo, have modified it a little

*/

//Using SDL and standard IO
#include "utils/sdl_utils.h"
#include <stdio.h>

int main(int argc, char* args[]) {

	if (util_SDLInit() < 0) {
		printf("Failed to initialize \n");
		return -1;
	}

	if (util_SDLLoadMedia("res/osaka.bmp") < 0) {
		printf("Failed to load media \n");
		return -1;
	}

	SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	SDL_Event e; 
	int quit = 0;
	while (quit == 0) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;
		}
	}

	util_SDLClose();

	return 0;
}
