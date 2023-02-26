#include "dto.h"
#include "input.h"
#include "output.h"
#include "state_controller.h"
#include "tests.h"

namespace drivers_controller {

StateController* stateController = new DelayStateController();
InputData input;

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

  //Serial.begin(9600);
}

void loop() {
  /////tests
  //echoOutput();
  //blinkAll();

  readInput(input);
  ControllerState state = stateController->determineState(input);
  writeOutput(state);
}

}

void setup() {
  drivers_controller::setup();
}
void loop() {
  drivers_controller::loop();
}
