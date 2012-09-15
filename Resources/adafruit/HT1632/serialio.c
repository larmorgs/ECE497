#include "serialio.h"

uint8_t cs = 0;
uint8_t wr = 0;
uint8_t rd = 0;
uint8_t da = 0;

int main() {
  return 0;
}

int shiftOut8(uint8_t data, uint8_t len) {
  uint8_t mask;
  switch (len) {
    case 0: return 0;
    case 1:
      mask = BIT0;
      break;
    case 2:
      mask = BIT1;
      break;
    case 3:
      mask = BIT2;
      break;
    case 4:
      mask = BIT3;
      break;
    case 5:
      mask = BIT4;
      break;
    case 6:
      mask = BIT5;
      break;
    case 7:
      mask = BIT6;
      break;
    case 8:
      mask = BIT7;
      break;
    default:
      return 1;
      break;
  }
  uint8_t i;
  for (i = 1; i < len; i++) {
    wr = 0;
    da = (data & mask) ? 1 : 0;
    wr = 1;
    data <<= 1;
  }
  wr = 0;
  da = (data & mask) ? 1 : 0;
  wr = 1;
  return 0;
}

int shiftOut16(uint16_t data, uint8_t len) {
  uint16_t mask;
  switch (len) {
    case 0: return 0;
    case 1:
      mask = BIT0;
      break;
    case 2:
      mask = BIT1;
      break;
    case 3:
      mask = BIT2;
      break;
    case 4:
      mask = BIT3;
      break;
    case 5:
      mask = BIT4;
      break;
    case 6:
      mask = BIT5;
      break;
    case 7:
      mask = BIT6;
      break;
    case 8:
      mask = BIT7;
      break;
    case 9:
      mask = BIT8;
      break;
    case 10:
      mask = BIT9;
      break;
    case 11:
      mask = BITA;
      break;
    case 12:
      mask = BITB;
      break;
    case 13:
      mask = BITC;
      break;
    case 14:
      mask = BITD;
      break;
    case 15:
      mask = BITE;
      break;
    case 16:
      mask = BITF;
      break;
    default:
      return 1;
      break;
  }
  uint8_t i;
  for (i = 1; i < len; i++) {
    wr = 0;
    da = ((data & mask) != 0) ? 1 : 0;
    wr = 1;
    data <<= 1;
  }
  wr = 0;
  da = ((data & mask) != 0) ? 1 : 0;
  wr = 1;
  return 0;
}

uint8_t shiftIn8(uint8_t len) {
  uint8_t dataIn = 0;
  uint8_t i;
  rd = 0;
  dataIn += da;
  rd = 1;
  for (i = 1; i < len; i++) {
    dataIn <<= 1;
    rd = 0;
    dataIn += da;
    rd = 1;
  }
  return 0;
}

uint16_t shiftIn16(uint8_t len) {
  uint16_t dataIn = 0;
  uint8_t i;
  rd = 0;
  dataIn += da;
  rd = 1;
  for (i = 1; i < len; i++) {
    dataIn <<= 1;
    rd = 0;
    dataIn += da;
    rd = 1;
  }
  return 0;
}

uint8_t readSingle(uint8_t address) {
  shiftOut8(READ, HEAD_LENGTH);
  shiftOut8(address, ADDRESS_LENGTH);
  return shiftIn8(READ_LENGTH);
}

void readBurst(uint8_t address, uint8_t* dataIn, uint16_t length) {
  uint8_t i;
  shiftOut8(READ, HEAD_LENGTH);
  shiftOut8(address, ADDRESS_LENGTH);
  for (i = 0; i < length; i++) {
    dataIn[i] = shiftIn8(READ_LENGTH);
  }
}

void writeSingle(uint8_t address, uint8_t dataOut) {
  shiftOut8(WRITE, HEAD_LENGTH);
  shiftOut8(address, ADDRESS_LENGTH);
  shiftOut8(dataOut, WRITE_LENGTH);
}

void writeBurst(uint8_t address, uint8_t* dataOut, uint16_t length) {
  uint8_t i;
  shiftOut8(WRITE, HEAD_LENGTH);
  shiftOut8(address, ADDRESS_LENGTH);
  for (i = 0; i < length; i++) {
    shiftOut8(dataOut[i], WRITE_LENGTH);
  }
}

uint8_t readModWriteSingle(uint8_t address, uint8_t dataOut) {
  uint8_t dataIn = 0;
  shiftOut8(READ_WRITE, HEAD_LENGTH);
  shiftOut8(address, ADDRESS_LENGTH);
  dataIn = shiftIn8(READ_LENGTH);
  shiftOut8(dataOut, WRITE_LENGTH);
  return dataIn;
}

void readModWriteBurst(uint8_t address, uint8_t* dataIn, uint8_t* dataOut, uint16_t length) {
  uint8_t i;
  shiftOut8(READ_WRITE, HEAD_LENGTH);
  shiftOut8(address, ADDRESS_LENGTH);
  for (i = 0; i < length; i++) {
    dataIn[i] = shiftIn8(READ_LENGTH);
    shiftOut8(dataOut[i], WRITE_LENGTH);
  }
}

void writeCommandSingle(uint16_t command) {
  shiftOut8(COMMAND, HEAD_LENGTH);
  shiftOut16(command, COMMAND_LENGTH);
}

void writeCommandBurst(uint16_t* commands, uint16_t length) {
  uint8_t i;
  shiftOut8(COMMAND, HEAD_LENGTH);
  for (i = 0; i < length; i++) {
    shiftOut16(commands[i], COMMAND_LENGTH);
  }
}
