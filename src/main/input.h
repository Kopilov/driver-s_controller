#pragma once

#include "pinout.h"

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

}
