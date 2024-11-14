#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

void countdown(int seconds);

int main(int argc, char* args[]) {

	printf("Timer for how long? (In seconds)\n");
	unsigned char input[4];
	unsigned char sec;

	if (!fgets(input, sizeof(input), stdin)) {
		return -1; // Reading failed
	}

	sec = (unsigned char) strtol(input, NULL, 10);

	if (sec < 0 && sec > 60) {
		printf("Please put a proper number between 0-60\n");
		return -1;
	}

	countdown(sec);

	return 0;
}

void countdown(int seconds) {
	while (seconds > 0) {
		printf("%d\n", seconds);

#ifdef _WIN32
		Sleep(1000); // in milisecond
#else
		sleep(1); // in second, for linux
#endif

		seconds--;
	}
	printf("Done!\n");
}
