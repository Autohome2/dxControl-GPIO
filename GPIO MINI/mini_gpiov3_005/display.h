#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//display module options . only choose one of the following defines for display selection  , comment out the unused ones 

//set display 1 type

#define DISP1_ACTIVE         0
#define DISP1_SPI_I2C        1          // 0 == SPI , 1 == I2C

//if I2C set these next three values
#define DISP1_ADDRESS        0          //direct i2c == 0 , specified address == screen address
#define DISP1_I2C_MUX_ROUTE  0x70       // direct i2c == 0 , via mux == mux address
#define DISP1_TCA_ROUTE_OUT  0          // the output port on the tca9548 screen is connected to if mux in use , set to 255 if not used
        
//only choose one of the following defines for display type selection  , comment out the unused ones
#define DISP1_USE_SSD1106_I2C
//#define DISP1_USE_SSD1306_I2C
//#define DISP1_USE_SSD1106_SPI
//#define DISP1_USE_SSH1106_SPI
//#define DISP1_USE_4x20_I2C_EXP

//set display size
#define USE_128x64
//#define USE_128x128

//set pins for screen 1 in spi mode
#define DISPLAY1_CS 7                //pin to use for CS
#define DISPLAY1_DC 6                //pin to use for DC
#define DISPLAY1_RESET 8 

//---------------------------------------------------------------------------------------------------------

//display 2

//set display 2 type
#define DISP2_ACTIVE         0 
#define DISP2_SPI_I2C        1             // 0 == SPI , 1 == I2C

//if I2C set these next three values
#define DISP2_ADDRESS        0             //direct i2c == 0 , specified address == screen address
#define DISP2_I2C_MUX_ROUTE  0x70             // direct i2c == 0 , via mux == mux address
#define DISP2_TCA_ROUTE_OUT  1             // the output port on the tca9548 screen is connected to if mux in use  , set to 255 if not used

//only choose one of the following defines for display type selection  , comment out the unused ones
#define DISP2_USE_SSD1106_I2C
//#define DISP2_USE_SSD1306_I2C
//#define DISP2_USE_SSD1106_SPI
//#define DISP2_USE_SSH1106_SPI
//#define DISP2_USE_4x20_I2C_EXP

//set pins for screen 2 in spi mode
#define DISPLAY2_CS 7                //pin to use for CS
#define DISPLAY2_DC 6                //pin to use for DC
#define DISPLAY2_RESET 8

//-----------------------------------------------------------------------------------------------------

//set display 3 type

#define DISP3_ACTIVE         0
#define DISP3_SPI_I2C        1             // 0 == SPI , 1 == I2C

//if I2C set these next three values
#define DISP3_ADDRESS        0          //direct i2c == 0 , specified address == screen address
#define DISP3_I2C_MUX_ROUTE  0x70             // direct i2c == 0 , via mux == mux address
#define DISP3_TCA_ROUTE_OUT  6             // the output port on the tca9548 screen is connected to if mux in use , set to 255 if not used

//only choose one of the following defines for display type selection  , comment out the unused ones
#define DISP3_USE_SSD1106_I2C
//#define DISP3_USE_SSD1306_I2C
//#define DISP3_USE_SSD1106_SPI
//#define DISP3_USE_SSH1106_SPI
//#define DISP3_USE_4x20_I2C_EXP

//set display size
//#define USE_128x64
//#define USE_128x128

//set pins for screen 3 in spi mode
#define DISPLAY3_CS 7                //pin to use for CS
#define DISPLAY3_DC 6                //pin to use for DC
#define DISPLAY3_RESET 8 

//---------------------------------------------------------------------------------------------------------

//display 4

//set display 4 type
#define DISP4_ACTIVE          0 
#define DISP4_SPI_I2C         1             // 0 == SPI , 1 == I2C

//if I2C set these next three values
#define DISP4_ADDRESS        0             //direct i2c == 0 , specified address == screen address
#define DISP4_I2C_MUX_ROUTE  0x70             // direct i2c == 0 , via mux == mux address
#define DISP4_TCA_ROUTE_OUT  7             // the output port on the tca9548 screen is connected to if mux in use , set to 255 if not used

//only choose one of the following defines for display type selection  , comment out the unused ones
#define DISP4_USE_SSD1106_I2C
//#define DISP4_USE_SSD1306_I2C
//#define DISP4_USE_SSD1106_SPI
//#define DISP4_USE_SSH1106_SPI
//#define DISP4_USE_4x20_I2C_EXP

//set pins for screen 4 in spi mode
#define DISPLAY4_CS 7                //pin to use for CS
#define DISPLAY4_DC 6                //pin to use for DC
#define DISPLAY4_RESET 8

//SPI NOTES:
//spi on mega2560 mosi == 51, clk(sck) == 52
//I2C NOTES:
// i2c on the mega2560 sda == 20, scl == 21

//---------------------------------------------------------------------------------------------------------

void driveDisplay();
void initialise_display();
void tcaselect(uint8_t i, uint8_t dispnum) ;

uint8_t displayloop = 1;       //variable for current display channel to run       

#endif
