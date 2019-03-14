void CAN0_INT_routine()
{ 
  #if OBD_CANPORT == 0
        #if OBD_ACTIVE == 1
            //obd_command(0);
        #else
            receive_CAN0_message();
        #endif
  #else
    receive_CAN0_message();     
  #endif    
}

void CAN1_INT_routine()
{
   #if OBD_CANPORT == 1    //use can1 for obd data stream
        #if OBD_ACTIVE == 1
           if ((rxId == 0x7DF) || (rxId == (configPage3.gpio_obd_address+0x100)))
              {
                obd_command(1);
              }  
        #endif
  #else
    receive_CAN1_message();      
  #endif
}

void initialiseCAN0()
{
  uint8_t tryInit0 = 0;
  START_INIT0: 
    if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK)                   // init can bus : baudrate = 500k
    {
       CAN0.setMode(MCP_NORMAL);
       BIT_SET(currentStatus.canstatus, BIT_CANSTATUS_CAN0ACTIVATED);
       BIT_CLEAR(currentStatus.canstatus, BIT_CANSTATUS_CAN0FAILED);
        //CONSOLE_SERIALLink.println("CAN BUS Shield init ok!");
    }
    else
    {
      BIT_CLEAR(currentStatus.canstatus, BIT_CANSTATUS_CAN0ACTIVATED);
      BIT_SET(currentStatus.canstatus, BIT_CANSTATUS_CAN0FAILED);
        //CONSOLE_SERIALLink.println("CAN BUS Shield init fail");
        //CONSOLE_SERIALLink.println("Init CAN BUS Shield again");
        delay(100);
        tryInit0++;
        if (tryInit0<50){goto START_INIT0;} //retry 50 times before quiting init
    }
   
}
//----------------------------------------------------------------------------------------
void initialiseCAN1()
{
  uint8_t tryInit1 = 0;
  START_INIT1:

    if(CAN1.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)                  // init can bus : baudrate = 500k
    {
       CAN1.setMode(MCP_NORMAL);
       BIT_SET(currentStatus.canstatus, BIT_CANSTATUS_CAN1ACTIVATED);
       BIT_CLEAR(currentStatus.canstatus, BIT_CANSTATUS_CAN1FAILED);

       // Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
       BIT_CLEAR(currentStatus.canstatus, BIT_CANSTATUS_CAN1ACTIVATED);
       BIT_SET(currentStatus.canstatus, BIT_CANSTATUS_CAN1FAILED);
      //  Serial.println("CAN BUS Shield init fail");
      //  Serial.println("Init CAN BUS Shield again");
        delay(100);       //this is ok as we havent started the actual firmware yet
        tryInit1++;
        if (tryInit1<50){goto START_INIT1;} //retry 50 times before quiting init
    }
   
}
//----------------------------------------------------------------------------------------
void Send_CAN0_message(byte bcChan, uint16_t theaddress, byte *thedata)
{
  byte sndStat = CAN0.sendMsgBuf(theaddress, 0, 8, thedata);    
  if(sndStat == CAN_OK)
    {
      //Serial.println("Message Sent Successfully!");
     BIT_SET(currentStatus.canstatus, BIT_CANSTATUS_CAN0MSGFAIL);
    } 
 else
    {
     //Serial.println("Error Sending Message...");
     BIT_CLEAR(currentStatus.canstatus, BIT_CANSTATUS_CAN0MSGFAIL);
    }   
}

//----------------------------------------------------------------------------------------
void Send_CAN1_message(byte bcChan, uint16_t theaddress, uint8_t *thedata)
{
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN1.sendMsgBuf(theaddress, 0, 8, thedata);
  if(sndStat == CAN_OK)
    {
      //Serial.println("Message Sent Successfully!");
      BIT_SET(currentStatus.canstatus, BIT_CANSTATUS_CAN1MSGFAIL);
    }
  else
    {
      //Serial.println("Error Sending Message...");
      BIT_CLEAR(currentStatus.canstatus, BIT_CANSTATUS_CAN1MSGFAIL);
    }

}


//---------------------------------------------------------------------------------------------

