#ifndef GLOBALS_H
#define GLOBALS_H
#include <Arduino.h>

#if defined(__AVR__)
//(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  #define BOARD_NR_GPIO_PINS 54
  #define LED_BUILTIN 13
  #define CORE_AVR
  #define USE_INT_EEPROM
  
#elif defined(ARDUINO_ARCH_SAMD)
      #define CORE_SAMD
      #define USE_INT_EEPROM        0
      #define USE_EXT_EEPROM        1
  
#elif defined(CORE_TEENSY)
      #define USE_INT_EEPROM
      #if defined(__MK64FX512__)
          #define TEENSY3_5
          #define BOARD_NR_GPIO_PINS 34
      #elif defined (__MK66FX1M0__)
          #define TEENSY3_6
#else 
    #error "unknown board"      
#endif
  
#elif defined(STM32_MCU_SERIES) || defined(_VARIANT_ARDUINO_STM32_) || (defined (ARDUINO_ARCH_STM32))     //the arch_stm32 comes from the stm32generic core addition
      #define CORE_STM32
//      #define LED_BUILTIN PC13
      //only choose one of the following two defines , comment out the unused ones
      #define USE_INT_EEPROM       1
      #define USE_EXT_FLASH        0
      #define USE_EXT_EEPROM       0
      #define USE_EXT_FRAM         0

      #define CONSOLE_USE_SER1     1        //select only one CONSOLE_USE_x
      #define CONSOLE_USE_SER2     0      // to choose which serial connects to TS
  
      //#define EXT_FLASH_SIZE 8192
      //#define FLASH_OFFSET  EXT_FLASH_SIZE / 2

      extern "C" char* sbrk(int incr); //Used to freeRam
 //     inline unsigned char  digitalPinToInterrupt(unsigned char Interrupt_pin) { return Interrupt_pin; } //This isn't included in the stm32duino libs (yet)
 //     #define portOutputRegister(port) (volatile byte *)( &(port->regs->ODR) ) //These are defined in STM32F1/variants/generic_stm32f103c/variant.h but return a non byte* value
 //     #define portInputRegister(port) (volatile byte *)( &(port->regs->IDR) ) //These are defined in STM32F1/variants/generic_stm32f103c/variant.h but return a non byte* value
#else
  #error Incorrect board selected. Please select the correct board (Usually Mega 2560) and upload again
#endif  

// now set specific processor compile flags
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  #define MEGA_AVR

#elif defined(ARDUINO_AVR_PRO)                      // pro mini ,nano or uno mcu type
  #define 328_AVR

#elif defined(ARDUINO_AVR_324)
  #define 324_AVR  

//#elif defined(ARDUINO_SAMD_ZERO)
//  #define SAMD_ZERO
  
#elif defined(ARDUINO_Nucleo_64)
  #define NUCLEO_64_STM32

#elif defined(MCU_STM32F103C8)
  #define F108C8_STM32

#elif defined(ARDUINO_BLUEPILL_F103C8)
  #define F108C8_STM32

#elif defined(MCU_STM32F407VGT6)
  #define F407_STM32  

//#elif defined (MATTAIRTECH_ARDUINO_SAMD_ZERO)
//  #define D21E_REVB

#elif defined (__SAMD21G18A__)                        // this is the arduino zero mcu type
  #define ARDUINO_ZERO
  #define USE_NATIVE         0                        // select  this or USE_PROG but not both
  #define USE_PROG           1                        // to choose which serial port is connected to TS

#elif defined (MATTAIRTECH_ARDUINO_SAMD_ZERO_SAMC21E18A)
  #define D21E_REVB_SAMC21E18A
  
#elif defined(__MK64FX512__)                               // teensy 3.5 mcu type
     #define TEENSY3_5
#else
  #error Specific board not detected. Please select the correct board (Usually Mega 2560) and upload again
    
#endif

#define NO_TS   1            //set to 1 if you DO NOT WANT to use TS to configure 
 
#define maincommand  'r'    // the command to send to the Speeduino
#define commandletterr  'r'
uint8_t tsCanId = 0;          // this is the tunerstudio canID for the device you are requesting data from , this is 0 for the main ecu in the system which is usually the speeduino ecu .                               

