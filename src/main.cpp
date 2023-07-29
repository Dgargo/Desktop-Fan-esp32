#include <Arduino.h>
#include <Wire.h>

#include "controller/PID_controller.h"
#include "fan/fan_3pin.h"
#include "sensor/bme280.h"
#include "assembly/assembly.h"
#include "task/task.h"

xQueueHandle sensor_queue_one;
xQueueHandle controller_queue_one;


float coefPid[] = {5,3,3};
//bme280 sensor_one(true,20,50,40,100);
PID_controller controller_one(30,10,coefPid,3);
Fan_3pin fan_one(GPIO_NUM_17,LEDC_TIMER_10_BIT,25000,LEDC_TIMER_1,LEDC_CHANNEL_1,GPIO_NUM_16);
Fan fan_two(GPIO_NUM_17,LEDC_TIMER_10_BIT,25000,LEDC_TIMER_1,LEDC_CHANNEL_1);
//assembly assembly_one(&sensor_one,&controller_one,&fan_one,sensor_queue_one,controller_queue_one);
void setup() {
  
  Serial.begin(115200);
  sensor_queue_one = xQueueCreate(20,sizeof(float));
  controller_queue_one = xQueueCreate(20,sizeof(float));
  Serial.println(controller_one.get_maxPWM());
  fan_one.show_debug_construct();
  fan_two.show_debug_construct();
  //sensor_one.read_data();
  /*
  
  Serial.println("start assembly");
  Serial.println("end assemby");
  assembly_one.assembly_check();
  
  assembly_one.simple_smart_assembly();
  */
 

  //xTaskCreate(task_simple_smart_assembly,"simple smart assembly",20000,&assembly_one,1,NULL);
  }

void loop() {
}