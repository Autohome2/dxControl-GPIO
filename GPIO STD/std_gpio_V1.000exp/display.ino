void driveDisplay()
{
/* insert your display code in the places marked below
    it is called at 10hz
    read the data directly from the currentStatus variables
    eg currentStatus.EXin[0] to currentStatus.EXin[15] or other local variables
*/  
#if DISP1_ACTIVE == 1 
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
    u8g2_1.begin();
#endif    

#if DISP2_ACTIVE == 1
    u8g2_2.begin();
#endif
} 

void tcaselect(uint8_t i, uint8_t dispnum) {
}
