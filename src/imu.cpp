#include "imu.h"

// Global variables for IMU data
imu_data_t *imu_data_raw_bmi;
imu_data_t *imu_data_bmi;
imu_data_t *imu_data_a2c;

int32_t imu_init_a2c()
{   // Initialize the A2C IMU
    imu_data_a2c = (imu_data_t *)malloc(sizeof(imu_data_t));
    if (imu_data_a2c == NULL)
    {   // Check if memory allocation was successful
        printf("Error: IMU_INIT_A2C");
        return 1;
    }
    return 0; // Return 0 if successful
}

int32_t imu_deinit_a2c() 
{   // Deinitialize the A2C IMU
    free(imu_data_a2c);
    return 0; // Return 0 if successful
}

int32_t imu_init_bmi()
{   // Initialize the BMI IMU
    imu_data_raw_bmi = (imu_data_t *)malloc(sizeof(imu_data_t));
    imu_data_bmi = (imu_data_t *)malloc(sizeof(imu_data_t));
    if (imu_data_raw_bmi == NULL || imu_data_bmi == NULL)
    {   // check if memory allocation was successful
        printf("Error: IMU_INIT_BMI");
        return 1;
    }
    return 0; // Return 0 if successful
}

int32_t imu_deinit_bmi()
{   // Deinitialize the BMI IMU
    free(imu_data_raw_bmi);
    free(imu_data_bmi);
    return 0; // Return 0 if successful
}