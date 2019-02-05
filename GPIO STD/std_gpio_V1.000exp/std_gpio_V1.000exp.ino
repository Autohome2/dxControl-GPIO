/*
GPIO STD V1.000. 
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
#include "sysconfig.h"
#include <SPI.h>
#if defined (CORE_AVR)
  #include <EEPROM.h>
#endif  

//#include <Wire.h>

#include <mcp_can.h>          //see canbus.h for all canbus config 
  MCP_CAN CAN0(CAN0_CS);      // Set MCP_CAN CAN0 instance CS to pin 11
  MCP_CAN CAN1(CAN1_CS);      // Set MCP_CAN CAN1 instance CS to pin 12

#include <U8g2lib.h>

struct config1 configPage1;
struct config2 configPage2;
struct config3 configPage3;
struct config4 configPage4;

#define NO_TS     0           // Set this to 1 if you do NOT want to use TS to configure GPIO but set the config in the noTsConfig function in sysconfig.ino

#if defined(ARDUINO_AVR_MEGA2560)
    HardwareSerial &SERIALLink = Serial3;          // setup which serial port connects to the speeduino secondary serial
    HardwareSerial &CONSOLE_SERIALLink = Serial;   // setup which serial port connects to TS
#else
    #error Incorrect board selected. Please select the correct board (Usually Mega 2560) and upload again  
#endif 

//struct statuses currentStatus;

volatile int mainLoopCount;
//volatile byte Achanloop;
volatile byte diginchanloop;
volatile byte driveoutloop;
volatile byte EXinchanloop;

//configure screen 1 display initialise options
#if DISP1_ACTIVE == 1
    #if defined DISP1_USE_SSD1106_SPI
        U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2_1(U8G2_R0, /* cs=*/ DISPLAY1_CS, /* dc=*/ DISPLAY1_DC, /* reset=*/ DISPLAY1_RESET);     
    #elif defined DISP1_USE_SSH1106_SPI
        U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2_1(U8G2_R0, /* cs=*/ DISPLAY1_CS, /* dc=*/ DISPLAY1_DC, /* reset=*/ DISPLAY1_RESET);    
    #endif
#endif    

//configure screen 2 display initialise options
#if DISP2_ACTIVE == 1
    #if defined DISP2_USE_SSD1106_SPI
        U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2_2(U8G2_R0, /* cs=*/ DISPLAY2_CS, /* dc=*/ DISPLAY2_DC, /* reset=*/ DISPLAY2_RESET);     
    #elif defined DISP2_USE_SSH1106_SPI
        U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2_2(U8G2_R0, /* cs=*/ DISPLAY2_CS, /* dc=*/ DISPLAY2_DC, /* reset=*/ DISPLAY2_RESET);
    #endif
#endif    

void setup() {
  // put your setup code here, to run once:
//  #if defined (CORE_STM32)
//      #if defined(USE_EXT_FLASH)
//          init_stm32_flash(1);
//      #endif

//      #if  defined(USE_EXT_EEPROM)
//           init_stm32_ext_eeprom(1);
//      #endif
//  #endif
  
  loadConfig();            
  setPinMapping(configPage1.pinLayout);
  setusageflags();
  initialiseADC();
  initialiseTimers();
  initialise_display();
  
/*   if (CAN0_ACTIVE == 1)
    //if (BIT_sCHECK(configPage1.canModuleConfig, CAN0ENABLE) == 1)
     {
       initialiseCAN0();     //init can interface 0           //CAN0_ACTIVE
     } 
      if (CAN1_ACTIVE == 1)
  //if (BIT_sCHECK(configPage1.canModuleConfig, CAN1ENABLE) == 1)
     {  
       initialiseCAN1();    //init can interface 1
     }
*/

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

      //Check for any requests from serial. Serial operations are checked under 2 scenarios:
      // 1) Every 64 loops (64 Is more than fast enough for TunerStudio). This function is equivalent to ((loopCount % 64) == 1) but is considerably faster due to not using the mod or division operations
      // 2) If the amount of data in the serial buffer is greater than a set threshold (See globals.h). This is to avoid serial buffer overflow when large amounts of data is being sent
      if (BIT_CHECK(TIMER_mask, BIT_TIMER_25HZ))
        {
         if (SERIALLink.available() > 0)      // if SERIALLink has data then do the remote serial command subroutine
            {
              remote_serial_command();
            }

            if (CONSOLE_SERIALLink.available() > 0)      // if CONSOLE_SERIALLink has data then do the direct serial command subroutine(Typical TS link)
              {
                direct_serial_command();
              }

         if (BIT_sCHECK(configPage1.canModuleConfig, CAN0ENABLE) == 1)
            {
             if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
               {
                CAN0_INT_routine() ;
               }
            }
       
         if (BIT_sCHECK(configPage1.canModuleConfig, CAN1ENABLE) == 1)
            {  
             // currentStatus.dev1 = 100;
             if(!digitalRead(CAN1_INT))                         // If CAN1_INT pin is low, read receive buffer
               {                
                CAN1_INT_routine();
               }
            }
                   
         BIT_CLEAR(TIMER_mask, BIT_TIMER_25HZ);
        }

      /* these next two serial checks are untimed only overflow */    
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

 /* now do the other periodic timed loops */                      
      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_4HZ)) //4 hertz
        {   
              if(BIT_CHECK(currentStatus.testIO_hardware, 0)) //if testenabled is set 
                {   
                  if(BIT_CHECK(currentStatus.testIO_hardware, 1) == 0) //and if testactive is clear 
                    {
                     BIT_CLEAR(currentStatus.testIO_hardware, 0);    //clear testenabled flag now all outputs have been forced
                    }
                }
          canbroadcastperfreq(1);     //4hz is position 1 in ts list
                         
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_4HZ);                         
        }

      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_5HZ)) //5 hertz
        {                 
          canbroadcastperfreq(2);     //5hz is position 2 in ts list
              
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_5HZ);                         
        }
        
      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_10HZ)) //10 hertz
        {
          canbroadcastperfreq(3);     //10hz is position 3 in ts list

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
          canbroadcastperfreq(4);     //15hz is position 4 in ts list
          
          for (byte Achan = 0; Achan <16 ; Achan++)
             {
              if (pinAin[(Achan+1)] < 255) {readAnalog(Achan);}        // if analog pin is in use(<255) read the analog inputs
             }
               
          if(!BIT_CHECK(currentStatus.testIO_hardware, 1))                    //if not in hardware testmode
             {
              for (byte Dinchan = 1; Dinchan <33 ; Dinchan++)
                 {
                  if (pinIn[Dinchan] < 255) { readDigitalIn(Dinchan);}        // if pin is in use(<255) read the digital input
                 }
             }
                
              driveOutputs();                    
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_15HZ);

       }     

      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_20HZ)) //20 hertz
        {
         canbroadcastperfreq(5);     //20hz is position 5 in ts list
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_20HZ);                         
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
