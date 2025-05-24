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

#define GRAYISH      CLITERAL(Color) {100,100,100,255}
#define BEIGE        CLITERAL(Color) { 245, 245, 220, 255 }    

typedef struct {
    double TotalTime;
    time_t TimeStarted;
    time_t TimeEnded;
} TimeHistory;

static Font Tahoma;

// Why am i using snake case again?
void draw_elapsed_time(double time, int8_t TimeText[], int32_t posX, int32_t posY);
void draw_history(TimeHistory TimeList[], uint32_t TimeCounted, RenderTexture2D target);
char* convert_time_from_seconds(double time);

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_ALWAYS_RUN);

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

    int HistoryBoxHeight = (SCREEN_HEIGHT / 2) - 30.0f;

    Rectangle HistoryBox = {
        20.0f,
        (float)SCREEN_HEIGHT / 2,
        (float)(SCREEN_WIDTH - 40.0f),
        (float)-HistoryBoxHeight,
    };

    RenderTexture2D HistoryBoxTexture = LoadRenderTexture((SCREEN_WIDTH - 40), HistoryBoxHeight);

    Tahoma = LoadFontEx("res/tahoma.ttf", 64, 0, 250);
	SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);

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

                // Clear array and empty render texture
                memset(AllTime, 0, sizeof(AllTime));
                BeginTextureMode(HistoryBoxTexture);
				ClearBackground(WHITE);
				EndTextureMode();

            }
        }

        if (CheckCollisionPointRec(MousePoint, HistoryBox))
        {
            float MouseWheel = GetMouseWheelMove();

            // TODO: Handle mouse scrolling in the history area here


            //printf("Current Mouse Wheel: %f \n", MouseWheel);
        }

        BeginDrawing();
        ClearBackground(BEIGE);

        DrawRectangleRounded(TotalTimeBox, 0.1f, 0, WHITE);
        DrawRectangleRoundedLines(TotalTimeBox, 0.1f, 1, 1.0f, GRAYISH);

        DrawRectangleRounded(CurrentTimeBox, 0.1f, 0, WHITE);
        DrawRectangleRoundedLines(CurrentTimeBox, 0.1f, 1, 1.0f, GRAYISH);
        DrawTextureRec(
            HistoryBoxTexture.texture, 
            HistoryBox, 
            (Vector2) 
			{ 
                HistoryBox.x,
                HistoryBox.y
			}, 
            WHITE
        );

        draw_elapsed_time(TimeElapsed, "Lap Time: ", (int32_t)MARGIN + 60, (int32_t)MARGIN + 15);
        draw_elapsed_time(TotalTimeElapsed, "Total Time Elapsed: ", (int32_t)(SCREEN_WIDTH / 2) + MARGIN + 10, (int32_t)MARGIN + 15);

        if (StopwatchStarted) 
        {
            DrawRectangleRounded(StartButton, 0.1, 1, RED);
        }
        else
        {
            DrawRectangleRounded(StartButton, 0.1, 1, GREEN);
        }
        DrawRectangleRoundedLines(StartButton, 0.1f, 1, 1.0f, GRAYISH);

        if (HasStartedOnce)
        {
            DrawRectangleRounded(ResetButton, 0.1, 1, WHITE);
        }
        else
        {
            DrawRectangleRounded(ResetButton, 0.1, 1, GRAY);
        }
        DrawRectangleRoundedLines(ResetButton, 0.1f, 1, 1.0f, GRAYISH);

	    DrawTextEx(Tahoma, 
            "TIME \t\t\t\t\t\t\t\t\tDATE STARTED\t\t\t\t\t\t\t\t\t\t\t\t DATE ENDED", // Very cringe manual offsetting
            (Vector2)
			{
				50, 
				(SCREEN_HEIGHT / 2),
			},
            28, 
            1,
            BLACK);
        draw_history(AllTime, TimeCounted, HistoryBoxTexture);
        
        EndDrawing();
    }

    CloseWindow();
	
	return 0;
}

void draw_elapsed_time(double time, int8_t TimeText[], int32_t posX, int32_t posY)
{
    char* TotalTime = convert_time_from_seconds(time); // a bit cringe that it calls another function
    char Formatted[32];
    snprintf(Formatted, sizeof(Formatted), "%s: %s \n", TimeText, TotalTime);
	DrawTextEx(
        Tahoma, 
        Formatted,
        (Vector2)
		{
        posX, 
        posY + 20, 
		},
        28, 
        1,
        BLACK);
}

void draw_history(TimeHistory TimeList[], uint32_t TimeCounted, RenderTexture2D target)
{
    BeginTextureMode(target);
	ClearBackground(WHITE);
    for (uint32_t i = 0; i < TimeCounted; i++)
    {
        char* TotalTime = convert_time_from_seconds(TimeList[i].TotalTime);
        char TotalTimeFormatted[32];
        snprintf(TotalTimeFormatted, sizeof(TotalTimeFormatted), "%s", TotalTime);

        // Wacky barrage of snprintf
	    char DateStarted[32];
        struct tm TimeStarted = *localtime(&TimeList[i].TimeStarted);
	    snprintf(DateStarted, sizeof(DateStarted), "%d/%02d/%02d %02d:%02d:%02d ", TimeStarted.tm_year + 1900, TimeStarted.tm_mon + 1, TimeStarted.tm_mday, TimeStarted.tm_hour, TimeStarted.tm_min, TimeStarted.tm_sec);

	    char DateEnded[32];
        struct tm TimeEnded = *localtime(&TimeList[i].TimeEnded);
	    snprintf(DateEnded, sizeof(DateEnded), "%d/%02d/%02d %02d:%02d:%02d", TimeEnded.tm_year + 1900, TimeEnded.tm_mon + 1, TimeEnded.tm_mday, TimeEnded.tm_hour, TimeEnded.tm_min, TimeEnded.tm_sec);

        char Formatted[128];
        snprintf(Formatted, sizeof(Formatted), "%s\t\t\t\t\t\t%s\t\t\t\t\t\t%s\n", TotalTimeFormatted, DateStarted, DateEnded);
	    DrawTextEx(
            Tahoma,
            Formatted,
            (Vector2)
			{
				50, 
				30 * i, 
			},
            28, 
            1,
            BLACK);
    }
    EndTextureMode();
}

char* convert_time_from_seconds(double time)
{
	int32_t TotalSecond = (int32_t) time % 60;
	int32_t TotalMinute = (int32_t) (time / 60) % 60;
    int32_t TotalHour = (int32_t) time / 3600;
    char* TotalTime[16];
	snprintf(TotalTime, 16, "%02d:%02d:%02d", TotalHour, TotalMinute, TotalSecond);
    return TotalTime;
}
