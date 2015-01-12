#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>

namespace util {
	// Name of the game, used for eg. filepaths.
	const char* const GAME_NAME = "NinjaBurgers";

	// Delimiter, \ on Windows, / elsewhere.
	extern const char DELIMITER;

	// Write a string to stderr and append newline.
	void log(const char* text);

	// Write a string to stderr and append datetime.
	void logWithTime(const char* text);

	/* Get save path for application data folder, creating it if it does not exist.
	On Windows, this is <User>\AppData\Roaming\<GameName>.
	On MacOS, this is ~/Library/Application Support/<GameName>.
	On Linux, this is .
	*/
	std::string savePath();

	/* Get save path for application data, creating the folder if it does not exist.
	On Windows, this is <User>\AppData\Roaming\<GameName>\<Filename>.
	On MacOS, this is ~/Library/Application Support/<GameName>/<Filename>.
	On Linux, this is .
	*/
	std::string savePath(const char* filename);
}

#endif