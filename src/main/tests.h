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

}