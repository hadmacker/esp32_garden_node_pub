# esp32_garden_node

## Getting Set Up

* Arduino IDE: https://www.arduino.cc/en/Main/Software
* ESP32 in Arduino IDE: https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
  * Arduino preferences, add "https://dl.espressif.com/dl/package_esp32_index.json" to the additional board manager URL property.

## EXP32 DevKitC Pinout

Image Origin: https://components101.com/sites/default/files/component_pin/ESP32-Pinout.png

![ESP32 DevKitC Pinout](ESP32-Pinout.png)

## Libraries Used

* adafruit_ssd1306 2.3.1
  * https://github.com/adafruit/Adafruit_SSD1306
* ArduinoJson 6.15.2
  * https://arduinojson.org
* WiFi 1.2.7
  * https://www.arduino.cc/en/Reference/WiFi
  * https://techtutorialsx.com/2017/06/29/esp32-arduino-getting-started-with-wifi/
* DHT sensor library 1.3.10
  * https://github.com/adafruit/DHT-sensor-library
* arduino-mqtt
  * https://github.com/256dpi/arduino-mqtt

## Additional Reference Materials

* Arduino AWS IOT example: https://github.com/hadmacker/arduino_aws_iot/blob/master/sketch_dec23a.ino
  * https://www.savjee.be/2019/07/connect-esp32-to-aws-iot-with-arduino-code/
    * https://github.com/Savjee/arduino-aws-iot-starter-template/blob/master/arduino-aws-iot-starter-template/arduino-aws-iot-starter-template.ino

## Pinout

| Interface  | PIN     | Pin Mode | Verb         | Library          |
| ---------- | ------- | -------- | ------------ | ---------------- |
| DHT11      | GPIO 14 |          | dht.read*    | dht.h            |
| light      | GPIO 32 | INPUT    | analogRead   |                  |
| moisture   | GPIO 33 | INPUT    | analogRead   |                  |
| BTN1       | GPIO 23 | INPUT    | digitalRead  |                  |
| LED1       | GPIO 5  | OUTPUT   | digitalWrite |                  |
| BTN2       | GPIO 15 | INPUT    | digitalRead  |                  |
| LED2       | GPIO 16 | OUTPUT   | digitalWrite |                  |
| BTN3       | GPIO 2  | INPUT    | digitalRead  |                  |
| LED3       | GPIO 4  | OUTPUT   | digitalWrite |                  |
| OLED SCL   | GPIO 19 |          |              | adafruit_ssd1306 |
| OLED SDA   | GPIO 18 |          |              |                  |

### Avoiding special pins

* GPIO0 cannot be pulled down (i.e., pushbutton) during boot. System booted successfully only when button was held down.
* See this link for some special considerations around special pins: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
* ADC2 pins cannot be used with WIFI: https://github.com/espressif/arduino-esp32/issues/440

## Specifications & Examples

### OLED

* Model: https://www.aliexpress.com/item/32780134267.html?spm=a2g0s.9042311.0.0.27424c4dikqNWr
* Example0: https://circuits4you.com/2019/01/09/esp32-oled-library-display-example/
* Example1: http://www.esp32learning.com/code/esp32-and-oled-display-example.php
* Example2: https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/

### DHT11 Sensor

* Example: http://www.esp32learning.com/code/esp32-and-dht11-sensor-example.php

### Soil Moisture Sensor

* Example: http://www.esp32learning.com/code/esp32-and-soil-moisture-sensor-example.php
* Supports both Digital Out and Analog Out.
* Using *Analog Out*.

### Light Sensor (Photoresistor)

* Example: http://www.esp32learning.com/code/esp32-and-ldr-example.php

### Momentary Tactile Button

* Example: https://microcontrollerslab.com/push-button-esp32-gpio-digital-input/

### LED

* Example: (See Momentary Tactile Button)

### Hall Effect Sensor

* Why? Why not. It's another data point. While it might be impractical for the current need, it's freely given.
* More Info: https://randomnerdtutorials.com/esp32-hall-effect-sensor/