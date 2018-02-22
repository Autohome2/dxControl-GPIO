#if defined (USE_EXT_EEPROM)

//defined (CORE_STM32)&& 

#include "ext_eeprom.h"

void init_stm32_ext_eeprom(uint8_t spiport)
{
  if (spiport == 1)
  {
  // Setup fext eeprom to use SPI 1
  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV8);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  pinMode(SPI1_NSS_PIN, OUTPUT);
  slaveselectPin =  SPI1_NSS_PIN;
  }
  else if (spiport == 2)
  {
    // Setup ext_eeprom to use SPI 2
//  SPI_2.begin(); //Initialize the SPI_2 port.
//  SPI_2.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
//  SPI_2.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 
//  SPI_2.setClockDivider(SPI_CLOCK_DIV8);  // Use a different speed to SPI 1
//  pinMode(SPI2_NSS_PIN, OUTPUT);
//  slaveselectPin = SPI2_NSS_PIN;
  }
}

void init_sam_ext_eeprom(uint8_t spiport)
{
  if (spiport == 1)
  {
  //const int dataReadyPin = 6;
  //const int chipSelectPin = 7;  
  
  // Setup fext eeprom to use SPI 1
  SPI.begin(); //Initialize the SPI_1 port.
  
  //SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  //SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  //SPI.setClockDivider(SPI_CLOCK_DIV8);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  //pinMode(SPI1_NSS_PIN, OUTPUT);
  //slaveselectPin =  SPI1_NSS_PIN;
  
    // initalize the  data ready and chip select pins:
  //pinMode(dataReadyPin, INPUT);
  //pinMode(chipSelectPin, OUTPUT);
  
  }
}
/*
 * print_page_bytes() is a simple helperf function that formats 256
 * bytes of data into an easier to read grid.
 */
void print_page_bytes(uint16_t *page_buffer,uint16_t dataleng) {
  char buf[10];
  for (int i = 0; i < dataleng; ++i) {
      sprintf(buf, "%02x", page_buffer[i]);
      Serial1.print(buf);
  }
      Serial1.println();
}

void print_single_byte(byte *page_buffer, byte bytenum)
{
  char buf[10];
      sprintf(buf, "%02x", page_buffer[bytenum]);
      Serial1.print(buf);
      Serial1.println();
}

/*
================================================================================
Low-Level Device Routines
The functions below perform the lowest-level interactions with the eeprom device.
They match the timing diagrams of the datahsheet. They are called by wrapper 
functions which provide a little more feedback to the user. I made them stand-
alone functions so they can be re-used. Each function corresponds to a eeprom
instruction opcode.
================================================================================
*/

void _read_bytes_address(uint16_t addr, uint16_t dataleng, uint16_t *page_buffer) {
  //digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);
  SPI.transfer(READ_MEM_ARRAY);
  //SPI.transfer16(addr);
  SPI.transfer(highByte(addr));
  SPI.transfer(lowByte(addr));
  for (uint16_t i = 0; i < dataleng; ++i) {
    page_buffer[i] = SPI.transfer(0);
  }
  digitalWrite(slaveselectPin, HIGH);
  _not_busy();
}

uint8_t _read_byte_address(uint16_t addr) {
//  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);
  SPI.transfer(READ_MEM_ARRAY);
  SPI.transfer(highByte(addr));
  SPI.transfer(lowByte(addr));
  uint8_t result = SPI.transfer(0); 
  digitalWrite(slaveselectPin, HIGH);
  _not_busy();
  return result;
}

void _write_byte_address(uint16_t addr, uint8_t databyte)
{
  if ((_check_status()&0) != 1)
    {
//  digitalWrite(slaveselectPin, HIGH);
    digitalWrite(slaveselectPin, LOW);  
    SPI.transfer(WB_WRITE_ENABLE);
    //interal wait state
    digitalWrite(slaveselectPin, HIGH);
    //end of enable section
    digitalWrite(slaveselectPin, LOW);  
    SPI.transfer(WRITE_MEM_ARRAY);
    SPI.transfer(highByte(addr));
    SPI.transfer(lowByte(addr));
    SPI.transfer(databyte);
    digitalWrite(slaveselectPin, HIGH);
    //end of write section
    digitalWrite(slaveselectPin, LOW);  
    SPI.transfer(WB_WRITE_DISABLE);
    digitalWrite(slaveselectPin, HIGH);
    //end of write disable section
    _not_busy();
    }
}


/* 
 * not_busy() polls the status bit of the device until it
 * completes the current operation. Most operations finish
 * in a few hundred microseconds or less, but chip erase 
 * may take 500+ms. Finish all operations with this poll.
 *
 * See section 9.2.8 of the datasheet
 */
void _not_busy(void) {
  //digitalWrite(slaveselectPin, HIGH);  
  digitalWrite(slaveselectPin, LOW);
  //SPI.transfer(READ_STATUS_REG);       
  while (SPI.transfer(READ_STATUS_REG) & 0) {}; 
  digitalWrite(slaveselectPin, HIGH);  
}

uint8_t _check_status(void) {
  //digitalWrite(slaveselectPin, HIGH);  
  digitalWrite(slaveselectPin, LOW);       
  uint8_t bitcheck = SPI.transfer(READ_STATUS_REG) ; 
  digitalWrite(slaveselectPin, HIGH);  
  return bitcheck;
}


uint8_t _read_status_register()
{
  digitalWrite(slaveselectPin, LOW);       
  uint8_t result = SPI.transfer(READ_STATUS_REG); 
  digitalWrite(slaveselectPin, HIGH);  
  return result;
}

void _write_status_register(uint8_t databyte)
{
  digitalWrite(slaveselectPin, LOW);       
  SPI.transfer(WRITE_STATUS_REG); 
  SPI.transfer(databyte);
  digitalWrite(slaveselectPin, HIGH);  
}
/*
================================================================================
User Interface Routines
The functions below map to user commands. They wrap the low-level calls with 
print/debug statements for readability.
================================================================================
*/

void read_bytes_address(uint16_t addr, uint16_t dataleng)
{
  char buf[80];
  sprintf(buf, "command: read_bytes(%04xh)", dataleng);
  Serial1.println(buf);
  uint16_t page_buffer[256];
  _read_bytes_address(addr,dataleng, page_buffer);
  print_page_bytes(page_buffer,dataleng);
  Serial1.println("Ready");
}

void read_byte_address(uint16_t addr )
{
  char buf[80];
  sprintf(buf, "command: read_byte(%03xh)", addr);
  Serial1.println(buf);
  //byte page_buffer[256];
  uint8_t result;
  result = _read_byte_address(addr);
  char buf2[10];
      sprintf(buf2, "%02x", result);
      Serial1.print(buf2);
      Serial1.println();
  Serial1.println("Ready");
}

void read_all_pages(void)
{
  Serial1.println("command: read_all_pages");
//  byte page_buffer[256];
  for (int i = 0; i < 4096; ++i)
      {
 //       _read_page(i, page_buffer);
//        print_page_bytes(page_buffer);
      }
  Serial1.println("Ready");
}

void write_byte_address(uint16_t addr, uint8_t databyte)
{
  char buf[80];
  sprintf(buf, "command: write_byte(%02xh)", addr, databyte);
  Serial1.println(buf);
  _write_byte_address(addr,databyte);
  Serial1.println("Ready");
}
#endif
