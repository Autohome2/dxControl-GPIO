#include <Arduino.h>

/*
gpio mini
Copyright (C) Darren Siepka
A full copy of the license may be found in the projects root directory

Based on code by Josh Stewart for the Speeduino project , see www.Speeduino.com for more info
*/

#include "globals.h"
#include "directcomms.h"
#include "remotecomms.h"
#include "storage.h"
#include "utils.h"

/*
This is called when a command is received over serial from TunerStudio
It parses the command and calls the relevant function
*/
void direct_serial_command()
{
    switch (CONSOLE_SERIALLink.read())
          {
          case 'A':
                  direct_sendValues(0, direct_packetSize, 60);//(offset,packet size lenght,cmd)
          break; 
           
          case 'B': // Burn current values to eeprom
                  //A 2nd byte of data is required after the 'P' specifying the new page number.
                  while (CONSOLE_SERIALLink.available() == 0) {}
                  currentStatus.currentPage = CONSOLE_SERIALLink.read();
                  BIT_CLEAR(currentStatus.systembits, BIT_SYSTEM_BURN_GOOD); //clear burn_good flag
                  writeConfig(currentStatus.currentPage);
          break;

          case 'C': // test communications. This is used by Tunerstudio to see whether there is an ECU on a given serial port
                  //      testComm();
          break;

          case 'E': // receive command button commands
                  byte tmp;
                  uint16_t theoffset;
                  while (CONSOLE_SERIALLink.available() == 0) {}
                  tmp = CONSOLE_SERIALLink.read();
                  while (CONSOLE_SERIALLink.available() == 0) {}
                  theoffset = (CONSOLE_SERIALLink.read()<<8) | tmp;
                 // theoffset = word(CONSOLE_SERIALLink.read(), tmp);
                  commandButtons(theoffset);
          break;
          
          case 'F': // send serial protocol version
                  CONSOLE_SERIALLink.print("001");
          break;

          case 'P': // set the current page
                    //A 2nd byte of data is required after the 'P' specifying the new page number.
                  while (CONSOLE_SERIALLink.available() == 0) {}
                  currentStatus.currentPage = CONSOLE_SERIALLink.read();
                  if (currentStatus.currentPage >= '0') {//This converts the ascii number char into binary
                  currentStatus.currentPage -= '0';
                  }
          break;
      
          case 'Q': // send code version
               // CONSOLE_SERIALLink.print("speeduino mini_GPIOV3.003 201711");
                    for (unsigned int sg = 0; sg < sizeof(GPIO_signature) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(GPIO_signature[sg]);  
                        }
          break;
          
          case 'S': // send code version
                    for (unsigned int sg = 0; sg < sizeof(GPIO_RevNum) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(GPIO_RevNum[sg]);
                        currentStatus.secl = 0; //This is required in TS3 due to its stricter timings
                        }
          break;

          case 'V': // send VE table and constants in binary
                while (CONSOLE_SERIALLink.available() == 0) {}
                tmp = CONSOLE_SERIALLink.read();
                while (CONSOLE_SERIALLink.available() == 0) {}
                theoffset = (CONSOLE_SERIALLink.read()<<8) | tmp;
               // theoffset = word(CONSOLE_SERIALLink.read(), tmp);
                while (CONSOLE_SERIALLink.available() == 0) {}
                tmp = CONSOLE_SERIALLink.read();
                while (CONSOLE_SERIALLink.available() == 0) {}
                thelength = (CONSOLE_SERIALLink.read()<<8) | tmp;
 
                direct_sendPage(theoffset,thelength,thistsCanId,0);
          break;

          case 'W': // receive new data value at 'W'+<offset>+<newbyte>
                //A 2nd byte of data is required after the 'P' specifying the new page number.
                //if (CONSOLE_SERIALLink.available() >= 3)
                //  {
                    //while (CONSOLE_SERIALLink.available() == 0) {}
              //      currentStatus.currentPage = CONSOLE_SERIALLink.read();
                while (CONSOLE_SERIALLink.available() == 0) {}
                tmp = CONSOLE_SERIALLink.read();
                while (CONSOLE_SERIALLink.available() == 0) {}
                theoffset = (CONSOLE_SERIALLink.read()<<8) | tmp;
                         //theoffset = word(CONSOLE_SERIALLink.read(), tmp);  this was replaced with the line above as not all cores supported the word option
                while (CONSOLE_SERIALLink.available() == 0) {}
                tmp = CONSOLE_SERIALLink.read();
                direct_receiveValue(theoffset, tmp);                      // 
                  
          break;

     
          case 'r': 
                byte cmd;
                byte tsCanId_sent;         
                while (CONSOLE_SERIALLink.available() == 0) {}
                tsCanId_sent = CONSOLE_SERIALLink.read(); //Read the $tsCanId
                while (CONSOLE_SERIALLink.available() == 0) {}
                cmd = CONSOLE_SERIALLink.read();
                      while (CONSOLE_SERIALLink.available() == 0) {}
                      tmp = CONSOLE_SERIALLink.read();
                      while (CONSOLE_SERIALLink.available() == 0) {}
                      theoffset = word(CONSOLE_SERIALLink.read(), tmp);
                      while (CONSOLE_SERIALLink.available() == 0) {}
                      tmp = CONSOLE_SERIALLink.read();
                      if (cmd != 87)          //if is "W" only 1 more byte is sent
                       {
                        while (CONSOLE_SERIALLink.available() == 0) {}
                          if ((cmd == 0x0f) || (cmd == 0x0e))          //if cmd is 14 or 15
                            { 
                             thelength = word(tmp, CONSOLE_SERIALLink.read());     //for some strange reason TS sends the canid check hard coded as big endian! 
                            } 
                            
                          else
                            {
                             thelength = word(CONSOLE_SERIALLink.read(), tmp);
                            }
                        
                       }
                      else{thelength = tmp;}

           //   currentStatus.dev1 = theoffset;
           //   currentStatus.dev2 = thelength;
          
             if (tsCanId_sent ==  thistsCanId)        //was the canid sent by TS the same as this device TScanID?
               {
                dolocal_rCommands(cmd,tsCanId_sent,theoffset,thelength);
               }
             else
               {
                //not this device can id 
                if (configPage1.speeduinoConnection == 1)
                  {
                   // connected to speeduino via serial3 direct do this
                   //directtsPassthrough(tsCanId_sent ,cmd, offset, length)  ;
                  }
                else if (configPage1.speeduinoConnection == 2)
                  {
                   // connected to speeduino via canbus do this 
                  }
                else if (configPage1.speeduinoConnection == 0)
                  {
                   // speeduino not connected so ignore 
                  }
                            
               }            
          break;
    
    }
//return;
 
}

