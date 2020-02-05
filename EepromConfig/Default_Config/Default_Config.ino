#include <ESP8266WiFi.h>
#include <EEPROM.h>

#define ADRESS 30

struct WifiConfig  {
  bool default_Enable;
  char default_SSID[30];
  char default_Pass[30];
};

WifiConfig test_config;

void setup() {
  Serial.begin(9600);
  WifiConfig default_config{
    true,
    "PandaPlug",
    "Panda!!!"
  };
  EEPROM.begin(512);
  EEPROM.put(ADRESS, default_config);
  EEPROM.commit();
}

void loop() {

    EEPROM.get(ADRESS,test_config);
    delay(100);
    Serial.println(test_config.default_Enable);
    Serial.println((String)test_config.default_SSID);
    Serial.println((String)test_config.default_Pass);
    delay(1000);

}