void receive_CAN0_message()
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
         
    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      {
       // id is extended 29bit address
       //sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
      }
    else  
      {
       // id is std 11 bit
       //sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

       //is it a output port change request? lets see...
       if(BIT_sCHECK(configPage3.canbroadcast_config, REMOTE_OUT0_15) == 1)  //are the remote outs pages enabled?
         {
          for(byte Ochan = 0; Ochan <16 ; Ochan++)
             { 
              if(BIT_sCHECK(configPage4.remoteoutput_sel_0_16, Ochan) == 1)   //is the individual remoteout enabled
                {
          currentStatus.dev1 = 104;
          currentStatus.dev2 = rxId;// ((configPage4.remoteoutput_can_address[Ochan]&2047)+0x100);
                 if(((configPage4.remoteoutput_can_address[Ochan]&2047)+0x100) == rxId)       // is the can address received same as a remoteoutput one
                   {
          currentStatus.dev1 = 100;
                    if(rxBuf[0] != 4)   //if the value is 4 then ignore the message as it is a status message sent by a gpio
                      {
          currentStatus.dev1 = 109;
                      //do the change. 
                      byte newstate;
                      newstate = (currentStatus.remote_output_status[Ochan] & 252 )| (rxBuf[0] & 3);       
                      //&252 masks the top 6bits ,clearing bits 0 and 1 , the &3 masks to leave bits 1 and 0 only 
                      //this will change state to on or off withouth affecting the error flags
                      currentStatus.remote_output_status[Ochan] = newstate;
          currentStatus.dev2 = newstate;
                      if (BIT_sCHECK(rxBuf[0],REMOTE_OUT_OFF == 1))
                        {
                         BIT_SET(currentStatus.digOut, (Ochan) );                                        
                        }
                 else if (BIT_sCHECK(rxBuf[0],REMOTE_OUT_OFF == 1)) 
                        {
                         BIT_CLEAR(currentStatus.digOut, (Ochan) );    
                        }
                      state = bitRead(currentStatus.digOut,Ochan);        //read current on/off from currentStatus
                      digitalWrite(pinOut[(Ochan+1)],state);              //write to pin[1] to pin [16]
                      }
                   }
                }   
             }     
         }
          
       if(BIT_sCHECK(configPage3.canbroadcast_config, REMOTE_OUT16_31) == 1)  //are the remote outs pages enabled?
         {
          for(byte Ochan = 0; Ochan <16 ; Ochan++)
             { 
              if(BIT_sCHECK(configPage4.remoteoutput_sel_17_31, Ochan) == 1)   //is the individual remoteout enabled
                {
                 if(((configPage4.remoteoutput_can_address[(Ochan+16)]&2047)+0x100) == rxId)       // is the can address received same as a remoteoutput one
                   {
                    if(rxBuf[0] != 4)   //if the value is 4 then ignore the message as it is a status message sent by a gpio
                      {
                       //do the change. 
                       byte newstate;
                       newstate = (currentStatus.remote_output_status[(Ochan+16)] & 252 )| (rxBuf[0] & 3);       
                       //&252 masks the top 6bits ,clearing bits 0 and 1 , the &3 masks to leave bits 1 and 0 only 
                       //this will change state to on or off withouth affecting the error flags
                       currentStatus.remote_output_status[(Ochan+16)] = newstate;
                       if (BIT_sCHECK(rxBuf[0],REMOTE_OUT_OFF == 1))
                         {
                          BIT_SET(currentStatus.digOut_2, (Ochan) );                                        
                         }
                 else if (BIT_sCHECK(rxBuf[0],REMOTE_OUT_OFF == 0))
                         {
                          BIT_CLEAR(currentStatus.digOut_2, (Ochan) );    
                         }
                       state = bitRead(currentStatus.digOut_2,Ochan);
                       digitalWrite(pinOut[(Ochan+17)],state);                   //write to pin[17] to pin [32]                    
                      }  
                   }
                }   
             }     
         }     
      } 

}

//---------------------------------------------------------------------------------------------

void receive_CAN1_message()
{
                       
}
//----------------------------------------------------------------------------------------------

