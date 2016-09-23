#include "Leap.h"
#include "LeapRecorder.hpp"

class Record {
public:
	int i = 0;
	Record::Record() {};
	Record::~Record() {};
	int Record::record(std::string filename)
	{

		FILE* test = fopen(filename.c_str(), "wb");
		if (!test) {
			std::cerr << "can not open " << filename << " for writing..." << std::endl;
			return 2;
		}
		fclose(test);
		Leap::Controller controller;
		LeapRecorder recorder;
		controller.addListener(recorder);
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

		if (!controller.isConnected()) {
			std::cerr << "error no LeapMotion found!" << std::endl;
			return 3;
		}

		// Record until Enter is pressed
		recorder.Record();
		std::cout << "Press Enter to quit..." << std::endl;
		std::cin.get();
		recorder.Stop();

		if (!recorder.Save(filename)) {
			std::cerr << "error during saving." << std::endl;
			return 2;
		}

		controller.removeListener(recorder);
		return 0;
	}

};

