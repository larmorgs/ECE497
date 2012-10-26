/******************************************************************************
    Filename: radio_config.h

    Description: Template for CC112x register export from SmartRF Studio

*******************************************************************************/
#ifndef RADIO_CONFIG_H
#define RADIO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
 * INCLUDES
 */
#include "hal_spi_rf_trxeb.h"
#include "cc112x_spi.h"
#include <stdint.h>

#define PKTLEN              1 // Packet length has to be within fifo limits ( 1 - 127 bytes)

#define FIFOLEN             0x40

#define RX_FIFO_ERROR       0x11
#define VCDAC_START_OFFSET 2
#define FS_VCO2_INDEX 0
#define FS_VCO4_INDEX 1
#define FS_CHP_INDEX 2

static const registerSetting_t preferredSettings[]=
{
  {CC112X_IOCFG3,            0xB0},
  {CC112X_IOCFG2,            0x06},
  {CC112X_IOCFG1,            0xB0},
  {CC112X_IOCFG0,            0x40},
  {CC112X_SYNC_CFG1,         0x07},
  {CC112X_DEVIATION_M,       0x53},
  {CC112X_MODCFG_DEV_E,      0x2F},
  {CC112X_DCFILT_CFG,        0x04},
  {CC112X_PREAMBLE_CFG1,     0x18},
  {CC112X_FREQ_IF_CFG,       0x00},
  {CC112X_IQIC,              0x00},
  {CC112X_CHAN_BW,           0x01},
  {CC112X_MDMCFG0,           0x05},
  {CC112X_DRATE2,            0xA9},
  {CC112X_DRATE1,            0x99},
  {CC112X_DRATE0,            0x99},
  {CC112X_AGC_REF,           0x3C},
  {CC112X_AGC_CS_THR,        0xEC},
  {CC112X_AGC_CFG3,          0x83},
  {CC112X_AGC_CFG2,          0x60},
  {CC112X_AGC_CFG1,          0xA9},
  {CC112X_AGC_CFG0,          0xC0},
  {CC112X_FIFO_CFG,          0x00},
  {CC112X_SETTLING_CFG,      0x03},
  {CC112X_FS_CFG,            0x12},
  {CC112X_PKT_CFG1,          0x04},
  {CC112X_PKT_CFG0,          0x00},
  {CC112X_RFEND_CFG1,        0x3F},
  {CC112X_RFEND_CFG0,        0x10},
  {CC112X_PA_CFG0,           0x01},
  {CC112X_PKT_LEN,           FIFOLEN},
  {CC112X_IF_MIX_CFG,        0x00},
  {CC112X_TOC_CFG,           0x0A},
  {CC112X_FREQ2,             0x72},
  {CC112X_FREQ1,             0x60},
  {CC112X_FS_DIG1,           0x00},
  {CC112X_FS_DIG0,           0x5F},
  {CC112X_FS_CAL1,           0x40},
  {CC112X_FS_CAL0,           0x0E},
  {CC112X_FS_DIVTWO,         0x03},
  {CC112X_FS_DSM0,           0x33},
  {CC112X_FS_DVC0,           0x17},
  {CC112X_FS_PFD,            0x50},
  {CC112X_FS_PRE,            0x6E},
  {CC112X_FS_REG_DIV_CML,    0x14},
  {CC112X_FS_SPARE,          0xAC},
  {CC112X_FS_VCO0,           0xB4},
  {CC112X_XOSC5,             0x0E},
  {CC112X_XOSC1,             0x03},
};

void registerConfig(void);
void createPacket(uint8_t txBuffer[]);
void manualCalibration(void);

#ifdef  __cplusplus
}
#endif
/******************************************************************************
  Copyright 2012 Texas Instruments Incorporated. All rights reserved.

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
#endif
