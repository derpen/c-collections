#include "sdl_utils.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

int SDLUtilInit(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL error! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	gWindow = SDL_CreateWindow("Timer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL) {
		printf("Window could not be created! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		printf("Renderer could NOT be created! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if ( !(IMG_Init(imgFlags) & imgFlags) ) {
		printf("SDL_Image could not be initialized! IMG_Error: %s \n", IMG_GetError());
		return -1;
	}

	if (TTF_Init() < 0) {
		printf("SDL_ttf could not be initialized! TTF_Error: %s \n", TTF_GetError());
		return -1;
	}

	return 0;
}

int SDLUtilLoadFont(char* filename, SDLTexture* s){
	SDLTextureFree(s);

	gFont = TTF_OpenFont(filename, 28);
	if (gFont == NULL) {
		printf("Failed to load Font! TTF_Error: %s \n", TTF_GetError());
		return -1;
	}
	
	return 0;
}

int SDLUtilShowText(char* text, SDLTexture* s){
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, textColor);
	if (textSurface == NULL) {
		printf("Unable to render Text! TTF_Error: %s \n", TTF_GetError());
		return -1;
	}

	s->Texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	if (s->Texture == NULL) {
		printf("Unable to create texture from rendered text! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	s->w = textSurface->w;
	s->h = textSurface->h;

	SDL_FreeSurface(textSurface);

	return 0;
}

void SDLUtilClose(SDLTexture* s){
	//Free loaded images
	SDLTextureFree(s);

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
	IMG_Quit();
}