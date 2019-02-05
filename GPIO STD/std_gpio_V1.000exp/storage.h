#ifndef STORAGE_H
#define STORAGE_H

void writeConfig(uint8_t thePage);
void loadConfig();

/*
Current layout of EEPROM data (Version 1) is as follows (All sizes are in bytes):
|---------------------------------------------------|
|Byte # |Size | Description                         |
|---------------------------------------------------|
| 0     |1    | Data structure version              |
| 10    |128  | configPage1
| 200   |704  | configpage2
| 1000  |256  | configPage3
| 1300  |336  | configPage4
*/

#define EEPROM_CONFIG1_START 10
#define EEPROM_CONFIG1_END 137     // 128 slots
#define EEPROM_CONFIG2_START 200
#define EEPROM_CONFIG2_END 903     //704 slots
#define EEPROM_CONFIG3_START 1000
#define EEPROM_CONFIG3_END 1255     //256 slots
#define EEPROM_CONFIG4_START 1300
#define EEPROM_CONFIG4_END 1635   //336 slots

byte EEPROM_loc;

#endif // STORAGE_H
