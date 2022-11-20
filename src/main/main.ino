#include "pinout.h"
#include "state_machine.h"
#include "output.h"
#include "tests.h"

using namespace drivers_controller;

ControllerStateMachine* controllerStateMachine;
void setup() {
  for (int i = 0; i < powerOutN; i++) {
    pinMode(i + powerOutOffset, OUTPUT);
  }

  for (int i = 0; i < powerInN; i++) {
    pinMode(i + powerInOffset, OUTPUT);
  }

  for (int i = 0; i < directionOutN; i++) {
    pinMode(i + directionOutOffset, OUTPUT);
  }

  for (int i = 0; i < directionInN; i++) {
    pinMode(i + directionInOffset, OUTPUT);
  }

  pinMode(directionSetForward,  INPUT_PULLUP);
  pinMode(directionSetBackward, INPUT_PULLUP);
  pinMode(powerSetIncrement,    INPUT_PULLUP);
  pinMode(powerSetDecrement,    INPUT_PULLUP);

  controllerStateMachine = new LoopbackStateMachine();
}

void loop() {
  controllerStateMachine->determineState();
  writeOutput(controllerStateMachine);
  delay(1000);
}
