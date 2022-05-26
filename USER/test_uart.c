//*****************************************************************************
// file		: test_uart.c
// process data communication with test
// Copyright (c) 2006-2012 HSAE co. Ltd. All rights reserved
//
// Change Logs:
// Date				Author		Note
// 2013/08/27    	chc
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup test
//! @{
//
//*****************************************************************************
#include "test_uart.h"
//#include "MX51\MX51Uart.h"
//#include "McuConfig_PinAssign.h"
//#include "driverlib\clock.h"
//#include "driverlib\uart.h"
//#include "platform\vectors.h"
#include "ringbuf.h"
#include "stm32f10x_usart.h"
#include "stm32f10x.h"


#define TEST_TXD_BUF_LEN					100



//
//! receive buffer struct
//
typedef struct
{
    unsigned char buf[TEST_RCV_BUF_LEN];	/**< store the received data */
    unsigned char cnt;						/**< receive data count */
    unsigned char len;						/**< packet length */
    unsigned char state;					/**< receive state */
    unsigned char timeout;					/**< check if has timeout */
}
tTestRxBuf;

//
//! send buffer struct
//
typedef struct
{
    unsigned char buf[TEST_TXD_BUF_LEN];	/**< store the transmitted data */
    unsigned char num;						/**< number of byte to send */
    unsigned char cnt;						/**< number of byte has sent */
}
tTestTxBuf;

//
//! define receive buffer
//
static tTestRxBuf sTestRcvBuf;

//
//! define tx buffer
//
static tTestTxBuf sTestTxdBuf;

//
//! store the data to upper layer
//
tTestComBuf TestRcvBuf[TEST_RCV_NUM];

//
//! tx ringbuf
//
tRingBuf s_tx_ringbuf;

unsigned char AutoTestFlag = 0;


//
//! tx buffer space
//
unsigned char tx_buf[TX_RINGBUF_SIZE];

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
void test_uart_init(void)
{
//    vector_SetIrq(ICR_LINT1, ILM_Level_5);
//    vector_SetIrq(ICR_LINR1, ILM_Level_5);
	  bsp_init(115200);


//    UART_Open(1,
//              BR_115200,
//              DATA_LEN_8BIT,
//              STOP_BIT_1,
//              PARITY_NONE);
//
//    UART_SetRxInterrupt(1, 1);
    ringbuf_init(&s_tx_ringbuf, tx_buf, TX_RINGBUF_SIZE);
}

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
unsigned char test_uart_send(unsigned char *pData, unsigned char len)
{
    if (ringbuf_free(&s_tx_ringbuf) < len)
    {
        return 0;
    }

    //UART_SetTxInterrupt(1, 0);
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    ringbuf_write(&s_tx_ringbuf, pData, len);
	//UART_SetTxInterrupt(1, 1);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
int test_uart_checkbuf(unsigned char state)
{
    int i;

    for (i = 0; i < TEST_RCV_NUM; i++)
    {
        if (TestRcvBuf[i].newflag == state)
        {
            return i;
        }
    }

    return -1;
}

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
void test_uart_bufset(unsigned char idx, unsigned char state)
{
    TestRcvBuf[idx].newflag = state;
}

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
void test_uart_fillbuf(unsigned char *pSrc, unsigned char len, unsigned char idx)
{
    unsigned char i;

    for (i = 0; i < len; i++)
    {
        TestRcvBuf[idx].buf[i] = pSrc[i];
    }

    TestRcvBuf[idx].newflag = 1;
}

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
unsigned char * test_uart_getbuf(unsigned char idx)
{
    unsigned char *pBuf;

    pBuf = TestRcvBuf[idx].buf;
    return pBuf;
}

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
//__interrupt void test_rcv_isr(void)
//{
//    unsigned char rb;
//
//    sTestRcvBuf.timeout	= 5;
//
//    if(UART1_SSR1_ORE == 1 || UART1_SSR1_FRE == 1 || UART1_SSR1_PE == 1)
//    {
//        UART1_SCR1_CRE = 1;
//    }
//    else
//    {
//        rb = UART1_RDR1;
//		
//        switch(sTestRcvBuf.state)
//        {
//        case 0: // head flag check
//            if(rb == 0xAA)
//            {
//                AutoTestFlag = 1; // auto test command
//                sTestRcvBuf.state = 1;
//                sTestRcvBuf.cnt = 0;
//                sTestRcvBuf.buf[sTestRcvBuf.cnt++] = rb;
//            }
//	     else
//     	     {
//     	         AutoTestFlag = 0;
//     	     }
//            break;
//
//        case 1: 		// Frame Counter
//            //airRcvPnt		=	0;
//            sTestRcvBuf.buf[sTestRcvBuf.cnt++] = rb;
//            sTestRcvBuf.state = 2;
//            break;
//
//        case 2: 		//package length
//            if(sTestRcvBuf.cnt < TEST_RCV_BUF_LEN)
//            {
//                sTestRcvBuf.buf[sTestRcvBuf.cnt++] = rb;
//            }
//            else		// package's length is too long
//            {
//                sTestRcvBuf.state = 0;
//            }
//
//            if(rb <= (TEST_RCV_BUF_LEN - 3))
//            {
//                sTestRcvBuf.state = 3;
//            }
//            else
//            {
//                sTestRcvBuf.state = 0;
//            }
//            break;
//
//        case 3: 		// data field
//        
//            sTestRcvBuf.buf[sTestRcvBuf.cnt++] = rb;
//            if(sTestRcvBuf.cnt >= (sTestRcvBuf.buf[2] + 3)) 	//check sum
//            {
//                int bufIdx =test_uart_checkbuf(0);
//
//                if(bufIdx >= 0)
//                {
//                    test_uart_fillbuf(sTestRcvBuf.buf, sTestRcvBuf.buf[2]+3, bufIdx);
//                }
//                sTestRcvBuf.timeout =	0;//正常接收正确
//                sTestRcvBuf.state	=	0;
//                sTestRcvBuf.cnt 	=	0;
//            }
//            break;
//
//        default:
//            sTestRcvBuf.state = 0;
//            break;
//        }
//	if(AutoTestFlag != 1) // filter 0x0A and 0x0D
//	{
//		GetShellDada(rb);
//	}
//    }
//}

/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
//__interrupt void test_snd_isr(void)
//{
//    if (ringbuf_empty(&s_tx_ringbuf))
//    {
//        UART_SetTxInterrupt(1, 0);
//    }
//    else
//    {
//        UART1_TDR1 = ringbuf_read_one(&s_tx_ringbuf);
//    }
//}

void USART1_IRQHandler(void)
{
	if (ringbuf_empty(&s_tx_ringbuf))
    {
        //UART_SetTxInterrupt(1, 0);
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    }
    else
    {
        //UART1_TDR1 = ringbuf_read_one(&s_tx_ringbuf);
        if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
        {
			USART_SendData(USART1, ringbuf_read_one(&s_tx_ringbuf));
		}
    }
}


/**
  * \brief
  *
  * \param None
  *
  * \return None
  */
void test_rcv_timeout_process(void)
{
    if(sTestRcvBuf.timeout > 0)
    {
        sTestRcvBuf.timeout--;

        if(sTestRcvBuf.timeout == 1)
        {
            sTestRcvBuf.state = 0;
            sTestRcvBuf.cnt = 0;
            sTestRcvBuf.timeout	=	0;
        }
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
