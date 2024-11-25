#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib/raylib.h"

#define WINDOW_HEIGHT 300
#define WINDOW_WIDTH 150

// Color defines
#define GRAYISH (Color) {100,100,100,255}
#define BEIGISH (Color) {245,245,220,255}

// Make sure to check the TODOs :3

typedef struct {
	bool mouseClicked;
	char current_value[3];
	int current_digit_amount;
	Font textFont;
	Rectangle box;
} TIMER_BUTTONS;

typedef struct {
	bool mouseClicked;
	Rectangle box;
	Font textFont;
} START_BUTTON;

TIMER_BUTTONS allButtons[3];

bool start_countdown(int* hour, int* min, int* sec, TIMER_BUTTONS* buttons);
void check_collision(Rectangle box, bool* mouseClicked, bool isStartButton);
void receive_input(TIMER_BUTTONS* buttons, bool limit);
void draw_scene(TIMER_BUTTONS buttons);
void draw_start_button(START_BUTTON button, bool startTimer);
void draw_colon(TIMER_BUTTONS button);

int main() {

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_ALWAYS_RUN); // hi-res

	InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Timer");

	TIMER_BUTTONS hourButton;
	TIMER_BUTTONS minButton;
	TIMER_BUTTONS secButton;
	START_BUTTON startButton;

	// TODO: Is this the C way of initializing data?

	// TODO: beautify UI
	// Target UI: old windows XP style UI
	// Can't really explain it, but current UI still is not satisfactory
	// Make alarm keeps playing until user press deactivate alarm <- Maybe not? Feels too complicated for a simple feature
	// A lot of this mess could be solved with enum, but I'm too much of a noob to figure it out
	Rectangle boxHour = { WINDOW_HEIGHT / 2.0f - 125, 20, 50, 50 };
	Rectangle boxMin = { WINDOW_HEIGHT / 2.0f - 25, 20, 50, 50 };
	Rectangle boxSec = { WINDOW_HEIGHT / 2.0f + 75, 20, 50, 50 };
	Rectangle boxStart = { WINDOW_HEIGHT / 2.0f - 125, 85, 250, 50 };
	hourButton.box = boxHour;
	minButton.box = boxMin;
	secButton.box = boxSec;
	startButton.box = boxStart;
	hourButton.mouseClicked = minButton.mouseClicked = secButton.mouseClicked = startButton.mouseClicked = false;
	hourButton.current_digit_amount = minButton.current_digit_amount = secButton.current_digit_amount = 0;
	hourButton.current_value[0] = minButton.current_value[0] = secButton.current_value[0] = '0';
	hourButton.current_value[1] = minButton.current_value[1] = secButton.current_value[1] = '\0';

	InitAudioDevice();   
	Sound alarmSFX = LoadSound("res/passingoftime.ogg");  // Passing of time by 4leafstudios
	Font tahomaFont = LoadFontEx("res/tahoma.ttf", 64, 0, 250);
	SetTextLineSpacing(12); // Set line spacing for multiline text (when line breaks are included '\n')
	SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);
	hourButton.textFont = minButton.textFont = secButton.textFont =startButton.textFont = tahomaFont;

	allButtons[0] = hourButton;
	allButtons[1] = minButton;
	allButtons[2] = secButton;

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
		if (allowModifyTimer) {
			// 2 is the amount of allButtons
			for (int i = 0; i <= 2; i++) {

				// Check collision for the timer buttons
				check_collision(
					allButtons[i].box,
					&allButtons[i].mouseClicked,
					false // not start button
				);

				if (i == 0) {
					receive_input(&allButtons[i], false);
				}
				else {
					receive_input(&allButtons[i], true);
				}
			}

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
		check_collision(
			startButton.box,
			&startButton.mouseClicked,
			true // is start button
		);
		if (startButton.mouseClicked != startTimerLastState) {
			if (isTimerComplete) {
				startTimer = !startTimer;
				allowModifyTimer = !allowModifyTimer;
				startTimerLastState = startButton.mouseClicked;
			}
			else {
				startButton.mouseClicked = false;
			}
		}

		if (startTimer) {
			fpsCounter++;

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
					// TODO
					// might wanna move this somewhere ?
					printf("Done :3 \n");
					PlaySound(alarmSFX);
					startTimer = false;
					allowModifyTimer = true;
					isTimerComplete = false;
					startButton.mouseClicked = false;
					startTimerLastState = false;
				}

				fpsCounter = 0;
			}
		}

		// Drawing part
		BeginDrawing();
			ClearBackground(BEIGISH);

			for (int i = 0; i <= 2; i++) {
				draw_scene(allButtons[i]);
			}
			
			for (int i = 0; i <= 1; i++) {
				draw_colon(allButtons[i]);
			}

			draw_start_button(startButton, startTimer);

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

	buttons[0].current_digit_amount = strlen(buttons[0].current_value);
	buttons[1].current_digit_amount = strlen(buttons[1].current_value);
	buttons[2].current_digit_amount = strlen(buttons[2].current_value);

	return false;
}

