#include "layout.h"
#include "config.h"

char hourDigit[MAX_INPUT_HOURS + 1] = "\0";
char minDigit[MAX_INPUT_MIN + 1] = "\0";
char secDigit[MAX_INPUT_SEC + 1] = "\0";

int hourCurrentDigit, minCurrentDigit, secCurrentDigit = 0;

BUTTONS_STATE active_button = NONE;

void CheckCollision(Rectangle box) {
	if (CheckCollisionPointRec(GetMousePosition(), box)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			active_button = HOUR;
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			active_button = HOUR;
	}
}

void GetInput() {
}

void DrawScene() {

}

void DrawAllRect() {

}