void dolocal_rCommands(uint8_t commandletter, uint8_t canid, uint16_t theoffset, uint16_t thelength)
{
  
    switch (commandletter)
           {
           case 15:    //  0x0f 
                    for (unsigned int sg = 0; sg < sizeof(GPIO_signature) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(GPIO_signature[sg]);  
                        }
           break;
                        
           case 14:  //   0x0e
                    for (unsigned int sg = 0; sg < sizeof(GPIO_RevNum) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(GPIO_RevNum[sg]);
                        currentStatus.secl = 0; //This is required in TS3 due to its stricter timings
                        }     
           break;
                        
           case 48:    //previously 0x30:
                                // CONSOLE_SERIALLink.print("got to 3d");
                                 // direct_sendValues(offset, length, cmd);
           break;
                        
           case 60:  //(0x3c+120 == 0xB4(112dec)):       
                   direct_sendValues(theoffset, thelength, 60);
           break;

           case 66: // r version of B == 0x42
                    // Burn current values to eeprom
                    currentStatus.currentPage = byte(theoffset);
                    BIT_CLEAR(currentStatus.systembits, BIT_SYSTEM_BURN_GOOD); //clear burn_good flag
                    writeConfig(currentStatus.currentPage);
           break;
           
           case 69: // r version of E == 0x45
                  commandButtons(theoffset);
           break;
                               
           case 80:  //r version of P == dec80
                  currentStatus.currentPage = byte(theoffset);
           break;
          
           case 86:  //r version of V == dec86
                  direct_sendPage(theoffset,thelength,thistsCanId,86);
           break;
                    
           case 87:  //r version of W(0x57)
                 // int valueOffset; //cannot use offset as a variable name, it is a reserved word for several teensy libraries
                  direct_receiveValue(theoffset, thelength);  //CONSOLE_SERIALLink.read());                    
           break;
       } //closes the switch/case 
}


