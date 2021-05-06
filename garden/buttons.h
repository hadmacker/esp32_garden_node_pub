#ifndef buttons_h
#define buttons_h

#include <Bounce2.h>
#include "pins.h"

const int bounceInterval = 25;

Bounce btn1 = Bounce();
Bounce btn2 = Bounce();
Bounce btn3 = Bounce();

int btn1Count = 0;
int btn2Count = 0;
int btn3Count = 0;

bool btn1Value = false;
bool btn2Value = false;
bool btn3Value = false;

void setupButton(Bounce* btn, int btnPin) {
  btn->attach(btnPin, INPUT_PULLUP);
  btn->interval(bounceInterval);
}

void setupButtons() {
  setupButton(&btn1, btn1Pin);
  setupButton(&btn2, btn2Pin);
  setupButton(&btn3, btn3Pin);
}

bool testButton(Bounce* btn, int ledPin) {
  btn->update();
  if(btn->fell()) {
    digitalWrite(ledPin,LOW);
  }
  if(btn->rose()) {
    digitalWrite(ledPin,HIGH);
    return true;
  }
  return false;
}

#endif