
/* in addition to this file see the canbus.h and display.h files for configuration of the canbus and display sections respectively */
/* This file contains the configuration of the board pin to function mapping, and the noTsConfig( only used if TS is NOT enabled) */
 

void setPinMapping(byte boardID)
{ 
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
      pinOut[17] = 255; //
      pinOut[18] = 255; //
      pinOut[19] = 255; //
      pinOut[20] = 255; //
      pinOut[21] = 255; //
      pinOut[22] = 255; //
      pinOut[23] = 255; //
      pinOut[24] = 255; //
      pinOut[25] = 255; //
      pinOut[26] = 255; //
      pinOut[27] = 255; //
      pinOut[28] = 255; //
      pinOut[29] = 255; //
      pinOut[30] = 255; //
      pinOut[31] = 255; //
      pinOut[32] = 255; //

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
      pinIn[17] = 255;
      pinIn[18] = 255;
      pinIn[19] = 255;
      pinIn[20] = 255;
      pinIn[21] = 255;
      pinIn[22] = 255;
      pinIn[23] = 255;
      pinIn[24] = 255;
      pinIn[25] = 255;
      pinIn[26] = 255;
      pinIn[27] = 255;
      pinIn[28] = 255;
      pinIn[29] = 255;
      pinIn[30] = 255;
      pinIn[31] = 255;
      pinIn[32] = 255;
                   
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
      #if defined(MEGA_AVR)
      case 1: // mega2560 default V1.000
      pinOut[1] = 255; //
      pinOut[2] = 2; //
      pinOut[3] = 3; //
      pinOut[4] = 255; //
      pinOut[5] = 255; //
      pinOut[6] = 255; //
      pinOut[7] = 7; //
      pinOut[8] = 255; //
      pinOut[9] = 255; //
      pinOut[10] = 255; //
      pinOut[11] = 255; //
      pinOut[12] = 255; //
      pinOut[13] = 13; //
      pinOut[14] = 255; //
      pinOut[15] = 255; //
      pinOut[16] = 16; //
      pinOut[17] = 255; //
      pinOut[18] = 255; //
      pinOut[19] = 255; //
      pinOut[20] = 255; //
      pinOut[21] = 255; //
      pinOut[22] = 255; //
      pinOut[23] = 255; //
      pinOut[24] = 24; //
      pinOut[25] = 25; //
      pinOut[26] = 26; //
      pinOut[27] = 27; //
      pinOut[28] = 255; //
      pinOut[29] = 255; //
      pinOut[30] = 255; //
      pinOut[31] = 255; //
      pinOut[32] = 255; //
      
      pinIn[1] = 255;
      pinIn[2] = 255;
      pinIn[3] = 255;
      pinIn[4] = 255;
      pinIn[5] = 5;
      pinIn[6] = 6;
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
      pinIn[17] = 255;
      pinIn[18] = 255;
      pinIn[19] = 255;
      pinIn[20] = 255;
      pinIn[21] = 255;
      pinIn[22] = 255;
      pinIn[23] = 255;
      pinIn[24] = 255;
      pinIn[25] = 255;
      pinIn[26] = 255;
      pinIn[27] = 255;
      pinIn[28] = 255;
      pinIn[29] = 255;
      pinIn[30] = 255;
      pinIn[31] = 255;
      pinIn[32] = 255;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = A4;
      pinAin[6] = 255; // A5;
      pinAin[7] = A6;
      pinAin[8] = A7;
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
      pinOut[17] = 255; //
      pinOut[18] = 255; //
      pinOut[19] = 255; //
      pinOut[20] = 255; //
      pinOut[21] = 255; //
      pinOut[22] = 255; //
      pinOut[23] = 255; //
      pinOut[24] = 255; //
      pinOut[25] = 255; //
      pinOut[26] = 255; //
      pinOut[27] = 255; //
      pinOut[28] = 255; //
      pinOut[29] = 255; //
      pinOut[30] = 255; //
      pinOut[31] = 255; //
      pinOut[32] = 255; //
      
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
      pinIn[17] = 255;
      pinIn[18] = 255;
      pinIn[19] = 255;
      pinIn[20] = 255;
      pinIn[21] = 255;
      pinIn[22] = 255;
      pinIn[23] = 255;
      pinIn[24] = 255;
      pinIn[25] = 255;
      pinIn[26] = 255;
      pinIn[27] = 255;
      pinIn[28] = 255;
      pinIn[29] = 255;
      pinIn[30] = 255;
      pinIn[31] = 255;
      pinIn[32] = 255;
                   
             
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

      #if defined(MEGA_AVR)
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
      pinOut[17] = 255; //
      pinOut[18] = 255; //
      pinOut[19] = 255; //
      pinOut[20] = 255; //
      pinOut[21] = 255; //
      pinOut[22] = 255; //
      pinOut[23] = 255; //
      pinOut[24] = 255; //
      pinOut[25] = 255; //
      pinOut[26] = 255; //
      pinOut[27] = 255; //
      pinOut[28] = 255; //
      pinOut[29] = 255; //
      pinOut[30] = 255; //
      pinOut[31] = 255; //
      pinOut[32] = 255; //

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
      pinIn[17] = 255;
      pinIn[18] = 255;
      pinIn[19] = 255;
      pinIn[20] = 255;
      pinIn[21] = 255;
      pinIn[22] = 255;
      pinIn[23] = 255;
      pinIn[24] = 255;
      pinIn[25] = 255;
      pinIn[26] = 255;
      pinIn[27] = 255;
      pinIn[28] = 255;
      pinIn[29] = 255;
      pinIn[30] = 255;
      pinIn[31] = 255;
      pinIn[32] = 255;
                   
             
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
      
      break;
      #endif

      #if defined(MEGA_AVR)
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
      pinOut[17] = 255; //
      pinOut[18] = 255; //
      pinOut[19] = 255; //
      pinOut[20] = 255; //
      pinOut[21] = 255; //
      pinOut[22] = 255; //
      pinOut[23] = 255; //
      pinOut[24] = 255; //
      pinOut[25] = 255; //
      pinOut[26] = 255; //
      pinOut[27] = 255; //
      pinOut[28] = 255; //
      pinOut[29] = 255; //
      pinOut[30] = 255; //
      pinOut[31] = 255; //
      pinOut[32] = 255; //

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
      pinIn[17] = 255;
      pinIn[18] = 255;
      pinIn[19] = 255;
      pinIn[20] = 255;
      pinIn[21] = 255;
      pinIn[22] = 255;
      pinIn[23] = 255;
      pinIn[24] = 255;
      pinIn[25] = 255;
      pinIn[26] = 255;
      pinIn[27] = 255;
      pinIn[28] = 255;
      pinIn[29] = 255;
      pinIn[30] = 255;
      pinIn[31] = 255;
      pinIn[32] = 255;
                   
             
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
      
      #if defined(AVR_324)
      case 5: // ATmega324 default V1.000
      pinOut[1] = 255; //
      pinOut[2] = 2; //
      pinOut[3] = 3; //
      pinOut[4] = 255; //
      pinOut[5] = 255; //
      pinOut[6] = 255; //
      pinOut[7] = 7; //
      pinOut[8] = 255; //
      pinOut[9] = 255; //
      pinOut[10] = 255; //
      pinOut[11] = 255; //
      pinOut[12] = 255; //
      pinOut[13] = 13; //
      pinOut[14] = 255; //
      pinOut[15] = 255; //
      pinOut[16] = 16; //
      pinOut[17] = 255; //
      pinOut[18] = 255; //
      pinOut[19] = 255; //
      pinOut[20] = 255; //
      pinOut[21] = 255; //
      pinOut[22] = 255; //
      pinOut[23] = 255; //
      pinOut[24] = 255; //
      pinOut[25] = 255; //
      pinOut[26] = 255; //
      pinOut[27] = 255; //
      pinOut[28] = 255; //
      pinOut[29] = 255; //
      pinOut[30] = 255; //
      pinOut[31] = 255; //
      pinOut[32] = 255; //
      
      pinIn[1] = 255;
      pinIn[2] = 255;
      pinIn[3] = 255;
      pinIn[4] = 255;
      pinIn[5] = 5;
      pinIn[6] = 6;
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
      pinIn[17] = 255;
      pinIn[18] = 255;
      pinIn[19] = 255;
      pinIn[20] = 255;
      pinIn[21] = 255;
      pinIn[22] = 255;
      pinIn[23] = 255;
      pinIn[24] = 255;
      pinIn[25] = 255;
      pinIn[26] = 255;
      pinIn[27] = 255;
      pinIn[28] = 255;
      pinIn[29] = 255;
      pinIn[30] = 255;
      pinIn[31] = 255;
      pinIn[32] = 255;
             
      pinAin[1] = A0;
      pinAin[2] = A1;
      pinAin[3] = A2;
      pinAin[4] = A3;
      pinAin[5] = A4;
      pinAin[6] = 255; // A5;
      pinAin[7] = A6;
      pinAin[8] = A7;
      pinAin[9] = 255;
      pinAin[10] = 255;
      pinAin[11] = 255;
      pinAin[12] = 255;
      pinAin[13] = 255;
      pinAin[14] = 255;
      pinAin[15] = 255;
      pinAin[16] = 255; //A15;
      
      break;
      #endif 

  }

  setpinmodes();  //now set pin modes eg input,output or analog
  
}