void direct_receiveValue(uint16_t rvOffset, uint8_t newValue)
{      
        
  void* pnt_configPage;//This only stores the address of the value that it's pointing to and not the max size

  switch (currentStatus.currentPage)
  {

    case 1: //simple_remote_setupPage:
      pnt_configPage = &configPage1; //Setup a pointer to the relevant config page
     //For some reason, TunerStudio is sending offsets greater than the maximum page size. I'm not sure if it's their bug or mine, 
     //but the fix is to only update the config page if the offset is less than the maximum size
      if ( rvOffset < page_1_size)
      {
        *((uint8_t *)pnt_configPage + (uint8_t)rvOffset) = newValue; //
      }
      break;

    case 2: //port editor config Page:
      pnt_configPage = &configPage2; //Setup a pointer to the relevant config page
     //For some reason, TunerStudio is sending offsets greater than the maximum page size. I'm not sure if it's their bug or mine, 
     //but the fix is to only update the config page if the offset is less than the maximum size
      if ( rvOffset < page_2_size)
      {
        *((uint8_t *)pnt_configPage + (uint16_t)rvOffset) = newValue; //
      }
    break;

    case 3: //canbus config Page:
      pnt_configPage = &configPage3; //Setup a pointer to the relevant config page
     //For some reason, TunerStudio is sending offsets greater than the maximum page size. I'm not sure if it's their bug or mine,
     //but the fix is to only update the config page if the offset is less than the maximum size
      if ( rvOffset < page_3_size)
      {
        *((uint8_t *)pnt_configPage + (uint16_t)rvOffset) = newValue; //
      }
    break;
      
    case 4: //canbus remote io config Page:
      pnt_configPage = &configPage4; //Setup a pointer to the relevant config page
     //For some reason, TunerStudio is sending offsets greater than the maximum page size. I'm not sure if it's their bug or mine,
     //but the fix is to only update the config page if the offset is less than the maximum size
      if ( rvOffset < page_4_size)
      {
        *((uint8_t *)pnt_configPage + (uint16_t)rvOffset) = newValue; //
      }
    break;
  }
}

 //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
sendPage() packs the data within the current page (As set with the 'P' command)
into a buffer and sends it.
Note that some translation of the data is required to lay it out in the way TunerStudio expect it
useChar - If true, all values are send as chars, this is for the serial command line interface. TunerStudio expects data as raw values, so this must be set false in that case
*/
void direct_sendPage(uint16_t send_page_offset, uint16_t send_page_Length, byte can_id, byte cmd)
{

 //currentPage = pagenum;
 
        void* pnt_configPage;

        switch (currentStatus.currentPage)
          {

            case simple_remote_setupPage:  //veSetPage:
                {
                // currentTitleIndex = 27;

                pnt_configPage = &configPage1; //Create a pointer to Page 1 in memory  
                  //send_page_Length = page_1_size; 
                }
            break;  

            case port_editor_config:  //port editor config Page:
                {
                // currentTitleIndex = 27;

                pnt_configPage = &configPage2; //Create a pointer to Page 2 in memory  
                  //send_page_Length = page_2_size; 
                }
            break;

            case canbus_config:  //can broadcast config Page:
                {
                pnt_configPage = &configPage3; //Create a pointer to Page 3 in memory  
                  //send_page_Length = page_3_size; 
                }
            break;
            
            case remotecanio_config:  //remote canbus io config Page:
                {
                pnt_configPage = &configPage4; //Create a pointer to Page 3 in memory  
                  //send_page_Length = page_4_size; 
                }
            break;
          }
    
          //All other bytes can simply be copied from the config table
          
          uint8_t response[send_page_Length];
          for ( uint16_t x = 0; x < send_page_Length; x++)
            {
              response[x] = *((uint8_t *)pnt_configPage +(uint16_t)(send_page_offset)+ (uint16_t)(x)); //Each byte is simply the location in memory of the configPage + the offset(not used) + the variable number (x)
            }

          if (cmd == 206)   //came via passthrough from serial3
            {
              SERIALLink.print("r");
              SERIALLink.write(thistsCanId);                //canId of the device you are requesting data from
              SERIALLink.write(cmd);                       //  
              SERIALLink.write(zero);                       // dummy offset lsb
              SERIALLink.write(zero);                       // dummy offset msb
              SERIALLink.write(lowByte(send_page_Length));  // length lsb
              SERIALLink.write(highByte(send_page_Length)); // length msb
              SERIALLink.write((uint8_t *)&response, sizeof(response));          
            }
          else
          {  
          CONSOLE_SERIALLink.write((uint8_t *)&response, sizeof(response));
          }
      
}

