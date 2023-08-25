# Desktop-Fan-esp32
This is a project of a tabletop portable fan.It is built using Object-Oriented Programming (OOP) principles and can be assembled in various configurations, utilizing different assembly types with a variety of sensors, control methods, and fans. Key features:

* Automatic fan speed adjustment based on sensor data
* Fan speed measurement using tachometer signal
* Temperature measurement using DS18B20
* Ambient parameter measurement using BME280: temperature, humidity, pressure
* Support of MQTT(under development)
* Application for displaying and controlling fan data(under development)
* LCD display for showing status information(under development)
* Parameter control adjustment via encoder(under development)

## Schematic(not final version)
![Simple](https://github.com/Dgargo/Desktop-Fan-esp32/assets/54078972/6481fdf6-6b7c-4313-ac16-57b11db092df)

## Part list
|   Parts    |           Description          |
| ---------- | ------------------------------ |
|   ESP32    |  ESP32 WROOM DevKit v1 38 Pin  |
|   BME280   |     3.3V with I2C and SPI      |
|   DS18B20  |                                |
|    Fan     |           12V 4pin             |
|   TP4056   | Type-C with battery protection function |
|   XL6009   | DC-DC step-up converter from 3-32V to 5-35V |
| NRC18650b  | Li-Ion 3400mah ,3.7V (2.75-4.2V) |

