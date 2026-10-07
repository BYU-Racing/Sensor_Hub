#pragma once
#include <Arduino.h>
#include <stdlib.h>

typedef struct {
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
} imu_data_t;

// Calibrate the IMU
int32_t imu_calibrate();

// Initialize the IMU
int32_t imu_init();

// Deinitialize the IMU
int32_t imu_deinit();

// Read processed data from the IMU
int32_t imu_read(imu_data_t *data);

// Read raw data from the IMU
// I'm not sure if we will get raw data or processed data from the IMU, so I will leave this function here for now.
int32_t imu_read_raw(imu_data_t *data);

// Convert raw data to processed data
int32_t imu_convert(imu_data_t *raw_data, imu_data_t *processed_data);
