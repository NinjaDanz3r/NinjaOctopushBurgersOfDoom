#include "WaveFile.h"

#include <fstream>
#include <stdio.h>
#include "util.h"

WaveFile::WaveFile(const char* filename) {
	std::ifstream waveFile;
	waveFile.open(filename, std::ios::binary);
	if (!waveFile.is_open()) {
		fprintf(stderr, "Couldn't open wave file %s for reading.\n", filename);
		fflush(stderr);
	}

	// Read RIFF.
	char id[4];
	waveFile.read(id, 4);
	if (!strcmp(id, "RIFF"))
		util::log("File is not a RIFF file.");

	// Read file size (excluding RIFF).
	unsigned long size;
	waveFile.read(reinterpret_cast<char*>(&size), sizeof(size));

	// Read WAVE.
	waveFile.read(id, 4);
	if (!strcmp(id, "WAVE"))
		util::log("File is not a wave file.");

	// Read format.
	unsigned long formatLength, avgBytesPerSec;
	short formatTag, channels, blockAlign, bitsPerSample;

	waveFile.read(id, 4);
	waveFile.read(reinterpret_cast<char*>(&formatLength), sizeof(formatLength));
	waveFile.read(reinterpret_cast<char*>(&formatTag), sizeof(formatTag));
	waveFile.read(reinterpret_cast<char*>(&channels), sizeof(channels));
	waveFile.read(reinterpret_cast<char*>(&_sampleRate), sizeof(_sampleRate));
	waveFile.read(reinterpret_cast<char*>(&avgBytesPerSec), sizeof(avgBytesPerSec));
	waveFile.read(reinterpret_cast<char*>(&blockAlign), sizeof(blockAlign));
	waveFile.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(bitsPerSample));

	// Read data.
	waveFile.read(id, 4);
	waveFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
	_data = new char[dataSize];
	waveFile.read(_data, dataSize);

	waveFile.close();

	_format = toALFormat(channels, bitsPerSample);
}

WaveFile::~WaveFile() {
	delete[] _data;
}

const char* WaveFile::data() const {
	return _data;
}

ALsizei WaveFile::size() const {
	return dataSize;
}

ALenum WaveFile::format() const {
	return _format;
}

ALsizei WaveFile::sampleRate() const {
	return _sampleRate;
}

ALenum WaveFile::toALFormat(short channels, short bitsPerSample) {
	bool stereo = (channels > 1);

	switch (bitsPerSample) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}