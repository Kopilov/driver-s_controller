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

int powerSwitchers[powerInN][powerOutN] = {
// QK10, QK1, QK9, QK2, QK3, QK4, QK11, QK12, QK5, QK6, QK7, QK8

  {1,    1,   0,   1,   0,   1,   1,    0,    1,   0,   1,   0},//6
  {1,    1,   0,   1,   0,   1,   1,    0,    1,   0,   1,   0},//5
  {1,    0,   0,   1,   0,   1,   1,    0,    1,   0,   1,   0},//4
  {1,    1,   0,   1,   1,   0,   1,    0,    1,   0,   1,   0},//3
  {1,    1,   0,   0,   1,   0,   1,    0,    1,   0,   1,   0},//2
  {1,    1,   0,   0,   0,   0,   1,    0,    1,   0,   1,   0},//1
  {0,    1,   0,   0,   0,   0,   0,    0,    0,   1,   0,   1},//0
  {0,    1,   1,   0,   0,   0,   0,    1,    0,   1,   0,   0},//1
  {0,    1,   1,   0,   1,   0,   0,    1,    0,   1,   0,   0},//2
  {0,    1,   1,   1,   1,   0,   0,    1,    0,   1,   0,   0},//3
  {0,    0,   1,   1,   0,   1,   0,    1,    0,   1,   0,   0},//4
  {0,    0,   1,   1,   1,   1,   0,    1,    0,   1,   0,   0},//5
  {0,    0,   1,   1,   1,   0,   0,    1,    0,   1,   0,   0},//X1
  {0,    0,   1,   1,   0,   0,   0,    1,    0,   1,   1,   0},//X2
  {0,    0,   1,   1,   0,   0,   0,    1,    1,   0,   1,   0},//X3
  {0,    0,   1,   1,   0,   1,   0,    1,    1,   0,   1,   0},//6
  {0,    1,   1,   1,   0,   1,   0,    1,    1,   0,   1,   0},//7
  {0,    1,   1,   1,   1,   1,   0,    1,    1,   0,   1,   0} //8
};

void writePowerSwitchers(int powerState) {
  for (int i = 0; i < powerOutN; i++) {
    digitalWrite(getPowerOutPin(i), powerSwitchers[powerState + 6][i]);
  }
}

void writeDirectionIndicator(int directionState) {
  for (int i = -1; i <=1; i++) {
    digitalWrite(getDirectionInPin(i), LOW);
  }
  digitalWrite(getDirectionInPin(directionState), HIGH);
}

int directionSwitchers[directionInN][directionOutN] = {
// QS1, QS3, QS2, QS4, QS5, QS7, QS6, QS8, QS9, QS10, QS11, QS12
  {0,   1,   0,   1,   0,   1,   0,   1,   0,   1,    1,    0}, //Назад
  {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    1,    1}, //O
  {1,   0,   1,   0,   1,   0,   1,   0,   1,   0,    0,    1}  //Вперёд
};


void writeDirectionSwitchers(int directionState) {
  for (int i = 0; i < directionOutN; i++) {
    digitalWrite(getDirectionOutPin(i), directionSwitchers[directionState + 1][i]);
  }
}

void writeOutput(ControllerStateMachine* controllerStateMachine) {
  writePowerIndicator(controllerStateMachine->getPower());
  writePowerSwitchers(controllerStateMachine->getPower());
  writeDirectionIndicator(controllerStateMachine->getDirection());
  writeDirectionSwitchers(controllerStateMachine->getDirection());
}

}
