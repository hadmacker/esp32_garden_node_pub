#ifndef LEDS_H
#define LEDS_H

void setupLeds() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
}

void ledsUp() {
  digitalWrite(led1Pin, HIGH);
  delay(200);
  digitalWrite(led2Pin, HIGH);
  delay(200);
  digitalWrite(led3Pin, HIGH);
}

void ledsDown() {
  digitalWrite(led1Pin, LOW);
  delay(200);
  digitalWrite(led2Pin, LOW);
  delay(200);
  digitalWrite(led3Pin, LOW);
}
#endif
