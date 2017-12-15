void driveOutputs()
{
  if(BIT_CHECK(currentStatus.testIO_hardware, 0) == 0)   //if testenable unset then check outputs according to port editor
     {
    //  currentStatus.dev1 = 11;
      for (byte DoutCH = 1; DoutCH < 17 ; DoutCH++)     //loop through outputs 1 to 32
         {      
          portX = DoutCH-1;
          if (pinOut[portX+1] < 255)    //if pin is not set to 255 then is in use by selected board so drive the digital outputs according to current active channel
            {                
            if(configPage2.port_Enabled[portX] == 1)
              {
//    currentStatus.dev1 = configPage2.port_Enabled[portX];              
               //uint8_t checkcondloop = 0;
               int16_t offValue1;
               int16_t offValue2;
               //first get the conditon checks into flag array for current io output channel 
               // 0 is first condition(EDITOR_COND_1) , 1 is second ,2 is reserved for third .
               // 3 is the first linking condition(EDITOR_LINK_COND_1) , 4 is reserved for the second linking condition
               currentStatus.currentInputvalueCond[EDITOR_COND_1] = configPage2.port_Condition[portX] ;                     //get first condition into array
               currentStatus.currentInputvalueCond[EDITOR_COND_2] = configPage2.port_Condition[portX+16] ;                 //get second condition into array
               currentStatus.currentInputvalueCond[EDITOR_LINK_COND_1] = configPage2.port_Condition_relationship[portX] ;  //get first linking condition into array
              for ( uint8_t checkcondloop = 0; checkcondloop < 2; checkcondloop++)
                 {
                  if (currentStatus.currentInputvalueCond[EDITOR_LINK_COND_1] == 32 && checkcondloop == 1)
                    {
                      currentStatus.condition_pass[(portX+(checkcondloop*16))] = 1;  //set status to pass
                      break; //if there is no connecting/linking condition(32) then exit the checkcondloop now           
                    }
                  getAnalogBYoffset(configPage2.port_OutOffset[(portX+(checkcondloop*16))],checkcondloop); //lookup analog value based on selected outchannel per current output
                  
//    currentStatus.dev2 = currentStatus.currentInputvalue[checkcondloop];     

                  switch (configPage2.port_Condition[(portX+(checkcondloop*16))])
                     {
                      case 38:
                      //& condition
                      if ((currentStatus.currentInputvalue[checkcondloop]) & (configPage2.port_Threshold[(portX+(checkcondloop*16))]) == configPage2.port_Hysteresis[(portX+(checkcondloop*16))])
                        {
                          currentStatus.condition_pass[(portX+(checkcondloop*16))] = 1;  //set status to pass
                        }
                      else
                        {
                         currentStatus.condition_pass[(portX+(checkcondloop*16))] = 0;  //set status to off 
                        } 
                      break;
                    
                      case 60:
                      //< condition
                       offValue2 = (configPage2.port_Threshold[(portX+(checkcondloop*16))] + configPage2.port_Hysteresis[(portX+(checkcondloop*16))]); 
                       if (offValue2 >= 1024 ){ offValue2 = 1024;}

                       if (currentStatus.currentInputvalue[checkcondloop] < configPage2.port_Threshold[(portX+(checkcondloop*16))])
                          {
                           //currentStatus.condition_pass_last[portX] = currentStatus.condition_pass[portX];  //set last status from status  
                           currentStatus.condition_pass[(portX+(checkcondloop*16))] = 1;  //set status to pass
                          }
  
                       if (currentStatus.currentInputvalue[checkcondloop] >= offValue2) 
                          {
                           //currentStatus.condition_pass_last[portX] = currentStatus.condition_pass[portX];  //set last status from status                          
                           currentStatus.condition_pass[(portX+(checkcondloop*16))] = 0;  //set status to off (threshold+hysteresis)
                          }
       
                      break;

                      case 61:
                      //= condition
                      offValue1 = (configPage2.port_Threshold[(portX+(checkcondloop*16))] - configPage2.port_Hysteresis[(portX+(checkcondloop*16))]);
                      if (offValue1 <= 0 ){offValue1 = 0;}
                      offValue2 = (configPage2.port_Threshold[(portX+(checkcondloop*16))] + configPage2.port_Hysteresis[(portX+(checkcondloop*16))]);
                      if (offValue2 >= 1024 ){ offValue2 = 1024;}
                    
                      if (currentStatus.currentInputvalue[checkcondloop] == configPage2.port_Threshold[(portX+(checkcondloop*16))])
                         {  
                             currentStatus.condition_pass[(portX+(checkcondloop*16))] = 1;  //set status to pass
                         }
                 else if (currentStatus.condition_pass[(portX+(checkcondloop*16))] == 1)
                         {
                          if (currentStatus.currentInputvalue[checkcondloop] < offValue1)  
                            { 
                             currentStatus.condition_pass[(portX+(checkcondloop*16))] = 0; // set status to fail (threshold-hysteresis)
                            }
                     else if (currentStatus.currentInputvalue[checkcondloop] > offValue2)  
                            {                    
                             currentStatus.condition_pass[(portX+(checkcondloop*16))] = 0; // set status to fail (threshold+hysteresis)
                            }
                         }
  
                      break;

                      case 62:
                      //> condition      
      //   currentStatus.dev2 = currentStatus.currentInputvalue[checkcondloop];             
                      offValue1 = (configPage2.port_Threshold[(portX+(checkcondloop*16))] - configPage2.port_Hysteresis[(portX+(checkcondloop*16))]);
                      if (offValue1 <= 0 ){offValue1 = 0;}
      
                      if (currentStatus.currentInputvalue[checkcondloop] > configPage2.port_Threshold[(portX+(checkcondloop*16))])
                         {
                          currentStatus.condition_pass[(portX+(checkcondloop*16))] = 1;  //set status to pass
                         }   
                      if (currentStatus.currentInputvalue[checkcondloop] <= offValue1) // has it dropped below the hys
                         {                         
                          currentStatus.condition_pass[(portX+(checkcondloop*16))] = 0;  //set status to off (threshold+hysteresis)
                         }   
                      break;                    
                    
                      } //ends the switch case
                 }  //ends the checkcondloop for loop 
/*now check the linking conditions*/
                // if both conditions(or first if only one) pass then check conditional relatioship for action output
                switch (currentStatus.currentInputvalueCond[EDITOR_LINK_COND_1])
                      {
                        case 32 :
                        // no second condition
                            if (currentStatus.condition_pass[portX] == 1)
                              {
                                currentStatus.condition_all_pass = 1; //no second condition so condition 0 passed so total pass 
                              }
                        //else if (currentStatus.condition_pass_last[portx] == 1 || currentStatus.condition_pass_last[portx] == 2)
                        //      {
                        //        if (currentStatus.condition_pass[portx] == 2)
                        //          {
                        //            currentStatus.condition_pass[(portx+32)] = 1;  // condition 0 passed so total pass
                        //          }
                        //      }      
                        else if (currentStatus.condition_pass[portX] == 0)
                              {
                                currentStatus.condition_all_pass = 0;     
                              }      
                       // else
                       //       {
                       //        currentStatus.condition_pass[(portx+32)] = 0 ; //total fail  
                       //       }
                       
                        break;
            
                        case 124 :
                        // OR
                            if (currentStatus.condition_pass[portX] == 1 || currentStatus.condition_pass[(portX+16)] == 1)
                                {
                                  currentStatus.condition_all_pass = 1;  // either condition[0] or [1] passed so total pass
                                }
                        //else if (currentStatus.condition_pass_last[portx] == 1 || currentStatus.condition_pass_last[(portx+16)] == 1 
                        //        || currentStatus.condition_pass_last[portx] == 2 || currentStatus.condition_pass_last[(portx+16)] == 2)
                        //        {
                        //          if (currentStatus.condition_pass[portx] == 2 || currentStatus.condition_pass[(portx+16)] == 2)
                        //            {
                        //              currentStatus.condition_pass[(portx+32)] = 1;  // either condition[0] or [1] passed so total pass
                        //            }  
                        //        }
                        else if (currentStatus.condition_pass[portX] == 0 && currentStatus.condition_pass[(portX+16)] == 0)
                                {
                                  currentStatus.condition_all_pass = 0;     //total fail 
                                } 
                        //else
                        //        {
                        //          currentStatus.condition_pass[(portx+32)] = 0 ; //total fail  
                        //        }  
                        break ;
            
                        case 38:
                        // AND
                            if (currentStatus.condition_pass[portX] == 1 && currentStatus.condition_pass[(portX+16)] == 1)
                                {
                                  currentStatus.condition_all_pass = 1;  // both condition[0] and [1] passed so total pass
                                }
                        else if (currentStatus.condition_pass[portX] == 0 || currentStatus.condition_pass[(portX+16)] == 0)
                                {
                                  currentStatus.condition_all_pass = 0;       //if either failed then total fail     
                                } 
                        //else if (currentStatus.condition_pass_last[portx] == 1 || currentStatus.condition_pass_last[(portx+16)] == 1 
                        //        || currentStatus.condition_pass_last[portx] == 2 || currentStatus.condition_pass_last[(portx+16)] == 2)
                        //        {
                        //          if (currentStatus.condition_pass[portx] == 2 || currentStatus.condition_pass[(portx+16)] == 2)
                        //            {
                        //              currentStatus.condition_pass[(portx+32)] = 1;  // either condition[0] or [1] passed so total pass
                        //            }  
                        //        }             
                       // else
                       //         {
                       //           currentStatus.condition_pass[(portx+32)] = 0 ; //total fail  
                       //         }
           
                        break ;
            
                        case 33:
                        // NOT
                            if (currentStatus.condition_pass[portX] == 1 && currentStatus.condition_pass[(portX+16)] == 0)
                                {
                                  currentStatus.condition_all_pass = 1;  //only condition[0] pass so total pass
                                }
                      else if (currentStatus.condition_pass[portX] == 0 && currentStatus.condition_pass[(portX+16)] == 1)
                                {
                                  currentStatus.condition_all_pass = 1;  //only condition[1] pass so total pass
                                }   
                      else if (currentStatus.condition_pass[portX] == 1 && currentStatus.condition_pass[(portX+16)] == 1)
                                {
                                  currentStatus.condition_all_pass = 0 ; //both condition[0] and [1] passed so total fail  
                                }
                      else if (currentStatus.condition_pass[portX] == 0 && currentStatus.condition_pass[(portX+16)] == 0)
                                {
                                  currentStatus.condition_all_pass = 0 ; //both condition[0] and [1] passed so total fail 
                                }                                     
                                      
                      break;

                      default:
                              currentStatus.condition_all_pass = 0;  //no relationship condition matched so output fails
                      break;
                  }  //closes switch/case for link relationship
          
            outputaction(portX); //set output high/lows
                                  
              } //ends the check is output is enabled
            
           //else   //else if output is not enabled
           //   {
           //           currentStatus.condition_pass[(portX+(checkcondloop*16))] = 0;      //set pin state to off 
           //   }
                                                 
            }    // ends is the pin used by board
       
          else             // else pin is not in use
            {
        configPage2.port_Enabled[portX] = 0; //disable output as pin is not configured for use
        state = 0;    //pin is unused(0 in utils) so set pin state off
            }
                    
         }     // ends the for next 1-17 count loop
     }  //ends the else (not a test)
  
  else if(BIT_CHECK(currentStatus.testIO_hardware, 0) == 1)       // so this is a test , do direct port ops according to the bitread  
     {
     // currentStatus.dev1 = 101;   
      for (byte ToutCH = 1; ToutCH < 17 ; ToutCH++)     //loop through outputs 1 to 17
         {
          portX = ToutCH-1;
          state = bitRead(currentStatus.digOut,(portX));
          digitalWrite(pinOut[portX+1],state);
          state = bitRead(currentStatus.digOut_2,(portX));
          digitalWrite(pinOut[portX+16],state);
         }  
     }  

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
          if (currentStatus.condition_all_pass == 1)
              {  
              //activate the output according to setup/config
              if (configPage2.port_PortValue[chanX] == 1 ) // if the output is active high
                  {
                   currentStatus.OutputPort[chanX] = B00000011;  // output1 is [0]
                   BIT_SET(currentStatus.digOut, (chanX) );
                  }  
              else if (configPage2.port_PortValue[chanX] == 0 )  // if the output is active low
                  {
                    currentStatus.OutputPort[chanX] = B00000001;
                    BIT_CLEAR(currentStatus.digOut, (chanX) );
                  }  
              }
              
 
          else if (currentStatus.condition_pass[chanX] == 0)  //means it met the conditions to turn off
                  {
                  //deactivate the output according to setup/config
                  if (configPage2.port_PortValue[chanX] == 1 ) // if the output is active high
                      {
                       currentStatus.OutputPort[chanX] = B00000010;             
                       BIT_CLEAR(currentStatus.digOut, (chanX) );
                      }    
                  else if (configPage2.port_PortValue[chanX] == 0 ) 
                      {
                       currentStatus.OutputPort[chanX] = B00000000;
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

