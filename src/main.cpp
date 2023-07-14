#include <Arduino.h>

#include "controller/PID_controller.h"
#include "fan/fan_3pin.h"
#include "sensor/bme280.h"
#include <Wire.h>


void setup() {
  
  float coefPid[] = {1,1,1};
  bme280 sensor_one(true,25,40,40,50,1,2);
  PID_controller controller_one(30,3,10,coefPid,3);
  Fan_3pin fan_one(GPIO_NUM_17,LEDC_TIMER_10_BIT,25000,LEDC_TIMER_1,LEDC_CHANNEL_1,GPIO_NUM_16);

}

void loop() {
  // put your main code here, to run repeatedly:
}