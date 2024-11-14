#include <stdio.h>
#include "layout.h"
#include "raylib/raylib.h"

#define MAX_INPUT_HOURS 3

int main() {

	InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "raylib-test");

	bool mouseOnHour = false;
	char hour[MAX_INPUT_HOURS + 1] = "\0";
	int digitCount = 0;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		if (CheckCollisionPointRec(GetMousePosition(), boxHour)) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				mouseOnHour = true;
			}
		}
		else {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				mouseOnHour = false;
		}

		if (mouseOnHour) {
			SetMouseCursor(MOUSE_CURSOR_IBEAM);

			int key = GetCharPressed();

			while (key > 0) {
				// 0-9 is keycode 48-57
				if ((key >= 32) && (key <= 125) && (digitCount < MAX_INPUT_HOURS)) {
					hour[digitCount] = (char)key;
					hour[digitCount + 1] = '\0';
					digitCount++;
					printf("Current keycode: %d", key);
				}

				key = GetCharPressed(); // Check next character in queue
			}

			if (IsKeyPressed(KEY_BACKSPACE)) {
				digitCount--;
				if (digitCount < 0) digitCount = 0;
				hour[digitCount] = '\0';
			}
		}
		else {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}

		// Drawing part
		BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawRectangleRec(boxHour, LIGHTGRAY);
			if(mouseOnHour) DrawRectangleLines((int)boxHour.x, (int)boxHour.y, (int)boxHour.width, (int)boxHour.height, RED);
			else DrawRectangleLines((int)boxHour.x, (int)boxHour.y, (int)boxHour.width, (int)boxHour.height, LIGHTGRAY);

			DrawText(hour, (int)boxHour.x + 5, (int)boxHour.y + 20, 40, MAROON);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}