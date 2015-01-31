#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>

/// Utilities namespace.
/**
 * Contains various utility functions, primarily related to the file system.
 */
namespace util {
	/// Name of the game, used for eg. filepaths.
	const char* const GAME_NAME = "NinjaBurgers";

	/// Delimiter, '\' on Windows, '/' elsewhere.
	extern const char DELIMITER;

	/// Write a string to stderr and append newline.
	/**
	 * @param text Log message.
	 */
	void log(const char* text);

	/// Write a string to stderr and append datetime.
	/**
	 * @param text Log message.
	 */
	void logWithTime(const char* text);

	/// Checks if a file exists.
	/**
	 * Works for directories as well.
	 * @param filename Filename (either relative or absolute) to check.
	 * @return Whether the file exists
	 */
	bool fileExists(const char* filename);

	/// Creates a directory if it does not already exist.
	/**
	 * Permission for new directory is 0777 on Unix.
	 * @param filename Filename (either absolute or relative) for the directory to create.
	 */
	void createDirectory(const char* filename);

	/// Get save path for application data folder.
	/**
	 * The application data folder is created if it does not already exist.
	 * On Windows, this is \<User>\\AppData\\Roaming\\\<GameName>.
	 * On MacOS, this is ~/Library/Application Support/\<GameName>.
	 * On Linux, this is ~/.local/\<GameName>.
	 * @return The path
	 */
	std::string savePath();

	/// Get save path for application data.
	/**
	 * The application data folder is created if it does not already exist.
	 * On Windows, this is \<User>\\AppData\\Roaming\\\<GameName>\\\<Filename>.
	 * On MacOS, this is ~/Library/Application Support/\<GameName>/\<Filename>.
	 * On Linux, this is ~/.local/\<GameName>/\<Filename>.
	 * @param filename Filename, eg. "settings.ini".
	 * @return The path
	 */
	std::string savePath(const char* filename);
}

#endif