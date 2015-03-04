#ifndef __UTIL_H__
#define __UTIL_H__

#include "Core.h"
#include <string>
#include <fstream>

/// Contains various utility functions
/**
* Primarily related to the file system.
*/
namespace util {
	/// Name of the game, used for eg. filepaths.
	const char* const GAME_NAME = "NinjaBurgers";

	/// Delimiter, '\' on Windows, '/' elsewhere.
	CORE_EXPORT extern const char DELIMITER;

	/// Write a string to stderr and append newline.
	/**
	* @param text Log message.
	*/
	CORE_EXPORT void log(const char* text);

	/// Write a string to stderr and append datetime.
	/**
	* @param text Log message.
	*/
	CORE_EXPORT void logWithTime(const char* text);

	/// Check if a file exists.
	/**
	* Works for directories as well.
	* @param filename Filename (either relative or absolute) to check.
	* @return Whether the file exists
	*/
	CORE_EXPORT bool fileExists(const char* filename);

	/// Create a directory if it does not already exist.
	/**
	* Permission for new directory is 0777 on Unix.
	* @param filename Filename (either absolute or relative) for the directory to create.
	*/
	CORE_EXPORT void createDirectory(const char* filename);

	/// Get save path for application data folder.
	/**
	* The application data folder is created if it does not already exist.
	* On Windows, this is \<User>\\AppData\\Roaming\\\<GameName>.
	* On MacOS, this is ~/Library/Application Support/\<GameName>.
	* On Linux, this is ~/.local/\<GameName>.
	* @return The path
	*/
	CORE_EXPORT std::string savePath();

	/// Get save path for application data.
	/**
	* The application data folder is created if it does not already exist.
	* On Windows, this is \<User>\\AppData\\Roaming\\\<GameName>\\\<Filename>.
	* On MacOS, this is ~/Library/Application Support/\<GameName>/\<Filename>.
	* On Linux, this is ~/.local/\<GameName>/\<Filename>.
	* @param filename Filename, eg. "settings.ini".
	* @return The path
	*/
	CORE_EXPORT std::string savePath(const char* filename);

	/// Write std::string to std::ofstream.
	/**
	* @param file File stream to write to.
	* @param str String to write.
	*/
	CORE_EXPORT void writeString(std::ofstream &file, std::string str);

	/// Read std::string from std::ifstream.
	/**
	* @param file File stream to read from.
	* @return The string read
	*/
	CORE_EXPORT std::string readString(std::ifstream &file);

}

#endif