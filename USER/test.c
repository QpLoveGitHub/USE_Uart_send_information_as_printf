//*****************************************************************************
// file		: test.c
// test module
// Copyright (c) 2011-2014 HSAE co. Ltd. All rights reserved
// 
// Change Logs:
// Date				Author		Note	
// 2014/01/21    	chc			
// 
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup 
//! @{
//
//*****************************************************************************
#include "test.h"
#include "test_uart.h"
//#include "test_msgproc.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
//#include "UnitCheck\BattCheck.h"
//#include "SystemManage\SystemStateManage\SystemStateManage.h"
//#include "SoftTimer\Manage_SoftTimer.h"
//#include "CarSignalManage\CarSignalManage.h"
//#include "Debug_Uart.h"
//#include "MX51\MX51MsgProcess.h"


//#define cmdMAX_INPUT_SIZE		128
//
//unsigned char cInputIndex = 0;
//static char cInputString[ cmdMAX_INPUT_SIZE ], cLastInputString[ cmdMAX_INPUT_SIZE ];
//
//
//unsigned char DEBUG_CanInfo = 0;		//CAN print
//unsigned char DEBUG_UartRec = 0;		//uart print
//unsigned char DEBUG_UartSend = 0;
//unsigned char DEBUG_ResendInfo = 0; 	//Resend Print
//unsigned char DEBUG_KeyInfo = 0;
//
//unsigned char DEBUG_KernelInfo = 0;
//
//
//extern unsigned char gHeartEnableFlag;
//extern unsigned char Mx51_CurrentState;
//extern Type_SystemState G_SystemState;
//extern unsigned char AMP_MuteState;
//extern unsigned char AutoTestRecved;
//
//tPrintLevel s_printlevel;
static unsigned char AutoTestRecved = 0;

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
void test_init(void)
{
	test_uart_init();
//	test_set_printlevel(TEST_PRINT_LEVEL_DEFAULT);
//	Debug_uart_init();
}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
//void test_set_printlevel(tPrintLevel level)
//{
//	s_printlevel = level;
//}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
//void test_process_per10ms(void)
//{
//	test_msgproc_rcvmsg();
//	test_rcv_timeout_process();
//}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
//void test_print_array(unsigned char *pByte, unsigned char len, tPrintLevel level)
//{
//	if (level >= s_printlevel)
//	{
//		test_uart_send(pByte, len);
//	}
//}

/**
  * \brief 
  *
  * \param None
  *   
  * \return None
  */
void test_printf(unsigned char printFlags, const char *fmt, ...)
{
		if((printFlags == 1) && (AutoTestRecved == 0)) /*添加自动测试检验*/
    {
		va_list args;
		unsigned char length;
		char buf[100];
		
		va_start(args, fmt);
		length = vsprintf(buf, fmt, args);

	    // auto test已经用了串口，故之前打印屏蔽 modify by kuan 2017年11月20日15:54:04
		test_uart_send((unsigned char *)buf, strlen(buf));
		
		va_end(args);
	}
}

/******************************************************************************
** Function    : getConsoleData
** Description : debug uart
** Input       : None
** Output      : None
** Author      : xuany
** Date        : 20180202
*******************************************************************************/
//unsigned char getConsoleData(char* pBuf, char* returnbuf,unsigned char bufSize)
//{
//    unsigned char i = 0;
//    unsigned char iPos = 0;
//
//    for ( ; i < bufSize; i++)
//    {
//        if((*(pBuf + i) == ' ')||(*(pBuf + i) == '-')||(*(pBuf + i) == ':'))
//        {
//            break;
//        }
//        else
//        {
//            returnbuf[iPos ++] = *(pBuf + i);
//        }
//    }
//    returnbuf[iPos ++] = '\0'; /*end*/
//    return iPos;
//}

