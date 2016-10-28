#include <iostream>
#include <cstring>
#include "Leap.h"
#include "Play.hpp"
#include "Record.hpp"

using namespace Leap;

int main(int argc, char** argv) {
  const char *FILE_NAME = NULL;
  if (argc < 2) {
    std::cout<<"Invalid number of args"<<std::endl;
    return 0;
  }
  else {
    if (strcmp(argv[1], "--bg") == 0)
      FILE_NAME = argv[2];
    else 
      FILE_NAME = argv[1];
  }

  // Create a sample listener and controller
  Controller controller;
  Play p;
  Record r;
  bool paused = false;

  int choice = 0;
  std::cout << "1. Track \n2. Record \n3. Play \n" << std::endl;
  std::cin >> choice;
  while (choice != 1 && choice != 2 && choice != 3) {
	  std::cout << "1. Track \n2. Record \n3. Play \n:";
	  std::cin >> choice;
	  std::cout << "choice = " << choice << std::endl;
  }
  
  Leap::Frame newFrame;

  switch (choice) {
  case 1:
	  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
		  controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	  controller.setPolicy(Leap::Controller::POLICY_ALLOW_PAUSE_RESUME);
    
	  // Keep this process running until Enter is pressed
	  std::cout << "Press Enter to quit, or enter 'p' to pause or unpause the service..." << std::endl;
	  std::cin.ignore(1);

    newFrame = controller.frame();
    p.displayFrame(newFrame);
    /* @aravind
	  while (true) {
		  char c = std::cin.get();
		  if (c == 'p') {
			  paused = !paused;
        controller.setPaused(paused);
        std::cin.get();
		  }
		  else
			  break;
	  }
    */
	  break;
  case 2:
	  std::cin.ignore(1);
	  r.record(FILE_NAME);
	  break;
  case 3:
	  std::cin.ignore(1);
    p.play(FILE_NAME);
  default:
	  break;
  }

  return 0;
}
