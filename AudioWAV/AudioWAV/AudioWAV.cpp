#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

//number of samples for 1 sec
const int sampleRate = 44100;

const int bitDepth = 16;

class Oscillate {
	float freq;
	float ampl;
	float angle = 0.0f, offset = 0.0f;

public:
	Oscillate(float f, float a) : freq(f), ampl(a) {

		offset = 2 * M_PI * freq / sampleRate;
	}
	//need to be called every sampling interval
	//angle needs to be updated with offset each time process is called
	float process() {
		//formula Asin(2*pi*frq/sampling rate)
		//ampl * sin(2 * M_PI * freq / sampleRate);

		float sample = ampl * sin(angle);
		angle += offset;
		return sample;
	}
};
int main() {
	Oscillate wave(440.0, 0.5);
	ofstream audioFile;
	audioFile.open("waveform", ios::binary);
	//needs to be 16 or 32 bit integer format, how commercial audio is stored
	cout << "float size" << sizeof(float) << endl;
	cout << "intger size" << sizeof(int) << endl;

		int seconds = 1;

		float maxAmp = pow(2, bitDepth - 1) - 1;
	for (int i = 0; i < sampleRate * seconds; i++) {
		float sample = wave.process();
	///	audioFile << wave.process() << endl;
		int sampleInt = static_cast<int> (sample * maxAmp);
	}
	audioFile.close();
	


	return 1;
}