/*
mini GPIO V3.001. 
supports Speeduino Secondary serial port data transfer.
On Mega2560 version this is Serial3.
Copyright (C) Darren Siepka
A full copy of the license may be found in the projects root directory 

Speeduino is Copyright (C) Josh Stewart
A full copy of the license may be found in the speeduino projects root directory

*/
//https://developer.mbed.org/handbook/C-Data-Types
#include <stdint.h>
//************************************************
#include "globals.h"
#include "utils.h"
#include "auxiliaries.h"
#include "sensors.h"
#include "directcomms.h"
#include "storage.h"
#include "timers.h"
#include "remotecomms.h"
#include "display.h"
#include "canbus.h"
#if defined (CORE_AVR)
  #include <EEPROM.h>
#endif  

#include <SPI.h>
#include <Wire.h>

#include <mcp_can.h>
  #define CAN0_INT   2    // Set INT to pin 2
  #define CAN1_INT   3    // Set INT to pin 3
  MCP_CAN CAN0(11);      // Set CS to pin 11
  MCP_CAN CAN1(12);    //  Set CS to pin 12

#include <U8g2lib.h>

  // stm32 pin assignments
#if defined (CORE_STM32)//(MCU_STM32F103C8)
  #if defined (USE_EXT_FRAM)
    #include "Adafruit_FRAM_SPI.h"
    /* Example code for the Adafruit SPI FRAM breakout */
    uint8_t FRAM_CS = PA15;//10;
 //   Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI
    uint8_t FRAM_SCK= PB3;//13;
    uint8_t FRAM_MISO = PB4;//12;
    uint8_t FRAM_MOSI = PB5;//11;
    //Or use software SPI, any pins!
    Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_SCK, FRAM_MISO, FRAM_MOSI, FRAM_CS);
    #endif
  #endif

  #if defined (USE_EXT_FLASH)
    //#include <SPI.h>
    #include "stm32_flash.h"
    SPIClass SPI_2(2); //Create an instance of the SPI Class called SPI_2 that uses the 2nd SPI Port   
  #endif

  #if defined (USE_EXT_EEPROM)
    //#include <SPI.h>
    #include "stm32_ext_eeprom.h"
    SPIClass SPI_2(2); //Create an instance of the SPI Class called SPI_2 that uses the 2nd SPI Port   
  #endif
  
// setup which serial port connects to the speeduino secondary serial
#if defined(ARDUINO_AVR_MEGA2560)
    // mega pin assignments
    HardwareSerial &SERIALLink = Serial3;
#elif defined(MCU_STM32F103C8)
    #define SERIALLink Serial2
#elif defined(ARDUINO_NUCLEO_64)//(CORE_STM32)
    #define SERIALLink Serial1   
#else
    #error Incorrect board selected. Please select the correct board (Usually Mega 2560) and upload again  
#endif 

//setup which serial port connects to TS
#if defined(ARDUINO_AVR_MEGA2560)
    HardwareSerial &CONSOLE_SERIALLink = Serial;

#elif defined (CORE_STM32)&&(MCU_STM32F103C8)
    #define CONSOLE_SERIALLink Serial1 
#endif

struct config1 configPage1;
struct config2 configPage2;
struct config3 configPage3;
struct statuses currentStatus;

volatile int mainLoopCount;
//volatile byte Achanloop;
volatile byte diginchanloop;
volatile byte driveoutloop;
volatile byte EXinchanloop;

