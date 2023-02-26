#include "pinout.h"
#include "dto.h"

#pragma once

namespace drivers_controller {

bool directionForwardEnabled() {
  return digitalRead(directionSetForward) == 0;
}

bool directionBackwardEnabled() {
  return digitalRead(directionSetBackward) == 0;  
}

bool powerIncrementEnabled() {
  return digitalRead(powerSetIncrement) == 0;
}

bool powerDecrementEnabled() {
  return digitalRead(powerSetDecrement) == 0;
}

void readInput(InputData& input) {
  input.directionForward = directionForwardEnabled();
  input.directionBackward = directionBackwardEnabled();
  input.powerIncrement = powerIncrementEnabled();
  input.powerDecrement = powerDecrementEnabled();

  if (input.directionForward && input.directionBackward) {
    //Ошибка (возможно, замыкание контактов). При необходимости добавить alarm
  }

  if (input.powerIncrement && input.powerDecrement) {
    //Ошибка (возможно, замыкание контактов). При необходимости добавить alarm
  }
}

}
