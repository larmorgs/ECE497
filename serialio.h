#include <stdint.h>

#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004
#define BIT3 0x0008
#define BIT4 0x0010
#define BIT5 0x0020
#define BIT6 0x0040
#define BIT7 0x0080
#define BIT8 0x0100
#define BIT9 0x0200
#define BITA 0x0400
#define BITB 0x0800
#define BITC 0x1000
#define BITD 0x2000
#define BITE 0x4000
#define BITF 0x8000

#define HEAD_LENGTH 3
#define ADDRESS_LENGTH 7

#define READ_LENGTH 4
#define WRITE_LENGTH READ_LENGTH
#define READ_WRITE_LENGTH (READ_LENGTH + WRITE_LENGTH)
#define COMMAND_LENGTH 9

#define READ 0b110
#define WRITE 0b101
#define READ_WRITE 0b101
#define COMMAND 0b100

int shiftOut8(uint8_t data, uint8_t len);
int shiftOut16(uint16_t data, uint8_t len);
uint8_t shiftIn8(uint8_t len);
uint16_t shiftIn16(uint8_t len);
uint8_t readSingle(uint8_t address);
void readBurst(uint8_t address, uint8_t* dataIn, uint16_t length);
void writeSingle(uint8_t address, uint8_t dataOut);
void writeBurst(uint8_t address, uint8_t* dataOut, uint16_t length);
uint8_t readModWriteSingle(uint8_t address, uint8_t dataOut);
void readModWriteBurst(uint8_t address, uint8_t* dataIn, uint8_t* dataOut, uint16_t length);
void writeCommandSingle(uint16_t command);
void writeCommandBurst(uint16_t* commands, uint16_t length);
