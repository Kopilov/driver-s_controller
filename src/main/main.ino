#include "pinout.h"
#include "tests.h"
#include "state_machine.h"

using namespace drivers_controller;

ControllerState currentControllerState;

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

  ControllerState currentControllerState;
}

void loop() {
  //manage state;
  //switch output;
}
