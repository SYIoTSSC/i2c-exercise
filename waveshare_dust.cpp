#include "mbed.h"
#include "waveshare_dust.h"

// DustSensor::DustSensor(PinName analog, PinName led) : d_analog(analog), d_led(led) {
//     flag_first = true;
//     sum = 0;
// }

DustSensor::DustSensor(PinName analog) : d_analog(analog) {
    flag_first = true;
    sum = 0;
}

float DustSensor::readDensity() {
    // d_led = 1;
    voltage = d_analog.read() * 3300 * 11;
    
    if(flag_first)
    {
        flag_first = false;

        for(int i = 0; i < BUFFER_MAX; ++i)
        {
            buffer[i] = voltage;
            sum += buffer[i];
        }
        
        mean_voltage = (float)voltage;
    }
    else
    {
        sum -= buffer[0];
        for(int i = 0; i < (BUFFER_MAX - 1); ++i)
        {
            buffer[i] = buffer[i + 1];
        }
        buffer[9] = voltage;
        sum += buffer[9];
        
        mean_voltage = sum / 10.0;
    }

    float density;
    if(mean_voltage >= NO_DUST_VOLTAGE)
    {
        mean_voltage -= NO_DUST_VOLTAGE;
        
        density = mean_voltage * COV_RATIO;
    }
    else
        density = 0;

    // d_led = 0;
    return density;
}