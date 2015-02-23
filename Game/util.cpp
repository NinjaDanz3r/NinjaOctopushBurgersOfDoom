#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined(_WIN32) || defined(WIN32)
#include <direct.h>
#endif

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
		fflush(stderr);
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

	bool fileExists(const char* filename) {
#if defined(_WIN32) || defined(WIN32)
		// Windows
		struct _stat buf;
		int result = _stat(filename, &buf);
#else
		// MacOS and Linux
		struct stat buf;
		int result = stat(Name.c_str(), &buf);
#endif
		return result == 0;
	}

	void createDirectory(const char* filename) {
#if defined(_WIN32) || defined(WIN32)
		// Windows
		_mkdir(filename);
#else
		// MacOS and Linux
		mkdir(filename, ACCESSPERMS);
#endif
	}

	std::string savePath() {
		std::string path;

#if defined(_WIN32) || defined(WIN32)
		// Windows
		path = getenv("APPDATA");
		path += DELIMITER;
		path += GAME_NAME;
#elif __APPLE__
		// MacOS
		path = "~/Library/Application Support/";
		path += GAME_NAME;
#elif __linux__
		// Linux
		path = "~/.local/";
		path += GAME_NAME;
#endif

		createDirectory(path.c_str());

		return path;
	}

	std::string savePath(const char* filename) {
		std::string path = savePath();
		path += DELIMITER;
		path += filename;

		return path;
	}

	void writeString(std::ofstream &file, std::string str) {
		std::string::size_type length = str.length();
		file.write(reinterpret_cast<const char*>(&length), sizeof(length));
		file.write(str.c_str(), str.length());
	}

	std::string readString(std::ifstream &file) {
		std::string::size_type length;
		file.read(reinterpret_cast<char*>(&length), sizeof length);

		char* buffer = new char[length];
		file.read(buffer, length);

		std::string str(buffer, length);
		delete[] buffer;
		return str;
	}
}