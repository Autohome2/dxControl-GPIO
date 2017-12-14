void driveDisplay()
{
/* insert your display code in the places marked below
    it is called at 10hz
    read the data directly from the currentStatus variables
    eg currentStatus.EXin[0] to currentStatus.EXin[15] or other local variables
*/  
#if DISP1_ACTIVE == 1 
     if ((DISP1_SPI_I2C == 1) && (DISP1_I2C_ROUTE !=0))
        {
           tcaselect(DISP1_ROUTE_OUT,1);
        }
      u8g2_1.setFont(u8g2_font_ncenB14_tr);
      u8g2_1.firstPage();
      do {
      /* start your user display code for display1 here */          
          u8g2_1.setCursor(0, 20);
          u8g2_1.print(F("RPM "));
          u8g2_1.setCursor(50, 20);
          u8g2_1.print(currentStatus.EXin[0]);
          u8g2_1.setCursor(0, 50);
          u8g2_1.print(F("MAP "));
          u8g2_1.setCursor(50, 50);
          u8g2_1.print(currentStatus.EXin[1]);
          } while ( u8g2_1.nextPage() );
#endif

#if DISP2_ACTIVE == 1 
     if ((DISP2_SPI_I2C == 1) && (DISP2_I2C_ROUTE !=0))
        {
           tcaselect(DISP2_ROUTE_OUT,2);
        }     
      u8g2_2.setFont(u8g2_font_ncenB14_tr);  
      u8g2_2.firstPage();
      do {                                              
      /* start your user display code for display2 here */  
          u8g2_2.setFont(u8g2_font_logisoso58_tr);
          u8g2_2.drawStr(0,63,"1");
          } while ( u8g2_2.nextPage() );
#endif
}

void initialise_display()
{
#if DISP1_ACTIVE == 1 
    if ((DISP1_SPI_I2C == 1) && (DISP1_ADDRESS !=0)){u8g2_1.setI2CAddress(DISP1_ADDRESS);}        //if i2c is selected , set i2c address of display if specified
    u8g2_1.begin();
#endif    

#if DISP2_ACTIVE == 1
    if ((DISP2_SPI_I2C == 1) && (DISP2_ADDRESS !=0)){u8g2_2.setI2CAddress(DISP2_ADDRESS);}       //if i2c is selected , set i2c address of display if specified
    u8g2_2.begin();
#endif
} 

void tcaselect(uint8_t i, uint8_t dispnum) {
  if (i > 7) return;
  if (dispnum == 1)  {Wire.beginTransmission(DISP1_I2C_ROUTE);}
  else if (dispnum == 2)  {Wire.beginTransmission(DISP2_I2C_ROUTE);}
  Wire.write(1 << i);
  Wire.endTransmission();  
}
