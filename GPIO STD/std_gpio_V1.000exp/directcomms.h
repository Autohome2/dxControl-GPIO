#ifndef DIRECTCOMMS_H
#define DIRECTCOMMS_H

//These are the page numbers that the Tuner Studio serial protocol uses to transverse the different map and config pages.

#define simple_remote_setupPage    1 //Config Page 1
#define port_editor_config         2 // port editor config page
#define canbus_config              3 // canbus configuration page
#define remotecanio_config         4 // canbus remote input and output page

byte direct_packetSize = 86;
volatile byte fullStatus[86];//[direct_packetSize];

unsigned long direct_requestCount = 0; //The number of times the A command has been issued

void direct_serial_command();
void dodirect_rCommands(uint8_t commandletter, uint8_t canid, uint16_t theoffset, uint16_t thelength);
void direct_receiveValue(uint16_t rvOffset, uint8_t newValue);
void direct_sendPage(uint16_t send_page_offset,uint16_t send_page_Length, byte can_id, byte cmd);
void direct_read_realtime();
void direct_sendValues(uint16_t offset, uint16_t packetLength, byte cmd);
void commandButtons(uint16_t cmdCombined);

#endif // DIRECTCOMMS_H
