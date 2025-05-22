#include <stdint.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define BUTTON_SIZE 50.0f 
#define MARGIN 22.5f
#define TIME_ZONE_WIDTH (SCREEN_WIDTH / 2) - 35.0f
#define TIME_ZONE_HEIGHT 100.0f

#define MAX_HISTORY 64

typedef struct {
    double TotalTime;
    time_t TimeStarted;
    time_t TimeEnded;
} TimeHistory;

void draw_elapsed_time(double time, int32_t posX, int32_t posY);
void draw_history(TimeHistory TimeList[], uint32_t TimeCounted);

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
    bool HasStartedOnce = false;

    uint32_t Fps = 0;
    SetTargetFPS(60);

    Vector2 MousePoint = { 0.0f, 0.0f };

    double TotalTimeElapsed = 0.0f;
    double TimeElapsed = 0.0f;
    uint32_t TimeCounted = 0; // To handle how many items will be in history box

    TimeHistory AllTime[MAX_HISTORY];

    while (!WindowShouldClose())
    {
        MousePoint = GetMousePosition();

        if (StopwatchStarted)
            TimeElapsed += GetFrameTime();

        if (CheckCollisionPointRec(MousePoint, StartButton))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                StopwatchStarted = !StopwatchStarted;

                // Started the clock
                if (StopwatchStarted)
                {
                    AllTime[TimeCounted].TimeStarted = time(NULL);
                }

                // Stopped the clock
                if (!StopwatchStarted)
                {
                    AllTime[TimeCounted].TimeEnded = time(NULL);
                    AllTime[TimeCounted].TotalTime = TimeElapsed;

                    TotalTimeElapsed += TimeElapsed;
                    TimeElapsed = 0.0f;
                    TimeCounted += 1;

                    if (!HasStartedOnce)
                    {
                        HasStartedOnce = true;
                    }
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
                HasStartedOnce = false;
            }
        }

        if (CheckCollisionPointRec(MousePoint, HistoryBox))
        {
            float MouseWheel = GetMouseWheelMove();

            // TODO: Handle mouse scrolling in the history area here


            //printf("Current Mouse Wheel: %f \n", MouseWheel);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRounded(TotalTimeBox, 0.1, 1, WHITE);
        DrawRectangleRounded(CurrentTimeBox, 0.1, 1, WHITE);
        DrawRectangleRounded(HistoryBox, 0.1, 1, WHITE);
        draw_elapsed_time(TotalTimeElapsed, (int32_t) (SCREEN_WIDTH / 2) + MARGIN + 10 , (int32_t) MARGIN + 15);
        draw_elapsed_time(TimeElapsed, (int32_t)MARGIN + 10, (int32_t)MARGIN + 15);

        if (StopwatchStarted) 
        {
            DrawRectangleRounded(StartButton, 0.1, 1, RED);
        }
        else
        {
            DrawRectangleRounded(StartButton, 0.1, 1, GREEN);
        }

        if (HasStartedOnce)
        {
            DrawRectangleRounded(ResetButton, 0.1, 1, WHITE);
        }
        else
        {
            DrawRectangleRounded(ResetButton, 0.1, 1, GRAY);
        }

        if (HasStartedOnce)
        {
            //draw_history(AllTime, TimeCounted);
	        DrawText("TIME ELAPSED\t\t\t\t\t\t\t\tDATE STARTED\t\t\t\t\t\t\t\tDATE ENDED", 50, (SCREEN_HEIGHT / 2) + 10, 20, RED);
        }
        
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
	int8_t TotalTime[1024];
	snprintf(TotalTime, 1024, "%s %02d:%02d:%02d \n", TimeText, TotalHour, TotalMinute, TotalSecond);
	
	DrawText(TotalTime, posX, posY, 20, RED);
}

void draw_history(TimeHistory TimeList[], uint32_t TimeCounted) 
{
    for (uint32_t i = 0; i < TimeCounted; i++)
    {
        printf("Time at : %d \n", i);

	    //DrawText("TIME ELAPSED\t\t\t\t\t\t\t\tDATE STARTED\t\t\t\t\t\t\t\tDATE ENDED", 50, (SCREEN_HEIGHT / 2) + 10, 20, RED);

        struct tm TimeStarted = *localtime(&TimeList[i].TimeStarted);
	    printf("%d/%02d/%02d %02d:%02d:%02d\n", TimeStarted.tm_year + 1900, TimeStarted.tm_mon + 1, TimeStarted.tm_mday, TimeStarted.tm_hour, TimeStarted.tm_min, TimeStarted.tm_sec);

        struct tm TimeEnded = *localtime(&TimeList[i].TimeEnded);
	    printf("%d/%02d/%02d %02d:%02d:%02d\n", TimeEnded.tm_year + 1900, TimeEnded.tm_mon + 1, TimeEnded.tm_mday, TimeEnded.tm_hour, TimeEnded.tm_min, TimeEnded.tm_sec);
    }
}

