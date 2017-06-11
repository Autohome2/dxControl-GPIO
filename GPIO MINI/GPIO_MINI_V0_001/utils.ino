/*
  Returns how much free dynamic memory exists (between heap and stack)
*/
#include "utils.h"

int freeRam ()
{
//#if defined(CORE_AVR)
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
//#elif defined(CORE_TEENSY)
//  uint32_t stackTop;
//  uint32_t heapTop;

  // current position of the stack.
//  stackTop = (uint32_t) &stackTop;

  // current position of heap.
//  void* hTop = malloc(1);
//  heapTop = (uint32_t) hTop;
//  free(hTop);

  // The difference is the free, available ram.
//  return (uint16_t)stackTop - heapTop;
//#elif defined(CORE_STM32)
  //Figure this out some_time
//  return 0;
//#endif
}

void setPinMapping(byte boardID)
{
    switch (boardID)
  {
    case 0:   //pro-mini demo V0.001
      pinOut[1] = 2; //
      pinOut[2] = 3; //
      pinOut[3] = 4; //
      pinOut[4] = 5; //
      pinOut[5] = 0; //
      pinOut[6] = 0; //
      pinOut[7] = 0; //
      pinOut[8] = 0; //
      pinOut[9] = 0; //
      pinOut[10] = 0; //
      pinOut[11] = 0; //
      pinOut[12] = 0; //
      pinOut[13] = 0; //
      pinOut[14] = 0; //
      pinOut[15] = 0; //
      pinOut[16] = 0; //

      pinIn[1] = 6;
      pinIn[2] = 7;
      pinIn[3] = 8;
      pinIn[4] = 9;
      pinIn[5] = 0;
      pinIn[6] = 0;
      pinIn[7] = 0;
      pinIn[8] = 0;
      pinIn[9] = 0;
      pinIn[10] = 0;
      pinIn[11] = 0;
      pinIn[12] = 0;
      pinIn[13] = 0;
      pinIn[14] = 0;
      pinIn[15] = 0;
      pinIn[16] = 0;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = 0;
      pinAin[6] = 0;
      pinAin[7] = 0;
      pinAin[8] = 0;
      pinAin[9] = 0;
      pinAin[10] = 0;
      pinAin[11] = 0;
      pinAin[12] = 0;
      pinAin[13] = 0;
      pinAin[14] = 0;
      pinAin[15] = 0;
      pinAin[16] = 0;
      
      break;

      case 1:   // mega2560 demo V0.001
      pinOut[1] = 2; //
      pinOut[2] = 3; //
      pinOut[3] = 4; //
      pinOut[4] = 5; //
      pinOut[5] = 0; //
      pinOut[6] = 41; //
      pinOut[7] = 0; //
      pinOut[8] = 0; //
      pinOut[9] = 36; //
      pinOut[10] = 0; //
      pinOut[11] = 0; //
      pinOut[12] = 0; //
      pinOut[13] = 13; //
      pinOut[14] = 0; //
      pinOut[15] = 0; //
      pinOut[16] = 0; //

      pinIn[1] = 6;
      pinIn[2] = 7;
      pinIn[3] = 8;
      pinIn[4] = 9;
      pinIn[5] = 0;
      pinIn[6] = 0;
      pinIn[7] = 0;
      pinIn[8] = 0;
      pinIn[9] = 0;
      pinIn[10] = 0;
      pinIn[11] = 0;
      pinIn[12] = 0;
      pinIn[13] = 0;
      pinIn[14] = 0;
      pinIn[15] = 0;
      pinIn[16] = 0;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = 0;
      pinAin[6] = 0;
      pinAin[7] = 0;
      pinAin[8] = 0;
      pinAin[9] = 0;
      pinAin[10] = 0;
      pinAin[11] = 0;
      pinAin[12] = 0;
      pinAin[13] = 0;
      pinAin[14] = 0;
      pinAin[15] = 0;
      pinAin[16] = 0;
      
      break;

      #if defined(ARDUINO_AVR_MEGA2560)
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
      pinOut[13] = 0; //
      pinOut[14] = 0; //
      pinOut[15] = 0; //
      pinOut[16] = 0; //

      pinIn[1] = 12;
      pinIn[2] = 0;
      pinIn[3] = 0;
      pinIn[4] = 0;
      pinIn[5] = 0;
      pinIn[6] = 0;
      pinIn[7] = 0;
      pinIn[8] = 0;
      pinIn[9] = 0;
      pinIn[10] = 0;
      pinIn[11] = 0;
      pinIn[12] = 0;
      pinIn[13] = 0;
      pinIn[14] = 0;
      pinIn[15] = 0;
      pinIn[16] = 0;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = A8;
      pinAin[6] = 0;
      pinAin[7] = 0;
      pinAin[8] = 0;
      pinAin[9] = 0;
      pinAin[10] = 0;
      pinAin[11] = 0;
      pinAin[12] = 0;
      pinAin[13] = 0;
      pinAin[14] = 0;
      pinAin[15] = 0;
      pinAin[16] = 0;
      
      break;
      #endif

      #if defined(ARDUINO_AVR_MEGA2560)
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
      pinOut[15] = 0; //
      pinOut[16] = 0; //

      pinIn[1] = 12;
      pinIn[2] = 0;
      pinIn[3] = 0;
      pinIn[4] = 0;
      pinIn[5] = 0;
      pinIn[6] = 0;
      pinIn[7] = 0;
      pinIn[8] = 0;
      pinIn[9] = 0;
      pinIn[10] = 0;
      pinIn[11] = 0;
      pinIn[12] = 0;
      pinIn[13] = 0;
      pinIn[14] = 0;
      pinIn[15] = 0;
      pinIn[16] = 0;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = A8;
      pinAin[6] = 0;
      pinAin[7] = 0;
      pinAin[8] = 0;
      pinAin[9] = 0;
      pinAin[10] = 0;
      pinAin[11] = 0;
      pinAin[12] = 0;
      pinAin[13] = 0;
      pinAin[14] = 0;
      pinAin[15] = 0;
      pinAin[16] = 0;
      
      break;
      #endif
  }

//setup pin use flags for digouts
    for(byte p=1; p<17; p++)
        {
        if (pinOut[p] > 0)
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
        if (pinIn[p] > 0)
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
        if (pinAin[p] > 0)
          {
            BIT_SET(configPage1.AinchanActive, (p-1));
          }
        else
          {  
            BIT_CLEAR(configPage1.AinchanActive, (p-1));    
          }
        }
                                         
      if (pinOut[1] > 0){pinMode(pinOut[1], OUTPUT);}
      if (pinOut[2] > 0){pinMode(pinOut[2], OUTPUT);}
      if (pinOut[3] > 0){pinMode(pinOut[3], OUTPUT);}
      if (pinOut[4] > 0){pinMode(pinOut[4], OUTPUT);}
      if (pinOut[5] > 0){pinMode(pinOut[5], OUTPUT);}
      if (pinOut[6] > 0){pinMode(pinOut[6], OUTPUT);}
      if (pinOut[7] > 0){pinMode(pinOut[7], OUTPUT);}
      if (pinOut[8] > 0){pinMode(pinOut[8], OUTPUT);}
      if (pinOut[9] > 0){pinMode(pinOut[9], OUTPUT);}
      if (pinOut[10] > 0){pinMode(pinOut[10], OUTPUT);}
      if (pinOut[11] > 0){pinMode(pinOut[11], OUTPUT);}
      if (pinOut[12] > 0){pinMode(pinOut[12], OUTPUT);}
      if (pinOut[13] > 0){pinMode(pinOut[13], OUTPUT);}
      if (pinOut[14] > 0){pinMode(pinOut[14], OUTPUT);}
      if (pinOut[15] > 0){pinMode(pinOut[15], OUTPUT);}
      if (pinOut[16] > 0){pinMode(pinOut[16], OUTPUT);}
            
      if (pinIn[1] > 0){pinMode(pinIn[1], INPUT);}
      if (pinIn[2] > 0){pinMode(pinIn[2], INPUT);}
      if (pinIn[3] > 0){pinMode(pinIn[3], INPUT);}
      if (pinIn[4] > 0){pinMode(pinIn[4], INPUT);}
      if (pinIn[5] > 0){pinMode(pinIn[5], INPUT);}
      if (pinIn[6] > 0){pinMode(pinIn[6], INPUT);}
      if (pinIn[7] > 0){pinMode(pinIn[7], INPUT);}
      if (pinIn[8] > 0){pinMode(pinIn[8], INPUT);}
      if (pinIn[9] > 0){pinMode(pinIn[9], INPUT);}
      if (pinIn[10] > 0){pinMode(pinIn[10], INPUT);}
      if (pinIn[11] > 0){pinMode(pinIn[11], INPUT);}
      if (pinIn[12] > 0){pinMode(pinIn[12], INPUT);}
      if (pinIn[13] > 0){pinMode(pinIn[13], INPUT);}
      if (pinIn[14] > 0){pinMode(pinIn[14], INPUT);}
      if (pinIn[15] > 0){pinMode(pinIn[15], INPUT);}
      if (pinIn[16] > 0){pinMode(pinIn[16], INPUT);}
                  
      if (pinAin[1] > 0){ pinMode(pinAin[1], INPUT);}
      if (pinAin[2] > 0){ pinMode(pinAin[2], INPUT);}
      if (pinAin[3] > 0){ pinMode(pinAin[3], INPUT);}
      if (pinAin[4] > 0){ pinMode(pinAin[4], INPUT);}
      if (pinAin[5] > 0){ pinMode(pinAin[5], INPUT);}
      if (pinAin[6] > 0){ pinMode(pinAin[6], INPUT);}
      if (pinAin[7] > 0){ pinMode(pinAin[7], INPUT);}
      if (pinAin[8] > 0){ pinMode(pinAin[8], INPUT);}
      if (pinAin[9] > 0){ pinMode(pinAin[9], INPUT);}
      if (pinAin[10] > 0){ pinMode(pinAin[10], INPUT);}
      if (pinAin[11] > 0){ pinMode(pinAin[11], INPUT);}
      if (pinAin[12] > 0){ pinMode(pinAin[12], INPUT);}
      if (pinAin[13] > 0){ pinMode(pinAin[13], INPUT);}
      if (pinAin[14] > 0){ pinMode(pinAin[14], INPUT);}
      if (pinAin[15] > 0){ pinMode(pinAin[15], INPUT);}
      if (pinAin[16] > 0){ pinMode(pinAin[16], INPUT);}
}

