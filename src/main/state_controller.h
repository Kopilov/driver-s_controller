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

  /**
   * Переключение реверса в нужное положение из нейтрали при сигнале на изменение мощности
   */
  int swithDirectionFromNeutral(InputData input) {
    int result = 0;
    if (input.directionForward) {
      result = stateMachine.forwardDirection();
    }
    if (input.directionBackward) {
      result = stateMachine.backwardDirection();
    }
  }

  /**
   * Разгон
   */
  int incrementPower() {
    return stateMachine.incrementPower();
  }

  /**
   * Тормоз
   */
  int decrementPower() {
    return stateMachine.decrementPower();
  }

  /**
   * Обработка переключений тумблера реверса (в том числе из недопустимых состояний)
   */
  int directionSwitchHandler() {
    if (stateMachine.getDirection() == 0) { //нейтральное положение
      //ничего не делаем, при разгоне направление будет учтено
    }
    if (stateMachine.getPower() == 0) {
      //При нулевой мощности переводим в нейтраль
      stateMachine.neutralDirection();
    }
    if (stateMachine.getPower() > 0) {
      //При положительной мощности аварийный тормоз
    }
    if (stateMachine.getPower() < 0) {
      //При тормозе асинхронно переводим в нейтраль
    }
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
      directionSwitchHandler();
    }

    if (!previousInput.directionBackward && input.directionBackward) { //включение тумблера реверса назад
      directionSwitchHandler();
    }

    previousInput = input;
    previousState = stateMachine.currentControllerState;
    return stateMachine.currentControllerState;
  }
};

}
