// Fonction qui lit un des octets sur un registre d'un bus I2C
// Inputs :
// - address : adresse du bus I2C
// - regist : adresse du registre sur lequel on souhaite lire des octets
// - nbytes : numéro de l'octet qu'on souhaite lire
// - data : tableau contenant les octets lus dans le registre (pointeur)
void I2Cread(uint8_t address, uint8_t regist, uint8_t nbytes, uint8_t* data);


// Fonction qui écrit un octet à l'adresse du registre voulu
// Inputs :
// - address : adresse du bus I2C
// - regist : adresse du registre dans lequel on souhaite écrire
// - data : octet qu'on souhaite écrire dans le registre
void I2CwriteByte(uint8_t address, uint8_t regist, uint8_t data);
