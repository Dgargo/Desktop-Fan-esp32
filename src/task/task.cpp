#include <task/task.h>
#include <assembly/assembly.h>


#ifdef DS18B20_SET
/**
 * @brief Task for running a simple assembly.
 * 
 * @param parameter A pointer to an `assembly` object passed as a task parameter.
 * 
 * 
 * @note Ensure that the `assembly` object passed as a parameter is properly initialized and contains valid data before starting this task. 
 */
void task_simple_assembly(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);
    while(true)
    {
        obj->simple_assembly();
        vTaskDelay(TASK_DELAY/portTICK_RATE_MS);
    }
}
/**
 * @brief Task for running a advanced assembly.
 * 
 * @param parameter A pointer to an `assembly` object passed as a task parameter.
 * 
 * 
 * @note Ensure that the `assembly` object passed as a parameter is properly initialized and contains valid data before starting this task. 
 */
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
/**
 * @brief Task for running a simple  smart assembly.
 * 
 * @param parameter A pointer to an `assembly` object passed as a task parameter.
 * 
 * 
 * @note Ensure that the `assembly` object passed as a parameter is properly initialized and contains valid data before starting this task. 
 */
void task_simple_smart_assembly(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);
    while(true)
    {
        obj->simple_smart_assembly();
        vTaskDelay(TASK_DELAY/portTICK_RATE_MS);
    }
}

/**
 * @brief Task for running a bme280 assembly.
 * 
 * @param parameter A pointer to an `assembly` object passed as a task parameter.
 * 
 * 
 * @note Ensure that the `assembly` object passed as a parameter is properly initialized and contains valid data before starting this task. 
 */
void task_bme280(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);

    while(true)
    {
        obj->bme280_assembly();
        vTaskDelay(TASK_DELAY/portTICK_RATE_MS);
    }
}

/**
 * @brief Task for running a controller assembly.
 * 
 * @param parameter A pointer to an `assembly` object passed as a task parameter.
 * 
 * 
 * @note Ensure that the `assembly` object passed as a parameter is properly initialized and contains valid data before starting this task. 
 */
void task_controller(void *parameter)
{
  assembly* obj = static_cast<assembly*>(parameter);
  while (true)
  {
    obj->controller_assembly();
    vTaskDelay(TASK_COTROLLER_DELAY/portTICK_RATE_MS);
  }
    
}
/**
 * @brief Task for running a PID controller assembly.
 * 
 * @param parameter A pointer to an `assembly` object passed as a task parameter.
 * 
 * 
 * @note Ensure that the `assembly` object passed as a parameter is properly initialized and contains valid data before starting this task. 
 */
void task_PID_controller(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);
    while(true)
    {
        obj->PID_controller_assembly();
        vTaskDelay(TASK_COTROLLER_DELAY/portTICK_RATE_MS);
    }
}
/**
 * @brief Task for running a Fan 3pin assembly.
 * 
 * @param parameter A pointer to an `assembly` object passed as a task parameter.
 * 
 * 
 * @note Ensure that the `assembly` object passed as a parameter is properly initialized and contains valid data before starting this task. 
 */
void task_Fan_3pin(void *parameter)
{
    assembly* obj = static_cast<assembly*>(parameter);
    while(true)
    {
        obj->Fan3pin_assembly();
        vTaskDelay(TASK_DELAY/portTICK_RATE_MS);
    }
}
#endif
