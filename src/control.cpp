#include "control.h"

#include <ArduinoLogger.h>

void preLaunch() {
  verb << "Pre-Launch\n";
}
void launch() {
  verb << "Launch\n";
}
void postLaunch() {
  verb << "Post-Launch\n";
}
void decent() {
  verb << "Decent\n";
}

// pointers to functions in array
void (*states[4])() = {preLaunch, launch, postLaunch, decent};

void StateMachine::progress() {
  StateMachine::currentState++;
}

void StateMachine::update() {
  states[StateMachine::currentState]();
}

void StateMachine::reset() {
  StateMachine::currentState = 0;
}
