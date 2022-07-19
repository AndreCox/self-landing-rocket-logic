#include "control.h"

#include <ArduinoLogger.h>

String charBuffer = "";

bool preLaunch() {
  // decode serial until we get a valid command
  while (Serial.available() > 0) {
    char c = Serial.read();
    charBuffer += c;
  }
  if (charBuffer.length() > 0) {
    if (charBuffer.equals("launch")) {
      inf << "Launch Command Received!" << endl;
      charBuffer = "";
      return true;
    }
    inf << "Serial: " << charBuffer << endl;
    charBuffer = "";
  }
  return false;
}
bool launch() {
  inf << "Starting Takeoff!" << endl;
  return true;
  return false;
}
bool postLaunch() {
  inf << "Finished Takeoff!" << endl;
  return true;
  return false;
}
bool decent() {
  inf << "Starting Descent!" << endl;
  while (true) {
    int i = 0;
  }

  return false;
}

// pointers to functions in array
bool (*states[4])() = {preLaunch, launch, postLaunch, decent};

void StateMachine::progress() {
  StateMachine::currentState++;
}

void StateMachine::update() {
  if (states[StateMachine::currentState]()) {
    verb << "State finished transitioning to next state" << endl;
    StateMachine::progress();
    verb << "State: " << StateMachine::currentState << endl;
  };
}

void StateMachine::reset() {
  verb << "Reseting State" << endl;
  StateMachine::currentState = 0;
}
