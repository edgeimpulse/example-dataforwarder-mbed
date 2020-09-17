#include "mbed.h"
#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_gyro.h"

static int64_t sampling_freq = 104; // in Hz.
static int64_t time_between_samples_us = (1000000 / (sampling_freq - 1));

int main()
{
    int16_t pDataXYZ[3] = {0};
    float gDataXYZ[3] = {0};

    BSP_ACCELERO_Init();
    BSP_GYRO_Init();

    // Keep a timer to check when next tick should be
    Timer t;
    t.start();

    while (1) {
        int64_t next_tick = t.read_us() + time_between_samples_us;

        BSP_ACCELERO_AccGetXYZ(pDataXYZ);
        BSP_GYRO_GetXYZ(gDataXYZ);
        printf("%f\t%f\t%f\t%f\t%f\t%f\n",
            static_cast<float>(pDataXYZ[0]) / 100.0f,
            static_cast<float>(pDataXYZ[1]) / 100.0f,
            static_cast<float>(pDataXYZ[2]) / 100.0f,
            gDataXYZ[0] / 10000.0f,
            gDataXYZ[1] / 10000.0f,
            gDataXYZ[2] / 10000.0f);

        while (t.read_us() < next_tick) {
            /* busy loop */
        }
    }
}
