#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  #define BOARD_NR_GPIO_PINS 54
  #define LED_BUILTIN 13
  #define CORE_AVR
  #define USE_INT_EEPROM
  
#elif defined(CORE_TEENSY)
  #define BOARD_NR_GPIO_PINS 34
  
#elif defined(STM32_MCU_SERIES) || defined(_VARIANT_ARDUINO_STM32_)
  #define CORE_STM32

  //only choose one of the following two defines
   #define USE_EXT_FLASH
   #define EXT_FLASH_SIZE 8192
   #define FLASH_OFFSET  EXT_FLASH_SIZE / 2
  // #define USE_EXT_SPI_EEPROM
//  #define USE_EXT_FRAM
  #define LED_BUILTIN PC13

  extern "C" char* sbrk(int incr); //Used to freeRam
  inline unsigned char  digitalPinToInterrupt(unsigned char Interrupt_pin) { return Interrupt_pin; } //This isn't included in the stm32duino libs (yet)
  #define portOutputRegister(port) (volatile byte *)( &(port->regs->ODR) ) //These are defined in STM32F1/variants/generic_stm32f103c/variant.h but return a non byte* value
  #define portInputRegister(port) (volatile byte *)( &(port->regs->IDR) ) //These are defined in STM32F1/variants/generic_stm32f103c/variant.h but return a non byte* value
#else
  #error Incorrect board selected. Please select the correct board (Usually Mega 2560) and upload again
#endif  

// now set specific processor compile flags
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  #define MEGA_AVR

#elif defined(ARDUINO_AVR_PRO)
  #define 328_AVR

#elif defined(ARDUINO_Nucleo_64)
  #define NUCLEO_64_STM32

#elif defined(MCU_STM32F103C8)
  #define F108C8_STM32

#elif defined(MCU_STM32F407VGT6)
  #define F407_STM32  

#endif


/*
 The "A" command allows you to specify where in the reltime data list you want the Speeduino to start sending you data from , and how many bytes you want to be sent.
 The format is "A" where
 A == the main command

 Speeduino replies with 
 "A" == confirming the command sent
 reply length == a single byte with a value of the number of bytes it will be sending
 xx bytes == the number of data bytes according to the replylength.
*/
 
/*
 The "r" command allows you to specify where in the reltime data list you want the Speeduino to start sending you data from , and how many bytes you want to be sent.
 The format is "r\$tsCanId\x30%2o%2c" where
 r == the main command
 tsCanId == the canid of the device being called
 x30 == dec48 the optimised output command
 2o == 2 bytes of offset
 2c == 2 bytes of length

 Speeduino replies with 
 "r" == confirming the command sent
 reply length == a single byte with a value of the number of bytes it will be sending
 xx bytes == the number of data bytes according to the replylength.
  
 */
#define maincommand  'r'    // the command to send to the Speeduino
#define commandletterr  'r'
uint8_t tsCanId = 0;          // this is the tunerstudio canID for the device you are requesting data from , this is 0 for the main ecu in the system which is usually the speeduino ecu . 
                              // this value is set in Tunerstudio when configuring your Speeduino
//uint16_t realtime_offset = 4;  // the offset of the realtime data to start reading from
//uint16_t realtime_bytes = 1;   // the number of bytes requested

/*
change the realtime_offset to what offset position you wish to read the realtime data from
eg : realtime_offset = 4 , this relates to the currentStatus.MAP
This is 1 byte long so if this is the only byte you want to read set realtime_bytes to 1

eg : realtime_offset = 8 , this relates to the  currentStatus.battery10 (battery voltage)
this is 1 byte long.
if you set realtime_bytes = 2
then you will also be sent offset 9 too which is currentStatus.O2
 */
const unsigned char simple_remote_signature[]    = "speeduino_mini_GPIOV0.003 201706"; //this must match the ini
const unsigned char simple_remote_RevNum[] = "speeduino 201706-mini GPIO V0.003";      //this is what is displayed in the TS header bar
uint8_t thistsCanId = 4;    // this is the tunerstudio canId of this device
const uint8_t data_structure_version = 2; //This identifies the data structure when reading / writing.
const uint8_t page_1_size = 128;
const uint16_t page_2_size = 256;
volatile uint8_t swap_page = 0; // current external flash swap page number
volatile bool swap_next_page = 0; // 0 == dont swap pages , 1 == swap pages when all written

byte zero = 0;
byte tmp;         //used in assembling incoming serial data ints
uint16_t theoffset, thelength;  //used with serial data

//Handy bitsetting macros
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_CHECK(var,pos) ((var) & (1<<(pos)))

#define BIT_TIMER_1HZ             0
#define BIT_TIMER_4HZ             1
#define BIT_TIMER_10HZ            2
#define BIT_TIMER_15HZ            3
#define BIT_TIMER_25HZ            4
#define BIT_TIMER_30HZ            5
#define celBlink_time             4   //4 seconds

volatile byte TIMER_mask;
volatile byte LOOP_TIMER;

