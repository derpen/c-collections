#include <stdio.h>
#include <stdlib.h>
#include "raylib/raylib.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 200

typedef struct {
	bool mouseClicked;
	char current_value[3];
	int current_digit_amount;
	Rectangle box;
} TIMER_BUTTONS;

typedef struct {
	bool mouseClicked;
	Rectangle box;
} START_BUTTON;

TIMER_BUTTONS allButtons[3];

//void start_countdown();
void check_collision(TIMER_BUTTONS* buttons);
void receive_input(TIMER_BUTTONS* buttons, bool limit);
void draw_scene(TIMER_BUTTONS buttons);

int main() {

	InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "raylib-test");

	TIMER_BUTTONS hourButton;
	TIMER_BUTTONS minButton;
	TIMER_BUTTONS secButton;
	START_BUTTON startButton;

	// TODO: Is this the C way of initializing data?
	Rectangle boxHour = { WINDOW_HEIGHT / 2.0f - 100, 100, 50, 50 };
	Rectangle minHour = { WINDOW_HEIGHT / 2.0f, 100, 50, 50 };
	Rectangle secHour = { WINDOW_HEIGHT / 2.0f + 100, 100, 50, 50 };
	Rectangle startTimer = { WINDOW_HEIGHT / 2.0f - 100, 250, 50, 50 };
	hourButton.box = boxHour;
	minButton.box = minHour;
	secButton.box = secHour;
	startButton.box = startTimer;
	hourButton.mouseClicked = minButton.mouseClicked = secButton.mouseClicked = startButton.mouseClicked = false;
	hourButton.current_digit_amount = minButton.current_digit_amount = secButton.current_digit_amount = 0;
	hourButton.current_value[0] = minButton.current_value[0] = secButton.current_value[0] = '\0';

	allButtons[0] = hourButton;
	allButtons[1] = minButton;
	allButtons[2] = secButton;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// 2 is the size of allButtons
		for (int i = 0; i <= 2; i++) {
			check_collision(&allButtons[i]);
			if (i == 0) {
				receive_input(&allButtons[i], false);
			}
			else {
				receive_input(&allButtons[i], true);
			}
		}

		// Drawing part
		BeginDrawing();
			ClearBackground(RAYWHITE);

			for (int i = 0; i <= 2; i++) {
				draw_scene(allButtons[i]);
			}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void check_collision(TIMER_BUTTONS* buttons) {
	if (CheckCollisionPointRec(GetMousePosition(), buttons->box)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			buttons->mouseClicked = true;
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			buttons->mouseClicked = false;
	}
}

void receive_input(TIMER_BUTTONS* buttons, bool limit) {
	if (buttons->mouseClicked) {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		int key = GetCharPressed();

		while (key > 0) {
			// 0-9 is keycode 48-57
			if ((key >= 48) && (key <= 57) && (buttons->current_digit_amount < 2)) {
				// TODO: add 0 in the front if theres only one digit
				// Might be a bit too hard actually
				buttons->current_value[buttons->current_digit_amount] = (char)key;
				buttons->current_value[buttons->current_digit_amount + 1] = '\0';
				buttons->current_digit_amount++;

				if (limit) {
					// limit minute and second to 59
					int currentValue = atoi(buttons->current_value);
					if (currentValue >= 60) {
						buttons->current_value[0] = '5';
						buttons->current_value[1] = '9';
						buttons->current_value[2] = '\0';
					}
				}
			}

			key = GetCharPressed(); // Check next character in queue
		}

		if (IsKeyPressed(KEY_BACKSPACE)) {
			buttons->current_digit_amount--;
			if (buttons->current_digit_amount < 0) buttons->current_digit_amount = 0;
			buttons->current_value[buttons->current_digit_amount] = '\0';
		}
	}
	else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}

void draw_scene(TIMER_BUTTONS buttons) {
	DrawRectangleRec(buttons.box, LIGHTGRAY);
	if(buttons.mouseClicked) DrawRectangleLines((int)buttons.box.x, (int)buttons.box.y, (int)buttons.box.width, (int)buttons.box.height, RED);
	else DrawRectangleLines((int)buttons.box.x, (int)buttons.box.y, (int)buttons.box.width, (int)buttons.box.height, LIGHTGRAY);
	DrawText(buttons.current_value, (int)buttons.box.x + 5, (int)buttons.box.y + 20, 40, MAROON);
}
