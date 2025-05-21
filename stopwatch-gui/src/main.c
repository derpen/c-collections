#include <stdint.h>
#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

// Rectangle
#define BUTTON_SIZE 50.0f 
#define MARGIN 22.5f
#define TIME_ZONE_WIDTH (SCREEN_WIDTH / 2) - 35.0f
#define TIME_ZONE_HEIGHT 100.0f

void draw_elapsed_time(double time, int posX, int posY);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stopwatch");

    Rectangle StartButton = {
        MARGIN,
        (float) SCREEN_HEIGHT / 3, 
        BUTTON_SIZE,
        BUTTON_SIZE,
    };

    Rectangle ResetButton = { 
        (float) SCREEN_WIDTH - BUTTON_SIZE - MARGIN,
        (float) SCREEN_HEIGHT / 3, 
        BUTTON_SIZE,
        BUTTON_SIZE,
    };

    Rectangle TotalTimeBox = {
        MARGIN,
        MARGIN,
        TIME_ZONE_WIDTH,
        TIME_ZONE_HEIGHT,
    };

    Rectangle CurrentTimeBox = {
        (float) (SCREEN_WIDTH / 2) + MARGIN,
        MARGIN,
        TIME_ZONE_WIDTH,
        TIME_ZONE_HEIGHT,
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

    double TotalTimeElapsed = 0.0f;
    double TimeElapsed = 0.0f;
    uint32_t TimeCounted = 0; // To handle how many items will be in history box

    while (!WindowShouldClose())
    {
        MousePoint = GetMousePosition();
        TimeElapsed += GetFrameTime();

        if (CheckCollisionPointRec(MousePoint, StartButton))
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
                    TotalTimeElapsed += TimeElapsed;
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
        {
            DrawRectangleRounded(StartButton, 0.1, 1, RED);
            DrawRectangleRounded(ResetButton, 0.1, 1, WHITE);
        }
        else
        {
            DrawRectangleRounded(StartButton, 0.1, 1, GREEN);
            DrawRectangleRounded(ResetButton, 0.1, 1, GRAY); // Should have another flag if already stopped once
        }
        
        DrawRectangleRounded(TotalTimeBox, 0.1, 1, WHITE);
        DrawRectangleRounded(CurrentTimeBox, 0.1, 1, WHITE);
        DrawRectangleRounded(HistoryBox, 0.1, 1, WHITE);
        draw_elapsed_time(TotalTimeElapsed, (int) (SCREEN_WIDTH / 2) + MARGIN + 10 , (int) MARGIN + 15);
        draw_elapsed_time(TimeElapsed, (int)MARGIN + 10, (int)MARGIN + 15);

        EndDrawing();
    }

    CloseWindow();
	
	return 0;
}

void draw_elapsed_time(double time, int posX, int posY)
{
	// TODO: Handle this gracefully
	// And the logic still broke lol
	char TimeText[] = "Time Elapsed: ";
	double TotalHour = time / 60.0f;
	double TotalMinute = TotalHour / 60.0f;
	double TotalSecond = TotalMinute / 60.0f;
	char TotalTime[1000];
	snprintf(TotalTime, 1000, "%s %f:%f:%f \n", TimeText, TotalHour, TotalMinute, TotalSecond);
	
	DrawText(TotalTime, posX, posY, 20, RED);
}