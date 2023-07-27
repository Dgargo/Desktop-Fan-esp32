
#include "fan.h"
#include "debug/debug.h"
#include "config.h"
Fan::Fan(gpio_num_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num)
{
    this->fan_pin = fan_pin;
    this->resolution = resolution;
    this->freq = freq;
    this->timer_num = timer_num;
    this->channel_num = channel_num;
    debug_costruct = true;
    set_state(true);
    setup_timer();
    setup_PWM_channel();
    #ifdef DEBUG
    Serial.println("Debug construct fan");
    Serial.printf("fan_pin : %d \n",fan_pin);
    Serial.printf("ledc_timer_bit_t: %d\n",resolution);
    Serial.printf("freq: %d\n",freq);
    Serial.printf("timer_num %d\n",timer_num);
    Serial.printf("channel_num %d\n",channel_num);
    Serial.println("______________________________");
    #endif
    
}
Fan:: Fan()
{
    debug_costruct = false;
}
Fan::~Fan()
{
}
void Fan::set_state(bool new_state)
{
    state= new_state;
    digitalWrite(fan_pin,state);
}

void Fan::setup_timer()
{
    ledc_timer_config_t ledc_timer =
    {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = resolution,
        .timer_num        = timer_num,
        .freq_hz          = freq,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
}

void Fan::setup_PWM_channel()
{
    uint32_t duty_value = (1 << resolution) - 1;
    ledc_channel_config_t ledc_channel = 
    {
        .gpio_num       = fan_pin,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = channel_num,
        .timer_sel      = timer_num,
        .duty           = duty_value,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void Fan::change_speed()
{
    #ifdef DEBUG
    Serial.println("before change_speed");
    Serial.printf("speedPWM %d\n",speedPWM);
    Serial.println("______________________");
    #endif

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE,channel_num ,speedPWM));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, channel_num));

    #ifdef DEBUG
    Serial.println("after change_speed");
    Serial.printf("speedPWM %d\n",speedPWM);
    Serial.println("______________________");
    #endif
}


void Fan::set_speed(uint32_t speedPWM)
{
    this->speedPWM=speedPWM;
}

bool Fan::get_debug_construct()
{
    return debug_costruct;
}

void Fan::show_debug_construct()
{
    Serial.printf("debug construct for Fan : %d",debug_costruct);
}

