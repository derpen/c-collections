#include "layout.h"

char hour[MAX_INPUT_HOURS + 1] = "\0";
int hourDigit = 0;

char min[MAX_INPUT_MIN + 1] = "\0";
int minuteDigit = 0;

char sec[MAX_INPUT_SEC + 1] = "\0";
int secondDigit = 0;

BUTTONS_STATE active_button = NONE;

Rectangle boxHour = { WINDOW_HEIGHT / 2.0f - 100, 180, 50, 50 };
Rectangle minHour = { WINDOW_HEIGHT / 2.0f - 200, 180, 50, 50 };
Rectangle secHour = { WINDOW_HEIGHT / 2.0f - 300, 180, 50, 50 };
Rectangle startTimer = { WINDOW_HEIGHT / 2.0f - 100, 250, 50, 50 };

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

void DrawAllRect() {

}

void DrawRectWrapper() {

}
