#include "sensors.h"
//#define TINY_BME280_SPI
//#include <TinyBME280.h>

#include "ArduinoLogger.h"
#include "globals.h"
#include "logging.h"
// tiny::BME280 barometer;

void imuSetup() {
  verb << "Initializing IMU" << endl;
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    err << "Ooops, no BNO055 detected, Check your wiring or I2C ADDR!" << endl;

    while (1) {
      errorCode(0);
    }
  }

  delay(1000);
  verb << "IMU Initialization Complete" << endl;
  return;
}

void pollSensors() {
  // A function to take data from the IMU and log it to an array

  sensors_event_t orientationData, angVelocityData, linearAccelData, magnetometerData,
      accelerometerData, gravityData;

  //  float temp = barometer.readFixedTempC();
  //  float hum = barometer.readFixedHumidity();
  //  float pres = barometer.readFixedPressure();

  // get data
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);

  // save data by passing array from matrix
  updateValues(&orientationData, data[0]);
  updateValues(&angVelocityData, data[1]);
  updateValues(&linearAccelData, data[2]);
  updateValues(&magnetometerData, data[3]);
  updateValues(&accelerometerData, data[4]);
  updateValues(&gravityData, data[5]);
}

// Take data row and append values based on which event type it is
void updateValues(sensors_event_t* event, float (&data)[3]) {
  switch (event->type) {
    case SENSOR_TYPE_ACCELEROMETER:
      // Serial.print("Accl:");
      data[0] = event->acceleration.x;
      data[1] = event->acceleration.y;
      data[2] = event->acceleration.z;
      break;

    case SENSOR_TYPE_ORIENTATION:
      // Serial.print("Orient:");
      data[0] = event->orientation.x;
      data[1] = event->orientation.y;
      data[2] = event->orientation.z;
      break;

    case SENSOR_TYPE_MAGNETIC_FIELD:
      // Serial.print("Mag:");
      data[0] = event->magnetic.x;
      data[1] = event->magnetic.y;
      data[2] = event->magnetic.z;

      break;

    case SENSOR_TYPE_GYROSCOPE:
      // Serial.print("Gyro:");
      data[0] = event->gyro.x;
      data[1] = event->gyro.y;
      data[2] = event->gyro.z;

      break;

    case SENSOR_TYPE_ROTATION_VECTOR:
      // Serial.print("Rot:");
      data[0] = event->gyro.x;
      data[1] = event->gyro.y;
      data[2] = event->gyro.z;

      break;

    case SENSOR_TYPE_LINEAR_ACCELERATION:
      // Serial.print("Linear:");
      data[0] = event->acceleration.x;
      data[1] = event->acceleration.y;
      data[2] = event->acceleration.z;

      break;

    default:
      // Serial.print("Unk:");
      break;
  }
}
