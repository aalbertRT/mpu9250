#include "Arduino.h"
#include "ArduI2C.h"

uint8_t I2CreadByte(uint8_t address, uint8_t regist) {
  // Création de la variable de sortie data
  uint8_t data;

  // Connexion au dispositif et placement sur le registre d'entrée
  Wire.beginTransmission(address);
  Wire.write(regist);
  Wire.endTransmission(false);

  // Lecture des octets
  Wire.requestFrom(address, (uint8_t) 1);
  data = Wire.read();
  return data;
}

void I2CreadBytes(uint8_t address, uint8_t regist, uint8_t nbytes, uint8_t* data) {
  // Connexion au dispositif et placement sur le registre d'entrée
  Wire.beginTransmission(address);
  Wire.write(regist);
  Wire.endTransmission(false); // Envoi d'un restart pour garder la connexion ouverte

  // Lecture des octets
  Wire.requestFrom(address, nbytes);
  uint8_t index = 0;
  while (Wire.available()) {
    data[index++] = Wire.read();
  }
}

void I2CwriteByte(uint8_t address, uint8_t regist, uint8_t data)
{
  // Connexion au dispositif
  Wire.beginTransmission(address);
  // On se place à l'adresse du registre
  Wire.write(regist);
  // Ecriture dans le registre
  Wire.write(data);
  Wire.endTransmission();
}
