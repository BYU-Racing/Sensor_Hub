#include "imu.h"


imu_data_t *imu_data_raw;
imu_data_t *imu_data;

int32_t imu_calibrate()
{
    return 0;
}

int32_t imu_init()
{
    imu_data_raw = (imu_data_t *)malloc(sizeof(imu_data_t));
    imu_data = (imu_data_t *)malloc(sizeof(imu_data_t));
    if (!imu_data_raw)
    {
        printf("Error IMU_INIT: Failed to allocate memory for raw IMU data\n");
        return 1;
    }
    if (!imu_data)
    {
        printf("Error IMU_INIT: Failed to allocate memory for processed IMU data\n");
        free(imu_data_raw);
        return 1;
    }
    return 0;
}

int32_t imu_deinit()
{
    free(imu_data_raw);
    free(imu_data);
    return 0;
}

int32_t imu_read(imu_data_t *data)
{   // Read processed data from the IMU

    
    
    
    return 0;
}

