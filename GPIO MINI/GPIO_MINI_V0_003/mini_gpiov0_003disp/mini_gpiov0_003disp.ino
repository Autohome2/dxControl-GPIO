/*
Example program to read specific value from Speeduino Secondary serial port.
On Mega2560 version this is Serial3.
This example program was written for a arduino promini but any arduino could be used just change the pins for the software serial ports
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
#include <EEPROM.h>


//#elif defined (MCU_STM32F103C8)//(STM32_MCU_SERIES) || defined(STM32F1) || defined(STM32F4) || defined(STM32)
  // stm32 pin assignments
#if defined (MCU_STM32F103C8)

  #if defined (USE_EXT_FRAM)
    #include "Adafruit_FRAM_SPI.h"
    /* Example code for the Adafruit SPI FRAM breakout */
    uint8_t FRAM_CS = PA15;//10;
    //Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI
    uint8_t FRAM_SCK= PB3;//13;
    uint8_t FRAM_MISO = PB4;//12;
    uint8_t FRAM_MOSI = PB5;//11;
    //Or use software SPI, any pins!
    Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_SCK, FRAM_MISO, FRAM_MOSI, FRAM_CS);
    #endif
  #endif

  #if defined (USE_EXT_FLASH)
    #include <SPI.h>
    #include "stm32_flash.h"
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
//    #error Incorrect
    //Serial.begin(115200);       // your console serial port 
    //Serial3.begin(115200);          //the external serial stream port

#elif defined (CORE_STM32)&&(MCU_STM32F103C8)
    #define CONSOLE_SERIALLink Serial1 
    //Serial1.begin(115200);
#endif

/*
 Note for softSerial config:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
*/

struct config1 configPage1;
struct config2 configPage2;
struct statuses currentStatus;

volatile int mainLoopCount;
//volatile byte Achanloop;
volatile byte diginchanloop;
volatile byte driveoutloop;
volatile byte EXinchanloop;

void setup() {
  // put your setup code here, to run once:
 loadConfig();
 setPinMapping(configPage1.pinLayout);
 initialiseADC();
 initialiseTimers();

 CONSOLE_SERIALLink.begin(115200);
 SERIALLink.begin(115200);  

#if defined (CORE_STM32) && defined(USE_EXT_FLASH)
    init_stm32_flash(1);
    CONSOLE_SERIALLink.print("ok");
#endif
    
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
          //Nothing here currently
          BIT_CLEAR(TIMER_mask, BIT_TIMER_4HZ);                         
        }

      if(BIT_CHECK(LOOP_TIMER, BIT_TIMER_10HZ)) //10 hertz
        {
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

          for (byte diginchanloop = 0; diginchanloop <16 ; diginchanloop++)
            {
             if (pinIn[diginchanloop] < 255) { readDigitalIn(diginchanloop);}        // if pin is not set to 0 then is in use so read the digital input
          //      if (diginchanloop < 16)
          //      {
          //        diginchanloop++;
          //      }
          //    else
          //      {
          //        diginchanloop = 0;
          //      }
            }
            
              if(!BIT_CHECK(currentStatus.testIO_hardware, 1))
                {
                  for (byte Dinchan = 1; Dinchan <17 ; Dinchan++)
                      {
                        if (pinIn[Dinchan] < 255) { readDigitalIn(Dinchan);}        // if pin is not set to 0 then is in use so read the digital input
                      }
                }
              driveOutputs();
 
              if(BIT_CHECK(currentStatus.testIO_hardware, 0)) //if testenabled is set 
                {   
                  if(BIT_CHECK(currentStatus.testIO_hardware, 1) == 0) //and if testactive is clear 
                    {
                     BIT_CLEAR(currentStatus.testIO_hardware, 0);    //clear testenabled flag now all outputs have been forced
                    }
                }   
             
             for (byte EXinchanloop = 0; EXinchanloop <16 ; EXinchanloop++)
                {
                 if (BIT_CHECK(configPage1.exinsel,EXinchanloop))
                   {
                    getExternalInput(EXinchanloop);
                   }        // read the external inputs if enabled                           
                }   
             driveDisplay();      
       }                  
}
