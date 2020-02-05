#include <ESP8266WiFi.h>
#include <EEPROM.h>

#define ADRESS 0
 
struct WifiConfig  {
  bool default_Enable;
  char* default_SSID;
  char* default_Pass;
};

WifiConfig default_config;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
}

void loop() {
    EEPROM.get(ADRESS,default_config);
    delay(100);
    Serial.println(default_config.default_Enable);
    Serial.println(default_config.default_SSID);
    Serial.println(default_config.default_Pass);
    delay(1000);
}
