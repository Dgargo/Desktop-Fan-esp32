#include "fan.h"


class Fan_3pin : public Fan
{
/**
 * @brief Class members
 * @{
 */
private:
    gpio_num_t tacho_pin;/**< pin tachometer sensor fan*/
    static uint32_t counter_tacho;/**< variable counter interrupt from the tachometer sensor*/
    uint32_t RPM;/**< round per minute*/
/**@}*/
public:
    /**
     * @brief Construct a new Fan_3pin object
     * 
     * @param fan_pin  pin control fan
     * @param resolution LEDC channel duty resolution
     * @param freq LEDC timer frequency (Hz)
     * @param timer_num The timer source of channel
     * @param channel_num LEDC channel
     * @param tacho_pin pin tachometer sensor fan
     * 
     * @note Additionally, it calls the setup_interrupt() method to configure the interrupt handling for the tachometer sensor.
     */
    Fan_3pin(gpio_num_t fan_pin, ledc_timer_bit_t resolution, uint32_t freq, ledc_timer_t timer_num, ledc_channel_t channel_num,gpio_num_t tacho_pin );
    
    /**
     * @brief Destroy the Fan_3pin object
     * 
     */
    ~Fan_3pin();
    
    /**
     * @brief Handler for processing interrupt from the tachometer senso
     * 
     * This static method is the interrupt handler function responsible for processing interrupts from the tachometer sensor.
     * It is called whenever an interrupt is triggered by the sensor.
     * 
     * @param args  is a pointer to additional arguments or the context of the interrupt handler.
     */
    static void IRAM_ATTR Intr_Handler_tacho(void *args);

    /**
     * @brief Set up the interrupt object for handling interrupts.
     * 
     * This method initializes and configures the interrupt object for handling interrupts from the sensor.
     * 
     * @note This method needs to be called before enabling interrupts for the sensor.
     */
    void setup_interrupt();

    /**
     * @brief Calculate revolutions per minute (RPM) based on sensor readings.
     * 
     * @return The calculated RPM value.
     */
    uint32_t calculate_RPM();
};



