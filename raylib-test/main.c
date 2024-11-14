#include <stdio.h>
#include "raylib/raylib.h"

int main() {

	InitWindow(800, 600, "raylib-test");

	unsigned int frameCounter = 0; // not sure where to use this thing
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("I FUCKING HATE THIS THING", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}