const unsigned char simple_remote_signature[]    = "speeduino_mini_GPIOV3.005 201802"; //this must match the ini
const unsigned char simple_remote_RevNum[] = "speeduino 201802-mini GPIO V3.005";      //this is what is displayed in the TS header bar
uint8_t thistsCanId = 4;    // this is the tunerstudio canId of this device

const uint8_t data_structure_version = 2; //This identifies the data structure when reading / writing.
const uint8_t page_1_size = 128;
const uint16_t page_2_size = 353;
const uint16_t page_3_size = 16;

volatile uint8_t swap_page = 0; // current external flash swap page number
volatile bool swap_next_page = 0; // 0 == dont swap pages , 1 == swap pages when all written

byte zero = 0;
byte tmp;         //used in assembling incoming serial data ints
uint16_t theoffset, thelength;  //used with serial data
#define addressoffset     0x100

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

//#define BIT_TIMER_1HZ             0
//#define BIT_TIMER_4HZ             1
//#define BIT_TIMER_5HZ             2
//#define BIT_TIMER_10HZ            3
//#define BIT_TIMER_15HZ            4
//#define BIT_TIMER_20HZ            5
//#define BIT_TIMER_25HZ            6
//#define BIT_TIMER_30HZ            7

#define celBlink_time             4   //4 seconds

//define masks for system status'
#define BIT_SYSTEM_READY                    0
#define BIT_SYSTEM_1                        1
#define BIT_SYSTEM_BURN_GOOD                7

//Define masks for CanStatus
#define BIT_CANSTATUS_CAN0ACTIVATED         0  //can0 has enabled
#define BIT_CANSTATUS_CAN0FAILED            1  //can0 failed to configure
#define BIT_CANSTATUS_CAN1ACTIVATED         2  //can1 has enabled
#define BIT_CANSTATUS_CAN1FAILED            3  //can1 failed o configure
#define BIT_CANSTATUS_CAN0MSGFAIL           4 //
#define BIT_CANSTATUS_CAN1MSGFAIL           5  //
#define BIT_CANSTATUS_7                     6       //
#define BIT_CANSTATUS_8                     7  //

// define masks for canModuleConfig;
#define CAN0ENABLE                          0
#define CAN1ENABLE                          1

// define maskes for generalConfig1
#define USE_REALTIME_BROADCAST              0
//#define unused1_7b                        1

//define masks for canbroadcast_config
#define GENERIC_BROADCAST                   0       // enable_canbroadcast_out  = bits,   U08,     0, [0:0], "Off", "On"
#define REMOTE_OUT0_15                      1       // enable_remoteoutput0_15  = bits,   U08,     0, [1:1], "Off", "On"
#define REMOTE_OUT16_31                     2       // enable_remoteoutput16_31 = bits,   U08,     0, [2:2], "Off", "On"
#define REMOTE_IN0_15                       3       // enable_remoteinput0_15   = bits,   U08,     0, [3:3], "Off", "On"
#define REMOTE_IN16_31                      4       // enable_remoteinput16_31  = bits,   U08,     0, [4:4], "Off", "On"
#define REMOTE_AIN0_15                      5       // enable_remoteAinput0_15 

//define masks for remote output status
#define REMOTE_OUT_OFF                      0
#define REMOTE_OUT_ON                       1
#define REMOTE_OUT_OPENCIRCUIT              2
#define REMOTE_OUT_SHORTCIRCUIT             3
#define REMOTE_OUT_THERMALOVERLOAD          4
#define REMOTE_OUT_CURRENTOVERLOAD          5
#define REMOTE_OUT_unused6                  6
#define REMOTE_OUT_unused7                  7

//define masks for remote input status
#define REMOTE_IN_OFF                      0
#define REMOTE_IN_ON                       1
#define REMOTE_IN_OPENCIRCUIT              2
#define REMOTE_IN_SHORTCIRCUIT             3
#define REMOTE_IN_THERMALOVERLOAD          4
#define REMOTE_IN_CURRENTOVERLOAD          5
#define REMOTE_IN_unused6                  6
#define REMOTE_IN_unused7                  7