/*
This function is used to store calibration data sent by Tuner Studio.
*/
void direct_receiveCalibration(byte tableID)
{

}

/*
 this function reads the realtime data into the fullStatus array
*/
 void direct_read_realtime()
 {
  fullStatus[0] = currentStatus.secl; //secl is simply a counter that increments each second. Used to track unexpected resets (Which will reset this count to 0)
  fullStatus[1] = currentStatus.systembits; //Squirt Bitfield
  fullStatus[2] = currentStatus.canstatus;  //canstatus Bitfield
  fullStatus[3] = lowByte(currentStatus.loopsPerSecond);
  fullStatus[4] = highByte(currentStatus.loopsPerSecond);
    //The following can be used to show the amount of free memory
  currentStatus.freeRAM = freeRam();
  fullStatus[5] = lowByte(currentStatus.freeRAM); //(byte)((currentStatus.loopsPerSecond >> 8) & 0xFF);
  fullStatus[6] = highByte(currentStatus.freeRAM);
  fullStatus[7] = lowByte(mainLoopCount);
  fullStatus[8] = highByte(mainLoopCount);
  fullStatus[9] = lowByte(currentStatus.dev1);
  fullStatus[10] = highByte(currentStatus.dev1);
  fullStatus[11] = lowByte(currentStatus.dev2);
  fullStatus[12] = highByte(currentStatus.dev2);
  fullStatus[13] = currentStatus.testIO_hardware;
  fullStatus[14] = lowByte(currentStatus.digIn);
  fullStatus[15] = highByte(currentStatus.digIn);
  fullStatus[16] = lowByte(currentStatus.digIn_2);
  fullStatus[17] = highByte(currentStatus.digIn_2);
  fullStatus[18] = lowByte(currentStatus.digOut);    
  fullStatus[19] = highByte(currentStatus.digOut);
  fullStatus[20] = lowByte(currentStatus.digOut_2);    
  fullStatus[21] = highByte(currentStatus.digOut_2);
  fullStatus[22] = lowByte(currentStatus.Analog[0]);
  fullStatus[23] = highByte(currentStatus.Analog[0]);
  fullStatus[24] = lowByte(currentStatus.Analog[1]);
  fullStatus[25] = highByte(currentStatus.Analog[1]);
  fullStatus[26] = lowByte(currentStatus.Analog[2]);
  fullStatus[27] = highByte(currentStatus.Analog[2]);
  fullStatus[28] = lowByte(currentStatus.Analog[3]);
  fullStatus[29] = highByte(currentStatus.Analog[3]);  
  fullStatus[30] = lowByte(currentStatus.Analog[4]);
  fullStatus[31] = highByte(currentStatus.Analog[4]);
  fullStatus[32] = lowByte(currentStatus.Analog[5]);
  fullStatus[33] = highByte(currentStatus.Analog[5]);
  fullStatus[34] = lowByte(currentStatus.Analog[6]);
  fullStatus[35] = highByte(currentStatus.Analog[6]);
  fullStatus[36] = lowByte(currentStatus.Analog[7]);
  fullStatus[37] = highByte(currentStatus.Analog[7]);
  fullStatus[38] = lowByte(currentStatus.Analog[8]);
  fullStatus[39] = highByte(currentStatus.Analog[8]);
  fullStatus[40] = lowByte(currentStatus.Analog[9]);
  fullStatus[41] = highByte(currentStatus.Analog[9]);
  fullStatus[42] = lowByte(currentStatus.Analog[10]);
  fullStatus[43] = highByte(currentStatus.Analog[10]);
  fullStatus[44] = lowByte(currentStatus.Analog[11]);
  fullStatus[45] = highByte(currentStatus.Analog[11]);  
  fullStatus[46] = lowByte(currentStatus.Analog[12]);
  fullStatus[47] = highByte(currentStatus.Analog[12]);
  fullStatus[48] = lowByte(currentStatus.Analog[13]);
  fullStatus[49] = highByte(currentStatus.Analog[13]);
  fullStatus[50] = lowByte(currentStatus.Analog[14]);
  fullStatus[51] = highByte(currentStatus.Analog[14]);
  fullStatus[52] = lowByte(currentStatus.Analog[15]);
  fullStatus[53] = highByte(currentStatus.Analog[15]);    
  fullStatus[54] = lowByte(currentStatus.EXin[0]);
  fullStatus[55] = highByte(currentStatus.EXin[0]);
  fullStatus[56] = lowByte(currentStatus.EXin[1]);
  fullStatus[57] = highByte(currentStatus.EXin[1]);
  fullStatus[58] = lowByte(currentStatus.EXin[2]);
  fullStatus[59] = highByte(currentStatus.EXin[2]);
  fullStatus[60] = lowByte(currentStatus.EXin[3]);
  fullStatus[61] = highByte(currentStatus.EXin[3]);  
  fullStatus[62] = lowByte(currentStatus.EXin[4]);
  fullStatus[63] = highByte(currentStatus.EXin[4]);
  fullStatus[64] = lowByte(currentStatus.EXin[5]);
  fullStatus[65] = highByte(currentStatus.EXin[5]);
  fullStatus[66] = lowByte(currentStatus.EXin[6]);
  fullStatus[67] = highByte(currentStatus.EXin[6]);
  fullStatus[68] = lowByte(currentStatus.EXin[7]);
  fullStatus[69] = highByte(currentStatus.EXin[7]);
  fullStatus[70] = lowByte(currentStatus.EXin[8]);
  fullStatus[71] = highByte(currentStatus.EXin[8]);
  fullStatus[72] = lowByte(currentStatus.EXin[9]);
  fullStatus[73] = highByte(currentStatus.EXin[9]);
  fullStatus[74] = lowByte(currentStatus.EXin[10]);
  fullStatus[75] = highByte(currentStatus.EXin[10]);
  fullStatus[76] = lowByte(currentStatus.EXin[11]);
  fullStatus[77] = highByte(currentStatus.EXin[11]);  
  fullStatus[78] = lowByte(currentStatus.EXin[12]);
  fullStatus[79] = highByte(currentStatus.EXin[12]);
  fullStatus[80] = lowByte(currentStatus.EXin[13]);
  fullStatus[81] = highByte(currentStatus.EXin[13]);
  fullStatus[82] = lowByte(currentStatus.EXin[14]);
  fullStatus[83] = highByte(currentStatus.EXin[14]);
  fullStatus[84] = lowByte(currentStatus.EXin[15]);
  fullStatus[85] = highByte(currentStatus.EXin[15]); 
 // fullStatus[82] = lowByte(currentStatus.dev3);
 // fullStatus[83] = highByte(currentStatus.dev3);
 // fullStatus[84] = lowByte(currentStatus.dev4);
 // fullStatus[85] = highByte(currentStatus.dev4);   
  
 }

