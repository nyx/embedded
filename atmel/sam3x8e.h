/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following condition is met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef _SAM3X8E_
#define _SAM3X8E_

/** \addtogroup SAM3X8E_definitions SAM3X8E definitions
  This file defines all structures and symbols for SAM3X8E:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>
#ifndef __cplusplus
typedef volatile const uint32_t RoReg; /**< Read only 32-bit register (volatile const unsigned int) */
#else
typedef volatile       uint32_t RoReg; /**< Read only 32-bit register (volatile const unsigned int) */
#endif
typedef volatile       uint32_t WoReg; /**< Write only 32-bit register (volatile unsigned int) */
typedef volatile       uint32_t RwReg; /**< Read-Write 32-bit register (volatile unsigned int) */
#endif

/* ************************************************************************** */
/*   CMSIS DEFINITIONS FOR SAM3X8E */
/* ************************************************************************** */
/** \addtogroup SAM3X8E_cmsis CMSIS Definitions */
/*@{*/

/**< Interrupt Number Definition */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ******************************/
  NonMaskableInt_IRQn   = -14, /**<  2 Non Maskable Interrupt                */
  MemoryManagement_IRQn = -12, /**<  4 Cortex-M3 Memory Management Interrupt */
  BusFault_IRQn         = -11, /**<  5 Cortex-M3 Bus Fault Interrupt         */
  UsageFault_IRQn       = -10, /**<  6 Cortex-M3 Usage Fault Interrupt       */
  SVCall_IRQn           = -5,  /**< 11 Cortex-M3 SV Call Interrupt           */
  DebugMonitor_IRQn     = -4,  /**< 12 Cortex-M3 Debug Monitor Interrupt     */
  PendSV_IRQn           = -2,  /**< 14 Cortex-M3 Pend SV Interrupt           */
  SysTick_IRQn          = -1,  /**< 15 Cortex-M3 System Tick Interrupt       */
