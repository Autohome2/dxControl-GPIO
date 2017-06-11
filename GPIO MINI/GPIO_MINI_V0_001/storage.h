#ifndef STORAGE_H
#define STORAGE_H

#include <EEPROM.h>

void writeConfig();
void loadConfig();

/*
Current layout of EEPROM data (Version 3) is as follows (All sizes are in bytes):
|---------------------------------------------------|
|Byte # |Size | Description                         |
|---------------------------------------------------|
| 0     |1    | Data structure version              |
| 10    |128  | configPage1
| 200   |256  | configpage2

*/

#define EEPROM_CONFIG1_START 10
#define EEPROM_CONFIG1_END 138     // 128 slots
#define EEPROM_CONFIG2_START 200
#define EEPROM_CONFIG2_END 456     //256 slots

byte EEPROM_loc;

#endif // STORAGE_H