/*
this function sends the realtime data to TS
*/ 
void direct_sendValues(uint16_t offset, uint16_t packetLength, uint8_t cmd)
{
  
  byte response[packetLength];

    if(direct_requestCount == 0) { currentStatus.secl = 0; }
    direct_requestCount++;

    direct_read_realtime();
  
    for(byte x=0; x<packetLength; x++)
  {
    response[x] = fullStatus[offset+x];
  }

  if (cmd == 60)
    {
      CONSOLE_SERIALLink.write(response, (size_t)packetLength); 
      //CONSOLE_SERIALLink.write(response, (size_t)packetLength);
    }
  else if (cmd == 180)
    {
      //CONSOLE_SERIALLink.print("r was sent");
      SERIALLink.write("r");         //confirm cmd letter 
      SERIALLink.write(zero);           //canid
      SERIALLink.write(cmd);          //confirm cmd
      SERIALLink.write(lowByte(offset));                       //start offset lsb
      SERIALLink.write(highByte(offset));                      //start offset msb
      SERIALLink.write(lowByte(packetLength));      //confirm no of byte to be sent
      SERIALLink.write(highByte(packetLength));      //confirm no of byte to be sent
      SERIALLink.write(response, (size_t)packetLength); //stream the realtime data requested
    }   
  return;
}

