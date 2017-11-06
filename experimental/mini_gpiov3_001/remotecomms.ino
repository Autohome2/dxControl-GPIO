#include <Arduino.h>

/*
mini gpio v0.002
Copyright (C) Darren Siepka
A full copy of the license may be found in the projects root directory

Based on code by Josh Stewart for the Speeduino project , see www.Speeduino.com for more info
*/

/*
This is called when a command is received over seriallink from external source
It parses the command and calls the relevant function
*/
#include "remotecomms.h"
#include "globals.h"

void remote_serial_command()
{

    switch (SERIALLink.read())
          {
          case 'A':
                  while (SERIALLink.available() == 0) {}
                  replylength = (SERIALLink.read());              //read in reply length
                  for (byte rdata = 0; rdata < replylength; rdata++) //read x bytes of data according to replylength
                      {
                       realtimebuffer[rdata] = (SERIALLink.read());
                      }
          break;  

          case 'r':           
                byte cmd;
                if ( SERIALLink.available() >= 2)
                    {
                      cmd =  SERIALLink.read();                    
                      if ((cmd >=64) && (cmd <80))        //16 commands for external analog data being READ by gpio
                        {
                          if ((configPage1.num_bytes[(cmd-64)]&3) == 1) //(rlength == 1)
                            {
                             realtimebuffer[0] = SERIALLink.read();
                             realtimebuffer[1] = 0;
                            }
                          if ((configPage1.num_bytes[(cmd-64)]&3) == 2) //(rlength == 2)
                            {
                             realtimebuffer[0] = SERIALLink.read();
                             realtimebuffer[1] = SERIALLink.read();  
                            }
                          //currentStatus.dev1 = cmd;    
                          //currentStatus.EXin[(cmd-64)] = word(realtimebuffer[1],realtimebuffer[0]) ;
                          currentStatus.EXin[(cmd-64)] = (realtimebuffer[1]<<8) | realtimebuffer[0];
                        }
                    }                                        
          break;
          
          case 'R':
                  byte tmp0;
                  byte tmp1;
                  byte canin_channel;
                  uint16_t Rdata;
                  uint16_t Rlocation;
                  if ( SERIALLink.available() >= 3)
                     {             
                      canin_channel = SERIALLink.read();                        
                      tmp0 = SERIALLink.read();                //read in lsb of source can address 
                      //Rdata = tmp;
                      tmp1 = SERIALLink.read();                     
                  Rdata = tmp1<<8 | tmp0 ;
   currentStatus.dev1 = Rdata;           //Rdata holds the source can address
  // currentStatus.dev2 = configPage1.master_controller_address+256;    //master controller adress +256 == the gpio base can id
  currentStatus.dev2 = canin_channel;
                  //    Rdata = word(SERIALLink.read(), tmp);   //read msb of source can address and combine it to make the 16bit value
                      if (Rdata > (configPage1.master_controller_address+0x100))   // && (Rdata < (configPage1.master_controller_address + 0x150)) )      //0x100 == 256dec , 0x150 == 336dec
                          {       
                            Rlocation = Rdata - (configPage1.master_controller_address+0x100);
                           // currentStatus.dev2 = Rlocation;
                                  if (Rlocation <=32)         //1 - 32 are reserved for digital inputs
                                    {
                                      // input is digital
                                      if (BIT_CHECK(currentStatus.digIn, (Rlocation-1)))
                                          {
                                            //bit is on so set to 1023  
                                            Gdata[0] = 255;
                                            Gdata[1] = 3;
                                          }
                                    else
                                          {
                                            // bit is off so set to 0      
                                            Gdata[0] = 0;
                                            Gdata[1] = 0;
                                          }
                                    }
                                  if((Rlocation <= 81) && (Rlocation >= 65))
                                    {
                                      // input is analog  
                                      Gdata[0] = lowByte(currentStatus.Analog[(Rlocation-65)]);
                                      Gdata[1] = highByte(currentStatus.Analog[(Rlocation-65)]);
                                 //    currentStatus.dev1 = Gdata[0];// Gdata[1]<<8 | Gdata[0];           //build Rdata to hold the paramgroup can address
                                 //    currentStatus.dev2 = Gdata[1];//currentStatus.Analog[(Rlocation-65)];
                                    }
                                    
                                 else 
                                    {
                                      return;     //the addrerss did not match any of GPIO sources   
                                    }
                                
                          }
                  
                      SERIALLink.write("G");                      // reply "G" cmd
                      SERIALLink.write(1);                        //send 1 to confirm cmd received and valid
                      SERIALLink.write(canin_channel);             //confirms the destination channel
                      for (byte Gx = 0; Gx < 8; Gx++)           //write all 8 bytes of data
                        {
                          SERIALLink.write(Gdata[Gx]);
                        }
                     }   
          break;
          
        }
 
}

void getExternalInput(uint8_t Xchan)
{
  uint16_t exOffset;
  uint16_t exLength;
   
  //now lookup speeduino output offset from list based on can address 
  //configPage1.speeduinoBaseCan holds the base address

  if (((configPage1.INdata_from_Can[Xchan]&2047)+0x100) == ((configPage1.speeduinoBaseCan&2047)+0x100)) //if indata can address == speeduino base can address
      {
       switch ((configPage1.speeduinoConnection&3))   //the bitwise & blanks off the unused upper 6 bits
          {
          case 1:         //if direct connected to serial3?
          exOffset = configPage1.data_from_offset[Xchan];
          exLength = (configPage1.num_bytes[Xchan]&3);

          SERIALLink.write(commandletterr);          // send command letter to the Speeduino
          SERIALLink.write(tsCanId);                 // canid
          SERIALLink.write((64+Xchan));                    // cmd
          SERIALLink.write(lowByte(exOffset));
          SERIALLink.write(highByte(exOffset));
          SERIALLink.write(lowByte(exLength));
          SERIALLink.write(highByte(exLength));      

         break;

         case 2:
          // send via canbus   
         break;
          }
      }    
   else if (((configPage1.INdata_from_Can[(Xchan-1)]&2047)+0x100) != ((configPage1.speeduinoBaseCan&2047)+0x100)) // base can address is not that of speeduino
      {
       //address is not speeduino so talk to the other device via canbus
       //make canbus calls 
      }

}      
