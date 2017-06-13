#include "sensors.h"

void initialiseADC()
{
   //This sets the ADC (Analog to Digitial Converter) to run at 1Mhz, greatly reducing analog read times (MAP/TPS) when using the standard analogRead() function
    //1Mhz is the fastest speed permitted by the CPU without affecting accuracy
    //Please see chapter 11 of 'Practical Arduino' (http://books.google.com.au/books?id=HsTxON1L6D4C&printsec=frontcover#v=onepage&q&f=false) for more detail
     BIT_SET(ADCSRA,ADPS2);
     BIT_CLEAR(ADCSRA,ADPS1);
     BIT_CLEAR(ADCSRA,ADPS0); 
}

void readAnalog(uint8_t AinCH)
{
    tempReading = analogRead( pinAin[AinCH]);   //read the adc channel
    tempReading = analogRead( pinAin[AinCH]);   //read it a second time to get a more stable /faster read
    currentStatus.Analog[(AinCH-1)] = tempReading;
    
}

void readDigitalIn(uint8_t DinCH)
{
  byte pinread = 0;
  pinread = digitalRead(pinIn[DinCH]);
  if ( pinread == 1)
    {
      BIT_SET(currentStatus.digIn, (DinCH-1));
    }
  else
    {  
      BIT_CLEAR(currentStatus.digIn, (DinCH-1));    
    }
    
//currentStatus.IO  
}

void getAnalogBYoffset(uint8_t AinCH, uint8_t readloop)
{
         switch (AinCH)
              {
              case 17:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[0];
              break;

              case 19:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[1];
              break;
            
              case 21:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[2];
              break;

              case 23:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[3];
              break;
      
              case 25:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[4];
              break;

              case 27:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[5];
              break;
            
              case 29:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[6];
              break;

              case 31:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[7];
              break;
                    
              case 33:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[8];
              break;

              case 35:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[9];
              break;
            
              case 37:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[10];
              break;

              case 39:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[11];
              break;
      
              case 41:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[12];
              break;

              case 43:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[13];
              break;
            
              case 45:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[14];
              break;

              case 47:
                    currentStatus.currentInputvalue[readloop] = currentStatus.Analog[15];
              break;

              case 49:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[0];
              break;

              case 51:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[1];
              break;
            
              case 53:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[2];
              break;

              case 55:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[3];
              break;
      
              case 57:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[4];
              break;

              case 59:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[5];
              break;
            
              case 61:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[6];
              break;

              case 63:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[7];
              break;
                    
              case 65:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[8];
              break;

              case 67:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[9];
              break;
            
              case 69:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[10];
              break;

              case 71:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[11];
              break;
      
              case 73:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[12];
              break;

              case 75:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[13];
              break;
            
              case 77:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[14];
              break;

              case 79:
                    currentStatus.currentInputvalue[readloop] = currentStatus.EXin[15];
              break;
              }  
}

