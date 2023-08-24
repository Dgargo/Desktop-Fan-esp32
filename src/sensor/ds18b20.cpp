#include "ds18b20.h"
#include "config.h"
#include "debug/debug.h"
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

  #ifdef DEBUG
  Serial.println("read_data from ds18b20");
  Serial.printf("tempC : %f\n",temperatureC);
  Serial.printf("tempF : %f\n",temperatureF);
  Serial.println("_____________________");
  #endif
}

void ds18b20 :: convert_data()
{
    convert_temperatureC = map(temperatureC,0,100,min_tempC,max_tempC);
    convert_temperatureC = constrain(convert_temperatureC,0,100);
    convert_temperatureF = map(temperatureF,0,100,min_tempF,max_tempF);
    convert_temperatureF = constrain(convert_temperatureF,0,100);

    #ifdef DEBUG
    Serial.println("convert_data from ds18b20");
    Serial.printf("convert tempC : %f\n",convert_temperatureC);
    Serial.printf("convert tempF : %f\n",convert_temperatureF);
    Serial.println("_____________________");
    #endif
}
float ds18b20 :: send_data()
{
    float data;
    if(convert_temperatureC <-20 || convert_temperatureC> 300)
    {
      Serial.println("YOUR SENSOR IS BREAK ,CHECK IT");
    }
    if(temp_mode)
    {
      data = convert_temperatureC;
    }
    else
    {
      data = convert_temperatureF;
    }

    return data;
}
void ds18b20 :: set_temp_mode(bool temp_mode)
{
  this->temp_mode = temp_mode;

  #ifdef DEBUG
  Serial.println("set_temp_mode");
  Serial.printf("temp_mode : %d \n",temp_mode);
  Serial.println("______________________________");
  #endif
}

ds18b20 :: ds18b20(int sensor_pin,bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF):one_wire(sensor_pin),temp_sensor(&one_wire) 
{
 this->temp_mode = temp_mode;
 this->min_tempC = min_tempC;
 this->max_tempC = max_tempC;
 this->min_tempF = min_tempC;
 this->max_tempF = max_tempF;

 #ifdef DEBUG
 const uint32_t data_arr[] = {(uint32_t)min_tempC,(uint32_t)max_tempC,(uint32_t)min_tempF,(uint32_t)max_tempF};
 size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
 const char* data_arr_name[] ={"min_tempC","max_tempC","min_tempF","max_tempF"}; 
 debug_print("ds18b20 construct",data_arr,num_data,data_arr_name);
 #endif
}

ds18b20 :: ~ds18b20()
{

} 



