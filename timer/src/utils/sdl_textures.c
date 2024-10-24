#include "sdl_textures.h"
#include "sdl_utils.h"

SDLTexture SDLTextureInit() {
	SDLTexture newTexture;
	newTexture.Texture = NULL;
	newTexture.w = 0;
	newTexture.h = 0;

	return newTexture;
}

int SDLTextureLoad(char* filename, SDLTexture* s) {
	SDLTextureFree(s);

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

	s->h = loadImage->h;
	s->w = loadImage->w;

	SDL_FreeSurface(loadImage);

	s->Texture = newTexture;

	return 0;
}

void _SDLTextureRender(SDLTexture* s, SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	int x = (SCREEN_WIDTH - s->w) / 2;
	int y = (SCREEN_HEIGHT - s->h) / 2;

	if (renderQuad == NULL) {
		SDL_Rect defaultRenderQuad = { x, y, s->w, s->h };
		renderQuad = &defaultRenderQuad;
	}

	if (clip != NULL) {
		renderQuad->w = clip->w;
		renderQuad->h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, s->Texture, clip, renderQuad, angle, center, flip);
}

void SDLTextureRender(SDLTexture* s) {
	SDL_Rect* clip = NULL;
	SDL_Rect* renderQuad = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	_SDLTextureRender(s, clip, renderQuad, angle, center, flip);
}


void SDLTextureFree(SDLTexture* s){
	if (s->Texture != NULL) {
		SDL_DestroyTexture(s->Texture);
		s->Texture = NULL;
		s->w = 0;
		s->h = 0;
	}
}
