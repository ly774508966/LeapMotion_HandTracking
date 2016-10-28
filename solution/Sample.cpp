/******************************************************************************\
* Copyright (C) 2012-2016 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <cstring>
#include "Leap.h"
#include "Play.hpp"
#include "Record.hpp"

using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
    virtual void onServiceChange(const Controller&);
    virtual void onDeviceFailure(const Controller&);
    virtual void onLogMessage(const Controller&, MessageSeverity severity, int64_t timestamp, const char* msg);
};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) 
{
  std::cout<<"Frame received"<<std::endl;
}

void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    /* @aravind
    std::cout << "  isSmudged:" << (devices[i].isSmudged() ? "true" : "false") << std::endl;
    std::cout << "  isLightingBad:" << (devices[i].isLightingBad() ? "true" : "false") << std::endl;
    */
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

void SampleListener::onServiceChange(const Controller& controller) {
  std::cout << "Service Changed" << std::endl;
}

void SampleListener::onDeviceFailure(const Controller& controller) {
  std::cout << "Device Error" << std::endl;
  /* @aravind
  const Leap::FailedDeviceList devices = controller.failedDevices();

  for (FailedDeviceList::const_iterator dl = devices.begin(); dl != devices.end(); ++dl) {
    const FailedDevice device = *dl;
    std::cout << "  PNP ID:" << device.pnpId();
    std::cout << "    Failure type:" << device.failure();
  }
  */
}

void SampleListener::onLogMessage(const Controller&, MessageSeverity s, int64_t t, const char* msg) {
  switch (s) {
  case Leap::MESSAGE_CRITICAL:
    std::cout << "[Critical]";
    break;
  case Leap::MESSAGE_WARNING:
    std::cout << "[Warning]";
    break;
  case Leap::MESSAGE_INFORMATION:
    std::cout << "[Info]";
    break;
  case Leap::MESSAGE_UNKNOWN:
    std::cout << "[Unknown]";
  }
  std::cout << "[" << t << "] ";
  std::cout << msg << std::endl;
}

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
  SampleListener listener;
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

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
