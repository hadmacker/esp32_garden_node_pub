#ifndef __AWS_CONFIG_ESP32_GARDEN_NODE`
#define __AWS_CONFIG_ESP32_GARDEN_NODE`

#define __rev2__
#define AWS_IOT_ENDPOINT "am37g1k3fe12l-ats.iot.us-east-1.amazonaws.com"
#define DEVICE_NAME "esp32_garden_node"
#define AWS_IOT_PORT 8883
#define GREENGRASS_DISCOVERY_PORT 8443
#define AWS_IOT_TOPIC "$aws/things/" DEVICE_NAME "/shadow/update"
#define AWS_IOT_UPDATE_TOPIC "$aws/things/" DEVICE_NAME "/config/update"
#define AWS_MAX_RECONNECT_TRIES 50

#endif