/******  SAM3X8E specific Interrupt Numbers *********************************/

  SUPC_IRQn            =  0, /**<  0 SAM3X8E Supply Controller (SUPC) */
  RSTC_IRQn            =  1, /**<  1 SAM3X8E Reset Controller (RSTC) */
  RTC_IRQn             =  2, /**<  2 SAM3X8E Real Time Clock (RTC) */
  RTT_IRQn             =  3, /**<  3 SAM3X8E Real Time Timer (RTT) */
  WDT_IRQn             =  4, /**<  4 SAM3X8E Watchdog Timer (WDT) */
  PMC_IRQn             =  5, /**<  5 SAM3X8E Power Management Controller (PMC) */
  EFC0_IRQn            =  6, /**<  6 SAM3X8E Enhanced Flash Controller 0 (EFC0) */
  EFC1_IRQn            =  7, /**<  7 SAM3X8E Enhanced Flash Controller 1 (EFC1) */
  UART_IRQn            =  8, /**<  8 SAM3X8E Universal Asynchronous Receiver Transceiver (UART) */
  SMC_IRQn             =  9, /**<  9 SAM3X8E Static Memory Controller (SMC) */
  PIOA_IRQn            = 11, /**< 11 SAM3X8E Parallel I/O Controller A, (PIOA) */
  PIOB_IRQn            = 12, /**< 12 SAM3X8E Parallel I/O Controller B (PIOB) */
  PIOC_IRQn            = 13, /**< 13 SAM3X8E Parallel I/O Controller C (PIOC) */
  PIOD_IRQn            = 14, /**< 14 SAM3X8E Parallel I/O Controller D (PIOD) */
  USART0_IRQn          = 17, /**< 17 SAM3X8E USART 0 (USART0) */
  USART1_IRQn          = 18, /**< 18 SAM3X8E USART 1 (USART1) */
  USART2_IRQn          = 19, /**< 19 SAM3X8E USART 2 (USART2) */
  USART3_IRQn          = 20, /**< 20 SAM3X8E USART 3 (USART3) */
  HSMCI_IRQn           = 21, /**< 21 SAM3X8E Multimedia Card Interface (HSMCI) */
  TWI0_IRQn            = 22, /**< 22 SAM3X8E Two-Wire Interface 0 (TWI0) */
  TWI1_IRQn            = 23, /**< 23 SAM3X8E Two-Wire Interface 1 (TWI1) */
  SPI0_IRQn            = 24, /**< 24 SAM3X8E Serial Peripheral Interface (SPI0) */
  SSC_IRQn             = 26, /**< 26 SAM3X8E Synchronous Serial Controller (SSC) */
  TC0_IRQn             = 27, /**< 27 SAM3X8E Timer Counter 0 (TC0) */
  TC1_IRQn             = 28, /**< 28 SAM3X8E Timer Counter 1 (TC1) */
  TC2_IRQn             = 29, /**< 29 SAM3X8E Timer Counter 2 (TC2) */
  TC3_IRQn             = 30, /**< 30 SAM3X8E Timer Counter 3 (TC3) */
  TC4_IRQn             = 31, /**< 31 SAM3X8E Timer Counter 4 (TC4) */
  TC5_IRQn             = 32, /**< 32 SAM3X8E Timer Counter 5 (TC5) */
  TC6_IRQn             = 33, /**< 33 SAM3X8E Timer Counter 6 (TC6) */
  TC7_IRQn             = 34, /**< 34 SAM3X8E Timer Counter 7 (TC7) */
  TC8_IRQn             = 35, /**< 35 SAM3X8E Timer Counter 8 (TC8) */
  PWM_IRQn             = 36, /**< 36 SAM3X8E Pulse Width Modulation Controller (PWM) */
  ADC_IRQn             = 37, /**< 37 SAM3X8E ADC Controller (ADC) */
  DACC_IRQn            = 38, /**< 38 SAM3X8E DAC Controller (DACC) */
  DMAC_IRQn            = 39, /**< 39 SAM3X8E DMA Controller (DMAC) */
  UOTGHS_IRQn          = 40, /**< 40 SAM3X8E USB OTG High Speed (UOTGHS) */
  TRNG_IRQn            = 41, /**< 41 SAM3X8E True Random Number Generator (TRNG) */
  EMAC_IRQn            = 42, /**< 42 SAM3X8E Ethernet MAC (EMAC) */
  CAN0_IRQn            = 43, /**< 43 SAM3X8E CAN Controller 0 (CAN0) */
  CAN1_IRQn            = 44, /**< 44 SAM3X8E CAN Controller 1 (CAN1) */

  PERIPH_COUNT_IRQn    = 45  /**< Number of peripheral IDs */
} IRQn_Type;

typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;

  /* Cortex-M handlers */
  void* pfnReset_Handler;
  void* pfnNMI_Handler;
  void* pfnHardFault_Handler;
  void* pfnMemManage_Handler;
  void* pfnBusFault_Handler;
  void* pfnUsageFault_Handler;
  void* pfnReserved1_Handler;
  void* pfnReserved2_Handler;
  void* pfnReserved3_Handler;
  void* pfnReserved4_Handler;
  void* pfnSVC_Handler;
  void* pfnDebugMon_Handler;
  void* pfnReserved5_Handler;
  void* pfnPendSV_Handler;
  void* pfnSysTick_Handler;

  /* Peripheral handlers */
  void* pfnSUPC_Handler;   /*  0 Supply Controller */
  void* pfnRSTC_Handler;   /*  1 Reset Controller */
  void* pfnRTC_Handler;    /*  2 Real Time Clock */
  void* pfnRTT_Handler;    /*  3 Real Time Timer */
  void* pfnWDT_Handler;    /*  4 Watchdog Timer */
  void* pfnPMC_Handler;    /*  5 Power Management Controller */
  void* pfnEFC0_Handler;   /*  6 Enhanced Flash Controller 0 */
  void* pfnEFC1_Handler;   /*  7 Enhanced Flash Controller 1 */
  void* pfnUART_Handler;   /*  8 Universal Asynchronous Receiver Transceiver */
  void* pfnSMC_Handler;    /*  9 Static Memory Controller */
  void* pvReserved10;
  void* pfnPIOA_Handler;   /* 11 Parallel I/O Controller A, */
  void* pfnPIOB_Handler;   /* 12 Parallel I/O Controller B */
  void* pfnPIOC_Handler;   /* 13 Parallel I/O Controller C */
  void* pfnPIOD_Handler;   /* 14 Parallel I/O Controller D */
  void* pvReserved15;
  void* pvReserved16;
  void* pfnUSART0_Handler; /* 17 USART 0 */
  void* pfnUSART1_Handler; /* 18 USART 1 */
  void* pfnUSART2_Handler; /* 19 USART 2 */
  void* pfnUSART3_Handler; /* 20 USART 3 */
  void* pfnHSMCI_Handler;  /* 21 Multimedia Card Interface */
  void* pfnTWI0_Handler;   /* 22 Two-Wire Interface 0 */
  void* pfnTWI1_Handler;   /* 23 Two-Wire Interface 1 */
  void* pfnSPI0_Handler;   /* 24 Serial Peripheral Interface */
  void* pvReserved25;
  void* pfnSSC_Handler;    /* 26 Synchronous Serial Controller */
  void* pfnTC0_Handler;    /* 27 Timer Counter 0 */
  void* pfnTC1_Handler;    /* 28 Timer Counter 1 */
  void* pfnTC2_Handler;    /* 29 Timer Counter 2 */
  void* pfnTC3_Handler;    /* 30 Timer Counter 3 */
  void* pfnTC4_Handler;    /* 31 Timer Counter 4 */
  void* pfnTC5_Handler;    /* 32 Timer Counter 5 */
  void* pfnTC6_Handler;    /* 33 Timer Counter 6 */
  void* pfnTC7_Handler;    /* 34 Timer Counter 7 */
  void* pfnTC8_Handler;    /* 35 Timer Counter 8 */
  void* pfnPWM_Handler;    /* 36 Pulse Width Modulation Controller */
  void* pfnADC_Handler;    /* 37 ADC Controller */
  void* pfnDACC_Handler;   /* 38 DAC Controller */
  void* pfnDMAC_Handler;   /* 39 DMA Controller */
  void* pfnUOTGHS_Handler; /* 40 USB OTG High Speed */
  void* pfnTRNG_Handler;   /* 41 True Random Number Generator */
  void* pfnEMAC_Handler;   /* 42 Ethernet MAC */
  void* pfnCAN0_Handler;   /* 43 CAN Controller 0 */
  void* pfnCAN1_Handler;   /* 44 CAN Controller 1 */
} DeviceVectors;

/* Cortex-M3 core handlers */
void Reset_Handler      ( void );
void NMI_Handler        ( void );
void HardFault_Handler  ( void );
void MemManage_Handler  ( void );
void BusFault_Handler   ( void );
void UsageFault_Handler ( void );
void SVC_Handler        ( void );
void DebugMon_Handler   ( void );
void PendSV_Handler     ( void );
void SysTick_Handler    ( void );

/* Peripherals handlers */
void ADC_Handler        ( void );
void CAN0_Handler       ( void );
void CAN1_Handler       ( void );
void DACC_Handler       ( void );
void DMAC_Handler       ( void );
void EFC0_Handler       ( void );
void EFC1_Handler       ( void );
void EMAC_Handler       ( void );
void HSMCI_Handler      ( void );
void PIOA_Handler       ( void );
void PIOB_Handler       ( void );
void PIOC_Handler       ( void );
void PIOD_Handler       ( void );
void PMC_Handler        ( void );
void PWM_Handler        ( void );
void RSTC_Handler       ( void );
void RTC_Handler        ( void );
void RTT_Handler        ( void );
void SMC_Handler        ( void );
void SPI0_Handler       ( void );
void SSC_Handler        ( void );
void SUPC_Handler       ( void );
void TC0_Handler        ( void );
void TC1_Handler        ( void );
void TC2_Handler        ( void );
void TC3_Handler        ( void );
void TC4_Handler        ( void );
void TC5_Handler        ( void );
void TC6_Handler        ( void );
void TC7_Handler        ( void );
void TC8_Handler        ( void );
void TRNG_Handler       ( void );
void TWI0_Handler       ( void );
void TWI1_Handler       ( void );
void UART_Handler       ( void );
void UOTGHS_Handler     ( void );
void USART0_Handler     ( void );
void USART1_Handler     ( void );
void USART2_Handler     ( void );
void USART3_Handler     ( void );
void WDT_Handler        ( void );

/*@}*/

#endif /* _SAM3X8E_ */
