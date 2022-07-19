#include "logging.h"

#include <ArduinoLogger.h>
//#include <SPI.h>
#include <SD.h>

#include "../configuration.h"
//#include "SdFat.h"
#include "globals.h"
//#include "sdios.h"

void logToSerial() {
// [1] orientation
// [2] angular velocity
// [3] linear acceleration
// [4] magnitometer
// [5] accelerometer
// [6] gravity
// [7] time
#ifdef LogSensorSerial
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.print(data[i][j]);
      Serial.print(",");
    }
    Serial.println();
  }
#endif
}

void sdSetup() {
#ifdef LOGSD
  verb << "Initializing SD" << endl;
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    err << "Card failed, or not present\n";

    while (1) {
      errorCode(1);
    }
  }
  verb << "SD Initialization Complete" << endl;
#endif
#ifndef LOGSD
  warn << "SD Logging Disabled" << endl;
#endif
}

void sdLog(float (&data)[7][3]) {
#ifdef LOGSD
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataWriteToFile(data, dataFile);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    err << "error opening datalog.txt";
  }
#endif
}

void dataWriteToFile(float data[7][3], File dataFile) {
#ifdef LOGSD
  //  A function to take accelleration data and write to a file in a csv format.
  for (int j = 0; j < 7; j++) {
    for (int k = 0; k < 3; k++) {
      String dataChar = (String)data[j][k];
      dataFile.print(dataChar + ",");
    }
  }
  dataFile.print("\n");
#endif
}

// Display error code (0 IMU error, 1 SD Connection Error, 2 Bluetooth Conection Error)
void errorCode(int error) {
#ifdef ErrorCodes
  switch (error) {
    case 0:  // IMU conection error (slow led blink)
      digitalWrite(ledPin, LOW);
      delay(1000);
      digitalWrite(ledPin, HIGH);
      delay(1000);
      break;
    case 1:  // SD connection error (fast led blink)
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      break;
    case 3:  // Bluetooth connection error (2 short blinks one long blink)
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(1000);
      digitalWrite(ledPin, HIGH);
      delay(1000);
    default:
      break;
  }
#endif
}