//The status struct contains the current values for all 'live' variables
//In current version this is x bytes
struct statuses {
  volatile byte secl; //Continous
  volatile byte systembits ;
  volatile unsigned int loopsPerSecond ;
 volatile  uint16_t freeRAM ;
 volatile uint8_t currentPage;
 volatile uint8_t testIO_hardware;//testIO_hardware
 uint16_t currentInputvalue[2];      //holds the analog input value for each conditional input , [0] first condition and [1] holds the second
 uint16_t currentInputvalueCond[3];  //holds the input test condition flags for each test condition , [0] holds first, [1] holds the second and [2] holds the total pass
 uint8_t condition_pass[16];          // array stores pass/fail flags for the one or two(if selected) condition checks
 uint8_t condition_pass_last[16];     // array stores pass/fail flags for the one or two(if selected) condition checks
 uint8_t OutputPort[16];             //output port operating condition status flags
 volatile uint16_t digOut;        //bits showing digital output state(0-15)
 volatile uint16_t digOut_Active; // bits show if channel is used by board selected when pin value is < 255
 volatile uint16_t digOut_2;
 volatile uint16_t digOut_2_Active; // bits show if channel is used by board selected when pin value is < 255
 volatile uint16_t digIn;         // bits showing digital input state(0-15)
 volatile uint16_t digIn_Active;  // bits showing channel is used by board selected when pin value is < 255
 volatile uint16_t Analog[16];    // 16bit analog value data array for local analog(0-15)
 volatile uint16_t Analog_Active; // bits showing channel is used by board selected when pin value is < 255
 volatile uint16_t EXin[16];      // 16bit value data array for external analog(0-15)
 
 volatile uint16_t dev1;          //developer use only
 volatile uint16_t dev2;          //developer use only
 volatile uint16_t dev3;          //developer use only
 volatile uint16_t dev4;          //developer use only
};
//struct statuses currentStatus; //The global status object

//Page 1 of the config - See the ini file for further reference
//this is laid out as first the byte size data then the words

struct __attribute__ ( ( packed ) ) config1 {
uint16_t master_controller_address:10 ;
byte pinLayout;
byte speeduinoConnection;       //type of connection to speedy , 0==none 1 == serial3 2 == canbus
uint16_t speeduinoBaseCan ;       //speeduino base can address
byte unused6;
byte unused7;
byte unused8;
byte unused9;
uint16_t DoutchanActive;          // digital outputchannels 1-16 active flags
uint16_t DoutchanActive_2;        // digital output channels 17-32 active flags
uint16_t DinchanActive;           // digital input channels 1-16 active flags
uint16_t DinchanActive_2;         // digital input channels 17-32 active flags
uint16_t AinchanActive;           // analog input channels 1-16 active flags
uint16_t AinchanActive_2;         // analog  input channels 17-32 active flags
uint16_t exinsel;                 // External input channel enabled bit flags
uint16_t INdata_from_Can[16];     // can address of source of data 0x100(256dec) to 0x7FF(2047dec) as 0 dec - 535 dec
byte data_from_offset[16];        // offset of data source 0 - 255
byte num_bytes[16];               // number of bytes length of data source 0,1,or 2
byte unused88;
byte unused89;
byte unused90;
byte unused91;
byte unused92;
byte unused93;
byte unused94;
byte unused95;
byte unused96;
byte unused97;
byte unused98;
byte unused99;
byte unused100;
byte unused101;
byte unused102;
byte unused103;
byte unused104;
byte unused105;
byte unused106;
byte unused107;
byte unused108;
byte unused109;
byte unused110;
byte unused111;
byte unused112;
byte unused113;
byte unused114;
byte unused115;
byte unused116;
byte unused117;
byte unused118;
byte unused119;
byte unused120 = 200;
byte unused121;
byte unused122;
byte unused123;
byte unused124;
byte unused125;
byte unused126 = 226;
byte unused127 = 227;
};

//Page 2 of the config - See the ini file for further reference
//this is laid out as first the byte size data then the words

struct __attribute__ ( ( packed ) ) config2 {
  uint8_t    port_Enabled[16];                // 1 if enabled 0 if not
  uint8_t    port_Condition[16];              // < is 60, = is 61, > is 62, & is 38
  uint8_t    port_Condition_relationship[16]; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  uint8_t    port_InitValue[16];              // 1 on 0 off
  uint8_t    port_PortValue[16];              // 1 if active high 0 if active low
  uint8_t    port_OutSize[16];                // unsure of purpose but must be present
  uint16_t   port_OutOffset[16];              // port offset refers to the offset value from the output channels
  uint16_t    port_Threshold[16];              // threshhold value for on/off
  uint16_t    port_Hysteresis[16];             // hysteresis value for on/off
  uint8_t    port_CanId[16];                  // TScanid of the device the output channel is from  
byte unused2_208;
byte unused2_209;
byte unused2_210;
byte unused2_211;
byte unused2_212;
byte unused2_213;
byte unused2_214;
byte unused2_215;
byte unused2_216;
byte unused2_217;
byte unused2_218;
byte unused2_219;
byte unused2_220;
byte unused2_221;
byte unused2_222;
byte unused2_223;
byte unused2_224;
byte unused2_225;
byte unused2_226;
byte unused2_227;
byte unused2_228;
byte unused2_229;
byte unused2_230;
byte unused2_231;
byte unused2_232;
byte unused2_233;
byte unused2_234;
byte unused2_235;
byte unused2_236;
byte unused2_237;
byte unused2_238;
byte unused2_239;
byte unused2_240;
byte unused2_241;
byte unused2_242;
byte unused2_243;
byte unused2_244;
byte unused2_245;
byte unused2_246;
byte unused2_247;
byte unused2_248;
byte unused2_249;
byte unused2_250;
byte unused2_251;
byte unused2_252;
byte unused2_253; 
byte unused2_254;
byte unused2_255; 
};

 //declare io pins
byte pinOut[17]; //digital outputs array is +1 as pins start at 1 not 0

byte pinIn[17];  //digital inputs

byte pinAin[17]; //analog inputs


// global variables // from passthrough_example.ino
extern struct statuses currentStatus; // from passthrough.ino
extern struct config1 configPage1;  
extern struct config2 configPage2;

//extern unsigned long currentLoopTime; //The time the current loop started (uS)
//extern unsigned long previousLoopTime; //The time the previous loop started (uS)

#endif // GLOBALS_H                              