//testIO_hardware bit fields
#define BIT_STATUS_TESTIO_OUTTESTENABLED       0
#define BIT_STATUS_TESTIO_OUTTESTACTIVE        1
#define BIT_STATUS_TESTIO_AINTESTENABLED       2
#define BIT_STATUS_TESTIO_AINTESTACTIVE        3
#define BIT_STATUS_TESTIO_UNUSED5              4
#define BIT_STATUS_TESTIO_UNUSED6              5
#define BIT_STATUS_TESTIO_UNUSED7              6

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
  volatile uint8_t testIO_hardware;   //testIO_hardware see bit field for bit allocation
  volatile uint16_t aintestsent;      //bitfield holding flag to show if forced value was sent
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

struct config1 {
uint16_t master_controller_address;//:11 ;
uint8_t  pinLayout;
uint8_t  speeduinoConnection;//:2;       //type of connection to speedy , 0==none 1 == serial3 2 == canbus
uint16_t speeduinoBaseCan ;//:11;       //speeduino base can address
uint8_t canModuleConfig;                //bit flags for canmodule configuration
uint8_t generalConfig1;
uint8_t  unused1_8;
uint8_t  unused1_9;
uint16_t DoutchanActive;          // digital outputchannels 1-16 active flags
uint16_t DoutchanActive_2;        // digital output channels 17-32 active flags
uint16_t DinchanActive;           // digital input channels 1-16 active flags
uint16_t DinchanActive_2;         // digital input channels 17-32 active flags
uint16_t AinchanActive;           // analog input channels 1-16 active flags
uint16_t AinchanActive_2;         // analog  input channels 17-32 active flags
uint16_t exinsel;                 // External input channel enabled bit flags
uint16_t INdata_from_Can[16];     // can address of source of data 0x100(256dec) to 0x7FF(2047dec) as 0 dec - 535 dec
uint8_t  data_from_offset[16];    // offset of data source 0 - 255
uint8_t  num_bytes[16];           // number of bytes length of data source 0,1,or 2
byte     unused1_88;
byte     unused1_89;
byte     unused1_90;
byte     unused1_91;
byte     unused1_92;
byte     unused1_93;
byte     unused1_94;
byte     unused1_95;
byte     unused1_96;
byte     unused97;
byte     unused98;
byte     unused99;
byte     unused100;
byte     unused101;
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
#if defined(CORE_AVR)
  };
#else
  } __attribute__((__packed__)); //The 32 bi systems require all structs to be fully packed
#endif

//Page 2 of the config - See the ini file for further reference
//this is laid out as first the byte size data then the words

struct config2 {
  uint8_t    port_Enabled[16];                // 1 if enabled 0 if not
  uint8_t    port_Condition[32];              // < is 60, = is 61, > is 62, & is 38
  uint8_t    port_Condition_relationship[16]; // none is 32 , OR is 124 , AND is 38 , NOT(!) is 33  
  uint8_t    port_InitValue[16];              // 1 on 0 off
  uint8_t    port_PortValue[16];              // 1 if active high 0 if active low
  uint8_t    port_OutSize[32];                // unsure of purpose but must be present
  uint16_t   port_OutOffset[32];              // port offset refers to the offset value from the output channels
  uint16_t   port_Threshold[32];              // threshhold value for on/off
  uint16_t   port_Hysteresis[32];             // hysteresis value for on/off
  uint8_t    port_CanId[32];                  // TScanid of the device the output channel is from  

#if defined(CORE_AVR)
  };
#else
  } __attribute__((__packed__)); //The 32 bit systems require all structs to be fully packed
#endif

//Page 3 of the config - This page is NOT SAVED IN NV MEMORY(EEPROM etc)
//this is laid out as first the byte size data then the words

struct config3 {
  uint8_t    aintestData[16];                // 

#if defined(CORE_AVR)
  };
#else
  } __attribute__((__packed__)); //The 32 bit systems require all structs to be fully packed
#endif

 //declare io pins
byte pinOut[33]; //digital outputs array is +1 as pins start at 1 not 0

byte pinIn[33];  //digital inputs

byte pinAin[17]; //analog inputs


// global variables // 
extern struct statuses currentStatus; // 
extern struct config1 configPage1;  
extern struct config2 configPage2;
extern struct config3 configPage3;

#endif // GLOBALS_H                              
