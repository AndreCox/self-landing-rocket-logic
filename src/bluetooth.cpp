#include <Arduino.h>
#include <ArduinoLogger.h>>
#include <SoftwareSerial.h>
#include <bluetooth.h>

SoftwareSerial bluetoothSetup(int ledPin, int output) {
  pinMode(ledPin, output);
  digitalWrite(ledPin, LOW);
  SoftwareSerial Bluetooth(PD0, PD1);  // RX, TX
  Bluetooth.begin(9600);
  verb << "Bluetooth Setup Complete\n";
  return Bluetooth;
}