#include <Arduino.h>
#include <Wire.h>

#include "controller/PID_controller.h"
#include "fan/fan_3pin.h"
#include "sensor/bme280.h"
#include "assembly/assembly.h"
#include "task/task.h"

//float COEF_PID[] = {COEF_P,COEF_I,COEF_D};

bme280 sensor_one(true,MIN_TEMP_C,MAX_TEMP_C,MIN_TEMP_F,MAX_TEMP_F);

//PID_controller controller_one(CONTROLLER_POINT_SET_UP,RESOLUTION,COEF_PID,DTIME);
controller controller_two(CONTROLLER_POINT_SET_UP,RESOLUTION);

Fan_3pin fan_one(FAN_PWM_PIN,RESOLUTION_FAN,FREQ,TIMER_NUM,CHANNEL_NUM,FAN_RPM_PIN);

//assembly assembly_one(&sensor_one,&controller_one,&fan_one);

assembly assembly_two(&sensor_one,&controller_two,&fan_one);
void setup() {
  
  Serial.begin(115200);

  sensor_one.bme_setup_I2C(BME_ADRESS);

  fan_one.setup_timer();
  fan_one.setup_PWM_channel();
  fan_one.setup_interrupt();
  
  xTaskCreate(task_bme280,"bme280",4096,&assembly_two,1,NULL);
  xTaskCreate(task_controller,"controller",4096,&assembly_two,1,NULL);
  //xTaskCreate(task_PID_controller,"PID controller",4096,&assembly_one,1,NULL);
  xTaskCreate(task_Fan_3pin,"Fan 3 pin",4096,&assembly_two,1,NULL);
 //xTaskCreate(task_simple_smart_assembly,"simple smart assembly",8096,&assembly_one,1,NULL);

  }

void loop() {
}