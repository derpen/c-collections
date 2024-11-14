#pragma once
#include "raylib/raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_INPUT_HOURS 3
#define MAX_INPUT_MIN 2
#define MAX_INPUT_SEC 2

extern char hour[MAX_INPUT_HOURS + 1];
extern int hourDigit;

extern char min[MAX_INPUT_MIN + 1];
extern int minuteDigit;

extern char sec[MAX_INPUT_SEC + 1];
extern int secondDigit;

typedef enum { NONE = 0, HOUR, MINUTE, SECOND } BUTTONS_STATE ;

extern BUTTONS_STATE active_button;

extern Rectangle boxHour;
extern Rectangle minHour;
extern Rectangle secHour;
extern Rectangle startTimer;

void CheckCollision(Rectangle box);
void GetInput();
void DrawAllRect();
void DrawRectWrapper();
