#include "Leap.h"
#include "LeapRecorder.hpp"
#include <iostream>
#include <Windows.h>

class Play {
public:
	Play::Play() {};
	Play::~Play() {};
	int i = 0;
	int Play::play(std::string filename)
	{
	Leap::Controller controller = Leap::Controller();
	LeapRecorder recorder;

		if (!recorder.Load(filename)) {
			return 2;
		}
		recorder.Play();
		while (recorder.get_state() != LeapRecorder::STATE_IDLE) {
			Leap::Frame frame = recorder.GetCurrentFrame();
			std::cout << "Got frame id #" << frame.id() << std::endl;
			//Sleep(13000);
		}
		return 0;
	}
};
