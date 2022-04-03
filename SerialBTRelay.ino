//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int relayPump = 26;
int relaySensor = 25;
int led = 2;
//String state = "";
bool state = 1;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("AutoBoomBT"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(relayPump, OUTPUT);
  pinMode(relaySensor, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(relayPump, state);
  digitalWrite(relaySensor, state);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {

    state = SerialBT.read();
    digitalWrite(relayPump, !state); 
    digitalWrite(relaySensor, !state); 
    digitalWrite(led, state);
    
  }
  delay(1);
}
