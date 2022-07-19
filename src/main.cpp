//------------------------------------------------------------------//
//                                                                  //
//                 Self Landing Model Rocket Logic                  //
//                     UBCO Aerospace Club                          //
//                                                                  //
//------------------------------------------------------------------//

// included libraries
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <ArduinoLogger.h>
#include <SD.h>
#include <SoftwareSerial.h>

#include "../configuration.h"
#include "bluetooth.h"
#include "control.h"
#include "globals.h"
#include "logging.h"
#include "sensors.h"

//////////// Global Var's & Constants ///////////////

/* Set the delay between fresh samples */
const uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

unsigned short chipSelect = ChipSelect;
unsigned short ledPin = LEDPin;
unsigned short state = 0;
unsigned short flag = 0;
SoftwareSerial bluetooth = bluetoothSetup(ledPin, HIGH);
float data[7][3] = {0};
StateMachine stateMachine = StateMachine();

/////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  logger.add(Serial, LOG_LEVEL_VERBOSE);  // This will log everything on Serial
  inf << np << endl;  // Displays an end of line without the prefix (Because of "np")
  verb << "Beginning Setup" << endl;
  imuSetup();
  sdSetup();
  delay(100);
  verb << "Setup Complete" << endl;
  verb << "Beginning Main Loop" << endl;
}

void loop() {
  /* Get new sensor events with the readings */
  pollSensors();
  /* Update the state machine */
  stateMachine.update();
  // verb << bluetooth.read();
}
