#include "Arduino.h"
#include "pinout.h"
#include "state_machine.h"

#pragma once

namespace drivers_controller {

void writePowerIndicator(int powerState) {
  for (int i = -6; i < powerInN - 6; i++) {
    digitalWrite(getPowerInPin(i), LOW);
  }
  digitalWrite(getPowerInPin(powerState), HIGH);
}

void writePowerSwitchers(int powerState) {
  for (int i = 0; i < powerOutN; i++) {
    digitalWrite(getPowerOutPin(i), LOW);
  }
}

void writeDirectionIndicator(int directionState) {
  for (int i = -1; i <=1; i++) {
    digitalWrite(getDirectionInPin(i), LOW);
  }
  digitalWrite(getDirectionInPin(directionState), HIGH);
}

void writeDirectionSwitchers(int directionState) {
  for (int i = 0; i < directionOutN; i++) {
    digitalWrite(getDirectionOutPin(i), LOW);
  }
}

void writeOutput(ControllerStateMachine* controllerStateMachine) {
  writePowerIndicator(controllerStateMachine->getPower());
  writePowerSwitchers(controllerStateMachine->getPower());
  writeDirectionIndicator(controllerStateMachine->getDirection());
  writeDirectionSwitchers(controllerStateMachine->getDirection());
}

}
