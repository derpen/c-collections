#include "sdl_button.h"

SDLButton SDLButtonInit(int posX, int posY, SDLTexture* s) {
	SDLButton newButton;

	newButton.texture = s;
	newButton.rect = (SDL_Rect){ posX, posY, s->w, s->h};
	newButton.angle = 0.0;
	newButton.position = (SDL_Point){ posX, posY };
	newButton.flip = SDL_FLIP_NONE;

	return newButton;
}

void SDLButtonHandleEvent(SDLButton* b, SDL_Event* e) {
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		// TODO: this thing
		int inside = 1;
		if (mouseX < b->position.x) {
			inside = 0;
		}
		else if (mouseX > b->position.x + b->texture->w) {
			inside = 0;
		}
		else if (mouseY < b->position.y) {
			inside = 0;
		}
		else if (mouseY > b->position.y + b->texture->h) {
			inside = 0;
		}

		if (inside) {
			printf("Click event happened :D \n");
		}
	}
}

void SDLButtonRender(SDLButton* b ,SDLTexture* s) {
	_SDLTextureRender(s, &b->rect, &b->rect, b->angle, &b->position, b->flip);
}
