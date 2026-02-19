#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11
const int WindSensor = 15;
const int PluvSensor = 16;
const float mmPercycle = 0.173;
int state = 0;
int statePrec = 0;

const int RecordTime = 3; //Define Measuring Time (Seconds)

const long frequency = 433E6;
const long spreadingFactor = 7;
const long bandwidth = 125E3;
const int codingRate = 5;

int InterruptCounter;
float v=0, h=0, t=0, p=0;
String LoRaMessage = "";

DHT dht(DHTPIN, DHTTYPE);

//define the pins used by the sender module
#define ss 17
#define rst 27
#define dio0 28

int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  dht.begin();
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa sender module
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(frequency)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  //LoRa.setSyncWord(0xF3);
  LoRa.setSpreadingFactor(spreadingFactor);
  LoRa.setSignalBandwidth(bandwidth);
  LoRa.setCodingRate4(codingRate);
  //LoRa.setTxPower(18);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  meassure();
  Serial.print("Pluie: ");
  Serial.print(p);       //rain in mm
  Serial.print(" mm - ");
  Serial.print("Vitesse du vent: ");
  Serial.print(v);       //Speed in km/h
  Serial.print(" km/h - ");
  Serial.print("Température ");
  Serial.print(t);
  Serial.print(" °C - ");
  Serial.print("Humidité ");
  Serial.print(h);
  Serial.print(" % \n");
  
  LoRaMessage = String(t) + "/" + String(h) + "&" + String(v) + "-" + String(p);
  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();

  delay(5000);
}

void meassure() {
  //Wind speed
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(WindSensor), countup, RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(WindSensor));
  v = (float)InterruptCounter / (float)RecordTime * 2.4;
  
  //Pluviometer
  state = digitalRead(16);
  if (state != statePrec) {
    p = p + mmPercycle;
  }
  delay(500);
  statePrec = state;
}

void countup() {
  InterruptCounter++;
}