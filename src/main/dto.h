#pragma once

namespace drivers_controller {

/**
 * Описание состояния (положения) оригинального контроллера,
 * включает положения главного и реверсивного барабанов.
 */
class ControllerState {
  public:
  int power = 0;
  int direction = 0;
};

/**
 * Данные, считываемые со входов
 */
class InputData {
  public:
  bool directionForward = false;
  bool directionBackward = false;
  bool powerIncrement = false;
  bool powerDecrement = false;
};

}
