#ifndef sensors_h
#define sensors_h

#include "pins.h"

DHT dht(dhtPin, DHT11);

int ldrValue = 0;
int hallValue = 0;
int soilValue;

bool dhtMode = false;
float dhtHumidity = 0.0;
float dhtTemp = 0.0;

void setupDht() {
  DHT* target = &dht;
  target->begin();
}

const int samplePeriod = 1200;
unsigned long lastSampleMillis = 0;
void testDht() {
  DHT* target = &dht;
  if(millis() < lastSampleMillis + samplePeriod && lastSampleMillis > 0) {
    return;
  }
  lastSampleMillis = millis();
  if(dhtMode) {
    dhtHumidity = target->readHumidity();
    isnan(dhtHumidity) ? dhtHumidity = 0 : 0;
  }
  if(!dhtMode) {
    dhtTemp = target->readTemperature();
    isnan(dhtTemp) ? dhtTemp = 0 : 0;
  }
  dhtMode = !dhtMode;
}

void testSoil() {
  soilValue = analogRead(soilPin);
  soilValue = map(soilValue, 4096, 0, 0, 4096);
}

void testLdr() {
  ldrValue = analogRead(ldrPin);
}

void testHall() {
  hallValue = hallRead();
}

#endif