//configure screen 1 display initialise options
#if defined DISP1_ACTIVE
    #if defined DISP1_USE_SSD1106_I2C
        U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2_1(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   
    #elif defined DISP1_USE_SSD1106_SPI
        U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2_1(U8G2_R0, /* cs=*/ DISPLAY1_CS, /* dc=*/ DISPLAY1_DC, /* reset=*/ DISPLAY1_RESET);     
    #elif defined DISP1_USE_SSH1106_SPI
        U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2_1(U8G2_R0, /* cs=*/ DISPLAY1_CS, /* dc=*/ DISPLAY1_DC, /* reset=*/ DISPLAY1_RESET);    
    #endif
#endif    

//configure screen 2 display initialise options
#if defined DISP2_ACTIVE
    #if defined DISP2_USE_SSD1106_I2C
        U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2_2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   
    #elif defined DISP2_USE_SSD1106_SPI
        U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2_2(U8G2_R0, /* cs=*/ DISPLAY2_CS, /* dc=*/ DISPLAY2_DC, /* reset=*/ DISPLAY2_RESET);     
    #elif defined DISP2_USE_SSH1106_SPI
        U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2_2(U8G2_R0, /* cs=*/ DISPLAY2_CS, /* dc=*/ DISPLAY2_DC, /* reset=*/ DISPLAY2_RESET);    
    #endif
#endif    

void setup() {
  // put your setup code here, to run once:
  #if defined (CORE_STM32)
      #if defined(USE_EXT_FLASH)
          init_stm32_flash(1);
      #endif

      #if  defined(USE_EXT_EEPROM)
           init_stm32_ext_eeprom(1);
      #endif
  #endif
  
 loadConfig();
 setPinMapping(configPage1.pinLayout);
 initialiseADC();
 initialiseTimers();
 initialise_display();
 //currentStatus.EXin[14] = configPage1.canModuleConfig;
 if (BIT_CHECK(configPage1.canModuleConfig, 0))
   {
    initialiseCAN0();     //init can interface 0
   } 
 if (BIT_CHECK(configPage1.canModuleConfig,1))
   {  
    initialiseCAN1();    //init can interface 1
   }
 CONSOLE_SERIALLink.begin(115200);
 SERIALLink.begin(115200);  
    
  mainLoopCount = 0;
  BIT_SET(currentStatus.systembits, 0); //set system ready flag
  initialOutputs();   //run the initialoutputs once to begin to preset initial on states   
  blinkCEL();
}

void loop()
{
  // put your main code here, to run repeatedly:
      mainLoopCount++;
      LOOP_TIMER = TIMER_mask;
      //Check for any requets from serial. Serial operations are checked under 2 scenarios:
      // 1) Every 64 loops (64 Is more than fast enough for TunerStudio). This function is equivalent to ((loopCount % 64) == 1) but is considerably faster due to not using the mod or division operations
      // 2) If the amount of data in the serial buffer is greater than a set threhold (See globals.h). This is to avoid serial buffer overflow when large amounts of data is being sent
      if (BIT_CHECK(TIMER_mask, BIT_TIMER_25HZ))
      //if ( ((mainLoopCount & 31) == 1) or (SERIALLink.available() > 32) )
        {
          if (SERIALLink.available() > 0)      // if SERIALLink has data then do the remote serial command subroutine
            {
              remote_serial_command();
            }
        //}     
       // if ( ((mainLoopCount & 31) == 1) or (Serial.available() > 32) )
          //{
            if (CONSOLE_SERIALLink.available() > 0)      // if CONSOLE_SERIALLink has data then do the direct serial command subroutine(Typical TS link)
              {
                direct_serial_command();
              }
   if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    CAN0_INT_routine() ;
  }
  
   if(!digitalRead(CAN1_INT))                         // If CAN1_INT pin is low, read receive buffer
  {
    CAN1_INT_routine();
  }
  
         BIT_CLEAR(TIMER_mask, BIT_TIMER_25HZ);
         }
          
      if  (SERIALLink.available() > 32) 
        {
          if (SERIALLink.available() > 0)      // if SERIALLink has data then do the remote serial command subroutine
            {
              remote_serial_command();
            }
        }     
        
     if  (CONSOLE_SERIALLink.available() > 32) 
        {
          if (CONSOLE_SERIALLink.available() > 0)      // if CONSOLE_SERIALLink has data then do the direct serial command subroutine(Typical TS link)
            {
              direct_serial_command();
            }
        }
                      
      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_4HZ)) //4 hertz
        {   
              if(BIT_CHECK(currentStatus.testIO_hardware, 0)) //if testenabled is set 
                {   
                  if(BIT_CHECK(currentStatus.testIO_hardware, 1) == 0) //and if testactive is clear 
                    {
                     BIT_CLEAR(currentStatus.testIO_hardware, 0);    //clear testenabled flag now all outputs have been forced
                    }
                }
              
            //  currentStatus.dev1 = configPage3.canbroadcast_out;
            //  currentStatus.dev2 = configPage3.canbroadcast_sel; 
              for (byte Bchan = 0; Bchan <16 ; Bchan++)
                 { 
                  if(BIT_CHECK(configPage3.canbroadcast_out, Bchan) == 1)
                    {
                     if(BIT_CHECK(configPage3.canbroadcast_sel, Bchan) == 1)
                       {
                        Send_CAN0_message(Bchan,0,0);
                       }  
                    }
                 }           
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_4HZ);                         
        }

      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_10HZ)) //10 hertz
        {
          driveDisplay();
          //if(BIT_CHECK(configPage1.generalConfig1, USE_REALTIME_BROADCAST) == 1)
          if (configPage1.exinsel !=0)  //if any of the external input channels are enabled
            {
              // send an "A" request
              getExternalInput(0xFF);
            } 
            
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_10HZ);                         
        }

              if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_15HZ)) //15 hertz
        {
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_15HZ);

          for (byte Achan = 1; Achan <17 ; Achan++)
             {
              if (pinAin[Achan] < 255) {readAnalog(Achan);}        // if analog pin is in use read the analog inputs
             }

          //for (byte diginchanloop = 0; diginchanloop <16 ; diginchanloop++)
          //  {
          //   if (pinIn[diginchanloop] < 255) { readDigitalIn(diginchanloop);}        // if pin is not set to 0 then is in use so read the digital input
          //  }


               
              if(!BIT_CHECK(currentStatus.testIO_hardware, 1))
                {
                  for (byte Dinchan = 1; Dinchan <17 ; Dinchan++)
                      {
                        if (pinIn[Dinchan] < 255) { readDigitalIn(Dinchan);}        // if pin is not set to 0 then is in use so read the digital input
                      }
                }
              driveOutputs();                    
       }     
       
      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_30HZ)) //30 hertz
      {             
        if (BIT_CHECK(configPage1.exinsel,EXinchanloop))        //if external input is active then read it
          {
            getExternalInput(EXinchanloop);
          }        // read the external inputs if enabled                                        
        if(EXinchanloop <16 ){EXinchanloop++;}                  //it takes approx 1 second to go through all 16 channels
        else {EXinchanloop = 0;}
        //Nothing here currently
        BIT_CLEAR(TIMER_mask, BIT_TIMER_30HZ);        
      }                    
}
