#pragma once

typedef struct {
	int hour;
	int minute;
	int second;
} CurrentTime ;

CurrentTime countdown(int h, int m, int s);
