#include <stdio.h>
#include <stdlib.h>
#include "raylib/raylib.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 200

// Make sure to check the TODOs :3

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

bool start_countdown(int* hour, int* min, int* sec, TIMER_BUTTONS* buttons);
void check_collision(Rectangle box, bool* mouseClicked);
void receive_input(TIMER_BUTTONS* buttons, bool limit);
void draw_scene(TIMER_BUTTONS buttons);
void draw_start_button(START_BUTTON button);

int main() {

	InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "raylib-test");

	TIMER_BUTTONS hourButton;
	TIMER_BUTTONS minButton;
	TIMER_BUTTONS secButton;
	START_BUTTON startButton;

	// TODO: Is this the C way of initializing data?

	// TODO: beautify UI
	// Target UI: old windows XP style UI
	// replicate it somehow with raylib, idk how yet
	Rectangle boxHour = { WINDOW_HEIGHT / 2.0f - 100, 50, 50, 50 };
	Rectangle boxMin = { WINDOW_HEIGHT / 2.0f, 50, 50, 50 };
	Rectangle boxSec = { WINDOW_HEIGHT / 2.0f + 100, 50, 50, 50 };
	Rectangle boxStart = { WINDOW_HEIGHT / 2.0f - 100, 125, 250, 50 };
	hourButton.box = boxHour;
	minButton.box = boxMin;
	secButton.box = boxSec;
	startButton.box = boxStart;
	hourButton.mouseClicked = minButton.mouseClicked = secButton.mouseClicked = startButton.mouseClicked = false;
	hourButton.current_digit_amount = minButton.current_digit_amount = secButton.current_digit_amount = 0;
	hourButton.current_value[0] = minButton.current_value[0] = secButton.current_value[0] = '\0';

	allButtons[0] = hourButton;
	allButtons[1] = minButton;
	allButtons[2] = secButton;

	InitAudioDevice();   
	Sound alarmSFX = LoadSound("res/passingoftime.ogg");  // Passing of time by 4leafstudios

	int hour = 0;
	int minute = 0;
	int second = 0;

	unsigned int fpsCounter = 0;
	SetTargetFPS(60);

	bool startTimer = false;
	bool startTimerLastState = false;
	bool isTimerComplete = false;
	bool allowModifyTimer = true;

	while (!WindowShouldClose()) {
		fpsCounter++;

		if (allowModifyTimer) {
			// 2 is the amount of allButtons
			for (int i = 0; i <= 2; i++) {

				// Check collision for the timer buttons
				check_collision(
					allButtons[i].box,
					&allButtons[i].mouseClicked
				);

				if (i == 0) {
					receive_input(&allButtons[i], false);
				}
				else {
					receive_input(&allButtons[i], true);
				}
			}

			// TODO
			// Make sure they are not assigned
			char* hour_value = allButtons[0].current_value;
			char* min_value = allButtons[1].current_value;
			char* sec_value = allButtons[2].current_value;
			if (
				hour_value[0] != '\0' && min_value[0] != '\0' && sec_value[0] != '\0' // This checks if its empty
				) 
			{
				hour = atoi(hour_value);
				minute = atoi(min_value);
				second = atoi(sec_value);

				if (hour != 0 || minute != 0 || second != 0) { // Only start if at least one is filled
					isTimerComplete = true;
				}
			}
			else {
				isTimerComplete = false;
			}
		}

		// Check collision for the start button and toggle startTimer bool
		// TODO: make this so that you have to click the timer button twice to toggle
		// Since the timer will change to a pause timer when countdown is triggered
		check_collision(
			startButton.box,
			&startButton.mouseClicked
		);
		if (startButton.mouseClicked != startTimerLastState) {
			if (isTimerComplete) {
				startTimer = !startTimer;
				allowModifyTimer = !allowModifyTimer;
				startTimerLastState = startButton.mouseClicked;
			}
		}

		if (startTimer) {
			if ((fpsCounter / 60) % 2 == 1) // Hopefully runs every sec
			{
				bool timerDone = start_countdown(
					&hour,
					&minute,
					&second,
					allButtons
				);

				if (timerDone) {
					// Reset button and play audio
					//TODO
					// might wanna move this somewhere ?
					printf("Done :3 \n");
					PlaySound(alarmSFX);
					startTimer = !startTimer;
					allowModifyTimer = !allowModifyTimer;
					startButton.mouseClicked = false;
					startTimerLastState = false;
				}

				fpsCounter = 0;
			}
		}

		// Drawing part
		BeginDrawing();
			ClearBackground(RAYWHITE);

			for (int i = 0; i <= 2; i++) {
				draw_scene(allButtons[i]);
			}
			draw_start_button(startButton);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

bool start_countdown(int* hour, int* min, int* sec, TIMER_BUTTONS* buttons){
	(*sec)--;

	if (*sec < 0) {
		*sec = 59;
		(*min)--;
	}

	if (*min < 0) {
		*min = 59;
		(*hour)--;
	}

	if (*hour < 0) {
		return true;
	}

	sprintf_s(buttons[0].current_value, 3, "%d", (*hour));
	sprintf_s(buttons[1].current_value, 3, "%d", (*min));
	sprintf_s(buttons[2].current_value, 3, "%d", (*sec));

	return false;
}

void check_collision(Rectangle box, bool* mouseClicked) {
	if (CheckCollisionPointRec(GetMousePosition(), box)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			*mouseClicked = !*mouseClicked;
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			*mouseClicked = false;
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

				// Another TODO:
				// If digit is currently just 0, replaces it instead of appending
				// and if digit is empty, replace it with 0
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
	DrawText(buttons.current_value, (int)buttons.box.x + 5, (int)buttons.box.y + 10, 38, MAROON);
}

void draw_start_button(START_BUTTON button) {
	DrawRectangleRec(button.box, LIGHTGRAY);
	if(button.mouseClicked) DrawRectangleLines((int)button.box.x, (int)button.box.y, (int)button.box.width, (int)button.box.height, RED);
	else DrawRectangleLines((int)button.box.x, (int)button.box.y, (int)button.box.width, (int)button.box.height, LIGHTGRAY);
	DrawText("Start Timer", (int)button.box.x + 5, (int)button.box.y + 10, 40, MAROON);
}
