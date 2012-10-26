/******************************************************************************
    Filename: hal_spi_rf_trxeb.c

    Description: Implementation file for common spi access with the CCxxxx
                 tranceiver radios using trxeb. Supports CC1101/CC112X radios

*******************************************************************************/


/******************************************************************************
 * INCLUDES
 */
#include "hal_spi_rf_trxeb.h"
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>

static const char *device = "/dev/spidev2.0";
static int fd;

/******************************************************************************
 * LOCAL FUNCTIONS
 */
static void trxReadWriteBurstSingle(uint8_t addr,uint8_t *pData,uint16_t len) ;


/******************************************************************************
 * FUNCTIONS
 */

/******************************************************************************
 * @fn          trxRfSpiInterfaceInit
 *
 * @brief       Function to initialize TRX SPI. CC1101/CC112x is currently
 *              supported. The supported prescalerValue must be set so that
 *              SMCLK/prescalerValue does not violate radio SPI constraints.
 *
 * input parameters
 *
 * @param       prescalerValue - SMCLK/prescalerValue gives SCLK frequency
 *
 * output parameters
 *
 * @return      void
 */
void trxRfSpiInterfaceInit(void)
{
  fd = open(device, O_RDWR);
  /*if (fd < 0) {
  
  }*/
}


/*******************************************************************************
 * @fn          trx8BitRegAccess
 *
 * @brief       This function performs a read or write from/to a 8bit register
 *              address space. The function handles burst and single read/write
 *              as specfied in addrByte. Function assumes that chip is ready.
 *
 * input parameters
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       addrByte - address byte of register.
 * @param       pData    - data array
 * @param       len      - Length of array to be read(TX)/written(RX)
 *
 * output parameters
 *
 * @return      chip status
 */
rfStatus_t trx8BitRegAccess(uint8_t accessType, uint8_t addrByte, uint8_t *pData, uint16_t len)
{
  uint8_t temp = accessType|addrByte;

  uint8_t ret = 0;
  uint8_t rx = 0;
  
  uint8_t trash = 0;
  
  struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)&temp,
		.rx_buf = (unsigned long)&rx,
		.len = len,
		.delay_usecs = 0,
		.speed_hz = 1000000,
		.bits_per_word = 8,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  
	tr.tx_buf = (unsigned long)&addrByte;
  tr.rx_buf = (unsigned long)&trash;
	tr.len = len;

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);

	tr.tx_buf = (unsigned long)pData;
  tr.rx_buf = (unsigned long)&trash;
	tr.len = len;

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	
	/*if (ret < 1)
		pabort("can't send spi message");
	*/
	return rx;

  /*TRXEM_SPI_BEGIN();
  TRXEM_SPI_TX(accessType|addrByte);
  TRXEM_SPI_WAIT_DONE();
  readValue = TRXEM_SPI_RX();
  trxReadWriteBurstSingle(accessType|addrByte,pData,len);
  TRXEM_SPI_END();*/
}

/******************************************************************************
 * @fn          trx16BitRegAccess
 *
 * @brief       This function performs a read or write in the extended adress
 *              space of CC112X.
 *
 * input parameters
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       extAddr - Extended register space address = 0x2F.
 * @param       regAddr - Register address in the extended address space.
 * @param       *pData  - Pointer to data array for communication
 * @param       len     - Length of bytes to be read/written from/to radio
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t trx16BitRegAccess(uint8_t accessType, uint8_t extAddr, uint8_t regAddr, uint8_t *pData, uint8_t len)
{
  uint8_t temp = accessType|addrByte;

  uint8_t ret = 0;
  uint8_t rx = 0;
  
  uint8_t trash = 0;
  
  struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)&temp,
		.rx_buf = (unsigned long)&rx,
		.len = len,
		.delay_usecs = 0,
		.speed_hz = 1000000,
		.bits_per_word = 8,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  
	tr.tx_buf = (unsigned long)&regAddr;
  tr.rx_buf = (unsigned long)&trash;
	tr.len = len;

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);

	tr.tx_buf = (unsigned long)pData;
  tr.rx_buf = (unsigned long)&trash;
	tr.len = len;

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	
	/*if (ret < 1)
		pabort("can't send spi message");
	*/
	return rx;

  /*TRXEM_SPI_BEGIN();
  TRXEM_SPI_TX(accessType|extAddr);
  TRXEM_SPI_WAIT_DONE();
  readValue = TRXEM_SPI_RX();
  TRXEM_SPI_TX(regAddr);
  TRXEM_SPI_WAIT_DONE();
  trxReadWriteBurstSingle(accessType|extAddr,pData,len);
  TRXEM_SPI_END();*/
}

/*******************************************************************************
 * @fn          trxSpiCmdStrobe
 *
 * @brief       Send command strobe to the radio. Returns status byte read
 *              during transfer of command strobe. Validation of provided
 *              is not done. Function assumes chip is ready.
 *
 * input parameters
 *
 * @param       cmd - command strobe
 *
 * output parameters
 *
 * @return      status byte
 */
rfStatus_t trxSpiCmdStrobe(uint8_t cmd)
{
    uint8_t rc;
    TRXEM_SPI_BEGIN();
    //while(P1IN & BIT1);
    TRXEM_SPI_TX(cmd);
    TRXEM_SPI_WAIT_DONE();
    rc = TRXEM_SPI_RX();
    TRXEM_SPI_END();
    return(rc);
}

/*******************************************************************************
 * @fn          trxReadWriteBurstSingle
 *
 * @brief       When the address byte is sent to the SPI slave, the next byte
 *              communicated is the data to be written or read. The address
 *              byte that holds information about read/write -and single/
 *              burst-access is provided to this function.
 *
 *              Depending on these two bits this function will write len bytes to
 *              the radio in burst mode or read len bytes from the radio in burst
 *              mode if the burst bit is set. If the burst bit is not set, only
 *              one data byte is communicated.
 *
 *              NOTE: This function is used in the following way:
 *
 *              TRXEM_SPI_BEGIN();
 *              while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);
 *              ...[Depending on type of register access]
 *              trxReadWriteBurstSingle(uint8_t addr,uint8_t *pData,uint16_t len);
 *              TRXEM_SPI_END();
 *
 * input parameters
 *
 * @param       none
 *
 * output parameters
 *
 * @return      void
 */
static void trxReadWriteBurstSingle(uint8_t addr,uint8_t *pData,uint16_t len)
{
	uint16_t i;
	/* Communicate len number of bytes: if RX - the procedure sends 0x00 to push bytes from slave*/
  if(addr&RADIO_READ_ACCESS)
  {
    if(addr&RADIO_BURST_ACCESS)
    {
      for (i = 0; i < len; i++)
      {
          TRXEM_SPI_TX(0);            /* Possible to combining read and write as one access type */
          TRXEM_SPI_WAIT_DONE();
          *pData = TRXEM_SPI_RX();     /* Store pData from last pData RX */
          pData++;
      }
    }
    else
    {
      TRXEM_SPI_TX(0);
      TRXEM_SPI_WAIT_DONE();
      *pData = TRXEM_SPI_RX();
    }
  }
  else
  {
    if(addr&RADIO_BURST_ACCESS)
    {
      /* Communicate len number of bytes: if TX - the procedure doesn't overwrite pData */
      for (i = 0; i < len; i++)
      {
        TRXEM_SPI_TX(*pData);
        TRXEM_SPI_WAIT_DONE();
        pData++;
      }
    }
    else
    {
      TRXEM_SPI_TX(*pData);
      TRXEM_SPI_WAIT_DONE();
    }
  }
  return;
}

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
  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
