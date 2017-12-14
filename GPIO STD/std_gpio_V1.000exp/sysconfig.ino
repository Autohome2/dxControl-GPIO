
/* in addition to this file see the canbus.h and display.h files for configuration of the canbus and display sections respectively */
/* This file contains the configuration of the board pin to function mapping, and the noTsConfig( only used if TS is NOT enabled) */
 
void noTsConfig()
{
  /* This function is in place of the load config and is used to set the configuration values that would normally be setup in TS */
  /* if the NO_TS define == 1 then the TS console serial port will NOT work and all values must be set here */
  
  configPage1.master_controller_address = 0x105-addressoffset ;
  configPage1.pinLayout = 2;
  configPage1.speeduinoConnection = 1;                //type of connection to speedy , 0==none 1 == serial3 2 == canbus
  configPage1.speeduinoBaseCan  = 0x220-addressoffset ;             //speeduino base can address 
  configPage1.canModuleConfig = 0b00000000 ;            //bit flags for canmodule configuration
  configPage1.generalConfig1 = 0b00000000 ;
  configPage1.exinsel = 0b0000000000000000 ;            // External input channel enabled bit flags the lsb is channel 1 , msb chan16
  configPage1.INdata_from_Can[0] = 0x100-addressoffset;             // can address of source of data 0x100(256dec) to 0x7FF(2047dec) as 0 dec - 535 dec
  configPage1.INdata_from_Can[1] = 0x100-addressoffset;
  configPage1.INdata_from_Can[2] = 0x100-addressoffset;
  configPage1.INdata_from_Can[3] = 0x100-addressoffset;
  configPage1.INdata_from_Can[4] = 0x100-addressoffset;
  configPage1.INdata_from_Can[5] = 0x100-addressoffset;
  configPage1.INdata_from_Can[6] = 0x100-addressoffset;
  configPage1.INdata_from_Can[7] = 0x100-addressoffset;
  configPage1.INdata_from_Can[8] = 0x100-addressoffset;
  configPage1.INdata_from_Can[9] = 0x100-addressoffset;
  configPage1.INdata_from_Can[10] = 0x100-addressoffset;
  configPage1.INdata_from_Can[11] = 0x100-addressoffset;
  configPage1.INdata_from_Can[12] = 0x100-addressoffset;
  configPage1.INdata_from_Can[13] = 0x100-addressoffset;
  configPage1.INdata_from_Can[14] = 0x100-addressoffset;
  configPage1.INdata_from_Can[15] = 0x100-addressoffset;
  configPage1.data_from_offset[0] = 0;        // offset of data source 0 - 255
  configPage1.data_from_offset[1] = 0;
  configPage1.data_from_offset[2] = 0;
  configPage1.data_from_offset[3] = 0;
  configPage1.data_from_offset[4] = 0;
  configPage1.data_from_offset[5] = 0;
  configPage1.data_from_offset[6] = 0;
  configPage1.data_from_offset[7] = 0;
  configPage1.data_from_offset[8] = 0;
  configPage1.data_from_offset[9] = 0;
  configPage1.data_from_offset[10] = 0;
  configPage1.data_from_offset[11] = 0 ;
  configPage1.data_from_offset[12] = 0;
  configPage1.data_from_offset[13] = 0;
  configPage1.data_from_offset[14] = 0;
  configPage1.data_from_offset[15] = 0;
  configPage1.num_bytes[0] = 0;              // number of bytes length of data source 0,1,or 2
  configPage1.num_bytes[1] = 0;
  configPage1.num_bytes[2] = 0 ;
  configPage1.num_bytes[3] = 0;
  configPage1.num_bytes[4] = 0;
  configPage1.num_bytes[5] = 0;
  configPage1.num_bytes[6] = 0;
  configPage1.num_bytes[7] = 0;
  configPage1.num_bytes[8] = 0;
  configPage1.num_bytes[9] = 0;
  configPage1.num_bytes[10] = 0;
  configPage1.num_bytes[11] = 0;
  configPage1.num_bytes[12] = 0;
  configPage1.num_bytes[13] = 0;
  configPage1.num_bytes[14] = 0;
  configPage1.num_bytes[15] = 0;
  //configPage2.port_Enabled[16];                // 1 if enabled 0 if not
  //configPage2.port_Condition[16];              // < is 60, = is 61, > is 62, & is 38
  //configPage2port_Condition_relationship[16]; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  //configPage2port_InitValue[16];              // 1 on 0 off
  //configPage2port_PortValue[16];              // 1 if active high 0 if active low
  //configPage2port_OutSize[16];                // unsure of purpose but must be present
  //configPage2port_OutOffset[16];              // port offset refers to the offset value from the output channels
  //configPage2port_Threshold[16];              // threshhold value for on/off
  //configPage2port_Hysteresis[16];             // hysteresis value for on/off
  //configPage2port_CanId[16];                  // TScanid of the device the output channel is from  
  // configPage3.canbroadcast_config;  
//configPage3.canbroadcast_sel;
  configPage3.canbroadcast_source_can_address[0]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[1]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[2]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[3]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[4]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[5]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[6]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[7]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[8]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[9]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[10]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[11]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[12]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[13]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[14]  = 0x220-addressoffset;
  configPage3.canbroadcast_source_can_address[15]  = 0x220-addressoffset;
  configPage3.canbroadcast_chan_offset[0] = 14;                               //the outchannel offset to the first(if more than one) byte of data
  configPage3.canbroadcast_chan_offset[1] = 14;
  configPage3.canbroadcast_chan_offset[2] = 14;
  configPage3.canbroadcast_chan_offset[3] = 14;
  configPage3.canbroadcast_chan_offset[4] = 14;
  configPage3.canbroadcast_chan_offset[5] = 14;
  configPage3.canbroadcast_chan_offset[6] = 14;
  configPage3.canbroadcast_chan_offset[7] = 14;
  configPage3.canbroadcast_chan_offset[8] = 14;
  configPage3.canbroadcast_chan_offset[9] = 14;
  configPage3.canbroadcast_chan_offset[10] = 14;
  configPage3.canbroadcast_chan_offset[11] = 14;
  configPage3.canbroadcast_chan_offset[12] = 14;
  configPage3.canbroadcast_chan_offset[13] = 14;
  configPage3.canbroadcast_chan_offset[14] = 14;
  configPage3.canbroadcast_chan_offset[15] = 14;
  //configPage3.canbroadcast_chan_size[16] = 2;                               // the number of bytes that make up the data
  //configPage3.canbroadcast_chan_canid[16] = 0; 
  configPage3.canbroadcast_freq[0] = 0;                                     //0 == 4hz , 1 == 5hz , 2 == 10hz , 3 == 15hz , 4 == 20hz 
  configPage3.canbroadcast_freq[1] = 0;
  configPage3.canbroadcast_freq[2] = 0;
  configPage3.canbroadcast_freq[3] = 0;
  configPage3.canbroadcast_freq[4] = 0;
  configPage3.canbroadcast_freq[5] = 0;
  configPage3.canbroadcast_freq[6] = 0;
  configPage3.canbroadcast_freq[7] = 0;
  configPage3.canbroadcast_freq[8] = 0;
  configPage3.canbroadcast_freq[9] = 0;
  configPage3.canbroadcast_freq[10] = 0;
  configPage3.canbroadcast_freq[11] = 0;
  configPage3.canbroadcast_freq[12] = 0;
  configPage3.canbroadcast_freq[13] = 0;
  configPage3.canbroadcast_freq[14] = 0;
  configPage3.canbroadcast_freq[15] = 0;
  configPage3.gpio_obd_address = 0x7E8-addressoffset;                       //GPIO OBD diagnostic address
  configPage3.speeduino_obd_address = 0x7E8-addressoffset;                       //Speeduino OBD diagnostic address
  configPage4.remoteoutput_sel_0_16 = 0b0000000000000000;
  configPage4.remoteoutput_sel_17_31 = 0b0000000000000000;
  //configPage4.remoteoutput_can_address[32] = 0x220-addressoffset;
  //configPage4.remoteoutput_port[32] = 0;
  configPage4.remoteoutput_statusEnable_0_16 = 0b0000000000000000;
  configPage4.remoteoutput_statusEnable_17_31 = 0b0000000000000000;
  //configPage4.remoteoutput_freq[32] = 0;               //0 == 4hz , 1 == 5hz , 2 == 10hz , 3 == 15hz , 4 == 20hz   
  configPage4.remoteinput_sel_0_16 = 0b0000000000000000;
  configPage4.remoteinput_sel_17_31 = 0b0000000000000000;
  //configPage4.remoteinput_can_address[32] = 0x200-addressoffset;
  //configPage4.remoteinput_port[32] = 0;
  //configPage4.remoteinput_freq[32] = 0;               //0 == 4hz , 1 == 5hz , 2 == 10hz , 3 == 15hz , 4 == 20hz   
  configPage4.remoteAninput_sel = 0b0000000000000000;
  configPage4.remoteAninput_can_address[0] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[1] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[2] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[3] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[4] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[5] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[6] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[7] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[8] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[9] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[10] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[11] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[12] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[13] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[14] = 0x100-addressoffset;
  configPage4.remoteAninput_can_address[15] = 0x100-addressoffset;
  //configPage4.remoteAninput_port[16] = 0;
  //configPage4.remoteAninput_freq[16] = 0;               //0 == 4hz , 1 == 5hz , 2 == 10hz , 3 == 15hz , 4 == 20hz 
 
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
      #if defined(CORE_AVR)
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
      pinIn[20] = 29;
      pinIn[21] = 255;
      pinIn[22] = 22;
      pinIn[23] = 23;
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
      pinAin[9] = A8;
      pinAin[10] = A9;
      pinAin[11] = A10;
      pinAin[12] = A11;
      pinAin[13] = A12;
      pinAin[14] = A13;
      pinAin[15] = A14;
      pinAin[16] = 255; //A15;
      
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

  }

  setpinmodes();  //now set pin modes eg input,output or analog
  
}
