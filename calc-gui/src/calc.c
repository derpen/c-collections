#include "clay_impl.h"
#include <clay/clay_raylib.c>
#include <stdio.h>

Clay_RenderCommandArray CreateCalcLayout() {
	Clay_BeginLayout();

	// -------------  Make UI here  ---------------

	return Clay_EndLayout();
}

bool debugEnabled = false;

void UpdateDrawFrame(void) {
	if (IsKeyPressed(KEY_D)) {
		debugEnabled != debugEnabled;
		Clay_SetDebugModeEnabled(debugEnabled);
	}

	BeginDrawing();

	ClearBackground(BLACK);
	Clay_RenderCommandArray renderCommands = CreateCalcLayout();
	Clay_Raylib_Render(renderCommands);
	EndDrawing();
}

bool reinitializeClay = false;

void HandleClayErrors(Clay_ErrorData errorData) {
	printf("%s", errorData.errorText.chars);
	if (errorData.errorType == CLAY_ERROR_TYPE_ELEMENTS_CAPACITY_EXCEEDED) {
		reinitializeClay = true;
		Clay_SetMaxElementCount(Clay_GetMaxElementCount() * 2);
	}
	else if (errorData.errorType == CLAY_ERROR_TYPE_TEXT_MEASUREMENT_CAPACITY_EXCEEDED) {
		reinitializeClay = true;
		Clay_SetMaxMeasureTextCacheWordCount(Clay_GetMaxMeasureTextCacheWordCount() * 2);
	}
}

int main() {

	const unsigned int screenWidth = 800;
	const unsigned int screenHeight = 600;

	uint64_t totalMemorySize = Clay_MinMemorySize();
	Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
	Clay_Initialize(arena, (Clay_Dimensions) { (float)GetScreenWidth(), (float)GetScreenHeight() }, (Clay_ErrorHandler) { HandleClayErrors });
	Clay_Raylib_Initialize(screenWidth, screenHeight, "The le Calc", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);

	// Tell clay how to measure text
	Clay_SetMeasureTextFunction(Raylib_MeasureText);

	// main loop
	while (!WindowShouldClose()) {
		if (reinitializeClay) {
			Clay_SetMaxElementCount(8192);
			totalMemorySize = Clay_MinMemorySize();
			arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
			Clay_Initialize(arena, (Clay_Dimensions) { (float)GetScreenWidth(), (float)GetScreenHeight() }, (Clay_ErrorHandler) { HandleClayErrors });
			reinitializeClay = false;
		}

		UpdateDrawFrame();
	}

	return 0;
}