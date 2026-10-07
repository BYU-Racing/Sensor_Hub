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

// Calibrate the A2C IMU
int32_t imu_calibrate_a2c();

// Initialize the A2C IMU
int32_t imu_init_a2c();

// Deinitialize the A2C IMU
int32_t imu_deinit_a2c();

// Read processed data from the A2C IMU
int32_t imu_read_a2c(imu_data_t *data);

// Calibrate the BMI IMU
int32_t imu_calibrate_bmi();

// Initialize the BMI IMU
int32_t imu_init_bmi();

// Deinitialize the BMI IMU
int32_t imu_deinit_bmi();

// Read raw data from the BMI IMU
// This function might need to be copied for a2c but not sure yet
int32_t imu_read_raw_bmi(imu_data_t *data);

// Convert raw data to processed data for the BMI IMU
int32_t imu_convert_bmi(imu_data_t *raw_data, imu_data_t *processed_data);
