#ifndef AWS_IOT_MQTT_H
#define AWS_IOT_MQTT_H

#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <MQTT.h>
#include "aws_config_esp32_garden_node.h"
#include "aws_cert.h"
#include "sensors.h"
#include <ArduinoJson.h>

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(512);

void messageReceived(String &topic, String &payload) {
    Serial.println("incoming:" + topic + " - " + payload);
}

String awsStatus = "";
bool connected = false;
unsigned int lastAwsConnectionTime = 0;
const int awsReconnectDelay = 20 * 1000;
int currentRetries = 0;
const int maxRetries = 10;
void connectToAws() {

    if(client.connected()) {
        return;
    } else {
        if(currentRetries >= maxRetries) {
            Serial.println("Exceeded AWS MQTT retry count.");
            return;
        }
        if(millis() < lastAwsConnectionTime + awsReconnectDelay && lastAwsConnectionTime > 0) {
            return;
        }
    }

    Serial.println("connecting aws...");

    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);
    client.begin(AWS_IOT_ENDPOINT, AWS_IOT_PORT, net);
    client.onMessage(messageReceived);

    connected = client.connect(DEVICE_NAME);

    if(connected) {
        awsStatus = "AWS";
        client.subscribe(AWS_IOT_UPDATE_TOPIC);
        Serial.println("AWS Connected!");
    } else {
        awsStatus = "";
        currentRetries++;
        Serial.println("AWS not connected!");
    }

    lastAwsConnectionTime = millis();
}

int lastTelemetryUpdate = 0;
const int telemetryUpdateDelay = 30 * 60 * 1000;
void awsTelemetry() {
    if(!client.connected()) {
        return;
    }

    if(millis() < lastTelemetryUpdate + telemetryUpdateDelay && lastTelemetryUpdate > 0) {
        return;
    }

    digitalWrite(led2Pin, HIGH);
    StaticJsonDocument<512> jsonDoc;
    JsonObject stateObj = jsonDoc.createNestedObject("state");
    JsonObject reportedObj = stateObj.createNestedObject("reported");

    reportedObj["message"] = "garden_sensor";
    reportedObj["light"] = ldrValue;
    reportedObj["temp"] = dhtTemp;
    reportedObj["humidity"] = dhtHumidity;
    reportedObj["soil"] = soilValue;
    reportedObj["hall"] = hallValue;

    char jsonBuffer[512];
    serializeJson(jsonDoc, jsonBuffer);
    Serial.println(jsonBuffer);
    client.publish(AWS_IOT_TOPIC, jsonBuffer);
    delay(100);
    digitalWrite(led2Pin, LOW);
    lastTelemetryUpdate = millis();
}

void awsButtons() {
    if(!client.connected()) {
        return;
    }

    StaticJsonDocument<512> jsonDoc;
    JsonObject stateObj = jsonDoc.createNestedObject("state");
    JsonObject reportedObj = stateObj.createNestedObject("reported");

    if(btn1Value) {
        reportedObj["button1"] = true;
    }
    if(btn2Value) {
        reportedObj["button2"] = true;
    }
    if(btn3Value) {
        reportedObj["button3"] = true;
    }
    if(btn1Value || btn2Value || btn3Value) {
        reportedObj["message"] = "garden_button";
        digitalWrite(led2Pin, HIGH);
        char jsonBuffer[512];
        serializeJson(jsonDoc, jsonBuffer);
        Serial.println(jsonBuffer);
        client.publish(AWS_IOT_TOPIC, jsonBuffer);
        btn1Value = false;
        btn2Value = false;
        btn3Value = false;
        delay(100);
        digitalWrite(led2Pin, LOW);
    }
}

#endif
