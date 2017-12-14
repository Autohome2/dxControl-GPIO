#include "sensors.h"

void initialiseADC()
{
   //This sets the ADC (Analog to Digitial Converter) to run at 1Mhz, greatly reducing analog read times (MAP/TPS) when using the standard analogRead() function
    //1Mhz is the fastest speed permitted by the CPU without affecting accuracy
    //Please see chapter 11 of 'Practical Arduino' (http://books.google.com.au/books?id=HsTxON1L6D4C&printsec=frontcover#v=onepage&q&f=false) for more detail
#if defined(ARDUINO_AVR_MEGA2560)
     BIT_SET(ADCSRA,ADPS2);
     BIT_CLEAR(ADCSRA,ADPS1);
     BIT_CLEAR(ADCSRA,ADPS0); 
     #endif
}

void readAnalog(uint8_t AinCH)
{
    tempReading = analogRead( pinAin[(AinCH+1)]);   //read the adc channel
       #if defined(ARDUINO_AVR_MEGA2560)
    tempReading = analogRead( pinAin[(AinCH+1)]);   //read it a second time to get a more stable /faster read
    #endif
    
    #if defined(MCU_STM32F103C8)
    tempReading >>= 2;  //rescales to max 1024 value else would be 0-4096
    #endif
    currentStatus.Analog[AinCH] = tempReading;
    
}

void readDigitalIn(uint8_t DinCH)
{
  byte pinread = 0;
  pinread = digitalRead(pinIn[DinCH]);
  if ( pinread == 1)
    {
      if (DinCH <17){ BIT_SET(currentStatus.digIn, (DinCH-1));}
      else { BIT_SET(currentStatus.digIn_2, (DinCH-17));}
    }
  else
    {  
      if (DinCH <17){BIT_CLEAR(currentStatus.digIn, (DinCH-1));}
      else {BIT_CLEAR(currentStatus.digIn_2, (DinCH-17));}
    }
    
//currentStatus.IO  
}

void getAnalogBYoffset(uint8_t AinCH, uint8_t readloop)
{
  
  /* NOTE IF THE TS comms FULLSTATUS LIST CHANGES THEN LIST LIST NEEDS TO BE UPDATED TOO !!!!! */
  /*-------------------------------------------------------------------------------------------*/
  
         switch (AinCH)
              {
              case 14:
                    currentStatus.currentInputvalue[readloop] = lowByte(currentStatus.digIn);      //digital in 1-8
              break;

              case 15:
                    currentStatus.currentInputvalue[readloop] = highByte(currentStatus.digIn);      //digital in 9-16
              break;
            
              case 16:
                    currentStatus.currentInputvalue[readloop] = lowByte(currentStatus.digIn_2);
              break;

              case 17:
                    currentStatus.currentInputvalue[readloop] = highByte(currentStatus.digIn_2);
              break;

              case 18:
                    currentStatus.currentInputvalue[readloop] = lowByte(currentStatus.digOut);      //digital out 1-8
              break;

              case 19:
                    currentStatus.currentInputvalue[readloop] = highByte(currentStatus.digOut);      //digital out 9-16
              break;
            
              case 20:
                    currentStatus.currentInputvalue[readloop] = lowByte(currentStatus.digOut_2);      //digital out 17-24
              break;

              case 21:
                    currentStatus.currentInputvalue[readloop] = highByte(currentStatus.digOut_2);      //digital out 25-32
              break;
                                                    
              case 22:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[0];
              break;

              case 24:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[1];
              break;
            
              case 26:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[2];
              break;

              case 28:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[3];
              break;
      
              case 30:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[4];
              break;

              case 32:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[5];
              break;
            
              case 34:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[6];
              break;

              case 36:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[7];
              break;
                    
              case 38:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[8];
              break;

              case 40:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[9];
              break;
            
              case 42:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[10];
              break;

              case 44:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[11];
              break;
      
              case 46:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[12];
              break;

              case 48:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[13];
              break;
            
              case 50:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[14];
              break;

              case 52:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[15];
              break;

              case 54:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[0];
              break;

              case 56:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[1];
              break;
            
              case 58:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[2];
              break;

              case 60:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[3];
              break;
      
              case 62:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[4];
              break;

              case 64:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[5];
              break;
            
              case 66:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[6];
              break;

              case 68:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[7];
              break;
                    
              case 70:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[8];
              break;

              case 72:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[9];
              break;
            
              case 74:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[10];
              break;

              case 76:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[11];
              break;
      
              case 78:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[12];
              break;

              case 80:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[13];
              break;
            
              case 82:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[14];
              break;

              case 84:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[15];
              break;

              default:
                    currentStatus.currentInputvalue[readloop] = 0;
              break;
              }  
}

