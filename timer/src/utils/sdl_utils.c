#include "sdl_utils.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gImage = NULL;

SDL_Texture* _texture = NULL;
int _imgWidth = 0;
int _imgHeight = 0;

TTF_Font* gFont = NULL;

int util_SDLInit() {
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

int util_SDLLoadTexture(char *filename){
	util_SDLFree();

	SDL_Surface* loadImage = IMG_Load(filename);
	if (loadImage == NULL) {
		printf("Unable to load Image! IMG_Error: %s \n", IMG_GetError());
		return -1;
	}

	//Color key image
	SDL_SetColorKey( loadImage, SDL_TRUE, SDL_MapRGB( loadImage->format, 0, 0xFF, 0xFF ) );

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface( gRenderer, loadImage );
	if( newTexture == NULL )
	{
		printf( "Unable to create texture from %s! SDL Error: %s \n", filename, SDL_GetError() );
		return -1;
	}

	_imgHeight = loadImage->h;
	_imgWidth = loadImage->w;

	SDL_FreeSurface(loadImage);

	_texture = newTexture;

	return 0;
}

int util_SDLLoadFont(char* filename) {
	util_SDLFree();

	gFont = TTF_OpenFont(filename, 28);
	if (gFont == NULL) {
		printf("Failed to load Font! TTF_Error: %s \n", TTF_GetError());
		return -1;
	}

	SDL_Color textColor = { 0, 0, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "Ayy lmao", textColor);
	if (textSurface == NULL) {
		printf("Unable to render Text! TTF_Error: %s \n", TTF_GetError());
		return -1;
	}

	_texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	if (_texture == NULL) {
		printf("Unable to create texture from rendered text! SDL_Error: %s \n", SDL_GetError());
		return -1;
	}

	_imgWidth = textSurface->w;
	_imgHeight = textSurface->h;

	SDL_FreeSurface(textSurface);

	return 0;
}

void util_SDLFree() {
	if (_texture != NULL) {
		SDL_DestroyTexture( _texture );
		_texture = NULL;
		_imgWidth = 0;
		_imgHeight = 0;
	}
}

void util_SDLRender() {

	//gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
	int x = (SCREEN_WIDTH - _imgWidth) / 2;
	int y = (SCREEN_HEIGHT - _imgHeight) / 2;

	SDL_Rect renderQuad = { x, y, _imgWidth, _imgHeight };
	SDL_Rect* clip = NULL;
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(gRenderer, _texture, clip, &renderQuad, angle, center, flip);

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
	TTF_Quit();
	SDL_Quit();
	IMG_Quit();
}