#pragma once
#include <Adafruit_BNO055.h>

void imuSetup();
void pollSensors();
void updateValues(sensors_event_t* event, float (&data)[3]);
