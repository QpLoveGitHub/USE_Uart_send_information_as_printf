//*****************************************************************************
// file		: test_uart.h
// communication with test
// Copyright (c) 2006-2012 HSAE co. Ltd. All rights reserved
// 
// Change Logs:
// Date				Author        Note	
// 2013/08/27		chc	      
// 
//*****************************************************************************
#ifndef __TEST_UART_H__
#define __TEST_UART_H__

//*****************************************************************************
//
//! \addtogroup test
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#define	SYNC_CODE					(0xA5)		/* frame data sync code */
#define	TRANS_ACK_TYPE				(0x3C)		/* transfer data type: ack */
#define	TRANS_DATA_TYPE				(0xC3)		/* transfer data type: data */

#define TEST_RCV_NUM				20

#define TEST_RCV_BUF_LEN					70
//
//! buf struct
//
typedef struct
{
    unsigned char buf[TEST_RCV_BUF_LEN];
    unsigned char newflag;
}
tTestComBuf;
//
//! tx ring buf size
//
#define TX_RINGBUF_SIZE     /*250*/TEST_RCV_BUF_LEN
extern tTestComBuf TestRcvBuf[TEST_RCV_NUM];

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void test_uart_init(void);
unsigned char test_uart_send(unsigned char *pData, unsigned char len);
int test_uart_checkbuf(unsigned char state);
void test_uart_bufset(unsigned char idx, unsigned char state);
unsigned char * test_uart_getbuf(unsigned char idx);
void test_rcv_timeout_process(void);
void GetShellDada(unsigned char RcvedChar);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif //  __TEST_UART_H__

