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
  int incrementPower(InputData input) {
    int result = 0;
    if (stateMachine.getDirection() == 0) { //нейтральное положение
      result = swithDirectionFromNeutral(input);
    } else {
      result = stateMachine.incrementPower();
    }
    if (result != 0) {
      //переключение не выполнено, при необходимости добавить логику
    }
  }

  /**
   * Тормоз
   */
  int decrementPower(InputData input) {
    int result = 0;
    if (stateMachine.getDirection() == 0) { //нейтральное положение
      result = swithDirectionFromNeutral(input);
    } else {
      result = stateMachine.decrementPower();
    }
    if (result != 0) {
      //переключение не выполнено, при необходимости добавить логику
    }
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

  //Удержание джойстика на разгон (факт удержания)
  int powerIncrementPressed = 0;
  //Удержание джойстика на разгон (время с момента регстрации события в мс )
  int powerIncrementDuration = 0;

  //Удержание джойстика на тормоз (факт удержания)
  int powerDecrementPressed = 0;
  //Удержание джойстика на тормоз (время с момента регстрации события в мс )
  int powerDecrementDuration = 0;

  public:

  ControllerState determineState(InputData input) {
    delay(readingPeriod);

    if (!previousInput.powerIncrement && input.powerIncrement) { //Нажатие джойстика на разгон
      powerIncrementPressed = 1;
      incrementPower(input);
    }

    if (previousInput.powerIncrement && !input.powerIncrement) { //Отпускание джойстика на разгон
      powerIncrementPressed = 0;
      powerIncrementDuration = 0;
    }

    if (previousInput.powerIncrement && input.powerIncrement) { //Удержание джойстика на разгон
      if (powerIncrementPressed) {
        powerIncrementDuration += readingPeriod;
      }
      if (powerIncrementDuration >= manualSwitchingInterval) {
        incrementPower(input);
        powerIncrementDuration = 0;
      }
    }

    if (!previousInput.powerDecrement && input.powerDecrement) { //Нажатие джойстика на тормоз
      powerDecrementPressed = 1;
      decrementPower(input);
    }

    if (previousInput.powerDecrement && !input.powerDecrement) { //Отпускание джойстика на тормоз
      powerDecrementPressed = 0;
      powerDecrementDuration = 0;
    }

    if (previousInput.powerDecrement && input.powerDecrement) { //Удержание джойстика на тормоз
      if (powerDecrementPressed) {
        powerDecrementDuration += readingPeriod;
      }
      if (powerDecrementDuration >= manualSwitchingInterval) {
        decrementPower(input);
        powerDecrementDuration = 0;
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
