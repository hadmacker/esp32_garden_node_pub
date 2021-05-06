#ifndef wificonnect_h
#define wificonnect_h

#include <WiFi.h>
#include "wificonfig.h"

String wifiStatus = "unstarted";

const int networkRefreshPeriod = 5 * 1000;
unsigned long lastNetworkUpdate = 0;
void connectToNetwork() {
  if(WiFi.status() == WL_CONNECTED) 
  {
    wifiStatus = "connected";
    return;
  }

  if(millis() < lastNetworkUpdate + networkRefreshPeriod && lastNetworkUpdate > 0) {
    return;
  }

  wifiStatus = "connecting...";
  Serial.println(wifiStatus);
  WiFi.begin(wifiSsid, wifiPassword);
  if(WiFi.status() == WL_CONNECTED) {
    wifiStatus = "connected";
  } else {
    wifiStatus = "disconnected";
  }
  Serial.println(wifiStatus);
  lastNetworkUpdate = millis();
}

#endif