//#define TRANSMITTER

#include <stdint.h>
#include "cc112x_spi.h"

rfStatus_t current;

uint8_t txBuffer;
uint8_t rxBuffer;

void initSPI(void) {

}

void main(void)
{
  initSPI();
  
  trxSpiCmdStrobe(CC112X_SRES);

  //__delay_cycles(16000000);

  registerConfig();

  manualCalibration();

  //__delay_cycles(32000000);
  
#ifdef TRANSMITTER
    trxSpiCmdStrobe(CC112X_SIDLE);
    trxSpiCmdStrobe(CC112X_SFTX);
    trxSpiCmdStrobe(CC112X_SFSTXON);
    while (1) {
      txBuffer = 0xAB;
      current = cc112xSpiWriteTxFifo(&txBuffer,1);
      if ((current & 0x70) == 0x70) {
//        trxSpiCmdStrobe(CC112X_SIDLE);
        trxSpiCmdStrobe(CC112X_SFTX);
        trxSpiCmdStrobe(CC112X_SFSTXON);
      } else {
        unsigned char numBytes = 0;
        cc112xSpiReadReg(CC112X_NUM_TXBYTES, &numBytes, 1);
        if (numBytes == FIFOLEN) {
          current = trxSpiCmdStrobe(CC112X_STX);
        }
      }
    }
#else
    unsigned char numBytes = 0;
    trxSpiCmdStrobe(CC112X_SIDLE);
    trxSpiCmdStrobe(CC112X_SFRX);
    trxSpiCmdStrobe(CC112X_SRX);
    while (1) {
      current = cc112xSpiReadReg(CC112X_NUM_RXBYTES, &numBytes, 1);
      if ((current & 0x70) == 0x60) {
//        trxSpiCmdStrobe(CC112X_SIDLE);
        trxSpiCmdStrobe(CC112X_SFRX);
        trxSpiCmdStrobe(CC112X_SRX);
      }
      if (numBytes != 0) {
        cc112xSpiReadRxFifo(&rxBuffer,1);
      }
    }

#endif
}
