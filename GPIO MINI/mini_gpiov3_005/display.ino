void driveDisplay(uint8_t displayloop)
{
/* put your display code in here
    it is called at 15hz
    configure the data you want to see in TS
    then read the data directly from the variables
    currentStatus.EXin[0] to currentStatus.EXin[15] 

    Due to issues with the i2c library on avr arduino do NOT use more than 2 i2c display at a time. otherwise TS connection issues will occur.
    
*/
 switch (displayloop)
       {
        case 1:  
        #if DISP1_ACTIVE == 1
            if ((DISP1_SPI_I2C == 1) && (DISP1_I2C_MUX_ROUTE != 255))
              {
               tcaselect(DISP1_TCA_ROUTE_OUT,DISP1_I2C_MUX_ROUTE);
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
        break;
        
        case 2:
        #if DISP2_ACTIVE == 1
            if ((DISP2_SPI_I2C == 1) && (DISP2_I2C_MUX_ROUTE != 255))
              {
               tcaselect(DISP2_TCA_ROUTE_OUT,DISP2_I2C_MUX_ROUTE);
              } 
            u8g2_2.firstPage();
            do {
                u8g2_2.setFont(u8g2_font_logisoso58_tr);
                u8g2_2.drawStr(0,63,"D 2");
               } while ( u8g2_2.nextPage() );
        #endif
        break;
        
        case 3:
        #if DISP3_ACTIVE == 1 
            if ((DISP3_SPI_I2C == 1) && (DISP3_I2C_MUX_ROUTE != 255))
              {
               tcaselect(DISP3_TCA_ROUTE_OUT,DISP3_I2C_MUX_ROUTE);
              }
            u8g2_3.firstPage();
            do {
                u8g2_3.setFont(u8g2_font_logisoso58_tr);
                u8g2_3.drawStr(0,63,"D 3");
               } while ( u8g2_3.nextPage() );
        #endif
        break;
        
        case 4:
        #if DISP4_ACTIVE == 1 
            if ((DISP4_SPI_I2C == 1) && (DISP4_I2C_MUX_ROUTE != 255))
              {
               tcaselect(DISP4_TCA_ROUTE_OUT,DISP4_I2C_MUX_ROUTE);
              }
            u8g2_4.firstPage();
            do {
                u8g2_4.setFont(u8g2_font_logisoso58_tr);
                u8g2_4.drawStr(0,63,"D 4");
               } while ( u8g2_4.nextPage() );
        #endif
        break;        
       }
}

void initialise_display()
{
#if DISP1_ACTIVE == 1
    if ((DISP1_SPI_I2C == 1) && (DISP1_I2C_MUX_ROUTE != 255))
        {
           tcaselect(DISP1_TCA_ROUTE_OUT,DISP1_I2C_MUX_ROUTE);
        }
        
    if ((DISP1_SPI_I2C == 1) && (DISP1_ADDRESS != 0)){u8g2_1.setI2CAddress(DISP1_ADDRESS);}        //if i2c is selected , set i2c address of display if specified 
    u8g2_1.begin();
#endif    

#if DISP2_ACTIVE == 1
    if ((DISP2_SPI_I2C == 1) && (DISP2_I2C_MUX_ROUTE != 255))
        {
           tcaselect(DISP2_TCA_ROUTE_OUT,DISP2_I2C_MUX_ROUTE);
        }
    
    if ((DISP2_SPI_I2C == 1) && (DISP2_ADDRESS != 0)){u8g2_2.setI2CAddress(DISP2_ADDRESS);}        //if i2c is selected , set i2c address of display if specified
    u8g2_2.begin();
#endif

#if DISP3_ACTIVE == 1 
    if ((DISP3_SPI_I2C == 1) && (DISP3_I2C_MUX_ROUTE != 255))
        {
           tcaselect(DISP3_TCA_ROUTE_OUT,DISP3_I2C_MUX_ROUTE);
        }
        
    if ((DISP3_SPI_I2C == 1) && (DISP3_ADDRESS != 0)){u8g2_3.setI2CAddress(DISP3_ADDRESS);}        //if i2c is selected , set i2c address of display if specified
    u8g2_3.begin();
#endif    

#if DISP4_ACTIVE == 1
    if ((DISP4_SPI_I2C == 1) && (DISP4_I2C_MUX_ROUTE != 255))
        {
           tcaselect(DISP4_TCA_ROUTE_OUT,DISP4_I2C_MUX_ROUTE);
        }
    if ((DISP4_SPI_I2C == 1) && (DISP4_ADDRESS != 0)){u8g2_4.setI2CAddress(DISP4_ADDRESS);}        //if i2c is selected , set i2c address of display if specified
    u8g2_4.begin();
#endif
} 

void tcaselect(uint8_t portnum, uint8_t address) 
{
  if (portnum > 7) return;
  Wire.beginTransmission(address);
  Wire.write(1 << portnum);
  Wire.endTransmission();  
}
