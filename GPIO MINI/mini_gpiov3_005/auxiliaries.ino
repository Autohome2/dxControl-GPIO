void driveOutputs()
{
  
  for (byte DoutCH = 1; DoutCH < 17 ; DoutCH++)     //loop through outputs 1 to 16
    {
      
     portX = DoutCH-1;
     if (pinOut[portX+1] < 255)    //if pin is not set to 255 then is in use by selected board so drive the digital outputs according to current active channel
       { 
        if(BIT_CHECK(currentStatus.testIO_hardware, 0) == 0)   //if testenable unset then check outputs according to port editor
          {   
    //currentStatus.dev1 = configPage2.port_Enabled[portX];
           if(configPage2.port_Enabled[portX] == 1)
             {
              uint8_t checkcondloop = 0;
              int16_t offValue1;
              int16_t offValue2;
              //first get the conditon checks into flag array for current io output channel (0 is first condition, 1 is second)
           //   currentStatus.currentInputvalueCond[checkcondloop] = configPage2.port_OutOffset[portX] ;  //get first condition into array
              getAnalogBYoffset(configPage2.port_OutOffset[portX],checkcondloop); //lookup analog value based on selected outchannel per current output
              switch (configPage2.port_Condition[portX])
                    {
                    case 38:
                    //& condition
                    
                    break;
                    
                    case 60:
                    //< condition
                     offValue2 = (configPage2.port_Threshold[portX] + configPage2.port_Hysteresis[portX]); 
                     if (offValue2 >= 1024 ){ offValue2 = 1024;}

                     if (currentStatus.currentInputvalue[checkcondloop] < configPage2.port_Threshold[portX])
                        {
                         //currentStatus.condition_pass_last[portX] = currentStatus.condition_pass[portX];  //set last status from status  
                         currentStatus.condition_pass[portX] = 1;  //set status to pass
                        }
 
                     if (currentStatus.currentInputvalue[checkcondloop] >= offValue2) 
                        {
                         //currentStatus.condition_pass_last[portX] = currentStatus.condition_pass[portX];  //set last status from status                          
                         currentStatus.condition_pass[portX] = 0;  //set status to off (threshold+hysteresis)
                        }
       
                    break;

                    case 61:
                    //= condition
                    offValue1 = (configPage2.port_Threshold[portX] - configPage2.port_Hysteresis[portX]);
                    if (offValue1 <= 0 ){offValue1 = 0;}
                    offValue2 = (configPage2.port_Threshold[portX] + configPage2.port_Hysteresis[portX]);
                    if (offValue2 >= 1024 ){ offValue2 = 1024;}
                    
                    if (currentStatus.currentInputvalue[checkcondloop] == configPage2.port_Threshold[portX])
                        {  
                             currentStatus.condition_pass[portX] = 1;  //set status to pass
                        }
               else if (currentStatus.condition_pass[portX] == 1)
                        {
                         if (currentStatus.currentInputvalue[checkcondloop] < offValue1)  
                            { 
                             currentStatus.condition_pass[portX] = 0; // set status to fail (threshold-hysteresis)
                            }
                    else if (currentStatus.currentInputvalue[checkcondloop] > offValue2)  
                            {                    
                             currentStatus.condition_pass[portX] = 0; // set status to fail (threshold+hysteresis)
                            }
                         }
  
                    break;

                    case 62:
                    //> condition      
      //   currentStatus.dev2 = currentStatus.currentInputvalue[checkcondloop];             
                    offValue1 = (configPage2.port_Threshold[portX] - configPage2.port_Hysteresis[portX]);
                    if (offValue1 <= 0 ){offValue1 = 0;}
      
                    if (currentStatus.currentInputvalue[checkcondloop] > configPage2.port_Threshold[portX])
                        {
                         currentStatus.condition_pass[portX] = 1;  //set status to pass
                        }   
                    if (currentStatus.currentInputvalue[checkcondloop] <= offValue1) // has it dropped below the hys
                        {                         
                         currentStatus.condition_pass[portX] = 0;  //set status to off (threshold+hysteresis)
                        }   
                    break;                    
                    
                    } //ends the switch case
                    
     
               
            } //ends the check is output is enabled
           else   //else if output is not enabled
            {
                      currentStatus.condition_pass[portX] = 0;      //set pin state to off 
            }
            
            outputaction(portX); //set output high/lows 
            
        }  //ends the else (not a test)
        
      else      //this is a test so do direct port ops according to the bitread  
          {   
           state = bitRead(currentStatus.digOut,(portX));
           digitalWrite(pinOut[portX+1],state);
          }
             
       }    // ends is the pin used by board
   else
      {
        configPage2.port_Enabled[portX] = 0; //disable output as pin is not configured
        state = 0;    //pin is unused(0 in utils) so set pin state off
      }        
    }     // ends the for next 1-17 count loop
    

}

void outputaction(uint8_t chanX)
{
  
  //the output stage is checked to set flags then the actual outputs are fed off those flags. this is for future proof when pwm outputs  and external outputs are added
 //bit0 == output on/off
 //bit1 == active high/low
 //bit2
 //bit3
 //bit4
 //bit5
 //bit6
 //bit7
 
  // now if the relationship conditions have passed(if required) then do the output action
          if (currentStatus.condition_pass[chanX] == 1)
              {  
              //activate the output according to setup/config
              if (configPage2.port_PortValue[chanX] == 1 ) // if the output is active high
                  {
                   currentStatus.OutputPort[chanX] = 0b00000011;  // output1 is [0]
                   BIT_SET(currentStatus.digOut, (chanX) );
                  }  
              else if (configPage2.port_PortValue[chanX] == 0 )  // if the output is active low
                  {
                    currentStatus.OutputPort[chanX] = 0b00000001;
                    BIT_CLEAR(currentStatus.digOut, (chanX) );
                  }  
              }
              
 
          else if (currentStatus.condition_pass[chanX] == 0)  //means it met the conditions to turn off
                  {
                  //deactivate the output according to setup/config
                  if (configPage2.port_PortValue[chanX] == 1 ) // if the output is active high
                      {
                       currentStatus.OutputPort[chanX] = 0b00000010;             
                       BIT_CLEAR(currentStatus.digOut, (chanX) );
                      }    
                  else if (configPage2.port_PortValue[chanX] == 0 ) 
                      {
                       currentStatus.OutputPort[chanX] = 0b00000000;
                       BIT_SET(currentStatus.digOut, (chanX) );
                      }   
                  }   

           state = bitRead(currentStatus.digOut,(chanX));
           digitalWrite(pinOut[chanX+1],state);     
}

void initialOutputs()
{
  
  for (byte DoutCH = 1; DoutCH < 17 ; DoutCH++)     //loop through outputs 1 to 16
    {
      
     portX = DoutCH-1;
     if (pinOut[portX+1] < 255)    //if pin is not set to 0 then is in use by selected board so drive the digital outputs according to current active channel
       { 
        state = configPage2.port_InitValue[portX];
        if (!configPage2.port_Enabled[portX])
          {
            state = 0;    //if output is disabled then set pin off
          } 
       }
   else
      {
        configPage2.port_Enabled[portX] = 0; //disable output as pin is not configured
        state = 0;    //pin is unused(0 in utils) so set pin state off
      }      
        currentStatus.condition_pass[portX] = state;
    }

}    
void blinkCEL()
{
  digitalWrite(LED_BUILTIN,1);

}

