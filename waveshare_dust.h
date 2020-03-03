
#ifndef WAVESHARE_DUST_H
#define WAVESHARE_DUST_H

#include "mbed.h"

#define        COV_RATIO                       0.2            //ug/mmm / mv
#define        NO_DUST_VOLTAGE                 500            //mv  
#define        BUFFER_MAX                      10 

class DustSensor
{
public:
    // DustSensor(PinName analog, PinName led);
    DustSensor(PinName analog);
    float mean_voltage;
    int voltage;
    float readDensity();
    
private:
    bool flag_first;
    int buffer[BUFFER_MAX], sum;
    AnalogIn d_analog;
    // DigitalOut d_led;
    
};

#endif