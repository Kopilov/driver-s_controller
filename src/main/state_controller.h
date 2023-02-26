#pragma once

#include "settings.h"
#include "state_machine.h"

namespace drivers_controller {


/**
 * Управление ControllerStateMachine на основе сигналов InputData
 */
class StateController {
  protected:

  ControllerStateMachine stateMachine;

  public:

  virtual ControllerState determineState(InputData input);
};

/**
 * Реализация ControllerStateMachine через задержки и счётчики, без часов реального времени
 */
class DelayStateController: public StateController {

  protected:

  // переключение реверса в нужное положение из нейтрали
  int swithDirectionFromNeutral(InputData input) {
    int result = 0;
    if (input.directionForward) {
      result = stateMachine.forwardDirection();
    }
    if (input.directionBackward) {
      result = stateMachine.backwardDirection();
    }
  }

  int incrementPower() {
    return stateMachine.incrementPower();
  }

  int decrementPower() {
    return stateMachine.decrementPower();
  }

  ControllerState previousState;
  InputData previousInput;

  public:

  ControllerState determineState(InputData input) {
    delay(readingPeriod);

    if (!previousInput.powerIncrement && input.powerIncrement) { //нажатие джойстика на разгон
      int result = 0;
      if (stateMachine.getDirection() == 0) { //нейтральное положение
        result = swithDirectionFromNeutral(input);
      } else {
        result = incrementPower();
      }
      if (result != 0) {
        //переключение не выполнено, при необходимости добавить логику
      }
    }

    if (!previousInput.powerDecrement && input.powerDecrement) { //нажатие джойстика на тормоз
      int result = 0;
      if (stateMachine.getDirection() == 0) { //нейтральное положение
        result = swithDirectionFromNeutral(input);
      } else {
        result = decrementPower();
      }
      if (result != 0) {
        //переключение не выполнено, при необходимости добавить логику
      }
    }

    if (!previousInput.directionForward && input.directionForward) { //включение тумблера реверса вперёд
//      stateMachine.forwardDirection();
    }

    if (!previousInput.directionBackward && input.directionBackward) { //включение тумблера реверса назад
//      stateMachine.backwardDirection();
    }

    previousInput = input;
    previousState = stateMachine.currentControllerState;
    return stateMachine.currentControllerState;
  }
};

}
