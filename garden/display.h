#ifndef display_h
#define display_h

#include <Wire.h>
#include "SSD1306Wire.h"
#include "wificonnect.h"
#include "aws_iot_mqtt.h"

SSD1306Wire display(0x3c, 18, 19);

void setupDisplay() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

const int displayRefreshPeriod = 100;
unsigned long lastDisplayUpdate = 0;
void drawDisplay() {
  if(millis() < lastDisplayUpdate + displayRefreshPeriod && lastDisplayUpdate > 0) {
    return;
  }

  lastDisplayUpdate = millis();
  char line2[20];
  char line3[20];

  sprintf(line2, "%04d %03d %d %d", ldrValue, hallValue, btn1Count, soilValue);
  sprintf(line3, "%.1f %.1f", dhtHumidity, dhtTemp);

  // clear the display
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  String line = String("wifi:" + wifiStatus + " " + awsStatus);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, line);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 15, line2);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 30, line3);
  display.display();
}

#endif
