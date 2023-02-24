#pragma once

#include "state_machine.h"

namespace drivers_controller {

class StateController {
  public:

  ControllerStateMachine stateMachime;
  virtual void determineState();
};

}
