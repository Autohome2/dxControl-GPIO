#include <EEPROM.h>
#include "storage.h"
#include "globals.h"
#if defined (MCU_STM32F103C8)
  #if defined (USE_EXT_FRAM)
    #include "Adafruit_FRAM_SPI.h"
  #endif
  #if defined (USE_EXT_EEPROM)  
    #include "stm32_ext_eeprom.h"
  #endif   
#endif

/*
Takes the current configuration (config pages and maps)
and writes them to EEPROM as per the layout defined in storage.h
*/
void writeConfig(uint8_t thePage)
{
  /*
  We only ever write to the EEPROM where the new value is different from the currently stored byte
  This is due to the limited write life of the EEPROM (Approximately 100,000 writes)
  */
  
 // int offset;
  //Create a pointer to the config page
  
  void* pnt_configPage;//This only stores the address of the value that it's pointing to and not the max size
  void* pnt_stm32_configPage;//This only stores the address of the value that it's pointing to and not the max size

#if defined (CORE_AVR)  
  if(EEPROM.read(0) != data_structure_version) { EEPROM.write(0,data_structure_version); }   //Write the data structure version

#elif defined (CORE_STM32)//(MCU_STM32F103C8)
      if(NVMEMread(0) != data_structure_version)
        {
         NVMEMwrite(0,data_structure_version,0);  //
      //   swap_next_page = 1;
        }   //Write the data structure version
    
#endif 
    switch (thePage)
  {

  case 1:
  /*---------------------------------------------------
  | Config page 1 (See storage.h for data layout)
  | 128 byte long config table
  -----------------------------------------------------*/
  #if defined (CORE_AVR)
    pnt_configPage = (uint8_t *)&configPage1; //Create a pointer to Page 1 in memory
  #elif defined (CORE_STM32)
    pnt_stm32_configPage = (uint8_t *)&configPage1; //Create a pointer to Page 1 in memory
  #endif
  
    for(uint16_t x = EEPROM_CONFIG1_START; x < EEPROM_CONFIG1_END ; x++)     //EEPROM_CONFIG1_END 
       { 
        #if defined (CORE_AVR)
          if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))); }
        #elif defined (CORE_STM32)//(MCU_STM32F103C8)
          if(NVMEMread(x)!= *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))) 
            {
              NVMEMwrite(x, *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG1_START)),0); 
            }      
        #endif
       }
  
  break;

  case 2:
  /*---------------------------------------------------
  | Config page 2 (See storage.h for data layout)
  | 705 byte long config table
  -----------------------------------------------------*/
  #if defined (CORE_AVR)
    pnt_configPage = (uint8_t *)&configPage2; //Create a pointer to Page 2 in memory
  #elif defined (CORE_STM32)
    pnt_stm32_configPage = (uint8_t *)&configPage2; //Create a pointer to Page 2 in memory
  #endif
  
    for(uint16_t x=EEPROM_CONFIG2_START; x<EEPROM_CONFIG2_END; x++) 
       { 
        #if defined (CORE_AVR)
          if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))); }
        #elif defined (CORE_STM32)//(MCU_STM32F103C8)
          if(NVMEMread(x) != *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG2_START)))
            {     
              NVMEMwrite(x, *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG2_START)),0); 
            }
        #endif
       }
  
  break;

  case 3:
  /*---------------------------------------------------
  | Config page 3 (See storage.h for data layout)
  | 256 byte long config table
  -----------------------------------------------------*/
  #if defined (CORE_AVR)
  pnt_configPage = (uint8_t *)&configPage3; //Create a pointer to Page 2 in memory
  #elif defined (CORE_STM32)
  pnt_stm32_configPage = (uint8_t *)&configPage3; //Create a pointer to Page 2 in memory
  #endif
  
  for(uint16_t x=EEPROM_CONFIG3_START; x<EEPROM_CONFIG3_END; x++) 
  { 
#if defined (CORE_AVR)
    if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG3_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG3_START))); }
#elif defined (CORE_STM32)//(MCU_STM32F103C8)
        if(NVMEMread(x) != *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG3_START)))
          {     
            NVMEMwrite(x, *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG3_START)),0); 
          }
#endif
  }
  
    break;

  case 4:
  /*---------------------------------------------------
  | Config page 4 (See storage.h for data layout)
  | 256 byte long config table
  -----------------------------------------------------*/
  #if defined (CORE_AVR)
  pnt_configPage = (uint8_t *)&configPage4; //Create a pointer to Page 2 in memory
  #elif defined (CORE_STM32)
  pnt_stm32_configPage = (uint8_t *)&configPage4; //Create a pointer to Page 2 in memory
  #endif
  
  for(uint16_t x=EEPROM_CONFIG4_START; x<EEPROM_CONFIG4_END; x++) 
  { 
#if defined (CORE_AVR)
    if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG4_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG4_START))); }
#elif defined (CORE_STM32)//(MCU_STM32F103C8)
        if(NVMEMread(x) != *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG4_START)))
          {     
            NVMEMwrite(x, *((uint8_t *)pnt_stm32_configPage + (uint8_t)(x - EEPROM_CONFIG4_START)),0); 
          }
