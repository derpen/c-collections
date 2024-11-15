#pragma once
#include "raylib/raylib.h"

#define MAX_INPUT_HOURS 3
#define MAX_INPUT_MIN 2
#define MAX_INPUT_SEC 2

typedef enum { NONE = 0, HOUR, MINUTE, SECOND } BUTTONS_STATE ;

void CheckCollision(Rectangle box);
void GetInput();
void DrawScene();
void DrawAllRect();
