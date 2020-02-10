#include "MMA8652.h"
#include "MiCS6814_GasSensor.h"
#include "mbed.h"


Serial pc(USBTX, USBRX);
RawSerial bluetooth(D1, D0, 9600);
DigitalOut led(LED_RED);

// Initialize i2c pins for communicating with sensors
MMA8652 mma8652(D14,D15);
// MiCS6814_GasSensor gas_sensor(D14,D15);

int main()
{
    mma8652.MMA8652_config();

    gas_sensor.initialize();
    
    float accel_data[3];

    printf("Begin reading data from accelerometer...\r\n\r\n");
    ThisThread::sleep_for(500);
    while(1)
    {
        printf("Acceleration Data:\r\n");
        mma8652.acquire_MMA8652_data_g(accel_data);
        printf("%4.2f,\t%4.2f,\t%4.2f,\t\r\n\r\n", accel_data[0], accel_data[1], accel_data[2]);

    
        printf("CO PPM:\r\n");
        float co_ppm = gas_sensor.getGas(CO);
        printf("%.2f\r\n", co_ppm);

        bluetooth.printf("%.2f\r\n", co_ppm);
        

        ThisThread::sleep_for(500);
    }
}
