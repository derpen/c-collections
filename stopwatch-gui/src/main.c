#include <stdint.h>
#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stopwatch");

    Rectangle StopwatchButton = { 
        (float) (SCREEN_WIDTH / 2) - 75.0f, 
        (float) SCREEN_HEIGHT / 8, 
        150.0f,
        150.0f
    };

    bool StopwatchStarted = false;

    uint32_t Fps = 0;
    SetTargetFPS(60);

    Vector2 MousePoint = { 0.0f, 0.0f };

    while (!WindowShouldClose())
    {
        MousePoint = GetMousePosition();

        if (CheckCollisionPointRec(MousePoint, StopwatchButton))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                StopwatchStarted = !StopwatchStarted;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (StopwatchStarted)
            DrawRectangleRounded(StopwatchButton, 0.1, 1, WHITE);
        else
            DrawRectangleRounded(StopwatchButton, 0.1, 1, BEIGE);
        EndDrawing();
    }

    CloseWindow();
	
	return 0;
}