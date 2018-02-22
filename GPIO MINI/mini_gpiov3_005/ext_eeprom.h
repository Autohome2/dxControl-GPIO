#ifndef EXT_EEPROM_H
#define EXT_EEPROM_H

/*
    Using the first SPI port (SPI_1)
    SS    <-->  PA4 <-->  BOARD_SPI1_NSS_PIN
    SCK   <-->  PA5 <-->  BOARD_SPI1_SCK_PIN
    MISO  <-->  PA6 <-->  BOARD_SPI1_MISO_PIN
    MOSI  <-->  PA7 <-->  BOARD_SPI1_MOSI_PIN

    Using the second SPI port (SPI_2)
    SS    <-->  PB12 <-->  BOARD_SPI2_NSS_PIN
    SCK   <-->  PB13 <-->  BOARD_SPI2_SCK_PIN
    MISO  <-->  PB14 <-->  BOARD_SPI2_MISO_PIN
    MOSI  <-->  PB15 <-->  BOARD_SPI2_MOSI_PIN
*/


#define SPI1_NSS_PIN PA4    //SPI_1 Chip Select pin is PA4. You can change it to the STM32 pin you want.
#define SPI2_NSS_PIN PB12   //SPI_2 Chip Select pin is PB12. You can change it to the STM32 pin you want.

// WinBond flash commands
#define WB_WRITE_ENABLE       0x06
#define WB_WRITE_DISABLE      0x04
#define READ_STATUS_REG       0x05 
#define WRITE_STATUS_REG      0x01
#define READ_MEM_ARRAY        0x03
#define WRITE_MEM_ARRAY       0x02
#define READ_ID_PAGE          0x83
#define WRITE_ID_PAGE         0x82

byte slaveselectPin ;

void init_stm32_ext_eeprom(uint8_t spiport);
void init_sam_ext_eeprom(uint8_t spiport);

void print_page_bytes(uint16_t *page_buffer,uint16_t dataleng);
void print_single_byte(byte *page_buffer, byte bytenum);

//Low-Level Device Routines
//void _read_page(word page_number, byte *page_buffer);
void _read_bytes_address(uint16_t addr, uint16_t dataleng, uint16_t *page_buffer);
uint8_t _read_byte_address(uint16_t addr);
//void _write_page(word page_number, byte *page_buffer);
void _write_byte_address(uint16_t addr, uint8_t databyte);
void _not_busy(void);
uint8_t _check_status(void); 
uint8_t _read_status_register();
void _write_status_register();

//User Interface Routines
//void read_page(unsigned int page_number);
void read_bytes_address(uint16_t addr, uint16_t dataleng);
void read_byte_address(uint16_t addr);
void read_all_pages(void);
//void write_byte(word page, byte offset, byte databyte);
void write_byte_address(uint16_t addr, uint16_t databyte);
#endif

