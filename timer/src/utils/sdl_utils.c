#include "sdl_utils.h"

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gImage = NULL;

int util_SDLInit() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL error! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	gWindow = SDL_CreateWindow("Timer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL) {
		printf("Window could not be created! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	return 0;
}

int util_SDLLoadMedia(char *filename){
	gImage = SDL_LoadBMP(filename);
	if (gImage == NULL) {
		printf("Failed to load %s ------- SDL_Error: %s \n", filename, SDL_GetError());
		return -1;
	}
	return 0;
}

void util_SDLClose() {
	//Deallocate surface
	SDL_FreeSurface(gImage);
	gImage = NULL;
	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}