void driveDisplay()
{
/* put your display code in here
    it is called at 15hz
    configure the data you want to see in TS
    then read the data directly from the variables
    currentStatus.EXin[0] to currentStatus.EXin[15] 
*/  
#if DISP1_ACTIVE == 1
     if ((DISP1_SPI_I2C == 1) && (DISP1_I2C_ROUTE !=0))
        {
           tcaselect(DISP1_ROUTE_OUT,1);
        }
      u8g2_1.setFont(u8g2_font_ncenB14_tr);
      u8g2_1.firstPage();
      do {
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
      u8g2_2.firstPage();
      do {
          u8g2_2.setFont(u8g2_font_logisoso58_tr);
          u8g2_2.drawStr(0,63,"1");
          } while ( u8g2_2.nextPage() );
#endif

#if DISP3_ACTIVE == 1 
     if ((DISP3_SPI_I2C == 1) && (DISP3_I2C_ROUTE !=0))
        {
           tcaselect(DISP3_ROUTE_OUT,3);
        }
      u8g2_3.firstPage();
      do {
          u8g2_3.setFont(u8g2_font_logisoso58_tr);
          u8g2_3.drawStr(0,63,"3");
          } while ( u8g2_3.nextPage() );
#endif

#if DISP4_ACTIVE == 1 
     if ((DISP4_SPI_I2C == 1) && (DISP4_I2C_ROUTE !=0))
        {
           tcaselect(DISP4_ROUTE_OUT,4);
        }
      u8g2_4.firstPage();
      do {
          u8g2_4.setFont(u8g2_font_logisoso58_tr);
          u8g2_4.drawStr(0,63,"4");
          } while ( u8g2_4.nextPage() );
#endif
}

void initialise_display()
{
#if DISP1_ACTIVE == 1
    if ((DISP1_SPI_I2C == 1) && (DISP1_ADDRESS !=0)){u8g2_1.setI2CAddress(DISP1_ADDRESS);}        //if i2c is selected , set i2c address of display if specified 
    u8g2_1.begin();
#endif    
#if DISP2_ACTIVE == 1
    if ((DISP2_SPI_I2C == 1) && (DISP2_ADDRESS !=0)){u8g2_2.setI2CAddress(DISP2_ADDRESS);}        //if i2c is selected , set i2c address of display if specified
    u8g2_2.begin();
#endif
#if DISP3_ACTIVE == 1 
    if ((DISP3_SPI_I2C == 1) && (DISP3_ADDRESS !=0)){u8g2_3.setI2CAddress(DISP3_ADDRESS);}        //if i2c is selected , set i2c address of display if specified
    u8g2_3.begin();
#endif    
#if DISP4_ACTIVE == 1
    if ((DISP4_SPI_I2C == 1) && (DISP4_ADDRESS !=0)){u8g2_4.setI2CAddress(DISP4_ADDRESS);}        //if i2c is selected , set i2c address of display if specified
    u8g2_4.begin();
#endif
} 

void tcaselect(uint8_t i, uint8_t dispnum) 
{
  if (i > 7) return;
  if (dispnum == 1)  {Wire.beginTransmission(DISP1_I2C_ROUTE);}
  else if (dispnum == 2)  {Wire.beginTransmission(DISP2_I2C_ROUTE);}
  else if (dispnum == 3)  {Wire.beginTransmission(DISP3_I2C_ROUTE);}
  else if (dispnum == 4)  {Wire.beginTransmission(DISP4_I2C_ROUTE);}
  Wire.write(1 << i);
  Wire.endTransmission();  
}
