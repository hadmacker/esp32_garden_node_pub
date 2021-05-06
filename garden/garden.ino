#include <stdio.h>
#include <Bounce2.h>
#include "DHT.h"
#include "pins.h"
#include "buttons.h"
#include "wificonnect.h"
#include "sensors.h"
#include "display.h"
#include "leds.h"
#include "aws_iot_mqtt.h"

void setup() {
  delay(1000);

  setupLeds();

  ledsUp();

  Serial.begin(115200);  
  Serial.println("setup");

  setupButtons();
  setupDht();
  setupDisplay();

  drawDisplay();

  ledsDown();
}

void loop() {
  btn1Value = testButton(&btn1, led1Pin);
  btn2Value = testButton(&btn2, led2Pin);
  btn3Value = testButton(&btn3, led3Pin);
  testSoil();
  testLdr();
  testHall();
  testDht();

  drawDisplay();

  connectToNetwork();
  connectToAws();
  client.loop();
  awsTelemetry();
  awsButtons();
}