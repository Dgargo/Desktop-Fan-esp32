#include <Arduino.h>


void debug_print(const char* name_function, const u_int32_t  data_arr[],size_t num_data,const char* data_arr_name[]);

void debug_print(const char* name_function, const float  data_arr[],size_t num_data,const char* data_arr_name[]);

bool check_input_parameters(int number,...);

