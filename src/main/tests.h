#include "pinout.h"
#include "state_machine.h"

#pragma once

namespace drivers_controller {

void blinkPowerOut() {
  for (int i = 0; i < powerOutN; i++) {
    digitalWrite(getPowerOutPin(i), HIGH);
    delay(300);
    digitalWrite(getPowerOutPin(i), LOW);
  }
}

void blinkPowerIn() {
  for (int i = -6; i < powerInN - 6; i++) {
    digitalWrite(getPowerInPin(i), HIGH);
    delay(300);
    digitalWrite(getPowerInPin(i), LOW);
  }
}

void blinkDirectionOut() {
  for (int i = 0; i < directionOutN; i++) {
    digitalWrite(getDirectionOutPin(i), HIGH);
    delay(300);
    digitalWrite(getDirectionOutPin(i), LOW);
  }
}

void blinkDirectionIn() {
  for (int i = -1; i <=1; i++) {
    digitalWrite(getDirectionInPin(i), HIGH);
    delay(300);
    digitalWrite(getDirectionInPin(i), LOW);
  }
}

void blinkAll() {
  blinkPowerOut();
  blinkPowerIn();
  blinkDirectionOut();
  blinkDirectionIn();
}

/**
 Тестовая реализация ControllerStateMachine, меняет положение контроллера по зацикленной траектории
*/
class LoopbackStateMachine: public ControllerStateMachine {
  /*
  Порядок переключений:
  0-вперёд-максимум-минимум-0-назад-минимум-максимум

  */
  private:
  int stages = 8;
  int stage = 0;
  public:
  ControllerState determineState() {
    switch(stage) {
      case 0: {
        forwardDirection();
        stage = 1;
        break;
      }
      case 1: {
        int s = incrementPower();
        if (s != 0) stage = 2;
        break;
      }
      case 3: {
        int s = decrementPower();
        if (s != 0) stage = 4;
      }
      case 4: {
        int s = incrementPower();
        if (getPower() == 0) stage = 5;
        break;
      }
      case 5: {
        neutralDirection();
        stage = 6;
        break;
      }
      case 6: {
        backwardDirection();
        stage = 7;
        break;
      }
      case 7: {
        int s = decrementPower();
        if (s != 0) stage = 8;
      }
      case 8: {
        int s = incrementPower();
        if (s != 0) stage = 9;
        break;
      }
      case 9: {
        int s = decrementPower();
        if (getPower() == 0) stage = 10;
        break;
      }
      case 10: {
        neutralDirection();
        stage = 0;
        break;
      }
     default: {}
    }
    return currentControllerState;
  }
};

}