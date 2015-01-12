#include "util.h"
#include <stdio.h>
#include <time.h>

namespace util {
#if defined(_WIN32) || defined(WIN32)
	// Windows
	const char DELIMITER = '\\';
#else
	// MacOS and Linux
	const char DELIMITER = '/';
#endif

	void log(const char* text) {
		fputs(text, stderr);
		fputs("\n", stderr);
	}

	void logWithTime(const char* text) {
		fputs(text, stderr);

		time_t rawtime;
		struct tm * timeinfo;
		char buffer[24];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, 24, " - %Y-%m-%d %H:%M:%S", timeinfo);
		
		log(buffer);
	}

	std::string savePath() {
		std::string path;

#if defined(_WIN32) || defined(WIN32)
		// Windows
		//#elif __APPLE__
		// MacOS
		path = "~/Library/Application Support/";
		path += GAME_NAME;
#else
		// Linux
#endif

		return path;
	}

	std::string savePath(const char* filename) {
		std::string path = savePath();
		path += DELIMITER;
		path += filename;

		return path;
	}
}