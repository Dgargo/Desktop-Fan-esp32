#ifndef DEBUG_SETTINGS_H
#define DEBUG_SETTINGS_H

#define DEBUG/**< on/off debug mode*/
#endif

#define I2C_SETTINGS_H
//#define SPI_SETTINGS_H

#ifdef I2C_SETTINGS_H
  #define I2C_SET /**< on/off I2C protocol */
#else
  #ifdef SPI_SETTINGS_H
    #define SPI_SET /**< on/off SPI protocol */
  #endif
#endif

