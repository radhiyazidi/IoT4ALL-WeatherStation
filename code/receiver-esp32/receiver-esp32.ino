#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

const long frequency = 433E6;
const long spreadingFactor = 7;
const long bandwidth = 125E3;
const int codingRate = 5;
int pos1, pos2, pos3;

// Initialize variables to get and save LoRa data
int rssi;
String loRaMessage;
String t, h, v, p;
int packetSize = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
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
  //LoRa.setSignalBandwidth(bandwidth);
  //LoRa.setCodingRate4(codingRate);
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
      v = LoRaData.substring(pos2 +1, pos3);
      p = LoRaData.substring(pos3 +1, LoRaData.length());
      Serial.print(t);
      Serial.print("°C - ");
      Serial.print(h);
      Serial.print("% - ");
      Serial.print(v);
      Serial.print("km/h - ");
      Serial.print(p);
      Serial.print("mm - "); 
    }
    Serial.println(LoRa.packetRssi());
    //Serial.println(packetSize);
  }
  
}