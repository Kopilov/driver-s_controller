#pragma once

namespace drivers_controller {

/**
Описание состояния (положения) оригинального контроллера,
включает положения главного и реверсивного барабанов.
*/
class ControllerState {
  public:
  int power = 0;
  int direction = 0;
};

/**
Конечный автомат, описывающий поведение контроллера через объект ControllerState.
Всего возможны 18 * 2 + 1 корректных состояний.
А именно, 18 положений главного барабана при двух рабочих
положениях реверсивного и нулевое положение.

Положение каждого барабана может изменяться только с соседнего на соседнее,
при этом нулевое положение реверсивного ставится только при нулевом положении главного и будучи выставленным,
не позволяет изменить положение главного на другое.

        main
        6 5 4 3 2 1 0 1 2 3 4 5 6 7 8 9 10 11
reverse
    -1  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*--*
                    |
     0              *
                    |
     1  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*--*


*/
class ControllerStateMachine {
  protected:
  ControllerState currentControllerState;
  int powerMin = -6;
  int powerMax = 11;

  public:

  int getPower() {
    return currentControllerState.power;
  }

  int getDirection() {
    return currentControllerState.direction;
  }

  /**
  Сдвинуть главный барабан на 1 позицию вперёд.
  Возвращает:
  * 0, если выполнено успешно (позиция изменена)
  * 1, если барабан сдвинут до упора (или максимально допустимой позиции)
  * 2, если барабан зафиксирован (нейтральное положение реверса)
  */
  int incrementPower() {
    if (currentControllerState.direction == 0) return 2;
    if (currentControllerState.power >= powerMax) return 1;
    currentControllerState.power++;
    return 0;
  }

  /**
  Сдвинуть главный барабан на 1 позицию назад.
  Возвращает:
  * 0, если выполнено успешно (позиция изменена)
  * 1, если барабан сдвинут до упора (или максимально допустимой позиции)
  * 2, если барабан зафиксирован (нейтральное положение реверса)
  */
  int decrementPower() {
    if (currentControllerState.direction == 0) return 2;
    if (currentControllerState.power <= powerMin) return 1;
    currentControllerState.power--;
    return 0;
  }

  /**
  Установить реверсивный барабан в положение «вперёд».
  Возвращает:
  * 0, если выполнено успешно (перемещение из нейтрального положения)
  * 1, если барабан уже на данной позиции (с любым положением главного барабана)
  * 2, если барабан зафиксирован (рабочее положение главного барабана, реверсивный в положении «назад»)
  * 3, если барабан был в позиции «назад», но не зафиксирован, тогда он перемещается на нейтральное положение
  */
  int forwardDirection() {
    if (currentControllerState.direction >= 1) return 1;
    if (currentControllerState.power != 0) return 2;
    if (currentControllerState.direction == 0) {
      currentControllerState.direction = 1;
      return 0;
    } else {
      currentControllerState.direction = 0;
      return 3;
    }
  }

  /**
  Установить реверсивный барабан в положение «назад».
  Возвращает:
  * 0, если выполнено успешно (перемещение из нейтрального положения)
  * 1, если барабан уже на данной позиции (с любым положением главного барабана)
  * 2, если барабан зафиксирован (рабочее положение главного барабана, реверсивный в положении «вперёд»)
  * 3, если барабан был в позиции «вперёд», но не зафиксирован, тогда он перемещается на нейтральное положение
  */
  int backwardDirection() {
    if (currentControllerState.direction <= -1) return 1;
    if (currentControllerState.power != 0) return 2;
    if (currentControllerState.direction == 0) {
      currentControllerState.direction = -1;
      return 0;
    } else {
      currentControllerState.direction = 0;
      return 3;
    }
  }

  /**
  Установить реверсивный барабан в положение «нейтраль».
  Возвращает:
  * 0, если выполнено успешно
  * 1, если барабан уже на данной позиции
  * 2, если барабан зафиксирован (рабочее положение главного барабана)
  */
  int neutralDirection() {
    if (currentControllerState.power != 0) return 2;
    if (currentControllerState.direction == 0) return 1;
    currentControllerState.direction = 0;
    return 0;
  }
  /**
  Вычислить текущее состояние из фактического предыдущего (одномомнтного или временного ряда)
  и внешних факторов (органы управления или тестовые данные)
  */
  virtual ControllerState determineState() = 0;
};

}
