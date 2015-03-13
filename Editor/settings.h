#ifndef __SETTINGS_H__
#define __SETTINGS_H__
#include <string>

/** @ingroup editor
* @{
*/

/// Handles various settings that the user can modify.
/**
 * Settings are stored in util::savePath("editor_settings.ini").
 */
namespace settings {
	/// Load settings from an ini file.
	/**
	 * Settings are given default values if file can not be found or does not contain the corresponding setting.
	 * @param filename Filename (relative or absolute)
	 */
	void load(const char* filename);

	/// Save the settings to an ini file.
	/**
	 * Creates the file if it does not already exist.
	 * @param filename Filename (relative or absolute)
	 */
	void save(const char* filename);

	/// Get whether write to a log file.
	/**
	 * Default false.
	 * @return Whether write to a log file
	 * @see util::savePath for where log file is saved.
	 */
	bool logging();

	/// Set whether to write to a log file.
	/**
	 * @param logging Whether to write to a log file.
	 * @see util::savePath for where log file is saved.
	 */
	void setLogging(bool logging);
}

/** @} */

#endif