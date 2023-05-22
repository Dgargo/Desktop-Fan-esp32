#include <Arduino.h>

#include "controller/PID_controller.h"
#include "fan/fan.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

void setup() {
  Fan fan1(GPIO_NUM_22,LEDC_TIMER_10_BIT,25000,LEDC_TIMER_1,LEDC_CHANNEL_1);
  fan1.set_state(false);
}

void loop() {
  // put your main code here, to run repeatedly:
}