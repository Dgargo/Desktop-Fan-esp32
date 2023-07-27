#include <task/task.h>
#include <assembly/assembly.h>


#ifdef DS18B20_SET

void task_simple_assembly(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);
    while(true)
    {
        obj->simple_assembly();
        vTaskDelay(TASK_DELAY/portTICK_RATE_MS);
    }
}

void task_advanced_assembly(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);
    while(true)
    {
        obj->advanced_assembly();
        vTaskDelay(TASK_DELAY/portTICK_RATE_MS);
    }
}
#else
void task_simple_smart_assembly(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);
    while(true)
    {
        obj->simple_smart_assembly();
        vTaskDelay(TASK_DELAY/portTICK_RATE_MS);
    }
}

#endif