void canbroadcastperfreq(byte freqcheck)
{
  bool canport;
  canport = BIT_CANSTATUS_CAN0ACTIVATED;           
  //canport = BIT_CANSTATUS_CAN1ACTIVATED;
  
  bool cpActive = 0;
  //if (BIT_sCHECK(configPage1.canModuleConfig, canport) == 1)
  //  {
     if(BIT_sCHECK(configPage3.canbroadcast_config, 0) == 1)         //generic can broadcasts
       {
        for(byte Bchan = 0; Bchan <16 ; Bchan++)
           { 
            if((configPage3.canbroadcast_freq[Bchan] & 7) == freqcheck)     // if the freq rate for chanX is set to freqcheck  (the &7 masks bit 0-2)
              {
               if(BIT_sCHECK(configPage3.canbroadcast_sel, Bchan) == 1)    //if the current channel is enabled
                 {              
                  direct_read_realtime();     //re-read the realtime data into array
                  senddata[0] = fullStatus[(configPage3.canbroadcast_chan_offset[(Bchan)])];
                  senddata[1] = 0;
                  byte tempD3 = configPage3.canbroadcast_chan_offset[(Bchan)];                  
                  //theaddress = (configPage3.canbroadcast_source_can_address[(bcChan-64)]+0x100);      
                  if (tempD3 != 0 | tempD3 !=1 | tempD3!=2 | tempD3!= 13 | tempD3!=14 | tempD3!=15 |tempD3!=16 |tempD3!=17 )    //check if value is two bytes long
                     {
                      senddata[1] = fullStatus[(configPage3.canbroadcast_chan_offset[(Bchan)]+1)];                                   //get the second byte
                     }
                  Send_CAN0_message((Bchan+64),(configPage3.canbroadcast_source_can_address[(Bchan)]+0x100),senddata);       // 
                 }  
              }
           }    
       }
    
     if(BIT_sCHECK(configPage3.canbroadcast_config, REMOTE_IN0_15) == 1)       //remote inputs 0-15
       { 
        //byte RIchan = 1;
        for(byte RIchan = 0; RIchan <16 ; RIchan++)
           { 
            if((configPage4.remoteinput_freq[RIchan] & 7) == freqcheck)     //  if the freq rate for chanX is set to freqcheck  (the &7 masks bit 0-2)
              {
               if(BIT_sCHECK(configPage4.remoteinput_sel_0_16, RIchan) == 1)            //if remoteinput channel X is enabled                 
                 {
                  if ((((configPage4.remoteinput_port[RIchan]&63)-1))<= 16)
                     {
                      cpActive = BIT_sCHECK(configPage1.DinchanActive, ((configPage4.remoteinput_port[RIchan]&63)-1));  
                      // if chanX input pin port is valid(ie enabled in utils)  &63 is a 6bit mask               
                      senddata[0] = (BIT_sCHECK(currentStatus.digIn, ((configPage4.remoteinput_port[RIchan]&63)-1)));   //set the first byte to the value of the input state                          
                      senddata[1] = 0;
                     }
                  else if ((((configPage4.remoteinput_port[RIchan]&63)-1)) >= 17)
                     {   
                      cpActive = BIT_sCHECK(configPage1.DinchanActive_2, ((configPage4.remoteinput_port[RIchan]&63)-17));
                      senddata[0] = (BIT_sCHECK(currentStatus.digIn_2, ((configPage4.remoteinput_port[RIchan]&63)-17)));   //set the first byte to the value of the input state
                      senddata[1] = 0;                      
                     }  
                 
                  if (cpActive == 1)
                     {
                      //currentStatus.dev2 = (BIT_sCHECK(currentStatus.digIn, ((configPage4.remoteinput_port[RIchan]&63)-1)));
                      //senddata[0] = (BIT_sCHECK(currentStatus.digIn, ((configPage4.remoteinput_port[RIchan]&63)-1)));   //set the first byte to the value of the input state                          
                      Send_CAN0_message(RIchan,(configPage4.remoteinput_can_address[RIchan]+0x100),senddata);                    
                     }
                 }
              }
           }
       }          
  
     if(BIT_sCHECK(configPage3.canbroadcast_config, REMOTE_IN16_31) == 1)     // remote inputs 16-31
       {
        for(byte RIchan = 16; RIchan <32 ; RIchan++)
           { 
            if((configPage4.remoteinput_freq[RIchan] & 7) == freqcheck)     //  if the freq rate for chanX is set to freqcheck  (the &7 masks bit 0-2)
              {
               if(BIT_sCHECK(configPage4.remoteinput_sel_17_31, (RIchan-16)) == 1)            //if remoteinput channel X is enabled                 
                 {
                  if ((((configPage4.remoteinput_port[RIchan]&63)-1)) <= 16)    //  &63 is a 6bit mask 
                     {
                      cpActive = BIT_sCHECK(configPage1.DinchanActive, ((configPage4.remoteinput_port[RIchan]&63)-1));      // if chanX input pin port is valid(ie enabled in utils)              
                      senddata[0] = (BIT_sCHECK(currentStatus.digIn, ((configPage4.remoteinput_port[RIchan]&63)-1)));   //set the first byte to the value of the input state                          
                      senddata[1] = 0;                      
                     }
                  else if ((((configPage4.remoteinput_port[RIchan]&63)-1)) >= 17)
                     {   
                      cpActive =BIT_sCHECK(configPage1.DinchanActive_2, ((configPage4.remoteinput_port[RIchan]&63)-17));
                      senddata[0] = (BIT_sCHECK(currentStatus.digIn_2, ((configPage4.remoteinput_port[RIchan]&63)-17)));   //set the first byte to the value of the input state
                      senddata[1] = 0;                      
                     }  
                 
                  if (cpActive ==1)
                    {
                      //senddata[0] = (BIT_sCHECK(currentStatus.digIn_2, ((configPage4.remoteinput_port[RIchan]&63)-17)));   //set the first byte to the value of the input state
                      Send_CAN0_message(RIchan,(configPage4.remoteinput_can_address[RIchan]+0x100),senddata);                    
                    }
                 }
              }
           }
       }
  
  //currentStatus.dev2 = freqcheck;
  //currentStatus.dev1 = BIT_sCHECK(configPage4.remoteAninput_sel, 1);//configPage3.canbroadcast_out; 
  //currentStatus.EXin[13] =  (configPage4.remoteAninput_port[1]&63)-1;
  //currentStatus.EXin[14] = BIT_sCHECK(configPage1.AinchanActive,  ((configPage4.remoteAninput_port[1]&63)-1));
  
     if(BIT_sCHECK(configPage3.canbroadcast_config, REMOTE_AIN0_15) == 1)       //remote Ainputs 0-15
       { 
        for(byte RIchan = 0; RIchan <16 ; RIchan++)
           { 
            if((configPage4.remoteAninput_freq[RIchan] & 7) == freqcheck)     //  if the freq rate for chanX is set to freqcheck  (the &7 masks bit 0-2)
              {
               if(BIT_sCHECK(configPage4.remoteAninput_sel, RIchan) == 1)            //if remoteinput channel X is enabled                 
                 {
                  if ((((configPage4.remoteAninput_port[RIchan]&63)-1))<= 16)
                     {
                      cpActive = BIT_sCHECK(configPage1.AinchanActive, ((configPage4.remoteAninput_port[RIchan]&63)-1));      // if chanX input pin port is valid(ie enabled in utils)  &63 is a 6bit mask               
                     }
                  //else if ((((configPage4.remoteAinput_port[RIchan]&63)-1))<= 32)
                 //   {   
                 //     cpActive =BIT_sCHECK(configPage1.AinchanActive_2, ((configPage4.remoteAinput_port[RIchan]&63)-17));
                 //   }  
                 
                  if (cpActive == 1)
                     {
                      senddata[0] = lowByte(currentStatus.Analog[((configPage4.remoteAninput_port[RIchan]&63)-1)]);    //set the first byte to the low byte value of the analog
                      senddata[1] = highByte(currentStatus.Analog[((configPage4.remoteAninput_port[RIchan]&63)-1)]);   //set the second byte to the high byte value of the analog
                      Send_CAN0_message(RIchan,(configPage4.remoteAninput_can_address[RIchan]+0x100),senddata);                    
                     }
                 }
              }
           }
       }          


     if(BIT_sCHECK(configPage3.canbroadcast_config, REMOTE_OUT0_15) == 1)       //remote outputs 0-15
       { 
        for(byte RIchan = 0; RIchan <16 ; RIchan++)
           {
            if(BIT_sCHECK(configPage4.remoteoutput_statusEnable_0_16, RIchan) == 1)
               {
                if((configPage4.remoteoutput_freq[RIchan] & 7) == freqcheck)     //  if the freq rate for chanX is set to freqcheck  (the &7 masks bit 0-2)
                  {
                   if(BIT_sCHECK(configPage4.remoteoutput_sel_0_16, RIchan) == 1)            //if remoteinput channel X is enabled                 
                     {
                      if((((configPage4.remoteoutput_port[RIchan]&63)-1))<= 16)           // if the port number of the current selected channel is <=16
                        {
                         cpActive = (currentStatus.remote_output_status[RIchan]&31);   //get status flags for current channel , & 31 to keep bits 0-5 only                                          
                         // if chanX input pin port is valid(ie enabled in utils)  &63 is a 6bit mask               
                        }
                      else if ((((configPage4.remoteoutput_port[RIchan]&63)-1))<= 32)      // if the port number of the current selected channel is <=32
                        {  
                         cpActive = (currentStatus.remote_output_status[RIchan]&31);                                           
                        }
                        senddata[0] = 4;          //set to 4 to show is a status message if transmitted on switching can address  
                        senddata[1] = cpActive;    //set the first byte to the value of the input state
                        Send_CAN0_message(RIchan,(configPage4.remoteoutput_can_address[RIchan]+0x100),senddata);                    
                     }
                  }
               }
           }          
       }
         
     if(BIT_sCHECK(configPage3.canbroadcast_config, REMOTE_OUT16_31) == 1)       //remote outputs 16-31
       { 
        for(byte RIchan = 16; RIchan <32 ; RIchan++)
           {
            if(BIT_sCHECK(configPage4.remoteoutput_statusEnable_17_31, RIchan) == 1)    //if status broadcast is enabled
               {
                if((configPage4.remoteoutput_freq[RIchan] & 7) == freqcheck)     //  if the freq rate for chanX is set to freqcheck  (the &7 masks bit 0-2)
                  {
                   if(BIT_sCHECK(configPage4.remoteoutput_sel_17_31, RIchan) == 1)            //if remoteinput channel X is enabled                 
                     {
                      if((((configPage4.remoteoutput_port[RIchan]&63)-1))<= 16)           // if the port number of the current selected channel is <=16
                        {
                         cpActive = (currentStatus.remote_output_status[RIchan]&31);   //get status flags for current channel , & 31 to keep bits 0-5 only                                          
                         // if chanX input pin port is valid(ie enabled in utils)  &63 is a 6bit mask               
                        }
                      else if ((((configPage4.remoteoutput_port[RIchan]&63)-1))<= 32)      // if the port number of the current selected channel is <=32
                        {  
                         cpActive = (currentStatus.remote_output_status[RIchan]&31);                                           
                        }  
                        senddata[0] = 4;          //set to 4 to show is a status message if transmitted on switching can address
                        senddata[1] = cpActive;    //set the first byte to the value of the input state
                        Send_CAN0_message(RIchan,(configPage4.remoteoutput_can_address[RIchan]+0x100),senddata);                    
                     }
                  }
               }
           }          
       }
                      
}

