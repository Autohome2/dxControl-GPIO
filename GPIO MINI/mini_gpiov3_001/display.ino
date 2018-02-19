void driveDisplay()
{
/* put your display code in here
    it is called at 15hz
    configure the data you want to see in TS
    then read the data directly from the variables
    currentStatus.EXin[0] to currentStatus.EXin[15] 
*/  
#if DISP1_ACTIVE == 1
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
      u8g2_2.firstPage();
      do {
          u8g2_2.setFont(u8g2_font_logisoso58_tr);
          u8g2_2.drawStr(0,63,"1");
          } while ( u8g2_2.nextPage() );
#endif
}

void initialise_display()
{
#if DISP1_ACTIVE == 1 
    u8g2_1.begin();
#endif    
#if DISP2_ACTIVE == 1
    u8g2_2.begin();
#endif
} 
