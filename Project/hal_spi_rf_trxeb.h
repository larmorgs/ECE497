/******************************************************************************
    Filename: hal_spi_rf_trxeb.h

    Description: Common header file for spi access to the different tranceiver
                 radios. Supports CC1101/CC112X radios

*******************************************************************************/

#ifndef HAL_SPI_RF_TRXEB_H
#define HAL_SPI_RF_TRXEB_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * INCLUDES
 */
#include <stdint.h>

/******************************************************************************
 * CONSTANTS
 */


#define RADIO_BURST_ACCESS   0x40
#define RADIO_SINGLE_ACCESS  0x00
#define RADIO_READ_ACCESS    0x80
#define RADIO_WRITE_ACCESS   0x00


/* Bit fields in the chip status byte */
#define STATUS_CHIP_RDYn_BM             0x80
#define STATUS_STATE_BM                 0x70
#define STATUS_FIFO_BYTES_AVAILABLE_BM  0x0F


/******************************************************************************
 * MACROS
 */

/* Macros for Tranceivers(TRX) */
#define TRXEM_SPI_BEGIN()              0//st( P2OUT &= ~BIT0; __no_operation(); )
#define TRXEM_SPI_TX(x)                0//st( UC0IFG &= ~UCA0RXIFG;UCA0TXBUF= (x); )
#define TRXEM_SPI_WAIT_DONE()          0//st( while(!(UC0IFG & UCA0RXIFG)); )
#define TRXEM_SPI_RX()                 0//UCA0RXBUF
#define TRXEM_SPI_END()                0//st( __no_operation(); P2OUT |= BIT0; )

/******************************************************************************
 * TYPEDEFS
 */

typedef struct
{
  uint16_t  addr;
  uint8_t   data;
}registerSetting_t;

typedef uint8_t rfStatus_t;

/******************************************************************************
 * PROTOTYPES
 */

void trxRfSpiInterfaceInit(void);
rfStatus_t trx8BitRegAccess(uint8_t accessType, uint8_t addrByte, uint8_t *pData, uint16_t len);
rfStatus_t trxSpiCmdStrobe(uint8_t cmd);

/* CC112X specific prototype function */
rfStatus_t trx16BitRegAccess(uint8_t accessType, uint8_t extAddr, uint8_t regAddr, uint8_t *pData, uint8_t len);

#ifdef  __cplusplus
}
#endif
/******************************************************************************
  Copyright 2010 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
*******************************************************************************/

#endif //HAL_SPI_RF_TRXEB_H
