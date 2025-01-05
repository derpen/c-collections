#include <stdio.h>
#include <raylib/raylib.h>

int main() {

	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenHeight, screenWidth, "Epic Calculator");

	SetTargetFPS(30);

	while (!WindowShouldClose()) {

		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Lorem Ipsum Dolor text here", screenWidth/4, screenHeight/2, 20, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}