#include "MiCS6814_GasSensor.h"
#include "Adafruit_SGP30.h"
#include "waveshare_dust.h"
#include "mbed.h"


Serial pc(USBTX, USBRX);

// Bluetooth connected D1, D0
RawSerial bluetooth(D1, D0, 9600);

// Main LED_RED, Dust sensor led D7
DigitalOut led(LED_RED);

// Initialize i2c pins for communicating with sensors
// Multichannel Gas Sensor
MiCS6814_GasSensor gas1(D14,D15);
// Adafruit SGP30 Gas Sensor
Adafruit_SGP30 gas2(D14,D15);

// Dust sensor analog input
// This sensor might need 10 readings before it settles in
DustSensor dust(A0);

int main()
{
    gas1.initialize();
    gas2.begin();
    gas2.IAQinit();

    ThisThread::sleep_for(500);
    while(1)
    {
        float co_ppm = gas1.getGas(CO);
        gas2.IAQmeasure();
        float co2_ppm = gas2.eCO2;
        float density = dust.readDensity();
        
        bluetooth.printf("CO: %.2f, CO2: %.2f. DustDensity: %.2f\r\n", co_ppm, co2_ppm, density);

        ThisThread::sleep_for(500);
    }
}
