#include "Arduino.h"
#include "ArduI2C.h"
#include "MPU9250.h"


MPU9250::MPU9250() : aScale(ACC_FULL_SCALE_2_G), gScale(GYRO_FULL_SCALE_250_DPS), mSCale(MAG_FULL_SCALE_14_BITS) {
}

MPU9250::MPU9250(uint8_t Ascale, uint8_t Gscale, uint8_t Mscale) : aScale(Ascale), gScale(Gscale), mSCale(Mscale) {
}

void MPU9250::getImuName() {
  // Lecture du registre who am I, par défaut réponse = 113
  imuName = I2CreadByte(MPU9250_ADDRESS, WHO_AM_I);
}

void MPU9250::setAscale(uint8_t accScale) {
  // Lecture de l'octet correspondant à la configuration de l'accéléromètre
  uint8_t c = I2CreadByte(MPU9250_ADDRESS, ACCEL_CONFIG);
  // On remplace les bits de configuration (3 et 4) par ceux de accScale
  c = c | accScale << 3;
  I2CwriteByte(MPU9250_ADDRESS, ACCEL_CONFIG, c);
}

void MPU9250::setGscale(uint8_t gyrScale) {
  // Lecture de l'octet correspondant à la configuration du gyromètre
  uint8_t c = I2CreadByte(MPU9250_ADDRESS, GYRO_CONFIG);
  // On remplace les bits de configuration (3 et 4) par ceux de gyrScale
  c = c | gyrScale << 3;
  I2CwriteByte(MPU9250_ADDRESS, GYRO_CONFIG, c);
}

void MPU9250::setMscale(uint8_t magScale) {
  // Lecture de l'octet correspondant à la configuration du magnétomètre
  uint8_t c = I2CreadByte(MPU9250_ADDRESS, MAG_CNTL);
  // On remplace le bit de configuration (5) par celui de magScale
  c = c | magScale << 4;
  I2CwriteByte(MPU9250_ADDRESS, MAG_CNTL, c);
}

MPU9250::getAres() {
  switch (aScale)
  {
    // La résolution de l'accéléromètre est codée sur 2 bits avec comme valeur possible :
    // 2g (00), 4g (01), 8g (10), et 16g (11).
    // On divise oar 32768 (2^(16-1)) car la mesure est codée sur 16 bits (2 octets)
    case ACC_FULL_SCALE_2_G:
      aRes = 2.0f / 32768.0f;
      break;
    case ACC_FULL_SCALE_4_G:
      aRes = 4.0f / 32768.0f;
      break;
    case ACC_FULL_SCALE_8_G:
      aRes = 8.0f / 32768.0f;
      break;
    case ACC_FULL_SCALE_16_G:
      aRes = 16.0f / 32768.0f;
      break;
  }
}

MPU9250::getGres() {
  switch (gScale)
  {
    // La résolution du gyro est codée sur 2 bits avec comme valeur possible :
    // 250deg/s (00), 400deg/s (01), 1000deg/s (10), et 2000deg/s (11).
    // On divise oar 32768 (2^(16-1)) car la mesure est codée sur 16 bits (2 octets)
    case GYRO_FULL_SCALE_250_DPS:
      gRes = 250.0f / 32768.0f;
      break;
    case GYRO_FULL_SCALE_500_DPS:
      gRes = 500.0f / 32768.0f;
      break;
    case GYRO_FULL_SCALE_1000_DPS:
      gRes = 1000.0f / 32768.0f;
    case GYRO_FULL_SCALE_2000_DPS:
      gRes = 2000.0f / 32768.0f;
      break;
  }
}

void MPU9250::getMres()
{
  switch (Mscale)
  {
    // La résolution du magnéto est codée sur 1 bit avec comme valeur possible :
    // 14 bit resolution (0) and 16 bit resolution (1)
    case MAG_FULL_SCALE_14_BITS:
      mRes = 10.0f * 4912.0f / 8190.0f; // Proper scale to return milliGauss
      break;
    case MAG_FULL_SCALE_16_BITS:
      mRes = 10.0f * 4912.0f / 32760.0f; // Proper scale to return milliGauss
      break;
  }
}

MPU9250::getAres() {
  switch (aScale)
  {
    // La résolution de l'accéléromètre est codée sr 2 bits avec comme valeur possible :
    // 2g (00), 4g (01), 8g (10), et 16g (11).
    // On divise oar 32768 (2^(16-1)) car la mesure est codée sur 16 bits (2 octets)
    case ACC_FULL_SCALE_2_G:
      aRes = 2.0f / 32768.0f;
      break;
    case ACC_FULL_SCALE_4_G:
      aRes = 4.0f / 32768.0f;
      break;
    case ACC_FULL_SCALE_8_G:
      aRes = 8.0f / 32768.0f;
      break;
    case ACC_FULL_SCALE_16_G:
      aRes = 16.0f / 32768.0f;
      break;
  }
}

void MPU9250::readAccData(int16_t *destination) {
  // Creation du tableau qui va contenir les octets des 3 axes capteurs
  uint8_t rawData[6];
  // Lecture du registre
  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);
  // Transformation des LSB et MSB en int16_t
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;
  destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;
  destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

void MPU9250::readGyrData(int16_t *destination) {
  // Creation du tableau qui va contenir les octets des 3 axes capteurs
  uint8_t rawData[6];
  // Lecture du registre
  readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);
  // Transformation des LSB et MSB en int16_t
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;
  destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;
  destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

void MPU9250::readMagData(int16_t *destination) {
  // Creation du tableau qui va contenir les octets des 3 axes capteurs
  uint8_t rawData[6];
  // Lecture du registre
  readBytes(MPU9250_ADDRESS, MAG_XOUT_H, 6, &rawData[0]);
  // Transformation des LSB et MSB en int16_t
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;
  destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;
  destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ;
}
