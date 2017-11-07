#include <Arduino.h>

/*
gpio mini
Copyright (C) Darren Siepka
A full copy of the license may be found in the projects root directory

Based on code by Josh Stewart for the Speeduino project , see www.Speeduino.com for more info
*/

/*
This is called when a command is received over serial from TunerStudio
It parses the command and calls the relevant function
*/
#include "directcomms.h"
#include "globals.h"
//#include "storage.h"


void direct_serial_command()
{
    switch (CONSOLE_SERIALLink.read())
          {
          case 'A':
                  direct_sendValues(0, direct_packetSize, 60);   //(offset,packet size lenght,cmd)
          break; 
           
          case 'B': // Burn current values to eeprom
                    writeConfig();
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
                    for (unsigned int sg = 0; sg < sizeof(simple_remote_signature) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(simple_remote_signature[sg]);  
                        }
          break;
          
          case 'S': // send code version
                    for (unsigned int sg = 0; sg < sizeof(simple_remote_RevNum) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(simple_remote_RevNum[sg]);
                        currentStatus.secl = 0; //This is required in TS3 due to its stricter timings
                        }
          break;

          case 'V': // send VE table and constants in binary
                  direct_sendPage(0,thistsCanId,0);
          break;

          case 'W': // receive new VE obr constant at 'W'+<offset>+<newbyte>
                while (CONSOLE_SERIALLink.available() == 0) {}
                tmp = CONSOLE_SERIALLink.read();
                while (CONSOLE_SERIALLink.available() == 0) {}
                theoffset = (CONSOLE_SERIALLink.read()<<8) | tmp;
                //theoffset = word(CONSOLE_SERIALLink.read(), tmp);
                while (CONSOLE_SERIALLink.available() == 0) {}
                direct_receiveValue(theoffset, CONSOLE_SERIALLink.read());
      }         
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
                theoffset = (CONSOLE_SERIALLink.read()<<8) | tmp;
               // theoffset = word(CONSOLE_SERIALLink.read(), tmp);
                while (CONSOLE_SERIALLink.available() == 0) {}
                tmp = CONSOLE_SERIALLink.read();
                
                if (cmd != 87)          //if is "W" only 1 more byte is sent
                 {
                  while (CONSOLE_SERIALLink.available() == 0) {}
                  thelength = (CONSOLE_SERIALLink.read()<<8) | tmp;
                 // thelength = word(CONSOLE_SERIALLink.read(), tmp); 
                 }
             else{thelength = tmp;}
         
             if (tsCanId_sent ==  thistsCanId)
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

return;
 
}
void dolocal_rCommands(uint8_t commandletter, uint8_t canid, uint16_t theoffset, uint16_t thelength)
{
  
    switch (commandletter)
           {
           case 15:    //
                    for (unsigned int sg = 0; sg < sizeof(simple_remote_signature) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(simple_remote_signature[sg]);  
                        }  
           break;
                        
           case 14:  //
                    for (unsigned int sg = 0; sg < sizeof(simple_remote_RevNum) - 1; sg++)
                        {
                        CONSOLE_SERIALLink.write(simple_remote_RevNum[sg]);
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
                    writeConfig();
           break;
           
           case 69: // r version of E == 0x45
                  commandButtons(theoffset);
           break;
                               
           case 80:  //r version of P == dec80
                  currentStatus.currentPage = byte(theoffset);
           break;
          
           case 86:  //r version of V == dec86
                  direct_sendPage(thelength,thistsCanId,86);
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
     //For some reason, TunerStudio is sending offsets greater than the maximum page size. I'm not sure if it's their bug or mine, but the fix is to only update the config page if the offset is less than the maximum size
      if ( rvOffset < page_1_size)
      {
        *((uint8_t *)pnt_configPage + (uint8_t)rvOffset) = newValue; //
      }
      break;

    case 2: //port editor config Page:
      pnt_configPage = &configPage2; //Setup a pointer to the relevant config page
     //For some reason, TunerStudio is sending offsets greater than the maximum page size. I'm not sure if it's their bug or mine, but the fix is to only update the config page if the offset is less than the maximum size
      if ( rvOffset < page_2_size)
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
Note that some translation of the data is required to lay it out in the way Megasqurit / TunerStudio expect it
useChar - If true, all values are send as chars, this is for the serial command line interface. TunerStudio expects data as raw values, so this must be set false in that case
*/
void direct_sendPage(uint16_t send_page_Length, byte can_id, byte cmd)
{

 //currentPage = pagenum;
 
        void* pnt_configPage;

        switch (currentStatus.currentPage)
          {

            case simple_remote_setupPage:  //veSetPage:
                {
                // currentTitleIndex = 27;

                pnt_configPage = &configPage1; //Create a pointer to Page 1 in memory  
                  send_page_Length = page_1_size; 
                }
            break;  

            case port_editor_config:  //port editor config Page:
                {
                // currentTitleIndex = 27;

                pnt_configPage = &configPage2; //Create a pointer to Page 2 in memory  
                  send_page_Length = page_2_size; 
                }
            break;

          }
    
          //All other bytes can simply be copied from the config table
          
          uint8_t response[send_page_Length];
          for ( uint16_t x = 0; x < send_page_Length; x++)
            {
              response[x] = *((uint8_t *)pnt_configPage + (uint16_t)(x)); //Each byte is simply the location in memory of the configPage + the offset(not used) + the variable number (x)
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

void direct_sendValues(uint16_t offset, uint16_t packetLength, uint8_t cmd)
{
  
  byte fullStatus[direct_packetSize];
  byte response[packetLength];

    if(direct_requestCount == 0) { currentStatus.secl = 0; }
    direct_requestCount++;

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

  switch (cmdCombined)
  {   
    case 256: // cmd is stop    
      BIT_CLEAR(currentStatus.testIO_hardware, 1);    //clear testactive flag
      currentStatus.digOut = 0;                   //reset all outputs to off
      break;

    case 257: // cmd is enable
      // currentStatus.testactive = 1;
      BIT_SET(currentStatus.testIO_hardware, 0);  //set testenabled flag    
      BIT_SET(currentStatus.testIO_hardware, 1);  //set testactive flag
      break;
          
    case 513:
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
  }
}        
