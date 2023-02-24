#include "pinout.h"
#include "state_controller.h"

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
 Тестовая реализация StateController, меняет положение контроллера по зацикленной траектории
*/
class LoopbackStateController: public StateController {
  /*
  Порядок переключений:
  0-вперёд-максимум-минимум-0-назад-минимум-максимум

  */
  private:
  int stage = 0;

  public:

  void determineState() {
    delay(1000);
    switch(stage) {
      case 0: {
        stateMachime.forwardDirection();
        stage = 1;
        break;
      }
      case 1: {
        int s = stateMachime.incrementPower();
        if (s != 0) stage = 2;
        break;
      }
      case 2: {
        int s = stateMachime.decrementPower();
        if (s != 0) stage = 3;
        break;
      }
      case 3: {
        int s = stateMachime.incrementPower();
        if (stateMachime.getPower() == 0) stage = 4;
        break;
      }
      case 4: {
        stateMachime.neutralDirection();
        stage = 5;
        break;
      }
      case 5: {
        stateMachime.backwardDirection();
        stage = 6;
        break;
      }
      case 6: {
        int s = stateMachime.decrementPower();
        if (s != 0) stage = 7;
        break;
      }
      case 7: {
        int s = stateMachime.incrementPower();
        if (s != 0) stage = 8;
        break;
      }
      case 8: {
        int s = stateMachime.decrementPower();
        if (stateMachime.getPower() == 0) stage = 9;
        break;
      }
      case 9: {
        stateMachime.neutralDirection();
        stage = 0;
        break;
      }
     default: {}
    }
    return stateMachime.currentControllerState;
  }
};

}