void check_collision(Rectangle box, bool* mouseClicked, bool isStartButton) {
	if (CheckCollisionPointRec(GetMousePosition(), box)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			*mouseClicked = !*mouseClicked;
		}
	}
	else {
		if (!isStartButton) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				*mouseClicked = false;
		}
	}
}

void receive_input(TIMER_BUTTONS* buttons, bool limit) {
	if (buttons->mouseClicked) {
		int key = GetCharPressed();

		while (key > 0) {
			// 0-9 is keycode 48-57
			if ((key >= 48) && (key <= 57) && (buttons->current_digit_amount < 2)) {
				// TODO: add 0 in the front if theres only one digit
				// Might be a bit too hard actually
				if (buttons->current_value[0] == '0') {
					buttons->current_digit_amount = 0;
				}

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
			if (buttons->current_digit_amount <= 0) {
				buttons->current_digit_amount = 0;
				buttons->current_value[0] = '0';
			}
			else {
				buttons->current_value[buttons->current_digit_amount] = '\0';
			}
		}
	}
}

void draw_scene(TIMER_BUTTONS buttons) {
	DrawRectangleRounded(buttons.box, 0.1f, 0, WHITE); // float roundness, int segments, Color color

	if(buttons.mouseClicked) DrawRectangleRoundedLines(buttons.box, 0.1f, 0, 1.0f, SKYBLUE); //  Rectangle rec, float roundness, int segments, float linethick, Color color
	else DrawRectangleRoundedLines(buttons.box, 0.1f, 0, 1.0f, LIGHTGRAY);

	if (strlen(buttons.current_value) > 1) {
		DrawTextEx(buttons.textFont, buttons.current_value, (Vector2) { (int)buttons.box.x + 7, (int)buttons.box.y + 5 }, 38, 2, GRAYISH);
	}
	else {
		DrawTextEx(buttons.textFont, buttons.current_value, (Vector2) { (int)buttons.box.x + 15, (int)buttons.box.y + 5}, 38, 2, GRAYISH);
	}
}

void draw_start_button(START_BUTTON button, bool startTimer) {
	DrawRectangleRounded(button.box, 0.1f, 0, WHITE);

	if(button.mouseClicked) DrawRectangleRoundedLines(button.box, 0.1f, 0, 1.0f, SKYBLUE);
	else DrawRectangleRoundedLines(button.box, 0.1f, 0, 1.0f, LIGHTGRAY);

	if (startTimer) {
		DrawTextEx(button.textFont, "Pause Timer", (Vector2) { (int)button.box.x + 30, (int)button.box.y + 5 }, 40, 2, GRAYISH);
	}
	else {
		DrawTextEx(button.textFont, "Start Timer", (Vector2) { (int)button.box.x + 30, (int)button.box.y + 5 }, 40, 2, GRAYISH);
	}
}

void draw_colon(TIMER_BUTTONS button) {
	DrawTextEx(button.textFont, ":", (Vector2) { (int)button.box.x + 70, (int)button.box.y }, 40, 2, GRAYISH);
}
