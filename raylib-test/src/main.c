#include <stdio.h>
#include "raylib/raylib.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 200
#define MAX_INPUT_HOURS 3 // Delete soon

typedef struct {
	bool mouseHovered;
	char* current_value[3];
	unsigned int current_digit_amount;
	Rectangle box;
} TIMER_BUTTONS;

typedef struct {
	bool mouseHovered;
	Rectangle box;
} START_BUTTON;

TIMER_BUTTONS allButtons[3];

void start_countdown();
void check_collision(Rectangle box, bool* mouseHoverStatus);
void receive_input(TIMER_BUTTONS buttons);
void draw_scene(TIMER_BUTTONS buttons);

int main() {

	InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "raylib-test");

	TIMER_BUTTONS hourButton;
	TIMER_BUTTONS minButton;
	TIMER_BUTTONS secButton;
	START_BUTTON startButton;

	//bool mouseOnHour = false;
	//char hour[MAX_INPUT_HOURS + 1] = "\0";
	//int digitCount = 0;

	// TODO: Is this the C way of initializing data?
	Rectangle boxHour = { WINDOW_HEIGHT / 2.0f - 100, 100, 50, 50 };
	Rectangle minHour = { WINDOW_HEIGHT / 2.0f - 200, 100, 50, 50 };
	Rectangle secHour = { WINDOW_HEIGHT / 2.0f - 300, 100, 50, 50 };
	Rectangle startTimer = { WINDOW_HEIGHT / 2.0f - 100, 250, 50, 50 };
	hourButton.box = boxHour;
	minButton.box = minHour;
	secButton.box = secHour;
	startButton.box = startTimer;
	hourButton.mouseHovered = minButton.mouseHovered = secButton.mouseHovered = startButton.mouseHovered = false;
	hourButton.current_digit_amount = minButton.current_digit_amount = secButton.current_digit_amount = 0;
	hourButton.current_value[0] = minButton.current_value[0] = secButton.current_value[0] = "\0";

	allButtons[0] = hourButton;
	allButtons[1] = minButton;
	allButtons[2] = secButton;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// 2 is the size of allButtons
		for (int i = 0; i < 2; i++) {
			check_collision(allButtons[i].box, &allButtons[i].mouseHovered);
			receive_input(allButtons[i]);
		}

		// Drawing part
		BeginDrawing();
			ClearBackground(RAYWHITE);

			for (int i = 0; i < 2; i++) {
				draw_scene(allButtons[i]);
			}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void check_collision(Rectangle box, bool* mouseHoverStatus) {
	if (CheckCollisionPointRec(GetMousePosition(), box)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			mouseHoverStatus = true;
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			mouseHoverStatus = false;
	}
}

void receive_input(TIMER_BUTTONS buttons) {
	if (buttons.mouseHovered) {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		int key = GetCharPressed();

		while (key > 0) {
			// 0-9 is keycode 48-57
			if ((key >= 48) && (key <= 57) && (buttons.current_digit_amount < 2)) {
				buttons.current_value[buttons.current_digit_amount] = (char)key;
				buttons.current_value[buttons.current_digit_amount + 1] = '\0';
				buttons.current_digit_amount++;
			}

			key = GetCharPressed(); // Check next character in queue
		}

		if (IsKeyPressed(KEY_BACKSPACE)) {
			buttons.current_digit_amount--;
			if (buttons.current_digit_amount < 0) buttons.current_digit_amount = 0;
			buttons.current_value[buttons.current_digit_amount] = '\0';
		}
	}
	else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}

void draw_scene(TIMER_BUTTONS buttons) {
	DrawRectangleRec(buttons.box, LIGHTGRAY);
	if(buttons.mouseHovered) DrawRectangleLines((int)buttons.box.x, (int)buttons.box.y, (int)buttons.box.width, (int)buttons.box.height, RED);
	else DrawRectangleLines((int)buttons.box.x, (int)buttons.box.y, (int)buttons.box.width, (int)buttons.box.height, LIGHTGRAY);
	DrawText(buttons.current_value, (int)buttons.box.x + 5, (int)buttons.box.y + 20, 40, MAROON);
}
