#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <WiFi.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

const long frequency = 433E6;
const long spreadingFactor = 12;
const long bandwidth = 125E3;
const int codingRate = 5;
int pos1, pos2, pos3;

// Initialize variables to get and save LoRa data
int rssi;
String loRaMessage;
double temperature, humidity, windSpeed, rainfall;
String t, h, w, r;
int packetSize = 0;

const char* ssid = "Ooredoo _S20_3EEB";
const char* pass = "6E27D3EF";
AsyncWebServer server(8080);

void setup() {

Serial.begin(9600);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println();
Serial.print("IP: "); Serial.println(WiFi.localIP());
server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["humidity"]    = humidity;
  doc["windSpeed"]   = windSpeed;
  doc["rainfall"]    = rainfall;
  doc["timestamp"]   = String(millis()); // ou iso8601
  String body;
  serializeJson(doc, body);
  request->send(200, "application/json", body);
});
server.begin();

  //initialize Serial Monitor
  
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  while (!LoRa.begin(frequency)) {
    Serial.println(".");
    delay(500);
  }
  //LoRa.setSyncWord(0xF3);
  LoRa.setSpreadingFactor(spreadingFactor);
  LoRa.setSignalBandwidth(bandwidth);
  LoRa.setCodingRate4(codingRate);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // try to parse packet
  packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet ");
    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      pos1 = LoRaData.indexOf('/');
      pos2 = LoRaData.indexOf('&');
      pos3 = LoRaData.indexOf('-');
      t = LoRaData.substring(0, pos1);
      h = LoRaData.substring(pos1 +1, pos2);
      w = LoRaData.substring(pos2 +1, pos3);
      r = LoRaData.substring(pos3 +1, LoRaData.length());
      Serial.print(temperature);
      Serial.print("°C - ");
      Serial.print(humidity);
      Serial.print("% - ");
      Serial.print(windSpeed);
      Serial.print("km/h - ");
      Serial.print(rainfall);
      Serial.print("mm - Rssi ");
      temperature = t.toDouble();
      humidity = h.toDouble();
      windSpeed = w.toDouble();
      rainfall = r.toDouble(); 
    }
    //Serial.println(LoRa.packetRssi());
    //Serial.println(packetSize);
    
    //delay(5000);
  }
}