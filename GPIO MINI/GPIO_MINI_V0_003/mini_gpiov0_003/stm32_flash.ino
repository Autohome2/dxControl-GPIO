#if defined (CORE_STM32) && defined (USE_EXT_FLASH)

void init_stm32_flash(uint8_t spiport)
{
  if (spiport == 1)
  {
  // Setup flash to use SPI 1
  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  pinMode(SPI1_NSS_PIN, OUTPUT);
  slaveselectPin =  SPI1_NSS_PIN;
  }
  else if (spiport == 2)
  {
    // Setup flash to use SPI 2
  SPI_2.begin(); //Initialize the SPI_2 port.
  SPI_2.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
  SPI_2.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 
  SPI_2.setClockDivider(SPI_CLOCK_DIV16);  // Use a different speed to SPI 1
  pinMode(SPI2_NSS_PIN, OUTPUT);
  slaveselectPin = SPI2_NSS_PIN;
  }
}
/*
 * print_page_bytes() is a simple helperf function that formats 256
 * bytes of data into an easier to read grid.
 */
void print_page_bytes(byte *page_buffer) {
  char buf[10];
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      sprintf(buf, "%02x", page_buffer[i * 16 + j]);
      Serial1.print(buf);
 }
    Serial1.println();
  }
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
The functions below perform the lowest-level interactions with the flash device.
They match the timing diagrams of the datahsheet. They are called by wrapper 
functions which provide a little more feedback to the user. I made them stand-
alone functions so they can be re-used. Each function corresponds to a flash
instruction opcode.
================================================================================
*/

/*
 * See the timing diagram in section 9.2.35 of the
 * data sheet, "Read JEDEC ID (9Fh)".
 */
void _get_jedec_id(byte *b1, byte *b2, byte *b3) {
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);
  SPI.transfer(WB_JEDEC_ID);
  *b1 = SPI.transfer(0); // manufacturer id
  *b2 = SPI.transfer(0); // memory type
  *b3 = SPI.transfer(0); // capacity
  digitalWrite(slaveselectPin, HIGH);
  not_busy();
}  

/*
 * See the timing diagram in section 9.2.26 of the
 * data sheet, "Chip Erase (C7h / 06h)". (Note:
 * either opcode works.)
 */
void _chip_erase(void) {
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_ENABLE);
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_CHIP_ERASE);
  digitalWrite(slaveselectPin, HIGH);
  /* See notes on rev 2 
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_DISABLE);
  digitalWrite(slaveselectPin, HIGH);
  */
  not_busy();
}

void _chip_erase_sector_4k(uint32_t sector_number) {
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_ENABLE);
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(SECTOR_E);
  SPI.transfer(sector_number>>16);
  SPI.transfer(sector_number>>8);
  SPI.transfer(sector_number);  
  digitalWrite(slaveselectPin, HIGH);
  /* See notes on rev 2 
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_DISABLE);
  digitalWrite(slaveselectPin, HIGH);
  */
  not_busy();
}

/*
 * See the timing diagram in section 9.2.10 of the
 * data sheet, "Read Data (03h)".
 */
void _read_page(word page_number, byte *page_buffer) {
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);
  SPI.transfer(WB_READ_DATA);
  // Construct the 24-bit address from the 16-bit page
  // number and 0x00, since we will read 256 bytes (one
  // page).
  SPI.transfer((page_number >> 8) & 0xFF);
  SPI.transfer((page_number >> 0) & 0xFF);
  SPI.transfer(0);
  for (int i = 0; i < 256; ++i) {
    page_buffer[i] = SPI.transfer(0);
  }
  digitalWrite(slaveselectPin, HIGH);
  not_busy();
}

void _read_byte(word page_number, byte *page_buffer, byte rb_offset) {
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);
  SPI.transfer(WB_READ_DATA);
  // Construct the 24-bit address from the 16-bit page
  // number and 0x00, since we will read 256 bytes (one
  // page).
  SPI.transfer((page_number >> 8) & 0xFF);
  SPI.transfer((page_number >> 0) & 0xFF);
  SPI.transfer(page_number);
  //for (int i = 0; i < 256; ++i) {
    page_buffer[0] = SPI.transfer(rb_offset);
  //}
  digitalWrite(slaveselectPin, HIGH);
  not_busy();
}

uint8_t _read_byte_address(uint32_t addr) {
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);
  SPI.transfer(WB_READ_DATA);
  // Construct the 24-bit address from the 16-bit page
  // number and 0x00, since we will read 256 bytes (one
  // page).
  SPI.transfer(addr >> 16);
  SPI.transfer(addr >> 8);
  SPI.transfer(addr);
  uint8_t rba_result = SPI.transfer(0);
  digitalWrite(slaveselectPin, HIGH);
  not_busy();
  return rba_result;
}
 
