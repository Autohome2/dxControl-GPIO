
/* in addition to this file see the canbus.h and display.h files for configuration of the canbus and display sections respectively */
/* This file contains the configuration of the board pin to function mapping, and the noTsConfig( only used if TS is NOT enabled) */
 
void noTsConfig()
{
  /* This function is in place of the load config and is used to set the configuration values that would normally be setup in TS */
  /* if the NO_TS define == 1 then the TS console serial port will NOT work and all values must be set here */
  
  configPage1.master_controller_address = 0x105 - addressoffset ;
  configPage1.pinLayout = 1; 
//"ProMini GPIO v0.002" == 0, "Mega2560 GPIO v0.003" == 1, "STM32 BluePill GPIO V0.003" == 3, "Speeduino v0.3" == 4, "Speeduino v0.4" == 5, ", "Teensy 3.5 REf" == 10,  "SAMD Ref" == 20
  configPage1.speeduinoConnection = 1;                //type of connection to speedy , 0==none 1 == serial3 2 == canbus
  configPage1.speeduinoBaseCan  = 0x220 - addressoffset ;             //speeduino base can address 
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
  configPage1.num_bytes[0] = 1 ;              // number of bytes length of data source 0,1,or 2
  configPage1.num_bytes[1] = 1 ;
  configPage1.num_bytes[2] = 1 ;
  configPage1.num_bytes[3] = 1 ;
  configPage1.num_bytes[4] = 1 ;
  configPage1.num_bytes[5] = 1 ;
  configPage1.num_bytes[6] = 1 ;
  configPage1.num_bytes[7] = 1 ;
  configPage1.num_bytes[8] = 1 ;
  configPage1.num_bytes[9] = 1 ;
  configPage1.num_bytes[10] = 1 ;
  configPage1.num_bytes[11] = 1 ;
  configPage1.num_bytes[12] = 1 ;
  configPage1.num_bytes[13] = 1 ;
  configPage1.num_bytes[14] = 1 ;
  configPage1.num_bytes[15] = 1 ;
  //configPage2.port_Enabled[16];                // 1 if enabled 0 if not
  configPage2.port_Enabled[0] = 0;                // 1 if enabled 0 if not
  configPage2.port_Enabled[1] = 0;                // 1 if enabled 0 if not
  configPage2.port_Enabled[2] = 0;                // 1 if enabled 0 if not
  configPage2.port_Enabled[3] = 0;                // 1 if enabled 0 if not
  configPage2.port_Enabled[4] = 0;                // 1 if enabled 0 if not
  configPage2.port_Enabled[5] = 0;                // 1 if enabled 0 if not
  configPage2.port_Enabled[6] = 0;                // 1 if enabled 0 if not
  configPage2.port_Enabled[7] = 0 ;                // 1 if enabled 0 if not
  configPage2.port_Enabled[8] = 0 ;                // 1 if enabled 0 if not
  configPage2.port_Enabled[9] = 0 ;                // 1 if enabled 0 if not
  configPage2.port_Enabled[10] = 0 ;                // 1 if enabled 0 if not
  configPage2.port_Enabled[11] = 0 ;                // 1 if enabled 0 if not
  configPage2.port_Enabled[12] = 0 ;                // 1 if enabled 0 if not
  configPage2.port_Enabled[14] = 0 ;                // 1 if enabled 0 if not
  configPage2.port_Enabled[15] = 0 ;                // 1 if enabled 0 if not
  //configPage2.port_Condition[16];              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*0)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*1)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*2)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*3)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*4)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*5)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*6)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*7)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*8)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*9)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*10)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*11)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*12)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*13)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*14)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(1*15)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+0)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+1)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+2)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+3)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+4)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+5)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+6)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+7)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+8)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+9)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+10)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+11)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+12)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+13)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+14)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  configPage2.port_Condition[(16+15)] = 61 ;              // < is 60, = is 61, > is 62, & is 38
  //configPage2port_Condition_relationship[16]; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[0] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[1] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[2] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[3] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[4] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[5] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[6] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[7] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[8] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[9] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[10] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[11] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[12] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[13] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[14] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  configPage2.port_Condition_relationship[15] = 32 ; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33    
  //configPage2port_InitValue[16];              // 1 on 0 off
  configPage2.port_InitValue[0] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[1] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[2] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[3] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[4] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[5] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[6] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[7] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[8] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[9] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[10] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[11] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[12] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[13] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[14] = 0 ;              // 1 on 0 off
  configPage2.port_InitValue[15] = 0 ;              // 1 on 0 off
  //configPage2port_PortValue[16];              // 1 if active high 0 if active low
  configPage2.port_PortValue[0] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[1] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[2] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[3] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[4] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[5] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[6] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[7] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[8] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[9] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[10] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[11] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[12] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[13] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[14] = 1;              // 1 if active high 0 if active low
  configPage2.port_PortValue[15] = 1;              // 1 if active high 0 if active low
  //configPage2.port_OutSize[16];                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*0)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*1)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*2)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*3)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*4)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*5)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*6)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*7)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*8)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*9)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*10)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*11)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*12)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*13)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*14)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(1*15)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+0)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+1)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+2)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+3)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+4)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+5)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+6)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+7)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+8)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+9)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+10)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+11)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+12)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+13)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+14)] = 0;                // unsure of purpose but must be present
  configPage2.port_OutSize[(16+15)] = 0;                // unsure of purpose but must be present
  //configPage2.port_OutOffset[16];              // port offset refers to the offset value from the output channels
  configPage2.port_OutOffset[(1*0)] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[1] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[2] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[3] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[4] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[5] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[6] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[7] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[8] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[9] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[10] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[11] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[12] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[13] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[14] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  configPage2.port_OutOffset[15] = 17;              // port offset refers to the offset value from the output channels see extract from directsend
  /*  this is the outchannel list the fullstatus [] value is the out channel
  fullStatus[0] = currentStatus.secl; //secl is simply a counter that increments each second. Used to track unexpected resets (Which will reset this count to 0)
  fullStatus[1] = currentStatus.systembits; //Squirt Bitfield
  fullStatus[2] = lowByte(currentStatus.loopsPerSecond);
  fullStatus[3] = highByte(currentStatus.loopsPerSecond);
    //The following can be used to show the amount of free memory
  currentStatus.freeRAM = freeRam();
  fullStatus[4] = lowByte(currentStatus.freeRAM); //(byte)((currentStatus.loopsPerSecond >> 8) & 0xFF);
  fullStatus[5] = highByte(currentStatus.freeRAM);
  fullStatus[6] = lowByte(mainLoopCount);
  fullStatus[7] = highByte(mainLoopCount);
  fullStatus[8] = lowByte(currentStatus.dev1);
  fullStatus[9] = highByte(currentStatus.dev1);
  fullStatus[10] = lowByte(currentStatus.dev2);
  fullStatus[11] = highByte(currentStatus.dev2);
  fullStatus[12] = currentStatus.testIO_hardware;
  fullStatus[13] = lowByte(currentStatus.digIn);
  fullStatus[14] = highByte(currentStatus.digIn);
  fullStatus[15] = lowByte(currentStatus.digOut);    
  fullStatus[16] = highByte(currentStatus.digOut);
  fullStatus[17] = lowByte(currentStatus.Analog[0]);
  fullStatus[18] = highByte(currentStatus.Analog[0]);
  fullStatus[19] = lowByte(currentStatus.Analog[1]);
  fullStatus[20] = highByte(currentStatus.Analog[1]);
  fullStatus[21] = lowByte(currentStatus.Analog[2]);
  fullStatus[22] = highByte(currentStatus.Analog[2]);
  fullStatus[23] = lowByte(currentStatus.Analog[3]);
  fullStatus[24] = highByte(currentStatus.Analog[3]);  
  fullStatus[25] = lowByte(currentStatus.Analog[4]);
  fullStatus[26] = highByte(currentStatus.Analog[4]);
  fullStatus[27] = lowByte(currentStatus.Analog[5]);
  fullStatus[28] = highByte(currentStatus.Analog[5]);
  fullStatus[29] = lowByte(currentStatus.Analog[6]);
  fullStatus[30] = highByte(currentStatus.Analog[6]);
  fullStatus[31] = lowByte(currentStatus.Analog[7]);
  fullStatus[32] = highByte(currentStatus.Analog[7]);
  fullStatus[33] = lowByte(currentStatus.Analog[8]);
  fullStatus[34] = highByte(currentStatus.Analog[8]);
  fullStatus[35] = lowByte(currentStatus.Analog[9]);
  fullStatus[36] = highByte(currentStatus.Analog[9]);
  fullStatus[37] = lowByte(currentStatus.Analog[10]);
  fullStatus[38] = highByte(currentStatus.Analog[10]);
  fullStatus[39] = lowByte(currentStatus.Analog[11]);
  fullStatus[40] = highByte(currentStatus.Analog[11]);  
  fullStatus[41] = lowByte(currentStatus.Analog[12]);
  fullStatus[42] = highByte(currentStatus.Analog[12]);
  fullStatus[43] = lowByte(currentStatus.Analog[13]);
  fullStatus[44] = highByte(currentStatus.Analog[13]);
  fullStatus[45] = lowByte(currentStatus.Analog[14]);
  fullStatus[46] = highByte(currentStatus.Analog[14]);
  fullStatus[47] = lowByte(currentStatus.Analog[15]);
  fullStatus[48] = highByte(currentStatus.Analog[15]);    
  fullStatus[49] = lowByte(currentStatus.EXin[0]);
  fullStatus[50] = highByte(currentStatus.EXin[0]);
  fullStatus[51] = lowByte(currentStatus.EXin[1]);
  fullStatus[52] = highByte(currentStatus.EXin[1]);
  fullStatus[53] = lowByte(currentStatus.EXin[2]);
  fullStatus[54] = highByte(currentStatus.EXin[2]);
  fullStatus[55] = lowByte(currentStatus.EXin[3]);
  fullStatus[56] = highByte(currentStatus.EXin[3]);  
  fullStatus[57] = lowByte(currentStatus.EXin[4]);
  fullStatus[58] = highByte(currentStatus.EXin[4]);
  fullStatus[59] = lowByte(currentStatus.EXin[5]);
  fullStatus[60] = highByte(currentStatus.EXin[5]);
  fullStatus[61] = lowByte(currentStatus.EXin[6]);
  fullStatus[62] = highByte(currentStatus.EXin[6]);
  fullStatus[63] = lowByte(currentStatus.EXin[7]);
  fullStatus[64] = highByte(currentStatus.EXin[7]);
  fullStatus[65] = lowByte(currentStatus.EXin[8]);
  fullStatus[66] = highByte(currentStatus.EXin[8]);
  fullStatus[67] = lowByte(currentStatus.EXin[9]);
  fullStatus[68] = highByte(currentStatus.EXin[9]);
  fullStatus[69] = lowByte(currentStatus.EXin[10]);
  fullStatus[70] = highByte(currentStatus.EXin[10]);
  fullStatus[71] = lowByte(currentStatus.EXin[11]);
  fullStatus[72] = highByte(currentStatus.EXin[11]);  
  fullStatus[73] = lowByte(currentStatus.EXin[12]);
  fullStatus[74] = highByte(currentStatus.EXin[12]);
  fullStatus[75] = lowByte(currentStatus.EXin[13]);
  fullStatus[76] = highByte(currentStatus.EXin[13]);
  fullStatus[77] = lowByte(currentStatus.EXin[14]);
  fullStatus[78] = highByte(currentStatus.EXin[14]);
  fullStatus[79] = lowByte(currentStatus.EXin[15]);
  fullStatus[80] = highByte(currentStatus.EXin[15]);    

   */
  configPage2.port_Threshold[(1*0)] = 0 ;              // threshhold value for on/off
  configPage2.port_Hysteresis[(1*0)] = 0 ;             // hysteresis value for on/off
  configPage2.port_CanId[(1*0)] = 0 ;                  // TScanid of the device the output channel is from  
  // configPage3.canbroadcast_config;  
//configPage3.canbroadcast_sel;
//  configPage3.canbroadcast_source_can_address[0]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[1]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[2]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[3]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[4]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[5]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[6]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[7]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[8]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[9]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[10]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[11]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[12]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[13]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[14]  = 0x220-addressoffset;
//  configPage3.canbroadcast_source_can_address[15]  = 0x220-addressoffset;
//  configPage3.canbroadcast_chan_offset[0] = 14;                               //the outchannel offset to the first(if more than one) byte of data
 // configPage3.canbroadcast_chan_offset[1] = 14;
//  configPage3.canbroadcast_chan_offset[2] = 14;
//  configPage3.canbroadcast_chan_offset[3] = 14;
//  configPage3.canbroadcast_chan_offset[4] = 14;
//  configPage3.canbroadcast_chan_offset[5] = 14;
//  configPage3.canbroadcast_chan_offset[6] = 14;
//  configPage3.canbroadcast_chan_offset[7] = 14;
//  configPage3.canbroadcast_chan_offset[8] = 14;
//  configPage3.canbroadcast_chan_offset[9] = 14;
//  configPage3.canbroadcast_chan_offset[10] = 14;
//  configPage3.canbroadcast_chan_offset[11] = 14;
//  configPage3.canbroadcast_chan_offset[12] = 14;
//  configPage3.canbroadcast_chan_offset[13] = 14;
//  configPage3.canbroadcast_chan_offset[14] = 14;
//  configPage3.canbroadcast_chan_offset[15] = 14;
  //configPage3.canbroadcast_chan_size[16] = 2;                               // the number of bytes that make up the data
  //configPage3.canbroadcast_chan_canid[16] = 0; 
//  configPage3.canbroadcast_freq[0] = 0;                                     //0 == 4hz , 1 == 5hz , 2 == 10hz , 3 == 15hz , 4 == 20hz 
//  configPage3.canbroadcast_freq[1] = 0;
//  configPage3.canbroadcast_freq[2] = 0;
//  configPage3.canbroadcast_freq[3] = 0;
//  configPage3.canbroadcast_freq[4] = 0;
//  configPage3.canbroadcast_freq[5] = 0;
//  configPage3.canbroadcast_freq[6] = 0;
//  configPage3.canbroadcast_freq[7] = 0;
//  configPage3.canbroadcast_freq[8] = 0;
//  configPage3.canbroadcast_freq[9] = 0;
//  configPage3.canbroadcast_freq[10] = 0;
//  configPage3.canbroadcast_freq[11] = 0;
//  configPage3.canbroadcast_freq[12] = 0;
//  configPage3.canbroadcast_freq[13] = 0;
//  configPage3.canbroadcast_freq[14] = 0;
//  configPage3.canbroadcast_freq[15] = 0;
//  configPage3.gpio_obd_address = 0x7E8-addressoffset;                       //GPIO OBD diagnostic address
//  configPage3.speeduino_obd_address = 0x7E8-addressoffset;                       //Speeduino OBD diagnostic address
//  configPage4.remoteoutput_sel_0_16 = 0b0000000000000000;
//  configPage4.remoteoutput_sel_17_31 = 0b0000000000000000;
  //configPage4.remoteoutput_can_address[32] = 0x220-addressoffset;
  //configPage4.remoteoutput_port[32] = 0;
//  configPage4.remoteoutput_statusEnable_0_16 = 0b0000000000000000;
//  configPage4.remoteoutput_statusEnable_17_31 = 0b0000000000000000;
  //configPage4.remoteoutput_freq[32] = 0;               //0 == 4hz , 1 == 5hz , 2 == 10hz , 3 == 15hz , 4 == 20hz   
//  configPage4.remoteinput_sel_0_16 = 0b0000000000000000;
//  configPage4.remoteinput_sel_17_31 = 0b0000000000000000;
  //configPage4.remoteinput_can_address[32] = 0x200-addressoffset;
  //configPage4.remoteinput_port[32] = 0;
  //configPage4.remoteinput_freq[32] = 0;               //0 == 4hz , 1 == 5hz , 2 == 10hz , 3 == 15hz , 4 == 20hz   
//  configPage4.remoteAninput_sel = 0b0000000000000000;
//  configPage4.remoteAninput_can_address[0] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[1] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[2] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[3] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[4] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[5] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[6] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[7] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[8] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[9] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[10] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[11] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[12] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[13] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[14] = 0x100-addressoffset;
//  configPage4.remoteAninput_can_address[15] = 0x100-addressoffset;
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

      #if defined(TEENSY3_5)
      case 10:   // TEENSY 3.5 ref board
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

      #if defined(CORE_SAMD)
      case 20:   // SAMD ref board
      pinOut[1] = 13; //
      pinOut[2] = 255; //
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
      pinOut[13] = 255; //
      pinOut[14] = 255; //
      pinOut[15] = 255; //
      pinOut[16] = 255; //

      pinIn[1] = 6;
      pinIn[2] = 7;
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
      pinAin[5] = A4;
      pinAin[6] = A5;
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

      default:   // default blank board
      pinOut[1] = 13; //
      pinOut[2] = 255; //
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
      pinOut[13] = 255; //
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
             
      pinAin[1] = A0;
      pinAin[2] = 255;
      pinAin[3] = 255;
      pinAin[4] = 255;
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

  }

  setpinmodes();  //now set pin modes eg input,output or analog
  
}
