// For the register map, see https://www.invensense.com/download-pdf/mpu-9250-register-map/

#define ADO 0
#if ADO
#define MPU9250_ADDRESS             0x69  // Device address when ADO = 1
#else
#define MPU9250_ADDRESS             0x68  // Device address when ADO = 0
#endif
#define AK8963_ADDRESS              0x0C

#define SELF_TEST_X_GYRO            0x00
#define SELF_TEST_Y_GYRO            0x01
#define SELF_TEST_Z_GYRO            0x02
#define SELF_TEST_X_ACCEL           0x0D
#define SELF_TEST_Y_ACCEL           0x0E
#define SELF_TEST_Z_ACCEL           0x0F

#define XG_OFFSET_H                 0x13
#define XG_OFFSET_L                 0x14
#define YG_OFFSET_H                 0x15
#define YG_OFFSET_L                 0x16
#define ZG_OFFSET_H                 0x17
#define ZG_OFFSET_L                 0x18

#define WOM_THR                     0x1F

#define GYRO_CONFIG                 0x1B
#define ACCEL_CONFIG                0x1C
#define ACCEL_CONFIG_2              0x1D

#define GYRO_FULL_SCALE_250_DPS     0x00
#define GYRO_FULL_SCALE_500_DPS     0x08
#define GYRO_FULL_SCALE_1000_DPS    0x10
#define GYRO_FULL_SCALE_2000_DPS    0x18

#define ACC_FULL_SCALE_2_G          0x00
#define ACC_FULL_SCALE_4_G          0x08
#define ACC_FULL_SCALE_8_G          0x10
#define ACC_FULL_SCALE_16_G         0x18

#define MAG_FULL_SCALE_14_BITS      0x00
#define MAG_FULL_SCALE_16_BITS      0x08


#define ACCEL_XOUT_H                0x3B
#define ACCEL_XOUT_L                0x3C
#define ACCEL_YOUT_H                0x3D
#define ACCEL_YOUT_L                0x3E
#define ACCEL_ZOUT_H                0x3F
#define ACCEL_ZOUT_L                0x40
#define TEMP_OUT_H                  0x41
#define TEMP_OUT_L                  0x42
#define GYRO_XOUT_H                 0x43
#define GYRO_XOUT_L                 0x44
#define GYRO_YOUT_H                 0x45
#define GYRO_YOUT_L                 0x46
#define GYRO_ZOUT_H                 0x47
#define GYRO_ZOUT_L                 0x48

#define SIGNAL_PATH_RESET           0x68
#define MOT_DETECT_CTRL             0x69
#define USER_CTRL                   0x6A
#define PWR_MGMT_1                  0x6B
#define PWR_MGMT_2                  0x6C

#define WHO_AM_I                    0x75
#define WHO_AM_I_DEFAULT_RESULT     113

#define XA_OFFSET_H                 0x77
#define XA_OFFSET_L                 0x78
#define YA_OFFSET_H                 0x77
#define YA_OFFSET_L                 0x78
#define ZA_OFFSET_H                 0x77
#define ZA_OFFSET_L                 0x78

#define MAG_XOUT_H                  0x3H
#define MAG_XOUT_L                  0x4H
#define MAG_YOUT_H                  0x5H
#define MAG_YOUT_L                  0x6H
#define MAG_ZOUT_H                  0x7H
#define MAG_ZOUT_L                  0x8H
#define MAG_CNTL                    0x0A

#define PI                          3.14159265359

class MPU9250 {
  public:
    // Constructeurs
    MPU9250();
    MPU9250(uint8_t Ascale, uint8_t Gscale, uint8_t Mscale);

    // Méthodes
    void getImuName();
    void initAK8963();
    void initMPU9250();
    void getAres();
    void getGres();
    void getMres();
    void setAscale(uint8_t);
    void setGscale(uint8_t);
    void setMscale(uint8_t);
    void readAccData(int16_t *);
    void readGyrData(int16_t *);
    void readMagData(int16_t *);

  private:
    // Attributs
    uint8_t imuName;
    float aRes;
    float gRes;
    float mRes;
    uint8_t aScale;
    uint8_t gScale;
    uint8_t mScale;
    int16_t acc_raw[3];
    int16_t gyr_raw[3];
    int16_t mag_raw[3];
    float ax, ay, az, gx, gy, gz, mx, my, mz;
    float tempature;
}
