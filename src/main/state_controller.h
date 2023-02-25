#pragma once

#include "settings.h"
#include "state_machine.h"

namespace drivers_controller {

/**
  * Данные, считываемые со входов
  */
class InputData {
  bool directionForward = false;
  bool directionBackward = false;
  bool powerIncrement = false;
  bool powerDecrement = false;
};

/**
 * Управление ControllerStateMachine на основе сигналов InputData
 */
class StateController {
  protected:

  ControllerStateMachine stateMachime;

  public:

  virtual ControllerState determineState(InputData input);
};

/**
 * Реализация ControllerStateMachine через задержки и счётчики, без часов реального времени
 */
class DelayStateController: public StateController {
  protected:

  ControllerState previousState;

  public:

  ControllerState determineState(InputData input) {
    delay(readingPeriod);

    return stateMachime.currentControllerState;
  }
};

}