/*
 * See the timing diagram in section 9.2.21 of the
 * data sheet, "Page Program (02h)".
 */
void _write_page(word page_number, byte *page_buffer)
{
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_ENABLE);
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_PAGE_PROGRAM);
  SPI.transfer((page_number >>  8) & 0xFF);
  SPI.transfer((page_number >>  0) & 0xFF);
  SPI.transfer(0);
  for (int i = 0; i < 256; ++i) {
    SPI.transfer(page_buffer[i]);
  }
  digitalWrite(slaveselectPin, HIGH);
  /* See notes on rev 2
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_DISABLE);
  digitalWrite(slaveselectPin, HIGH);
  */
  not_busy();
}

void _write_byte_address(uint32_t addr, uint8_t databyte)
{
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_ENABLE);
  digitalWrite(slaveselectPin, HIGH);
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_PAGE_PROGRAM);
  SPI.transfer(addr >> 16);
  SPI.transfer(addr >> 8);
  SPI.transfer(addr);
  SPI.transfer(databyte);
  digitalWrite(slaveselectPin, HIGH);
  /* See notes on rev 2
  digitalWrite(slaveselectPin, LOW);  
  SPI.transfer(WB_WRITE_DISABLE);
  digitalWrite(slaveselectPin, HIGH);
  */
  currentStatus.dev1 = databyte;
  not_busy();
}


/* 
 * not_busy() polls the status bit of the device until it
 * completes the current operation. Most operations finish
 * in a few hundred microseconds or less, but chip erase 
 * may take 500+ms. Finish all operations with this poll.
 *
 * See section 9.2.8 of the datasheet
 */
void not_busy(void) {
  digitalWrite(slaveselectPin, HIGH);  
  digitalWrite(slaveselectPin, LOW);
  SPI.transfer(WB_READ_STATUS_REG_1);       
  while (SPI.transfer(0) & 1) {}; 
  digitalWrite(slaveselectPin, HIGH);  
}

/*
================================================================================
User Interface Routines
The functions below map to user commands. They wrap the low-level calls with 
print/debug statements for readability.
================================================================================
*/

/* 
 * The JEDEC ID is fairly generic, I use this function to verify the setup
 * is working properly.
 */
void get_jedec_id(void) {
  Serial1.println("command: get_jedec_id");
  byte b1, b2, b3;
  _get_jedec_id(&b1, &b2, &b3);
  char buf[128];
  sprintf(buf, "Manufacturer ID: %02xh\nMemory Type: %02xh\nCapacity: %02xh",
    b1, b2, b3);
  Serial1.println(buf);
  Serial1.println("Ready");
} 

void chip_erase(void)
{
  Serial1.println("command: chip_erase");
  _chip_erase();
  Serial1.println("Ready");
}

void chip_erase_sector_4k(unsigned int sector_number)
{
  Serial1.println("command: chip_erase_sector");
  _chip_erase_sector_4k(sector_number);
  Serial1.println("Ready");
}

void read_page(unsigned int page_number)
{
  char buf[80];
  sprintf(buf, "command: read_page(%04xh)", page_number);
  Serial1.println(buf);
  byte page_buffer[256];
  _read_page(page_number, page_buffer);
  print_page_bytes(page_buffer);
  Serial1.println("Ready");
}

void read_byte(unsigned int page_number, byte offset )
{
  char buf[80];
  //sprintf(buf, "command: read_page(%04xh)", page_number);
  sprintf(buf, "command: read_byte(%04xh, %04xh)", page_number, offset);
  Serial1.println(buf);
  byte page_buffer[256];
  _read_byte(page_number, page_buffer, offset);
  print_single_byte(page_buffer,offset);
  Serial1.println("Ready");
}

void read_byte_address(uint32_t addr )
{
  char buf[80];
  sprintf(buf, "command: read_byte(%04xh)", addr);
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
  byte page_buffer[256];
  for (int i = 0; i < 4096; ++i)
      {
        _read_page(i, page_buffer);
        print_page_bytes(page_buffer);
      }
  Serial1.println("Ready");
}

void write_byte(word page, byte offset, byte databyte)
{
  char buf[80];
  sprintf(buf, "command: write_byte(%04xh, %04xh, %02xh)", page, offset, databyte);
  Serial1.println(buf);
  byte page_data[256];
  _read_page(page, page_data);
  page_data[offset] = databyte;
  _write_page(page, page_data);
  Serial1.println("Ready");
}

void write_byte_address(uint32_t addr, uint8_t databyte)
{
  char buf[80];
  sprintf(buf, "command: read_byte(%04xh)", addr);
  Serial1.println(buf);
  _write_byte_address(addr,databyte);
  Serial1.println("Ready");
}
#endif
