#include <Arduino.h>

class sensor {
public:
    virtual void read_data(); 
    virtual void convert_data();
    virtual void send_data(xQueueHandle xData_sensor_queue); 
};