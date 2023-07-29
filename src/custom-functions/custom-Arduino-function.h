#include <Arduino.h>


/**
 * @brief Custom Arduino map function to correctly return float.
 * 
 * @tparam T The template type used for input values of different types.
 * @param value The number to map.
 * @param fromLow The lower bound of the value’s current range.
 * @param fromHigh The upper bound of the value’s current range.
 * @param toLow The lower bound of the value’s target range.
 * @param toHigh The upper bound of the value’s target range.
 * @return float The mapped value.
 */
template <typename T1>
float map_float(float value , T1 fromLow, T1 fromHigh, T1 toLow, T1 toHigh)
{
    return (value - static_cast<float>(fromLow)) * (static_cast<float>(toHigh) - static_cast<float>(toLow)) / (static_cast<float>(fromHigh) - static_cast<float>(fromLow)) + static_cast<float>(toLow);
}

/**
 * @brief Custom Arduino constrain function to correctly return float.
 * 
 * @tparam T The template type used for input values of different types.
 * @param value The number to constrain.
 * @param lower The lower end of the range.
 * @param upper The upper end of the range.
 * @return float The constrained value.
 */
template <typename T2>
float constrain_float(float value, T2 lower , T2 upper)
{
    if(value < static_cast<float>(lower))
    {
        return static_cast<float>(lower);
    }
    else if ( value > static_cast<float>(upper) )
    {
        return static_cast<float>(upper);
    }
    else
    {
        return value;
    }
}