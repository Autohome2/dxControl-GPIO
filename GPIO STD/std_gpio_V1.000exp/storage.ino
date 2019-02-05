
#include "storage.h"
#include "globals.h"
#include "directcomms.h"
#include <EEPROM.h>

//#if defined (MCU_STM32F103C8)
//  #if defined (USE_EXT_FRAM)
//    #include "Adafruit_FRAM_SPI.h"
//  #endif
//  #if defined (USE_EXT_EEPROM)  
//    #include "stm32_ext_eeprom.h"
//  #endif   
//#endif

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
  
  //void* pnt_configPage;//This only stores the address of the value that it's pointing to and not the max size
  byte* pnt_configPage;

  if(EEPROM.read(0) != data_structure_version) { EEPROM.write(0,data_structure_version); }   //Write the data structure version
 
  switch (thePage)
        {
         case 1:
         /*---------------------------------------------------
         | Config page 1 (See storage.h for data layout)
         | 128 byte long config table
         -----------------------------------------------------*/
         pnt_configPage = (uint8_t *)&configPage1; //Create a pointer to Page 1 in memory
  
         for(uint16_t x = EEPROM_CONFIG1_START; x < EEPROM_CONFIG1_END ; x++)     //EEPROM_CONFIG1_END 
            {         
             if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START))); }        
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
             //if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START))); }
             if(EEPROM.read(x) != *(pnt_configPage + byte(x - EEPROM_CONFIG2_START))) { EEPROM.write(x, *(pnt_configPage + byte(x - EEPROM_CONFIG2_START)));}
            }
  
         break;

         case 3:
         /*---------------------------------------------------
         | Config page 3 (See storage.h for data layout)
         | 256 byte long config table
          -----------------------------------------------------*/         
         pnt_configPage = (uint8_t *)&configPage3; //Create a pointer to Page 2 in memory  
  
         for(uint16_t x=EEPROM_CONFIG3_START; x<EEPROM_CONFIG3_END; x++) 
            {       
             if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG3_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG3_START))); }
             //if(EEPROM.read(x) != *(pnt_configPage + byte(x - EEPROM_CONFIG3_START))) { EEPROM.write(x, *(pnt_configPage + byte(x - EEPROM_CONFIG3_START)));}    
            }
  
         break;

         case 4:
         /*---------------------------------------------------
         | Config page 4 (See storage.h for data layout)
         | 256 byte long config table
         -----------------------------------------------------*/  
         pnt_configPage = (uint8_t *)&configPage4; //Create a pointer to Page 2 in memory
  
         for(uint16_t x=EEPROM_CONFIG4_START; x<EEPROM_CONFIG4_END; x++) 
            { 
             if(EEPROM.read(x) != *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG4_START))) { EEPROM.write(x, *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG4_START))); }
            //if(EEPROM.read(x) != *(pnt_configPage + byte(x - EEPROM_CONFIG4_START))) { EEPROM.write(x, *(pnt_configPage + byte(x - EEPROM_CONFIG4_START)));}
            }
  
         break;
       }     

  BIT_SET(currentStatus.systembits, BIT_SYSTEM_BURN_GOOD); //set burn_good flag
}

//---------------------------------------------------------------------------------------------------------------------------------------

void loadConfig()
 {
   //Create a pointer to the config page
   uint8_t* pnt_configPage;

   pnt_configPage = (uint8_t *)&configPage1; //Create a pointer to Page 1 in memory
       
   for(uint16_t x=EEPROM_CONFIG1_START; x<EEPROM_CONFIG1_END; x++)        // x=10 to 138
      { 
       *((uint8_t *)pnt_configPage + (uint8_t)(x - EEPROM_CONFIG1_START)) = EEPROM.read(x);
      }
  
  //That concludes the reading of config1

   pnt_configPage = (uint8_t *)&configPage2; //Create a pointer to Page 2 in memory

   for(uint16_t x=EEPROM_CONFIG2_START; x<EEPROM_CONFIG2_END; x++)        // x=200;x<454
      {       
       *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG2_START)) = EEPROM.read(x);     // note the uint16_t instead of 8 this is due to the page going over 256!
      }
  
  //That concludes the reading of config2

 
   pnt_configPage = (uint8_t *)&configPage3; //Create a pointer to Page 3 in memory

   for(uint16_t x=EEPROM_CONFIG3_START; x<EEPROM_CONFIG3_END; x++)        // x=500;x<756
      {       
       *((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG3_START)) = EEPROM.read(x);
      }
  
  //That concludes the reading of config3

   pnt_configPage = (uint8_t *)&configPage4; //Create a pointer to Page 4 in memory

   for(uint16_t x=EEPROM_CONFIG4_START; x<EEPROM_CONFIG4_END; x++)        // x=800;x<1156
      {      
       //*((uint8_t *)pnt_configPage + (uint16_t)(x - EEPROM_CONFIG4_START)) = EEPROM.read(x);     // note the uint16_t instead of 8 this is due to the page going over 256!
       *(pnt_configPage + uint16_t(x - EEPROM_CONFIG4_START)) = EEPROM.read(x);    
      }
  
  //That concludes the reading of config4
  
}

//---------------------------------------------------------------------------------------------------