//void  ConsoleDataInfo(char* pSourceBuf, char* pDestBuf)
//{	
//	unsigned char  index =0,iPos = 0;
//	unsigned char  ConsoleStatus = 0;  /*open : 1   close : 0*/
//	unsigned char  ConfigVehicleBuf[5]= {0x00};
//	unsigned long  EEpromAddr = 0;
//	unsigned char  ReadEEpromBuf[9]= {0x00};
//	unsigned char  i = 0;
//	
//	iPos = getConsoleData((char *)(pSourceBuf+index), (char *)pDestBuf, strlen(pSourceBuf)-index);/*open or close*/	
//
//	if(strcmp(pDestBuf,"init") == 0)
//	{
//		test_printf(0,"error\r\n");
//	}
//	
//	else if(strcmp(pDestBuf,"Open")==0)
//	{
//		ConsoleStatus = 1;
//	}
//	else if(strcmp(pDestBuf,"Close")==0)
//	{
//		ConsoleStatus = 0;
//	}
//	else if (strcmp(pDestBuf, "Reset") == 0)
//	{
//		SystemGotoRestart(5);
//	}
//
//	index += iPos;
//	iPos = getConsoleData((char *)(pSourceBuf+index), (char *)pDestBuf, strlen(pSourceBuf)-index);
//
//	if(strcmp(pDestBuf,"Can")==0)
//	{
//			if(ConsoleStatus)  DEBUG_CanInfo=1;
//			else               DEBUG_CanInfo=0;	
//	}
//	else if(strcmp(pDestBuf,"UartRec")==0)
//	{
//		if(ConsoleStatus)  DEBUG_UartRec=1;
//		else               DEBUG_UartRec=0;
//	}
//	else if(strcmp(pDestBuf,"UartSend")==0)
//	{
//		if(ConsoleStatus)  DEBUG_UartSend=1;
//		else               DEBUG_UartSend=0;
//	}
//	else if(strcmp(pDestBuf,"Resend")==0)
//	{
//			if(ConsoleStatus)  DEBUG_ResendInfo=1;
//			else               DEBUG_ResendInfo=0;	
//	}
//	else if(strcmp(pDestBuf,"Key")==0)
//	{
//			if(ConsoleStatus)  DEBUG_KeyInfo=1;
//			else               DEBUG_KeyInfo=0;	
//	}
//	else if(strcmp(pDestBuf,"Heart")==0)/*Heart*/
//	{
//		if(ConsoleStatus)  gHeartEnableFlag = 1;
//		else               gHeartEnableFlag = 0;
//	}
//	else if(strcmp(pDestBuf,"Vat")==0)/*Battery*/
//	{
//		test_printf(1,"Vat:%d\r\n",sBattManage.ad_val);
//	}
//	else if(strcmp(pDestBuf,"ShakeHand")==0)/*ShakeHand*/
//	{
//		test_printf(1,"ShakeHand:%x,%x,%x,%x\r\n",Mx51_CurrentState,G_SystemState.CurrentState,AMP_MuteState,CarSignal_ACCState_Inquire());
//	}
//	else if(strcmp(pDestBuf,"Bsp")==0)
//	{
//		test_printf(1,"BspHeartCount:%d\r\n",ReceiveBspCount);
//	}
//	else if(strcmp(pDestBuf,"Kernel")==0)
//	{
//		DEBUG_KernelInfo = 1;
//	}
//}


//void GetShellDada(unsigned char RcvedChar)
//{
//
///* Was it the end of the line? */
//	if( RcvedChar == '\n' || RcvedChar == '\r' )
//	{
//		/* Just to space the output from the input. */
//		test_printf(1,"\r\n");
//		test_printf(1,">");
//
//		/*analyze uart data*/		
//		ConsoleDataInfo( ( char * ) cInputString, ( char * ) cLastInputString );
//
//		/* All the strings generated by the input command have been sent.
//		Clear the input string ready to receive the next command.  Remember
//		the command that was just processed first in case it is to be
//		processed again. */
//		cInputIndex = 0;
//		memset( cInputString, 0x00, cmdMAX_INPUT_SIZE );
//		memset( cLastInputString, 0x00, cmdMAX_INPUT_SIZE );
////		DebugUart_PutString(">");
//		/* xPrintf( pcEndOfOutputMessage ); */
//	}
//	else
//	{
//		if( RcvedChar == '\r' )
//		{
//			/* Ignore the character. */
//		}
//		else if( (RcvedChar == '\b') || ((RcvedChar == (char)127)) )
//		{	/* Key BackSpace Value is 127 from minicom */
//			/* Backspace was pressed.  Erase the last character in the
//			string - if any. */
//			if( cInputIndex > 0 )
//			{
//				cInputIndex--;
//				cInputString[ cInputIndex ] = '\0';
//				/* ease one char on the uart console */
//				
//				test_printf(1,"\b");
//				test_printf(1," ");
//				test_printf(1,"\b");
//			}
//		}
//		else
//		{
//			/* A character was entered.  Add it to the string
//			entered so far.  When a \n is entered the complete
//			string will be passed to the command interpreter. */
//			if( ( RcvedChar >= ' ' ) && ( RcvedChar <= '~' ) )
//			{
//				/* Echo the character back. */
//				test_printf(1,"%c",RcvedChar);
//
//				if( cInputIndex < cmdMAX_INPUT_SIZE )
//				{
//					cInputString[ cInputIndex ] = RcvedChar;
//					cInputIndex++;
//				}
//			}
//		}
//	}
//}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

