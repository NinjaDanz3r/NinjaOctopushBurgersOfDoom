#include "util.h"
#include <stdio.h>
#include <time.h>

namespace util {
	void logWithTime(const char* text) {
		fputs(text, stderr);

		time_t rawtime;
		struct tm * timeinfo;
		char buffer[25];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, 25, " - %Y-%m-%d %H:%M:%S\n", timeinfo);
		
		fputs(buffer, stderr);
	}
}