void initialiseCAN0()
{
  uint8_t tryInit0 = 0;
  START_INIT0: 
    if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK)//(CAN_OK == CAN1.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
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

    if(CAN1.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK)//  if(CAN_OK == CAN2.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
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
void Send_CAN0_message(byte bcChan)
{
  //byte data[8] = {lowByte(currentStatus.EXin[0]),highByte(currentStatus.EXin[0]), 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
  direct_read_realtime();     //re-read the realtime data into array
  byte tempD1 = fullStatus[(configPage3.canbroadcast_chan_offset[bcChan])];
  byte tempD2 = 0;
  byte tempD3 = configPage3.canbroadcast_chan_offset[bcChan];
 
  if (tempD3 != 0 | tempD3 !=1 | tempD3!=2 | tempD3!= 13 | tempD3!=14 | tempD3!=15 |tempD3!=16 |tempD3!=17 ){tempD2 = fullStatus[(configPage3.canbroadcast_chan_offset[bcChan]+1)];}
  byte data[8] = {tempD1,tempD2, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  //byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  byte sndStat = CAN0.sendMsgBuf((configPage3.canbroadcast_source_can_address[bcChan]+0x100), 0, 8, data);
  if(sndStat == CAN_OK){
    //Serial.println("Message Sent Successfully!");
    BIT_CLEAR(currentStatus.canstatus, BIT_CANSTATUS_CAN0MSGFAIL);
  } else {
    //Serial.println("Error Sending Message...");
    BIT_SET(currentStatus.canstatus, BIT_CANSTATUS_CAN0MSGFAIL);
  }

}

//---------------------------------------------------------------------------------------------
void receive_CAN0_message()
{

}
