#include <stdint.h>
#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define BUTTON_SIZE 50.0f 
#define MARGIN 22.5f
#define TIME_ZONE_WIDTH (SCREEN_WIDTH / 2) - 35.0f
#define TIME_ZONE_HEIGHT 100.0f

void draw_elapsed_time(double time, int32_t posX, int32_t posY);

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
                    TimeCounted += 1;
                }
            }
        }


        if (CheckCollisionPointRec(MousePoint, ResetButton))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                StopwatchStarted = false;
                TotalTimeElapsed = 0.0f;
                TimeElapsed = 0.0f;
                TimeCounted = 0;
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
        }
        else
        {
            DrawRectangleRounded(StartButton, 0.1, 1, GREEN);
        }

        if (TimeCounted > 0)
        {
            DrawRectangleRounded(ResetButton, 0.1, 1, WHITE);
        }
        else
        {
            DrawRectangleRounded(ResetButton, 0.1, 1, GRAY);
        }
        
        DrawRectangleRounded(TotalTimeBox, 0.1, 1, WHITE);
        DrawRectangleRounded(CurrentTimeBox, 0.1, 1, WHITE);
        DrawRectangleRounded(HistoryBox, 0.1, 1, WHITE);
        draw_elapsed_time(TotalTimeElapsed, (int32_t) (SCREEN_WIDTH / 2) + MARGIN + 10 , (int32_t) MARGIN + 15);
        draw_elapsed_time(TimeElapsed, (int32_t)MARGIN + 10, (int32_t)MARGIN + 15);

        EndDrawing();
    }

    CloseWindow();
	
	return 0;
}

void draw_elapsed_time(double time, int32_t posX, int32_t posY)
{
	int8_t TimeText[] = "Time Elapsed: ";
	int32_t TotalSecond = (int32_t) time % 60;
	int32_t TotalMinute = (int32_t) (time / 60) % 60;
    int32_t TotalHour = (int32_t) time / 3600;
	int8_t TotalTime[1000];
	snprintf(TotalTime, 1000, "%s %02d:%02d:%02d \n", TimeText, TotalHour, TotalMinute, TotalSecond);
	
	DrawText(TotalTime, posX, posY, 20, RED);
}