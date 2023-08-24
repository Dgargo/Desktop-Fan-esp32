#include "fan_3pin.h"
#include "config.h"

uint32_t Fan_3pin::counter_tacho;

Fan_3pin :: Fan_3pin(gpio_num_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num,gpio_num_t tacho_pin ): Fan(fan_pin,resolution,freq,timer_num,channel_num)
{
 this->tacho_pin=tacho_pin;
 
 #ifdef DEBUG
 Serial.println("fan3_pin construct");
 Serial.printf("tacho_pin %d \n",tacho_pin);
 Serial.println("_____________________________");
 #endif 
}

Fan_3pin ::Fan_3pin()
{
  
}
void  IRAM_ATTR Fan_3pin :: Intr_Handler_tacho(void *args)
{
   counter_tacho++;
}

Fan_3pin ::~Fan_3pin()
{
}


void Fan_3pin :: setup_interrupt()
{
  gpio_set_intr_type(tacho_pin,GPIO_INTR_POSEDGE);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(tacho_pin,Intr_Handler_tacho,NULL);
}

uint32_t Fan_3pin :: calculate_RPM()
{
    #ifdef DEBUG
    const uint32_t data_arr[] = {RPM,counter_tacho};
    size_t num_data = sizeof(data_arr) / sizeof(data_arr[0]);
    const char* data_arr_name[] ={"RPM","counter_tacho"}; 
    debug_print("calculate_RPM",data_arr,num_data,data_arr_name);
    #endif
    RPM = counter_tacho * 30 ;
    counter_tacho=0;
    return RPM;
}