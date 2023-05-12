
#include "fan.h"
 
Fan::Fan(uint32_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num)
{
    this->fan_pin = fan_pin;
    this->resolution = resolution;
    this->freq = freq;
    this->timer_num = timer_num;
    this->channel_num = channel_num;

    setup_timer();
    setup_PWM_channel();
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
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE,channel_num ,speedPWM));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, channel_num));
}


