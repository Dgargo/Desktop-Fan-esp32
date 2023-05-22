#include "ds18b20.h"


void ds18b20 :: ds18b20_setup()
{
    temp_sensor.begin();
    temp_sensor.setResolution(12);
}

void ds18b20 :: read_data()
{
  if (temp_sensor.requestTemperatures() != 1)
  {
  Serial.println("Error: Failed to retrieve temperature from sensor.");
  return;
  }
  temperatureC = temp_sensor.getTempCByIndex(0);
  temperatureF = temp_sensor.getTempFByIndex(0);
}

void ds18b20 :: convert_data()
{
    convert_temperatureC = map(temperatureC,0,100,min_tempC,max_tempC);
    convert_temperatureC = constrain(convert_temperatureC,0,100);
    convert_temperatureF = map(temperatureF,0,100,min_tempF,max_tempF);
    convert_temperatureF = constrain(convert_temperatureF,0,100);
}
void ds18b20 :: send_data(xQueueHandle xData_sensor_queue)
{
  portBASE_TYPE xStatus;

    if(temp_mode)
    {
      xStatus = xQueueSendToBack(xData_sensor_queue,&temperatureC,1000/portTICK_RATE_MS);
    }
    else
    {
      xStatus = xQueueSendToBack(xData_sensor_queue,&temperatureF,1000/portTICK_RATE_MS);
    }

    if(xStatus != pdPASS)
      {
        Serial.println("Could not send to the queue");
      }
}
void ds18b20 :: set_temp_mode(bool temp_mode)
{
  this->temp_mode = temp_mode;
}

ds18b20 :: ds18b20(int sensor_pin,bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF):one_wire(sensor_pin),temp_sensor(&one_wire) 
{
 this->temp_mode = temp_mode;
 this->min_tempC = min_tempC;
 this->max_tempC = max_tempC;
 this->min_tempF = min_tempC;
 this->max_tempF = max_tempF;
 ds18b20_setup();
}

ds18b20 :: ~ds18b20()
{

} 



