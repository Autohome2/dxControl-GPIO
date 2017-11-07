/*
  Returns how much free dynamic memory exists (between heap and stack)
*/
#include "utils.h"

uint16_t freeRam ()
{
#if defined (CORE_AVR)
  extern int __heap_start, *__brkval;
  uint16_t v;

  return (uint16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);

#elif defined(CORE_TEENSY)
  uint32_t stackTop;
  uint32_t heapTop;

  // current position of the stack.
  stackTop = (uint32_t) &stackTop;

  // current position of heap.
  void* hTop = malloc(1);
  heapTop = (uint32_t) hTop;
  free(hTop);

  // The difference is the free, available ram.
  return (uint16_t)stackTop - heapTop;
#elif defined(CORE_STM32)
  char top = 't';
  return &top - reinterpret_cast<char*>(sbrk(0));  //what is sbrk?
//  return 0;
#endif
}

void setPinMapping(byte boardID)
{
    //This is dumb, but it'll do for now to get things compiling
  #if defined(MCU_STM32F103C8)
    //STM32F1/variants/.../board.cpp
  //  #define A0  boardADCPins[0]
  //  #define A1  boardADCPins[1]
  //  #define A2  boardADCPins[2]
  //  #define A3  boardADCPins[3]
   // #define A4  boardADCPins[4]
 //   #define A5  boardADCPins[5]
 //   #define A6  boardADCPins[6]
 //   #define A7  boardADCPins[7]
 //   #define A8  boardADCPins[8]
 //   #define A9  boardADCPins[9]
    //STM32F1 have only 9 12bit adc
//    #define A10  boardADCPins[0]
 //   #define A11  boardADCPins[1]
 //   #define A12  boardADCPins[2]
 //   #define A13  boardADCPins[3]
 //   #define A14  boardADCPins[4]
//    #define A15  boardADCPins[5]
  #endif
  
    switch (boardID)
  {
    #if defined (__PRO_MINI__)
    case 0://pro-mini demo V0.001
      pinOut[1] = 2; //
      pinOut[2] = 3; //
      pinOut[3] = 4; //
      pinOut[4] = 5; //
      pinOut[5] = 255; //
      pinOut[6] = 255; //
      pinOut[7] = 255; //
      pinOut[8] = 255; //
      pinOut[9] = 255; //
      pinOut[10] = 255; //
      pinOut[11] = 255; //
      pinOut[12] = 255; //
      pinOut[13] = 255; //
      pinOut[14] = 255; //
      pinOut[15] = 255; //
      pinOut[16] = 255; //

      pinIn[1] = 6;
      pinIn[2] = 7;
      pinIn[3] = 8;
      pinIn[4] = 9;
      pinIn[5] = 255;
      pinIn[6] = 255;
      pinIn[7] = 255;
      pinIn[8] = 255;
      pinIn[9] = 255;
      pinIn[10] = 255;
      pinIn[11] = 255;
      pinIn[12] = 255;
      pinIn[13] = 255;
      pinIn[14] = 255;
      pinIn[15] = 255;
      pinIn[16] = 255;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = 255;
      pinAin[6] = 255;
      pinAin[7] = 255;
      pinAin[8] = 255;
      pinAin[9] = 255;
      pinAin[10] = 255;
      pinAin[11] = 255;
      pinAin[12] = 255;
      pinAin[13] = 255;
      pinAin[14] = 255;
      pinAin[15] = 255;
      pinAin[16] = 255;
      #endif
      
      break;
      #if defined(CORE_AVR)
      case 1: // mega2560 demo V0.001
      pinOut[1] = 2; //
      pinOut[2] = 3; //
      pinOut[3] = 4; //
      pinOut[4] = 5; //
      pinOut[5] = 255; //
      pinOut[6] = 255; //
      pinOut[7] = 255; //
      pinOut[8] = 255; //
      pinOut[9] = 255; //
      pinOut[10] = 255; //
      pinOut[11] = 255; //
      pinOut[12] = 255; //
      pinOut[13] = 13; //
      pinOut[14] = 255; //
      pinOut[15] = 255; //
      pinOut[16] = 255; //

      pinIn[1] = 6;
      pinIn[2] = 7;
      pinIn[3] = 8;
      pinIn[4] = 9;
      pinIn[5] = 255;
      pinIn[6] = 255;
      pinIn[7] = 255;
      pinIn[8] = 255;
      pinIn[9] = 255;
      pinIn[10] = 255;
      pinIn[11] = 255;
      pinIn[12] = 255;
      pinIn[13] = 255;
      pinIn[14] = 255;
      pinIn[15] = 255;
      pinIn[16] = 255;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = A4;
      pinAin[6] = A5;
      pinAin[7] = A6;
      pinAin[8] = A7;
      pinAin[9] = A8;
      pinAin[10] = A9;
      pinAin[11] = A10;
      pinAin[12] = A11;
      pinAin[13] = A12;
      pinAin[14] = A13;
      pinAin[15] = A14;
      pinAin[16] = A15;
      
      break;
      #endif 

      #if defined(MCU_STM32F103C8)
      case 2: // stm32F103C8 demo V0.003
      pinOut[1] = PB10; //
      pinOut[2] = PB11; //
      pinOut[3] = 255; //
      pinOut[4] = 255; //
      pinOut[5] = 255; //
      pinOut[6] = 255; //
      pinOut[7] = 255; //
      pinOut[8] = 255; //
      pinOut[9] = 255; //
      pinOut[10] = 255; //
      pinOut[11] = 255; //
      pinOut[12] = 255; //
      pinOut[13] = PC13; //
      pinOut[14] = 255; //
      pinOut[15] = 255; //
      pinOut[16] = 255; //

      pinIn[1] = 255;
      pinIn[2] = 255;
      pinIn[3] = 255;
      pinIn[4] = 255;
      pinIn[5] = 255;
      pinIn[6] = 255;
      pinIn[7] = 255;
      pinIn[8] = 255;
      pinIn[9] = 255;
      pinIn[10] = 255;
      pinIn[11] = 255;
      pinIn[12] = 255;
      pinIn[13] = 255;
      pinIn[14] = 255;
      pinIn[15] = 255;
      pinIn[16] = 255;
             
      pinAin[1] = PA0;
      pinAin[2] = PA1;
      pinAin[3] = PA2;
      pinAin[4] = PA3;
      pinAin[5] = PA4;
      pinAin[6] = PA5;
      pinAin[7] = PA6;
      pinAin[8] = PA7;
      pinAin[9] = 255;
      pinAin[10] = 255;
      pinAin[11] = 255;
      pinAin[12] = 255;
      pinAin[13] = 255;
      pinAin[14] = 255;
      pinAin[15] = 255;
      pinAin[16] = 255;
      //spi_portused = 1;
      
      break;
      #endif 

      #if defined(CORE_AVR)
      case 3:   // mega2560 using Speeduino V0.3 board
      pinOut[1] = 8; //
      pinOut[2] = 9; //
      pinOut[3] = 10; //
      pinOut[4] = 11; //
      pinOut[5] = 28; //
      pinOut[6] = 24; //
      pinOut[7] = 40; //
      pinOut[8] = 36; //
      pinOut[9] = 4; //
      pinOut[10] = 5; //
      pinOut[11] = 6; //
      pinOut[12] = 7; //
      pinOut[13] = 255; //
      pinOut[14] = 255; //
      pinOut[15] = 255; //
      pinOut[16] = 255; //

      pinIn[1] = 12;
      pinIn[2] = 255;
      pinIn[3] = 255;
      pinIn[4] = 255;
      pinIn[5] = 255;
      pinIn[6] = 255;
      pinIn[7] = 255;
      pinIn[8] = 255;
      pinIn[9] = 255;
      pinIn[10] = 255;
      pinIn[11] = 255;
      pinIn[12] = 255;
      pinIn[13] = 255;
      pinIn[14] = 255;
      pinIn[15] = 255;
      pinIn[16] = 255;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = A8;
      pinAin[6] = 255;
      pinAin[7] = 255;
      pinAin[8] = 255;
      pinAin[9] = 255;
      pinAin[10] = 255;
      pinAin[11] = 255;
      pinAin[12] = 255;
      pinAin[13] = 255;
      pinAin[14] = 255;
      pinAin[15] = 255;
      pinAin[16] = 255;
      
      break;
      #endif

      #if defined(CORE_AVR)
      case 4:   // mega2560 using Speeduino V0.4 board
      pinOut[1] = 8; //
      pinOut[2] = 9; //
      pinOut[3] = 10; //
      pinOut[4] = 11; //
      pinOut[5] = 40; //
      pinOut[6] = 38; //
      pinOut[7] = 52; //
      pinOut[8] = 50; //
      pinOut[9] = 4; //
      pinOut[10] = 5; //
      pinOut[11] = 6; //
      pinOut[12] = 7; //
      pinOut[13] = 45; //
      pinOut[14] = 47; //
      pinOut[15] = 255; //
      pinOut[16] = 255; //

      pinIn[1] = 12;
      pinIn[2] = 255;
      pinIn[3] = 255;
      pinIn[4] = 255;
      pinIn[5] = 255;
      pinIn[6] = 255;
      pinIn[7] = 255;
      pinIn[8] = 255;
      pinIn[9] = 255;
      pinIn[10] = 255;
      pinIn[11] = 255;
      pinIn[12] = 255;
      pinIn[13] = 255;
      pinIn[14] = 255;
      pinIn[15] = 255;
      pinIn[16] = 255;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = A8;
      pinAin[6] = 255;
      pinAin[7] = 255;
      pinAin[8] = 255;
      pinAin[9] = 255;
      pinAin[10] = 255;
      pinAin[11] = 255;
      pinAin[12] = 255;
      pinAin[13] = 255;
      pinAin[14] = 255;
      pinAin[15] = 255;
      pinAin[16] = 255;
      
      break;
      #endif
  }

//setup pin use flags for digouts
    for(byte p=1; p<17; p++)
        {
        if (pinOut[p] < 255)
          {
            BIT_SET(configPage1.DoutchanActive, (p-1));
          }
        else
          {  
            BIT_CLEAR(configPage1.DoutchanActive, (p-1));    
          }
        }

// setup pin use flags for dig ins
    for(byte p=1; p<17; p++)
        {
        if (pinIn[p] < 255)
          {
            BIT_SET(configPage1.DinchanActive, (p-1));
          }
        else
          {  
            BIT_CLEAR(configPage1.DinchanActive, (p-1));    
          }
        }

//seup pin use flags for analog ins
      for(byte p=1; p<17; p++)
        {
        if (pinAin[p] < 255)
          {
            BIT_SET(configPage1.AinchanActive, (p-1));
          }
        else
          {  
            BIT_CLEAR(configPage1.AinchanActive, (p-1));    
          }
        }
                                         
      if (pinOut[1] < 255){pinMode(pinOut[1], OUTPUT);}
      if (pinOut[2] < 255){pinMode(pinOut[2], OUTPUT);}
      if (pinOut[3] < 255){pinMode(pinOut[3], OUTPUT);}
      if (pinOut[4] < 255){pinMode(pinOut[4], OUTPUT);}
      if (pinOut[5] < 255){pinMode(pinOut[5], OUTPUT);}
      if (pinOut[6] < 255){pinMode(pinOut[6], OUTPUT);}
      if (pinOut[7] < 255){pinMode(pinOut[7], OUTPUT);}
      if (pinOut[8] < 255){pinMode(pinOut[8], OUTPUT);}
      if (pinOut[9] < 255){pinMode(pinOut[9], OUTPUT);}
      if (pinOut[10] < 255){pinMode(pinOut[10], OUTPUT);}
      if (pinOut[11] < 255){pinMode(pinOut[11], OUTPUT);}
      if (pinOut[12] < 255){pinMode(pinOut[12], OUTPUT);}
      if (pinOut[13] < 255){pinMode(pinOut[13], OUTPUT);}
      if (pinOut[14] < 255){pinMode(pinOut[14], OUTPUT);}
      if (pinOut[15] < 255){pinMode(pinOut[15], OUTPUT);}
      if (pinOut[16] < 255){pinMode(pinOut[16], OUTPUT);}
            
      if (pinIn[1] < 255){pinMode(pinIn[1], INPUT);}
      if (pinIn[2] < 255){pinMode(pinIn[2], INPUT);}
      if (pinIn[3] < 255){pinMode(pinIn[3], INPUT);}
      if (pinIn[4] < 255){pinMode(pinIn[4], INPUT);}
      if (pinIn[5] < 255){pinMode(pinIn[5], INPUT);}
      if (pinIn[6] < 255){pinMode(pinIn[6], INPUT);}
      if (pinIn[7] < 255){pinMode(pinIn[7], INPUT);}
      if (pinIn[8] < 255){pinMode(pinIn[8], INPUT);}
      if (pinIn[9] < 255){pinMode(pinIn[9], INPUT);}
      if (pinIn[10] < 255){pinMode(pinIn[10], INPUT);}
      if (pinIn[11] < 255){pinMode(pinIn[11], INPUT);}
      if (pinIn[12] < 255){pinMode(pinIn[12], INPUT);}
      if (pinIn[13] < 255){pinMode(pinIn[13], INPUT);}
      if (pinIn[14] < 255){pinMode(pinIn[14], INPUT);}
      if (pinIn[15] < 255){pinMode(pinIn[15], INPUT);}
      if (pinIn[16] < 255){pinMode(pinIn[16], INPUT);}

  #if defined(MCU_STM32F103C8)
      if (pinAin[1] < 255){ pinMode(pinAin[1], INPUT_ANALOG);}
      if (pinAin[2] > 255){ pinMode(pinAin[2], INPUT_ANALOG);}
      if (pinAin[3] > 255){ pinMode(pinAin[3], INPUT_ANALOG);}
      if (pinAin[4] > 255){ pinMode(pinAin[4], INPUT_ANALOG);}
      if (pinAin[5] > 255){ pinMode(pinAin[5], INPUT_ANALOG);}
      if (pinAin[6] > 255){ pinMode(pinAin[6], INPUT_ANALOG);}
      if (pinAin[7] > 255){ pinMode(pinAin[7], INPUT_ANALOG);}
      if (pinAin[8] > 255){ pinMode(pinAin[8], INPUT_ANALOG);}
      if (pinAin[9] > 255){ pinMode(pinAin[9], INPUT_ANALOG);}
      if (pinAin[10] > 255){ pinMode(pinAin[10], INPUT_ANALOG);}
      if (pinAin[11] > 255){ pinMode(pinAin[11], INPUT_ANALOG);}
      if (pinAin[12] > 255){ pinMode(pinAin[12], INPUT_ANALOG);}
      if (pinAin[13] > 255){ pinMode(pinAin[13], INPUT_ANALOG);}
      if (pinAin[14] > 255){ pinMode(pinAin[14], INPUT_ANALOG);}
      if (pinAin[15] > 255){ pinMode(pinAin[15], INPUT_ANALOG);}
      if (pinAin[16] > 255){ pinMode(pinAin[16], INPUT_ANALOG);}
#else                        
      if (pinAin[1] > 255){ pinMode(pinAin[1], INPUT);}
      if (pinAin[2] > 255){ pinMode(pinAin[2], INPUT);}
      if (pinAin[3] > 255){ pinMode(pinAin[3], INPUT);}
      if (pinAin[4] > 255){ pinMode(pinAin[4], INPUT);}
      if (pinAin[5] > 255){ pinMode(pinAin[5], INPUT);}
      if (pinAin[6] > 255){ pinMode(pinAin[6], INPUT);}
      if (pinAin[7] > 255){ pinMode(pinAin[7], INPUT);}
      if (pinAin[8] > 255){ pinMode(pinAin[8], INPUT);}
      if (pinAin[9] > 255){ pinMode(pinAin[9], INPUT);}
      if (pinAin[10] > 255){ pinMode(pinAin[10], INPUT);}
      if (pinAin[11] > 255){ pinMode(pinAin[11], INPUT);}
      if (pinAin[12] > 255){ pinMode(pinAin[12], INPUT);}
      if (pinAin[13] > 255){ pinMode(pinAin[13], INPUT);}
      if (pinAin[14] > 255){ pinMode(pinAin[14], INPUT);}
      if (pinAin[15] > 255){ pinMode(pinAin[15], INPUT);}
      if (pinAin[16] > 255){ pinMode(pinAin[16], INPUT);}
#endif     
}