#endif
  }
  
    break;
  
  }     
  
  #if defined (USE_EXT_FLASH)
  if (swap_next_page == 1)
    {
      erase_flash_swap_page(); // erase current swap_page 
      swap_page = !swap_page; // last config page burned so swap_flash page for next time
      swap_next_page == 0;    //reset swap_next_page flag
    }
  #endif  

BIT_SET(currentStatus.systembits, BIT_SYSTEM_BURN_GOOD); //set burn_good flag
}


void loadConfig()
{
  //Create a pointer to the config page

  uint8_t* pnt_configPage;

    pnt_configPage = (uint8_t *)&configPage1; //Create a pointer to Page 1 in memory
  
   for(uint16_t x=EEPROM_CONFIG1_START; x<EEPROM_CONFIG1_END; x++)        // x=10 to 138
      { 
      #if defined (CORE_AVR)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START)) = EEPROM.read(x);
    
      #elif defined (CORE_STM32)    //(MCU_STM32F103C8)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START)) = (uint8_t)NVMEMread(x); 
      #endif
      }
  
  //That concludes the reading of config1

  pnt_configPage = (uint8_t *)&configPage2; //Create a pointer to Page 2 in memory

  for(uint16_t x=EEPROM_CONFIG2_START; x<EEPROM_CONFIG2_END; x++)        // x=200;x<454
      { 
      #if defined (CORE_AVR)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG2_START)) = EEPROM.read(x);
    
      #elif defined (CORE_STM32)    //(MCU_STM32F103C8)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG2_START)) = (uint8_t)NVMEMread(x);
      #endif
      }
  
  //That concludes the reading of config2

  
  pnt_configPage = (uint8_t *)&configPage3; //Create a pointer to Page 3 in memory

  for(uint16_t x=EEPROM_CONFIG3_START; x<EEPROM_CONFIG3_END; x++)        // x=500;x<756
      { 
      #if defined (CORE_AVR)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG3_START)) = EEPROM.read(x);
    
      #elif defined (CORE_STM32)    //(MCU_STM32F103C8)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG3_START)) = (uint8_t)NVMEMread(x);
      #endif
      }
  
  //That concludes the reading of config3

    pnt_configPage = (uint8_t *)&configPage4; //Create a pointer to Page 4 in memory

  for(uint16_t x=EEPROM_CONFIG4_START; x<EEPROM_CONFIG4_END; x++)        // x=800;x<1056
      { 
      #if defined (CORE_AVR)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG4_START)) = EEPROM.read(x);
    
      #elif defined (CORE_STM32)    //(MCU_STM32F103C8)
          *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG4_START)) = (uint8_t)NVMEMread(x);
      #endif
      }
  
  //That concludes the reading of config4
}

uint8_t NVMEMread(uint16_t address)
{
  uint8_t theValue;
  
#if defined (CORE_AVR)
      theValue = EEPROM.read(address);
#elif defined (CORE_STM32)//(MCU_STM32F103C8)
  #if defined (USE_EXT_FRAM)
      theValue = fram.read8(address);
  #endif

  #if defined (USE_EXT_EEPROM)
      byte tmp;
      theValue = _read_byte_address(address);
  #endif

  #if defined (USE_EXT_FLASH)
  //  if (swap_page == 0)         // read flash swap page 0
  //  {  
  //    theValue =_read_byte_address(address);
  //  }

  //  else if (swap_page == 1)    //read flash swap page1
  //  {  
      //theValue =_read_byte_address((address + FLASH_OFFSET));
  //  }

  #endif
#endif    
  
  return theValue;
}

void NVMEMwrite(uint16_t address, uint8_t data_Byte, bool erase_flash)
{
#if defined (CORE_AVR)
  EEPROM.write(address,data_Byte);
#elif defined (CORE_STM32)//(MCU_STM32F103C8)
  #if defined (USE_EXT_FRAM)  
    fram.writeEnable(true);
    fram.write8(address, data_Byte);
    fram.writeEnable(false);
  #endif
  
  #if defined (USE_EXT_EEPROM)
   //currentStatus.dev1 = address;
   //currentStatus.dev2 = data_Byte;
  _write_byte_address(address,data_Byte);
  #endif
  
  #if defined (USE_EXT_FLASH)
    //currentStatus.dev2 = 44;
    //if (swap_page == 0)         // 
    //{         
      //_write_byte_address((address+FLASH_OFFSET), data_Byte);   //write to swap_page 1  
    //}  

    //else if (swap_page == 1)         // 
    //{ 
      //_write_byte_address(address, data_Byte);   //write to swap_page 0
    //}
    
  //    if (erase_flash == 1)
  //      {
        //byte was 0xFF so sector erase first
  //        int sector_4k = 0;
  //        chip_erase_sector_4k(sector_4k);  
  //      }
        // now write the byte
  //       _write_byte_address(address, data_Byte);
  #endif
#endif  
}


  #if defined (USE_EXT_FLASH)
void erase_flash_swap_page()
{
    if (swap_page == 0)         // 
    {  
      //chip_erase_sector_4k(0);
    }  

    else if (swap_page == 1)         // 
    {  
      //chip_erase_sector_4k(4096);
    }
}
#endif