void commandButtons(uint16_t cmdCombined)
{
  
 // currentStatus.dev1 = cmdCombined;
  
  switch (cmdCombined)
  {   
    case 256: // cmd is stop    
      BIT_CLEAR(currentStatus.testIO_hardware, 1);    //clear testactive flag
      currentStatus.digOut = 0;                   //reset all outputs to off
      currentStatus.digOut_2 = 0;                   //reset all outputs to off
      currentStatus.digIn = 0;                   //reset all inputs to off
      currentStatus.digIn_2 = 0;                   //reset all inputs to off
      break;

    case 257: // cmd is enable
      // currentStatus.testactive = 1;
      BIT_SET(currentStatus.testIO_hardware, 0);  //set testenabled flag    
      BIT_SET(currentStatus.testIO_hardware, 1);  //set testactive flag
      break;
          
    case 513:  // cmd group is on actions
    case 514:
    case 515:
    case 516:
    case 517:
    case 518:
    case 519:
    case 520:
    case 521:
    case 522:
    case 523:
    case 524:
    case 525:
    case 526:
    case 527:
    case 528: // cmd group is on actions
          if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_SET(currentStatus.digOut, (cmdCombined-513));
        }
    break;
    
    case 529:  // cmd group is on actions
    case 530:
    case 531:
    case 532:
    case 533:
    case 534:
    case 535:
    case 536:
    case 537:
    case 538:
    case 539:
    case 540:
    case 541:
    case 542:
    case 543:
    case 544:
    /* to do case 529: ... 544: is a GCC extension , the above method is official C method see http://forum.arduino.cc/index.php?topic=247382.0 */
      if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_SET(currentStatus.digOut_2, (cmdCombined-529));
        }
      break;
      
    case 769: // cmd group is off actions
    case 770:
    case 771:
    case 772:
    case 773:
    case 774:
    case 775:
    case 776:
    case 777:
    case 778:
    case 779:
    case 780:
    case 781:
    case 782:
    case 783:
    case 784:
      if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_CLEAR(currentStatus.digOut, (cmdCombined-769));
        }
    break;
    
    case 785:
    case 786:
    case 787:
    case 788:
    case 789:
    case 790:
    case 791:
    case 792:
    case 793:
    case 794:
    case 795:
    case 796:
    case 797:
    case 798:
    case 799:
    case 800:
    /*...*/
      if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_CLEAR(currentStatus.digOut_2, (cmdCombined-785));
        }
    break;

    case 1281: // cmd group is on actions
    case 1282:
    case 1283:
    case 1284:
    case 1285:
    case 1286:
    case 1287:
    case 1288:
    case 1289:
    case 1290:
    case 1291:
    case 1292:
    case 1293:
    case 1294:
    case 1295:
    case 1296:
      if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_SET(currentStatus.digIn, (cmdCombined-1281));
        }
    break;
    
    case 1297:// cmd group is on actions
    case 1298:
    case 1299:
    case 1300:
    case 1301:
    case 1302:
    case 1303:
    case 1304:
    case 1305:
    case 1306:
    case 1307:
    case 1308:
    case 1309:
    case 1310:
    case 1311:
    case 1312:
    /*...*/
      if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_SET(currentStatus.digIn_2, (cmdCombined-1297));
        }
    break;

    case 1537: // cmd group is off actions
    case 1538:
    case 1539:
    case 1540:
    case 1541:
    case 1542:
    case 1543:
    case 1544:
    case 1545:
    case 1546:
    case 1547:
    case 1548:
    case 1549:
    case 1550:
    case 1551:
    case 1552:
      if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_CLEAR(currentStatus.digIn, (cmdCombined-1537));
        }
    break;
    
    case 1553:// cmd group is off actions
    case 1554:
    case 1555:
    case 1556:
    case 1557:
    case 1558:
    case 1559:
    case 1560:
    case 1561:
    case 1562:
    case 1563:
    case 1564:
    case 1565:
    case 1566:
    case 1567:
    case 1568:
    /*...*/
      if(BIT_CHECK(currentStatus.testIO_hardware, 1))
        {
          BIT_CLEAR(currentStatus.digIn_2, (cmdCombined-1553));
        }
    break;

  }
}        
