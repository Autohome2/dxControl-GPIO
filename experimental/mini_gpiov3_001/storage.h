#ifndef STORAGE_H
#define STORAGE_H

#include <EEPROM.h>
#if defined (MCU_STM32F103C8)
  #include "Adafruit_FRAM_SPI.h"
#endif
#if defined (USE_EXT_EEPROM)
  //#include <SPI.h>
  #include "stm32_ext_eeprom.h"
#endif  

void writeConfig(uint8_t thePage);
void loadConfig();
uint8_t NVMEMread(uint16_t address);
void NVMEMwrite(uint16_t address, uint8_t dataByte);
void erase_flash_swap_page();
//void write_byte(word page, byte offset, byte databyte);
  #if defined (USE_EXT_FLASH)
  void erase_flash_swap_page();
  #endif

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
