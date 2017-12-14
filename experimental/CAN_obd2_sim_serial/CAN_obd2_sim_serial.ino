// CAN Receive Example
//

#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string
  uint16_t obdcalcA;
  uint16_t obdcalcB;
  uint16_t obdcalcC;
  uint16_t obdcalcD;

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(12);                               // Set CS to pin 12


void setup()
{
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
  
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    Serial.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }
        
    Serial.println();
    Serial.print(rxBuf[2]);
    Serial.println();
    send_can(rxBuf[2]);
    
  }
}


void send_can(byte therequest)
{
  //The response has an ID of the device assigned ID plus 8 e.g. 7E8h through 7EFh
   byte obddata[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  switch (therequest)
  {
  case 0:  
  obddata[0] =  0x06;    // sending 6 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x00;    // pid code
  obddata[3] =  0x08; //B1000
  obddata[4] =  0x7E; //B0000
  obddata[5] =  0x38; //B0000
  obddata[6] =  0x11; //B0000
  obddata[7] = 0x00;
  break;

  case 5:      //engine coolant temperature A-40 , range is -40 to 215 deg C
  int16_t enginecoolant;
  enginecoolant = 77;
  obdcalcA = enginecoolant + 40;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x05;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  break;


  case 10:      //fuel pressure(gauge pressure), 3A , range is 0 to 765 kPa
  uint16_t fuelpressure;
  fuelpressure = 567;
  obdcalcA = fuelpressure/3;
  obddata[0] =  0x04;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x0A;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  break;
  
  case 11:        //0B or MAP , A ,range is 0 to 255 kPa
  obddata[0] =  0x03;    // sending 3 byte
  obddata[1] =  0x41;    // 
  obddata[2] =  0x0B;    // pid code
  obddata[3] =  0x30;    // the map value
  obddata[4] =  0x00;
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  break;

  case 12:        //0C or rpm , 256A+B / 4 , range is 0 to 16383.75 rpm
  uint16_t revs; 
  revs = 3260;
  uint16_t revcalcA;
  uint16_t revcalcB;
  uint16_t revcalcC;
  uint16_t revcalcD;
  revcalcA = revs*4;
  revcalcB = revcalcA/256;              //the rmainder will be lost for the next calculation which we dont want! it is the first byte for sending
  revcalcC = revcalcB*256;              //
  revcalcD = revcalcA - revcalcC;       //calcs the second byte for sending
  obddata[0] =  0x04;    // sending 4 byte
  obddata[1] =  0x41;    // 
  obddata[2] =  0x0C;    // pid code
  obddata[3] =  revcalcB;
  obddata[4] =  revcalcD;
  obddata[5] =  0x00; //B0000
  obddata[6] =  0x00; //B0000
  obddata[7] = 0x00;
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
  break;

  
  case 14:      //timing advance , A/2 - 64 , range is -64 to 63.5 BTDC
  int8_t timingadvance;
  timingadvance = 16;
  obdcalcA = ((timingadvance + 64) *2) ;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x0E;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
  break;

  case 15:      //inlet air temperature, A-40 , range is -40 to 215 deg C
  uint16_t engineIAT;
  engineIAT = 88;
  obdcalcA = engineIAT + 40;
  obddata[0] =  0x03;    // sending 3 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x0F;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  0x00;   //the data value B
  obddata[5] =  0x00; 
  obddata[6] =  0x00; 
  obddata[7] =  0x00;
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
  break;

  case 36:      //O2 sensor2, AB fuel/air equivalence ratio, CD voltage ,  2/65536(256A +B) ,8/65536(256C+D) , range is 0 to <2 and 0 to >8V
  uint16_t O2_1e;
  int16_t O2_1V; 
  O2_1e = obdcalcF ;     //afr(is *10 so 25.5 is 255) / stoich(is *10 so 14.7 is 147)
  O2_1V = (realtimebufferA[10]*10);                             //afr
  uint32_t tp1;
  uint16_t tp2;
  tp2 = 147;
  tp1 = 168;
  obdcalcE = (tp1<<8) / tp2;      //(realtimebufferA[10]<<8) / realtimebufferA[81];          
  obdcalcF = (obdcalcE *32768)>>8;          
  obdcalcA = highByte(obdcalcF);
  obdcalcB = lowByte(obdcalcF);       
  
  obddata[0] =  0x06;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x24;    // pid code
  obddata[3] =  obdcalcA;   //the data value A
  obddata[4] =  obdcalcB;   //the data value B
  obddata[5] =  0;//obdcalcC; 
  obddata[6] =  75;//obdcalcD; 
  obddata[7] =  0x00;
  break;

    case 64:       //pids 41-60  
  obddata[0] =  0x06;    // sending 4 bytes
  obddata[1] =  0x41;    // Same as query, except that 40h is added to the mode value. So:41h = show current data ,42h = freeze frame ,etc.
  obddata[2] =  0x40;    // pid code
  obddata[3] =  0x04; //B1000
  obddata[4] =  0x00; //B0000
  obddata[5] =  0x40; //B0000
  obddata[6] =  0x10; //B0000
  obddata[7] = 0x00;
  break;

  default:
  return;
  break;
  
  }
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x7E8, 0, 8, obddata);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(100);   // send data per 100ms
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
