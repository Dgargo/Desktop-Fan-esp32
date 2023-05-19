
#include "debug/debug.h"


/**

*@brief Print information for debugging purposes.
*
*This function allows for the output of information about variables to the serial port,
*which can be useful for further analysis and debugging.

*@param name_function The name of the function where the debug_print function is called.
*@param data_arr An array that contains the values of the variables to output to the port.
*@param num_data The number of variables in the array.
*@param data_arr_name An array of variable names.
*/
void debug_print(const char* name_function, const uint32_t  data_arr[],size_t num_data,const char* data_arr_name[])
{
    Serial.println(name_function);
    for(int i = 0 ;i<num_data;i++)
    {
        Serial.printf("%s : %d \n",data_arr_name[i],data_arr[i]);
    }
    Serial.println("___________________________________"); 
}

void debug_print(const char* name_function, const float data_arr[],size_t num_data,const char* data_arr_name[])
{
    Serial.println(name_function);
    for(int i = 0 ;i<num_data;i++)
    {
        Serial.printf("%s : %f \n",data_arr_name[i],data_arr[i]);
    }
    Serial.println("___________________________________"); 
}

/**
*@brief Check input parameters for validity.
*
*This function validates the input parameters to ensure that they are correct and within the specified range.
*The first and second parameters after the "number" parameter determine the range size,
*with the first parameter indicating the minimum value and the second parameter indicating the maximum value.

*@param number The number of parameters.
*
*@param ... Unlimited number of parameters.
*@return True if all parameters are within the specified range, False otherwise.
*/
bool check_input_parameters(int number,...)
{
  va_list args;
    va_start(args, number);
    int min = va_arg(args, int);
    int max = va_arg(args, int);
    for (int i = 0; i < number-2; i++) 
    {
        int num = va_arg(args, int);
        if (num < min || num > max) 
        {
            va_end(args);
            return false;
        }
    }
    va_end(args);
    return true;
}