void obd_command(byte usecan)
{
      switch(usecan)
        { 
         case 0:
             CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
         break;

         case 1:
             CAN1.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
         break;
        }
    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
    {
      // id is extended 29bit address
      //sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    }
    else  
    {
      // id is std 11 bit
      //sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
    
      uint16_t obdreplyaddress = obd_response(rxBuf[2],rxId);           //build the obd response , return the address from which ecu value came ie gpio or speeduino
    
      #if OBD_CANPORT == 0    //use can0 to send obd data stream
          Send_CAN0_message(0xFF,((configPage3.gpio_obd_address&15)+0x7E8),obddata);
      #endif
    
      #if OBD_CANPORT == 1    //use can1 to send obd data stream         
          Send_CAN1_message(0xFF,((configPage3.gpio_obd_address&15)+0x7E8),obddata);
         // Send_CAN0_message(0xFF,((configPage3.gpio_obd_address&15)+0x7E8),obddata);
      #endif
        
    } 
     
}

uint16_t obd_response(byte therequestedPID, uint16_t therequestedCANID)
{
  switch (therequestedPID)
  {
  case 0:  
  obddata[0] =  0x06;    // sending 6 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x00;    // pid code
  obddata[3] =  0x08;   //B0000 1000
  obddata[4] =  0x7E;   //B0111 1110
  obddata[5] =  0xB8;   //B1011 1000
  obddata[6] =  0x11;   //B0001 0001
  obddata[7] = 0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 5:      //engine coolant temperature A-40 , range is -40 to 215 deg C
  int16_t enginecoolant;
  enginecoolant = (realtimebufferA[(7)]-40);
  obdcalcA = enginecoolant + 40;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x05;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;


  case 10:      //fuel pressure(gauge pressure) 3A , range is 0 to 765 kPa
  uint16_t fuelpressure;
  fuelpressure = 567;                  // TEST VALUE !!!!
  obdcalcA = fuelpressure/3;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x0A;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;
  
  case 11:        //0B or MAP , A ,range is 0 to 255 kPa
  uint16_t engineMap;
  engineMap = (realtimebufferA[(5)]<<8) | realtimebufferA[4];
  obddata[0] =  0x03;    // sending 3 byte
  obddata[1] =  0x41;    // 
  obddata[2] =  0x0B;    // pid code
  obddata[3] =  engineMap;    // the map value
  obddata[4] =  0x00;
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 12:        //0C or rpm , 256A+B / 4 , range is 0 to 16383.75 rpm
  uint16_t revs; 
  revs = (realtimebufferA[(15)]<<8) | realtimebufferA[14];
  obdcalcA = revs*4;
  obdcalcB = obdcalcA/256;              //the rmainder will be lost for the next calculation which we dont want! it is the first byte for sending
  obdcalcC = obdcalcB*256;              //
  obdcalcD = obdcalcA - obdcalcC;       //calcs the second byte for sending
  obddata[0] =  0x04;    // sending 4 byte
  obddata[1] =  0x41;    // 
  obddata[2] =  0x0C;    // pid code
  obddata[3] =  obdcalcB;
  obddata[4] =  obdcalcD;
  obddata[5] =  0x00; //B0000
  obddata[6] =  0x00; //B0000
  obddata[7] = 0x00;
  return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 13:        // 0D or vehicle speed , A , range is 0 to 255 km/h
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x0D;    // pid code
  obddata[3] =  0x04;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  
  case 14:      //timing advance , A/2 - 64 , range is -64 to 63.5 BTDC
  int8_t timingadvance;
  timingadvance = realtimebufferA[23];
  obdcalcA = ((timingadvance + 64) *2) ;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x0E;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;


  case 15:      //inlet air temperature, A-40 , range is -40 to 215 deg C
  uint16_t engineIAT;
  engineIAT = (realtimebufferA[(6)]-40);
  obdcalcA = engineIAT + 40;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x0F;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 17:      //tps percentage, 100/256 A , range is 0 to 100 percent
  uint16_t tpsPC;
  tpsPC = realtimebufferA[24];
  obdcalcA = (tpsPC *256) /100;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x11;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;


  case 19:      //oxygen sensors present, A0-A3 == bank1 , A4-A7 == bank2 , 
  uint16_t O2present;
  O2present = B00000011 ;//realtimebufferA[24];         TEST VALUE !!!!!
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x13;    // pid code
  obddata[3] =  3;//O2present;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 20:      //O2 sensor2, A voltage B short term fuel trim ,  A/200 ,((100/128) B) -100 , range is 0 to 1.275 and -100 to 99.2 percent
  uint16_t O2_1v;     // send data *10
  int16_t O2_1pc;     // data *10
  O2_1v = 11;//(realtimebufferA[24]*10);              TEST VALUE!!!!!
  O2_1pc = 27;//realtimebufferA[10]*10;
  obdcalcA = O2_1v *20;
  obdcalcB = (((O2_1pc +1000)*128)/1000);
  obddata[0] =  0x04;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x14;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0xFF;//obdcalcB;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 21:      //O2 sensor2, A voltage B short term fuel trim ,  A/200 100/128 B -100 , range is 0 to 1.276 and -100 to 99.2 percent
  uint16_t O2_2v;       //send data *10           
  int16_t O2_2pc;       //data *10
  O2_2v = 12;   //realtimebufferA[24]*10;           TEST VALUE!!!!
  O2_2pc = 26;  //realtimebufferA[39]*10;
  obdcalcA = O2_2v *20;
  obdcalcB = (((O2_2pc +1000)*128)/1000);
  obddata[0] =  0x04;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x15;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0xFF;//obdcalcB;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;
  
  case 28:      //obd standard
  uint16_t obdstandard;
  obdstandard = 7;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x1C;    // pid code
  obddata[3] =  obdstandard;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;
  
  case 32:      //pids 21-40
  obddata[0] =  0x06;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x20;    // pid code
  obddata[3] =  0x18; //B0001 1000
  obddata[4] =  0x00; //B0000 0000
  obddata[5] =  0x18; //B0001 1000
  obddata[6] =  0x01; //B0000 0001
  obddata[7] = 0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 36:      //O2 sensor2, AB fuel/air equivalence ratio, CD voltage ,  2/65536(256A +B) ,8/65536(256C+D) , range is 0 to <2 and 0 to >8V
  uint16_t O2_1e;
  int16_t O2_1V; 
  //O2_1e = obdcalcF ;     //afr(is *10 so 25.5 is 255) /
  O2_1V = (realtimebufferA[10]*10);                             //afr
  
  obdcalcH16 = 147;    //used in calcs = 147;    // stoich(is *10 so 14.7 is 147)
  obdcalcE32 = 138; //(realtimebufferA[10]; // afr(is *10 so 25.5 is 255) , needs a 32bit else will overflow
  obdcalcF32 = (obdcalcE32<<8) / obdcalcH16;      //this is same as (obdcalcE32/256) / obdcalcH16 . this calculates the ratio      
  obdcalcG16 = (obdcalcF32 *32768)>>8;          
  obdcalcA = highByte(obdcalcG16);
  obdcalcB = lowByte(obdcalcG16);       

  obdcalcF32 = 451;                              //wideband volts to send is wideband voltage *100    
  obdcalcG16 = (obdcalcF32 *20992)>>8;          
  obdcalcC = highByte(obdcalcG16);
  obdcalcD = lowByte(obdcalcG16);
    
  obddata[0] =  0x06;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x24;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  obdcalcB;   //the data value B
  obddata[5] =  obdcalcC; 
  obddata[6] =  obdcalcD; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 37:      //O2 sensor2, AB fuel/air equivalence ratio, CD voltage ,  2/65536(256A +B) ,8/65536(256C+D) , range is 0 to <2 and 0 to >8V
  uint16_t O2_2e;
  int16_t O2_2V; 
 // O2_2e = 
  O2_2V = (realtimebufferA[39]*10);                           //afr2
  obdcalcH16 = 147;    // stoich(is *10 so 14.7 is 147)  
  obdcalcE32 = 121; //(realtimebufferA[10]; // afr(is *10 so 25.5 is 255) , needs a 32bit else will overflow
  obdcalcF32 = (obdcalcE32<<8) / obdcalcH16;      //(realtimebufferA[10]<<8) / realtimebufferA[81];          
  obdcalcG16 = (obdcalcF32 *32768)>>8;          
  obdcalcA = highByte(obdcalcG16);
  obdcalcB = lowByte(obdcalcG16); 

  obdcalcF32 = 426;    
  obdcalcG16 = (obdcalcF32 *20992)>>8;          
  obdcalcC = highByte(obdcalcG16);
  obdcalcD = lowByte(obdcalcG16);
  
  obddata[0] =  0x06;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x25;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  obdcalcB;   //the data value B
  obddata[5] =  obdcalcC; 
  obddata[6] =  obdcalcD; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

    case 64:       //pids 41-60  
  obddata[0] =  0x06;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x40;    // pid code
  obddata[3] =  0x40; //B0100 0000
  obddata[4] =  0x00; //B0000 0000
  obddata[5] =  0x40; //B0100 0000
  obddata[6] =  0x10; //B0001 0000
  obddata[7] = 0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 66:      //control module voltage, 256A+B / 1000 , range is 0 to 65.535v
  uint16_t ecuBatt;
  ecuBatt = realtimebufferA[9];
  obdcalcA = ecuBatt*100;               //should be *1000 but ecuBatt needs a /10
  obdcalcB = obdcalcA/256;              //the rmainder will be lost for the next calculation which we dont want! it is the first byte for sending
  obdcalcC = obdcalcB*256;              //
  obdcalcD = obdcalcA - obdcalcC;       //calcs the second byte for sending
  obddata[0] =  0x04;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x42;    // pid code
  obddata[3] =  obdcalcB;   //the data value A
  obddata[4] =  obdcalcD;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  case 82:        //0B or MAP , A ,range is 0 to 255 kPa
  uint16_t ethanolpc;
  ethanolpc = 42;//realtimebufferA[34];                        TEST VALUE !!!!!!!!!!
  obdcalcA = (ethanolpc *256) /100;
  obddata[0] =  0x03;    // sending 3 byte
  obddata[1] =  0x41;    // 
  obddata[2] =  0x52;    // pid code
  obddata[3] =  obdcalcA;    // the map value
  obddata[4] =  0x00;
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
    return ((configPage3.speeduino_obd_address&15)+0x7E8);
  break;

  default:
  return 0 ;
  break;
  
  }  
}

