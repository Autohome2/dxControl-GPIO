#include <EEPROM.h>
#include "storage.h"
#include "globals.h"
#if defined (MCU_STM32F103C8)
#include "Adafruit_FRAM_SPI.h"
#endif
/*
Takes the current configuration (config pages and maps)
and writes them to EEPROM as per the layout defined in storage.h
*/
void writeConfig()
{
  /*
  We only ever write to the EEPROM where the new value is different from the currently stored byte
  This is due to the limited write life of the EEPROM (Approximately 100,000 writes)
  */
  
 // int offset;
  //Create a pointer to the config page
  
  void* pnt_configPage;//This only stores the address of the value that it's pointing to and not the max size
#if defined (CORE_AVR)  
  if(EEPROM.read(0) != data_structure_version) { EEPROM.write(0,data_structure_version); }   //Write the data structure version
#elif defined (MCU_STM32F103C8)
  if(NVMEMread(0) != data_structure_version) { NVMEMwrite(0,data_structure_version); }   //Write the data structure version
#endif 
    switch (currentStatus.currentPage)
  {

    case 1:
  /*---------------------------------------------------
  | Config page 1 (See storage.h for data layout)
  | 128 byte long config table
  -----------------------------------------------------*/
  pnt_configPage = (uint8_t *)&configPage1; //Create a pointer to Page 1 in memory
  for(uint16_t x=EEPROM_CONFIG1_START; x<EEPROM_CONFIG1_END; x++) 
  { 
#if defined (CORE_AVR)
    if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))); }
#elif defined (MCU_STM32F103C8)
    if(NVMEMread(x) != *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))) { NVMEMwrite(x, *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))); }
#endif
  }
  
    break;

    case 2:
  /*---------------------------------------------------
  | Config page 2 (See storage.h for data layout)
  | 705 byte long config table
  -----------------------------------------------------*/
  pnt_configPage = (uint8_t *)&configPage2; //Create a pointer to Page 2 in memory
  for(uint16_t x=EEPROM_CONFIG2_START; x<EEPROM_CONFIG2_END; x++) 
  { 
#if defined (CORE_AVR)
    if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))); }
#elif defined (MCU_STM32F103C8)
    if(NVMEMread(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))) { NVMEMwrite(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))); }
#endif
  }
  
    break;
  
  }     
}


void loadConfig()
{
  //Create a pointer to the config page
  //void* pnt_configPage;
  uint8_t* pnt_configPage;
  
  pnt_configPage = (uint8_t *)&configPage1; //Create a pointer to Page 1 in memory
  for(uint16_t x=EEPROM_CONFIG1_START; x<EEPROM_CONFIG1_END; x++)        // x=100;x<164
  { 
 //   #if defined (CORE_AVR)
 //   *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START)) = EEPROM.read(x);
 //   #elif defined (MCU_STM32F103C8)
  //  *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START)) = NVMEMread(x);
      *(pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START)) = NVMEMread(x);
 //   #endif
  }
  //That concludes the reading of config2

  pnt_configPage = (uint8_t *)&configPage2; //Create a pointer to Page 1 in memory
  for(uint16_t x=EEPROM_CONFIG2_START; x<EEPROM_CONFIG2_END; x++)        // x=200;x<454
  { 
 //   #if defined (CORE_AVR)
 //   *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START)) = EEPROM.read(x);
 //   #elif defined (MCU_STM32F103C8)
 //   *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START)) = NVMEMread(x);
      *(pnt_configPage + uint8_t(x - EEPROM_CONFIG2_START)) = NVMEMread(x);
 //   #endif
  }
  //That concludes the reading of config2
  
}

uint8_t NVMEMread(uint16_t address)
{
#if defined (CORE_AVR)
  uint8_t theValue = EEPROM.read(address);
#elif defined (MCU_STM32F103C8)
  uint8_t theValue = fram.read8(address);
#endif  
  return theValue;
}

void NVMEMwrite(uint16_t address, uint8_t dataByte)
{
#if defined (CORE_AVR)
  EEPROM.write(address,dataByte);
#elif defined (MCU_STM32F103C8)  
  fram.writeEnable(true);
  fram.write8(address, dataByte);
  fram.writeEnable(false);
#endif  
}

