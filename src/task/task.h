#include <config.h>

#ifdef DS18B20_SET
void task_simple_assembly(void *parameter);

void task_advanced_assembly(void *parameter);
#else
void task_simple_smart_assembly(void *parameter);

void task_IOT_assembly(void *parameter);

void task_bme280(void *parameter);

void task_PID_controller(void *parameter);

void task_Fan_3pin(void *parameter);
#endif
