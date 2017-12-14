#ifndef STORAGE_H
#define STORAGE_H

#if defined (CORE_AVR)
#include <EEPROM.h>
#endif

#if defined (CORE_STM32)
  #if defined (USE_EXT_FRAM)
    #include "Adafruit_FRAM_SPI.h"
  #elif defined (USE_EXT_EEPROM)
    //#include <SPI.h>
    #include "stm32_ext_eeprom.h"
  #endif
#endif  

void writeConfig(uint8_t thePage);
void loadConfig();
uint8_t NVMEMread(uint16_t address);
void NVMEMwrite(uint16_t address, uint8_t dataByte);
//void erase_flash_swap_page();
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
| 500   |256  | configPage3
| 800   |256  | configPage4
*/

#define EEPROM_CONFIG1_START 10
#define EEPROM_CONFIG1_END 138     // 128 slots
#define EEPROM_CONFIG2_START 200
#define EEPROM_CONFIG2_END 904     //704 slots
#define EEPROM_CONFIG3_START 1000
#define EEPROM_CONFIG3_END 1256     //256 slots
#define EEPROM_CONFIG4_START 1300
#define EEPROM_CONFIG4_END 1634     //334 slots

byte EEPROM_loc;

#endif // STORAGE_H
