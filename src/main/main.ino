#include "pinout.h"
#include "state_controller.h"
#include "output.h"
#include "tests.h"

using namespace drivers_controller;

StateController* stateController;
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

  stateController = new LoopbackStateController();
}

void loop() {
  stateController->determineState();
  writeOutput(stateController->stateMachime);
  //blinkAll();
}
