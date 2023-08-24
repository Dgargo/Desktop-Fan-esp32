#ifndef DEBUG_SETTINGS_H
#define DEBUG_SETTINGS_H

#define DEBUG/**< on/off debug mode*/
#endif

//-------------------- MAIN -------------------------
#define LENGTH_ARRAY_DATA 3

//-------------------- SENSOR -----------------------

#define CELSIUS_MODE 1

#define FAHRENHEIT_MODE 0

#define MIN_TEMP_C 15

#define MAX_TEMP_C 35

#define MIN_TEMP_F 68

#define MAX_TEMP_F 140


#define I2C_SETTINGS_H
//#define SPI_SETTINGS_H
//#define DS18B20_SETTINGS_H

#ifdef I2C_SETTINGS_H
  #define I2C_SET /**< on/off I2C protocol */

  #define BME_ADRESS 0x76

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


//-------------------------- CONTROLLER ------------

#define CONTROLLER_POINT_SET_UP  30

#define RESOLUTION 10

#define DTIME 5

#define COEF_P 1.0

#define COEF_I 0.1

#define COEF_D 0.01

//----------------- FAN -------------------------

#define FAN_PWM_PIN GPIO_NUM_17

#define FAN_RPM_PIN GPIO_NUM_16

#define RESOLUTION_FAN LEDC_TIMER_10_BIT

#define FREQ 25000

#define TIMER_NUM LEDC_TIMER_1

#define CHANNEL_NUM LEDC_CHANNEL_1

//-------------------------- TASK CONFIG -----------------------------------------
#define TASK_DELAY 5000

#define TASK_COTROLLER_DELAY 10000



