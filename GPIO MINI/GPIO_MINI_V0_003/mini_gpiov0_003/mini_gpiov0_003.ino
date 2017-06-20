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
#include <EEPROM.h>

#if defined (MCU_STM32F103C8)
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

// setup which serial port connects to the speeduino
#if defined(ARDUINO_AVR_MEGA2560)
  // mega pin assignments
HardwareSerial &SERIALLink = Serial3;

#elif defined(MCU_STM32F103C8)
 #define SERIALLink Serial2

//#elif defined (MCU_STM32F103C8)//(STM32_MCU_SERIES) || defined(STM32F1) || defined(STM32F4) || defined(STM32)
  // stm32 pin assignments

#elif defined(ARDUINO_NUCLEO_64)//(CORE_STM32)
  #define SERIALLink Serial2 
  
#else
  #error Incorrect board selected. Please select the correct board (Usually Mega 2560) and upload again  
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
volatile byte Achanloop;
volatile byte diginchanloop;
volatile byte driveoutloop;
volatile byte EXinchanloop;

void setup() {
  // put your setup code here, to run once:
 loadConfig();
 setPinMapping(configPage1.pinLayout);
 initialiseADC();
 initialiseTimers();
    
 Serial.begin(115200);       // your console serial port
#if defined(ARDUINO_AVR_MEGA2560) 
Serial3.begin(115200);
#elif defined(MCU_STM32F103C8) 
Serial2.begin(115200);
#endif

 SERIALLink.begin(115200);  

  mainLoopCount = 0;
  BIT_SET(currentStatus.systembits, 0); //set system ready flag
  initialOutputs();   //run the initialoutputs once to begin to preset initial on states   
}

void loop()
{
  // put your main code here, to run repeatedly:
      mainLoopCount++;
      //Check for any requets from serial. Serial operations are checked under 2 scenarios:
      // 1) Every 64 loops (64 Is more than fast enough for TunerStudio). This function is equivalent to ((loopCount % 64) == 1) but is considerably faster due to not using the mod or division operations
      // 2) If the amount of data in the serial buffer is greater than a set threhold (See globals.h). This is to avoid serial buffer overflow when large amounts of data is being sent
      if ( ((mainLoopCount & 63) == 1) or ( SERIALLink.available() > 32) )
        {
          if ( SERIALLink.available() > 0)      // if SERIALLink has data then do the command subroutine
            {
             remote_serial_command();
            }
        } 
            
      if ( ((mainLoopCount & 63) == 1) or (Serial.available() > 32) )
        {
         if (Serial.available() > 0)      // if Serial has data then do the command subroutine
           {
            direct_serial_command();
           }
        }
        
       if ((mainLoopCount & 63) == 1) //Every 32 loops read analog and digital inputs
            {
             if (pinAin[Achanloop] < 255) {readAnalog(Achanloop);}        // read the analog inputs
              if (Achanloop < 16)
                {
                  Achanloop++;
                }
              else
                {
                  Achanloop = 0;
                }
              
             if (pinIn[diginchanloop] < 255) { readDigitalIn(diginchanloop);}        // if pin is not set to 0 then is in use so read the digital input
              if (diginchanloop < 16)
                {
                  diginchanloop++;
                }
              else
                {
                  diginchanloop = 0;
                }
            }

       if ((mainLoopCount & 63) == 1) //Every 32 loops do outputs
            {
            driveOutputs(driveoutloop); 
                         if (driveoutloop < 16)
                {
                  driveoutloop++;
                }
              else
                {
                  driveoutloop = 0;
                  if(BIT_CHECK(currentStatus.testOutputs, 0)) //if testenabled is set 
                      {   
                      if(BIT_CHECK(currentStatus.testOutputs, 1) == 0) //and if testactive is clear 
                          {
                            BIT_CLEAR(currentStatus.testOutputs, 0);    //clear testenabled flag now all outputs have been forced
                          }
                      }   
                } 
            }

       if ((mainLoopCount & 63) == 1) //Every 64 loops read analog and digital inputs
            {
             if (BIT_CHECK(configPage1.exinsel,(EXinchanloop-1)))
               {
                getExternalInput(EXinchanloop);
               }        // read the external inputs if enabled
                           
             if (EXinchanloop < 16)
                {
                  EXinchanloop++;
                }
              else
                {
                  EXinchanloop = 0;
                }    
            }                  
}
