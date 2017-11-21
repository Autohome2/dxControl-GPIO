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
      #define LED_BUILTIN PC13
      //only choose one of the following two defines , comment out the unused ones
   // #define USE_EXT_FLASH
      #define USE_EXT_EEPROM
  //  #define USE_EXT_FRAM
  
      #define EXT_FLASH_SIZE 8192
      #define FLASH_OFFSET  EXT_FLASH_SIZE / 2

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

//Define masks for CanStatus
#define BIT_CANSTATUS_CAN0ACTIVATED         0  //can0 has enabled
#define BIT_CANSTATUS_CAN0FAILED            1  //can0 failed to configure
#define BIT_CANSTATUS_CAN1ACTIVATED         2  //can1 has enabled
#define BIT_CANSTATUS_CAN1FAILED            3  //can1 failed o configure
#define BIT_CANSTATUS_CAN0MSGFAIL           4 //
#define BIT_CANSTATUS_CAN1MSGFAIL           5  //
#define BIT_CANSTATUS_7                     6       //
#define BIT_CANSTATUS_8                     7  //

//define maskes for generalConfig1
#define USE_REALTIME_BROADCAST              0
//#define unused1_7b                          1

#define maincommand  'r'    // the command to send to the Speeduino
#define commandletterr  'r'
uint8_t tsCanId = 0;          // this is the tunerstudio canID for the device you are requesting data from , this is 0 for the main ecu in the system which is usually the speeduino ecu . 
                              // this value is set in Tunerstudio when configuring your Speeduino
//uint16_t realtime_offset = 4;  // the offset of the realtime data to start reading from
//uint16_t realtime_bytes = 1;   // the number of bytes requested

const unsigned char GPIO_signature[]    = "speeduino_mini_GPIOV3.003 201711"; //this must match the ini
const unsigned char GPIO_RevNum[] = "speeduino 201711-mini GPIO V3.003";      //this is what is displayed in the TS header bar

uint8_t thistsCanId = 4;    // this is the tunerstudio canId of this device

const uint8_t data_structure_version = 2; //This identifies the data structure when reading / writing.
const uint8_t page_1_size = 128;
const uint16_t page_2_size = 256;
const uint16_t page_3_size = 256;
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
  volatile byte canstatus;    //canstatus bitfield
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
  volatile uint8_t EXinchanloop = 0; 
  
  volatile uint16_t dev1;          //developer use only
  volatile uint16_t dev2;          //developer use only
  volatile uint16_t dev3;          //developer use only
  volatile uint16_t dev4;          //developer use only
};
//struct statuses currentStatus; //The global status object

//Page 1 of the config - See the ini file for further reference
//this is laid out as first the byte size data then the words

struct config1 {
uint16_t master_controller_address:11 ;
uint8_t pinLayout;
uint8_t speeduinoConnection ;//:2;       //type of connection to speedy , 0==none 1 == serial3 2 == canbus
uint16_t speeduinoBaseCan ;//:11;       //speeduino base can address
uint8_t canModuleConfig;                //bit flags for canmodule configuration
uint8_t generalConfig1;
uint8_t unused8;
uint8_t unused9;
uint16_t DoutchanActive;          // digital outputchannels 1-16 active flags
uint16_t DoutchanActive_2;        // digital output channels 17-32 active flags
uint16_t DinchanActive;           // digital input channels 1-16 active flags
uint16_t DinchanActive_2;         // digital input channels 17-32 active flags
uint16_t AinchanActive;           // analog input channels 1-16 active flags
uint16_t AinchanActive_2;         // analog  input channels 17-32 active flags
uint16_t exinsel;                 // External input channel enabled bit flags
uint16_t INdata_from_Can[16];     // can address of source of data 0x100(256dec) to 0x7FF(2047dec) as 0 dec - 535 dec
uint8_t data_from_offset[16];        // offset of data source 0 - 255
uint8_t num_bytes[16];               // number of bytes length of data source 0,1,or 2
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
#if defined(CORE_AVR)
  };
#else
  } __attribute__((__packed__)); //The 32 bi systems require all structs to be fully packed
#endif

//};

//Page 2 of the config - See the ini file for further reference
//this is laid out as first the byte size data then the words

struct config2 {
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
#if defined(CORE_AVR)
  };
#else
  } __attribute__((__packed__)); //The 32 bit systems require all structs to be fully packed
#endif
//};

//Page 3 of the config - See the ini file for further reference
//this is laid out as first the byte size data then the words

