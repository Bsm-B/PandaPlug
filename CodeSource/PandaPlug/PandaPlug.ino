#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <EEPROM.h>

#define ADRESS 30
#define PORT 5000

IPAddress staticIP(10, 10, 10, 10);
IPAddress gateway(10, 10, 10, 1);
IPAddress subnet(255, 0, 0, 0);

ESP8266WebServer server(PORT);

struct WifiConfig  {
  bool default_Enable;
  char default_SSID[30];
  char default_Pass[30];
};

WifiConfig Config;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  EEPROM.get(ADRESS, Config);
  delay(25);

  Serial.println(Config.default_Enable);
  Serial.println((String)Config.default_SSID);
  Serial.println((String)Config.default_Pass);

  if (Config.default_Enable) {

    WiFi.softAP(Config.default_SSID, Config.default_Pass);
    WiFi.softAPConfig(staticIP, gateway, subnet);
    Serial.println("AP START");
    server.on("/", HTTP_GET, handleRoot);
    server.on("/configwifi", HTTP_POST, handleConfig);
    server.onNotFound(handleNotFound);

    server.begin();


  } else {

  }

}

void loop() {
  server.handleClient();
}


void handleRoot() {

  server.send(200, "text/html", "<h1>welcome</h1>");
}


void handleConfig() {
  if ( ! server.hasArg("ssid") || ! server.hasArg("pass")
       || server.arg("ssid") == NULL || server.arg("pass") == NULL) {
    server.send(400, "text/plain", "400: Invalid Request");
    return;
  }

 /*// (server.arg("ssid") == "" && server.arg("pass") == "") 

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(server.arg("ssid") , server.arg("pass"));
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
*/
}

void handleNotFound() {

  server.send(404, "text/plain", "404: Not found");

}
