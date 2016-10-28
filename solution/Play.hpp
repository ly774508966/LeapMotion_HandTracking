#include "Leap.h"
#include "LeapRecorder.hpp"
#include <iostream>
// #include <Windows.h>

using namespace Leap;

class Play {
public:
	Play() {};
	~Play() {};
	void displayFrame(Frame frame);
	int play(std::string filename);
};