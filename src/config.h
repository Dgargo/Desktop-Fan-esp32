#ifndef DEBUG_SETTINGS_H
#define DEBUG_SETTINGS_H

#define DEBUG/**< on/off debug mode*/
#endif

#define I2C_SETTINGS_H
//#define SPI_SETTINGS_H
//#define DS18B20_SETTINGS_H

#ifdef I2C_SETTINGS_H
  #define I2C_SET /**< on/off I2C protocol */

  #define SDA_PIN GPIO_NUM_21
  #define SCL_PIN GPIO_NUM_22
#elif defined(SPI_SETTINGS_H)
  #define SPI_SET /**< on/off SPI protocol */

  #define SPI_PIN GPIO_NUM_18
  #define MISO_PIN GPIO_NUM_19
  #define MOSI_PIN GPIO_NUM_23
  #define CS_PIN GPIO_NUM_5
#elif DS18B20_SETTINGS_H
  #define DS18B20_SET /**< on/off DS18B20 protocol */

  #define DS18B20_PIN GPIO_NUM_32
#else
  #error "Please select a valid sensor mode"
#endif


#define FAN_PWM_PIN GPIO_NUM_17

#define FAN_RPM_PIN GPIO_NUM_16

#define DS18b20_NUM_PARAMETER 1

#define BME280_NUM_PARAMETERS 3

#define CONTROLLE_PARAMETER_SENSOR_SET_UP = 50;

