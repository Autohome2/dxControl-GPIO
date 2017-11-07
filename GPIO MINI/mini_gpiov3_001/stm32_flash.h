#ifndef STM32_FLASH_H
#define STM32_FLASH_H

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
#define WB_CHIP_ERASE         0xc7
#define WB_READ_STATUS_REG_1  0x05
#define WB_READ_DATA          0x03
#define WB_PAGE_PROGRAM       0x02
#define WB_JEDEC_ID           0x9f
#define BLK_E_64K  0xD8  //block erase 64KB
#define BLK_E_32K 0x52  //block erase 32KB
#define SECTOR_E  0x20  //sector erase 4KB

byte slaveselectPin ;

void init_stm32_flash(uint8_t spiport);

void print_page_bytes(byte *page_buffer);
void print_single_byte(byte *page_buffer, byte bytenum);

//Low-Level Device Routines
void _get_jedec_id(byte *b1, byte *b2, byte *b3);
void _chip_erase(void);
void _chip_erase_sector_4k(uint32_t sector_number);
void _read_flash_page(word page_number, byte *page_buffer);
void _read_flash_byte(word page_number, byte *page_buffer, byte rb_offset);
uint8_t _read_flash_byte_address(uint32_t addr);
void _write_flash_page(word page_number, byte *page_buffer);
void _write_flash_byte_address(uint32_t addr, uint8_t databyte);
void not_busy(void);

//User Interface Routines
void get_jedec_id(void);
void chip_erase(void);
void chip_erase_sector_4k(unsigned int sector_number);
void read_flash_page(unsigned int page_number);
void read_flash_byte(unsigned int page_number, byte offset );
void read_flash_byte_address(uint32_t addr);
void read_flash_all_pages(void);
void write_flash_byte(word page, byte offset, byte databyte);
void write_flash_byte_address(uint32_t addr, uint8_t databyte);
#endif

