
#include "fan.h"

/**
 * @brief Construct a new Fan:: Fan object
 * 
 * @param fan_pin[in]  pin control fan
 * @param resolution[in] LEDC channel duty resolution
 * @param timer_num[in]  The timer source of channel
 * @param channel_num[in]  LEDC channel
 */
Fan::Fan(uint32_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num)
{
    this->fan_pin = fan_pin;
    this->resolution = resolution;
    this->freq = freq;
    this->timer_num = timer_num;
    this->channel_num = channel_num;

    setup_timer(timer_num, resolution, freq);
    setup_PWM_channel(fan_pin, timer_num, channel_num, resolution);
}

/**
 * @brief Destroy the Fan:: Fan object
 * 
 */
Fan::~Fan()
{
}
/**
* @brief on/of fan
* 
* @param state[in]  true-on fan , false-off fan
* @param fan_pin  pin control fan
*/
void Fan::state_fan(bool state,uint8_t fan_pin)
{
    digitalWrite(fan_pin,state);
}

/**
* @brief Configuration parameters of LEDC Timer timer for PWM channel
* 
* @param timer_num[in]  The timer source of channel 
* @param resolution[in] LEDC channel duty resolution
* @param freq[in] LEDC timer frequency (Hz)
*/

void Fan::setup_timer(ledc_timer_t timer_num,ledc_timer_bit_t resolution,uint32_t freq )
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
/**
* @brief Set the up PWM channel 
* 
* @param fan_pin[in] pin control fan
* @param timer_num[in]  The timer source of channel 
* @param channel_num[in] LEDC channel  
* @param resolution[in] LEDC channel duty resolution
*/
void Fan::setup_PWM_channel(uint8_t fan_pin,ledc_timer_t timer_num,ledc_channel_t channel_num,ledc_timer_bit_t resolution )
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
/**
* @brief Change speed fan 
* 
* @param channel_num[in] LEDC channel 
* @param speedPWM[in]  speed in PWM value
*/
void Fan::change_speed(ledc_channel_t channel_num,uint32_t speedPWM)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE,channel_num ,speedPWM));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, channel_num));
}


