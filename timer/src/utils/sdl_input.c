#include "sdl_input.h"

SDLInputText SDLInputInit(char* text){
	SDLInputText newInput;

	//newInput.font = f;

	strncpy_s(newInput.inputText, sizeof(newInput.inputText), text, _TRUNCATE); /* This is how u copy string in this language */
	newInput.isTyping = false;

	return newInput;
}

void SDLInputToggle(SDLInputText t){
	t.isTyping = !t.isTyping;
}

void SDLInputRender(SDLInputText t) {
	//// Render, lots of parameter
	//SDL_Rect* clip = NULL;
	//SDL_Rect* renderQuad = NULL;
	//double angle = 0.0;
	//SDL_Point center = t.position;
	//SDL_RendererFlip flip = SDL_FLIP_NONE;
	//_SDLTextureRender(s, clip, renderQuad, angle, &center, flip);

}

void SDLInputHandleEvent(SDLInputText t, SDL_Event e){
	if (t.isTyping) {
		if (e.type == SDL_TEXTINPUT) {
			strncat(t.inputText, e.text.text, MAX_INPUT_SIZE - strlen(t.inputText) - 1); /* <-- TODO: wtf is this ?? */
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_BACKSPACE) {
				// Remove the last character
				size_t len = strlen(t.inputText);
				if (len > 0) {
					t.inputText[len - 1] = '\0';
				}
			}
		}
	}
}
