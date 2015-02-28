#ifndef __CONVERT_H__
#define __CONVERT_H__

/// Contains various conversion functions.
namespace convert {
	/// Convert image to TGA.
	/**
	 * Supported file formats:
	 * 
	 * @param inName Filename of the input image.
	 * @param outName Filename of the output TGA image.
	 */
	void convertImage(const char* inName, const char* outName);
}

#endif