#include "bme280.h"
#include "debug/debug.h"
#include <custom-functions/custom-Arduino-function.h>


bme280::bme280()
{
  
}
void bme280 :: set_temp_mode(bool temp_mode)
{
  this->temp_mode = temp_mode;

  #ifdef DEBUG
  Serial.println("set_temp_mode");
  Serial.printf("temp_mode : %d \n",temp_mode);
  Serial.println("______________________________");
  #endif
}

void bme280 :: read_data()
{
    temperatureC = bme.readTemperature();
    temperatureF = 1.8*bme.readTemperature()+32;
    pressure = bme.readPressure()/100.0F;
    humidity = bme.readHumidity();

    #ifdef DEBUG
    Serial.println("read_data from bme280");
    Serial.printf("tempC : %f\n",temperatureC);
    Serial.printf("tempF : %f\n",temperatureF);
    Serial.printf("pressure : %f\n",pressure);
    Serial.printf("humidity : %f\n",humidity);
    Serial.println("_____________________");
    #endif
}

void bme280 ::convert_data()
{
    convert_temperatureC = map_float(temperatureC,0,100,min_tempC,max_tempC);
    convert_temperatureC = constrain_float(convert_temperatureC,0,100);

    convert_temperatureF = map_float(temperatureF,0,100,min_tempF,max_tempF);
    convert_temperatureF = constrain_float(convert_temperatureF,0,100);

    #ifdef DEBUG
    Serial.println("convert_data from ds18b20");
    Serial.printf("convert tempC : %f\n",convert_temperatureC);
    Serial.printf("convert tempF : %f\n",convert_temperatureF);
    Serial.println("_____________________");
    #endif
}

void bme280 :: send_data(xQueueHandle xData_sensor_queue)
{
     portBASE_TYPE xStatus;

    if(temp_mode)
    {
      xStatus = xQueueSendToBack(xData_sensor_queue,&convert_temperatureC,1000/portTICK_RATE_MS);
    }
    else
    {
      xStatus = xQueueSendToBack(xData_sensor_queue,&convert_temperatureF,1000/portTICK_RATE_MS);
    }
    if(xStatus != pdPASS)
      {
        Serial.println("Could not send to the queue");
      }
}
#ifdef I2C_SET
bme280 :: bme280(bool temp_mode,int32_t min_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF)
{
    this->temp_mode = temp_mode;
    this->min_tempC = min_tempC;
    this->max_tempC = max_tempC;
    this->min_tempF = min_tempC;
    this->max_tempF = max_tempF;
    Wire.begin();
    bool status;
    status = bme.begin(0x76);
    if(!status)
    {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (true);
    }
    #ifdef DEBUG
      const uint32_t data_arr[] = {(uint32_t)min_tempC,(uint32_t)max_tempC,(uint32_t)min_tempF,(uint32_t)max_tempF};
      size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
      const char* data_arr_name[] ={"min_tempC","max_tempC","min_tempF","max_tempF"}; 
      debug_print("bme280 construct",data_arr,num_data,data_arr_name);
    #endif
}
#endif

#ifdef SPI_SET
bme280 :: bme280(int8_t CS,bool temp_mode,int32_t mix_tempC ,int32_t max_tempC ,int32_t min_tempF ,int32_t max_tempF)
{
    this->temp_mode = temp_mode;
    this->min_tempC = min_tempC;
    this->max_tempC = max_tempC;
    this->min_tempF = min_tempC;
    this->max_tempF = max_tempF;
    bme.begin(CS);

    #ifdef DEBUG
      const uint32_t data_arr[] = {(uint32_t)min_tempC,(uint32_t)max_tempC,(uint32_t)min_tempF,(uint32_t)max_tempF};
      size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
      const char* data_arr_name[] ={"min_tempC","max_tempC","min_tempF","max_tempF"}; 
      debug_print("ds18b20 construct",data_arr,num_data,data_arr_name);
    #endif
}
#endif

bme280 :: ~bme280()
{
  
}