struct config3 {
uint8_t canbroadcast_out;  
uint16_t canbroadcast_sel;
uint16_t canbroadcast_source_can_address[16];
uint16_t canbroadcast_chan_offset[16];
uint8_t canbroadcast_chan_size[16];
uint8_t canbroadcast_chan_canid[16];
//byte unused3_53;
//byte unused3_54;
//byte unused3_55;
//byte unused3_56;
//byte unused3_57;
//byte unused3_58;
//byte unused3_59;
//byte unused3_60;
//byte unused3_61;
//byte unused3_62;
//byte unused3_63;
//byte unused3_64;
//byte unused3_65;
//byte unused3_66;
//byte unused3_67;
//byte unused3_68;
//byte unused3_69;
//byte unused3_70;
//byte unused3_71;
//byte unused3_72;
//byte unused3_73;
//byte unused3_74;
//byte unused3_75;
//byte unused3_76;
//byte unused3_77;
//byte unused3_78;
//byte unused3_79;
//byte unused3_80;
//byte unused3_81;
//byte unused3_82;
//byte unused3_83;
//byte unused3_84;
//byte unused3_85;
//byte unused3_86;
//byte unused3_87;
//byte unused3_88;
//byte unused3_89;
//byte unused3_90;
//byte unused3_91;
//byte unused3_92;
//byte unused3_93;
//byte unused3_94;
//byte unused3_95;
//byte unused3_96;
//byte unused3_97;
//byte unused3_98;
byte unused3_99 = 99;
byte unused3_100;
byte unused3_101;
byte unused3_102;
byte unused3_103;
byte unused3_104;
byte unused3_105 = 105;
byte unused3_106;
byte unused3_107;
byte unused3_108;
byte unused3_109;
byte unused3_110;
byte unused3_111;
byte unused3_112;
byte unused3_113;
byte unused3_114;
byte unused3_115;
byte unused3_116;
byte unused3_117;
byte unused3_118;
byte unused3_119;
byte unused3_120 = 200;
byte unused3_121;
byte unused3_122;
byte unused3_123;
byte unused3_124;
byte unused3_125;
byte unused3_126 = 226;
byte unused3_127 = 227;
byte unused3_128;
byte unused3_129;
byte unused3_130 = 200;
byte unused3_131;
byte unused3_132;
byte unused3_133;
byte unused3_134;
byte unused3_135;
byte unused3_136 = 236;
byte unused3_137 = 237;
byte unused3_138;
byte unused3_139;
byte unused3_140;
byte unused3_141;
byte unused3_142;
byte unused3_143;
byte unused3_144;
byte unused3_145;
byte unused3_146;
byte unused3_147;
byte unused3_148;
byte unused3_149;
byte unused3_150;
byte unused3_151;
byte unused3_152;
byte unused3_153;
byte unused3_154;
byte unused3_155;
byte unused3_156;
byte unused3_157;
byte unused3_158;
byte unused3_159;
byte unused3_160;
byte unused3_161;
byte unused3_162;
byte unused3_163;
byte unused3_164;
byte unused3_165;
byte unused3_166;
byte unused3_167;
byte unused3_168;
byte unused3_169;
byte unused3_170;
byte unused3_171;
byte unused3_172;
byte unused3_173;
byte unused3_174;
byte unused3_175;
byte unused3_176;
byte unused3_177;
byte unused3_178;
byte unused3_179;
byte unused3_180;
byte unused3_181;
byte unused3_182;
byte unused3_183;
byte unused3_184;
byte unused3_185;
byte unused3_186;
byte unused3_187;
byte unused3_188;
byte unused3_189;
byte unused3_190;
byte unused3_191;
byte unused3_192;
byte unused3_193;
byte unused3_194;
byte unused3_195;
byte unused3_196;
byte unused3_197;
byte unused3_198;
byte unused3_199;
byte unused3_200 = 200;
byte unused3_201;
byte unused3_202;
byte unused3_203;
byte unused3_204;
byte unused3_205;
byte unused3_206 = 206;
byte unused3_207 = 207;  
byte unused3_208;
byte unused3_209;
byte unused3_210;
byte unused3_211;
byte unused3_212;
byte unused3_213;
byte unused3_214;
byte unused3_215;
byte unused3_216;
byte unused3_217;
byte unused3_218;
byte unused3_219;
byte unused3_220;
byte unused3_221;
byte unused3_222;
byte unused3_223;
byte unused3_224;
byte unused3_225;
byte unused3_226;
byte unused3_227;
byte unused3_228;
byte unused3_229;
byte unused3_230;
byte unused3_231;
byte unused3_232;
byte unused3_233;
byte unused3_234;
byte unused3_235;
byte unused3_236;
byte unused3_237;
byte unused3_238;
byte unused3_239;
byte unused3_240;
byte unused3_241;
byte unused3_242;
byte unused3_243;
byte unused3_244;
byte unused3_245;
byte unused3_246;
byte unused3_247;
byte unused3_248;
byte unused3_249;
byte unused3_250;
byte unused3_251;
byte unused3_252;
byte unused3_253; 
byte unused3_254;
byte unused3_255; 

#if defined(CORE_AVR)
  };
#else
  } __attribute__((__packed__)); //The 32 bit systems require all structs to be fully packed
#endif
  
 //declare io pins
byte pinOut[17]; //digital outputs array is +1 as pins start at 1 not 0

byte pinIn[17];  //digital inputs

byte pinAin[17]; //analog inputs


// global variables // from passthrough_example.ino
extern struct statuses currentStatus; // from passthrough.ino
extern struct config1 configPage1;  
extern struct config2 configPage2;
extern struct config3 configPage3;

//extern unsigned long currentLoopTime; //The time the current loop started (uS)
//extern unsigned long previousLoopTime; //The time the previous loop started (uS)

#endif // GLOBALS_H                              
