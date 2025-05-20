#include <stdint.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>

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

    Rectangle HistoryBox = {
        20.0f,
        (float)SCREEN_HEIGHT / 2,
        (float)(SCREEN_WIDTH - 40.0f),
        (float)(SCREEN_HEIGHT / 2) - 20.0f,
    };

    bool StopwatchStarted = false;

    uint32_t Fps = 0;
    SetTargetFPS(60);

    Vector2 MousePoint = { 0.0f, 0.0f };

    double TimeElapsed = 0.0f;
    uint32_t TimeCounted = 0; // To handle how many items will be in history box

    while (!WindowShouldClose())
    {
        MousePoint = GetMousePosition();
        TimeElapsed += GetFrameTime();

        if (CheckCollisionPointRec(MousePoint, StopwatchButton))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                StopwatchStarted = !StopwatchStarted;

                // TODO: Handle date, write this to history box later
                //time_t t = time(NULL);
                //struct tm tm = *localtime(&t);
                //printf("%d/%02d/%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

                if (!StopwatchStarted)
                {
                    TimeElapsed = 0.0f;
                }
            }
        }

        if (CheckCollisionPointRec(MousePoint, HistoryBox))
        {
            float MouseWheel = GetMouseWheelMove();

            // Handle mouse scrolling in the history area here


            //printf("Current Mouse Wheel: %f \n", MouseWheel);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (StopwatchStarted)
            DrawRectangleRounded(StopwatchButton, 0.1, 1, WHITE);
        else
            DrawRectangleRounded(StopwatchButton, 0.1, 1, BEIGE);
        
        DrawRectangleRounded(HistoryBox, 0.1, 1, WHITE);

        // TODO: Handle this gracefully
        // And the logic still broke lol
		if (!StopwatchStarted)
		{
			char TimeText[] = "Time Elapsed: ";
            double TotalHour = TimeElapsed / 60.0f;
            double TotalMinute = TotalHour / 60.0f;
            double TotalSecond = TotalMinute / 60.0f;
            char TotalTime[1000];
            snprintf(TotalTime, 1000, "%s %f:%f:%f \n", TimeText, TotalHour, TotalMinute, TotalSecond);
            
			DrawText(TotalTime, 200, 300, 20, RED);
		}

        EndDrawing();
    }

    CloseWindow();
	
	return 0;
}